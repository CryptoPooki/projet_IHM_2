#include "automate_morceaux.h"

Automate_morceaux::Automate_morceaux(QObject *parent) : QObject(parent)
{


  // Une machine
  machine =new QStateMachine(this);

  // Un état initial "begin"
  begin = new QState(machine);
  // Un état "go"
  go = new QState(machine);
  begin->addTransition(this, SIGNAL(signalGo()), go);
    connect(this, SIGNAL(signalGo()),SLOT(debugg()));
  HS_index = 0; pseudo_max = 0;

  // Un état final
  end = new QFinalState(machine);
  go->addTransition(this, SIGNAL(signalFinal()), end);

  QObject::connect(end, &QState::entered, [this](){
      qDebug()<<"Arrêt de mpv";
      emit signalMachine(kSignalPhase, false, KPhaseEndCycle);
    });
/*
  int i;
  for(i=0; i<1000;i++)
      HistoryStack[i] = NULL;
*/
  // J'enverrai des messages à l'UI
  setupMessages();
  initDebug();
}

void Automate_morceaux::debugg()
{
    qDebug() << "ppppppppppppppp";
}

/*
 * Messages pour l'UI
 */
void Automate_morceaux::setupMessages()
{
  QObject::connect(go, &QState::entered, [this](){
      emit signalMachine(kSignalPhase, true, kPhase);
    });
  QObject::connect(go, &QState::exited, [this](){
      emit signalMachine(kSignalPhase, false, kPhase);
    });
}

void Automate_morceaux::initDebug()
{
  machine->setObjectName("machine") ;
  go->setObjectName("go");

  QObject::connect(machine, &QStateMachine::started, [this](){
      qDebug()<<"Machine morceaux started";
    });
  QObject::connect(machine, &QStateMachine::stopped, [this](){
      qDebug()<<"Machine morceaux stopped";
    });
  QObject::connect(go, &QState::entered, [this](){
      qDebug()<<"go morceaux entered";
    });
  QObject::connect(go, &QState::exited, [this](){
      qDebug()<<"go morceaux exited";
    });
}

void Automate_morceaux::setBegin(bool b)
{
  if (!b)
  {
      // On arrête la machine
      machine->stop();
      return;
  }

  // On va commencer par l'état initial
  machine->setInitialState(begin);
  machine->start();
}

void Automate_morceaux::setGo()
{
    emit signalGo();
    qDebug() << "igigidflmjg";
}

void Automate_morceaux::setFinal()
{
    emit signalFinal();
}

void Automate_morceaux::changeMode(bool r)
{
    if(r)
    {
        emit signalModeRadio();
    }
}
