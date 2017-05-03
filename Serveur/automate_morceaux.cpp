#include "automate_morceaux.h"

Automate_morceaux::Automate_morceaux(QObject *parent) : QObject(parent)
{
  // Une machine
  machine =new QStateMachine(this);

  // Un état initial "begin"
  begin = new QState(machine);

  // Un état "go"
  go = new QState(machine);
  HS_index = 0; HS_length = 0;

  /*
   * POURQUOI ÇA
   *
   * // On ajoute la pause
   * fonction->addTransition(this, SIGNAL(signalPause()), pause);
   * pause->addTransition(this, SIGNAL(signalPause()), fonctionHistory);
   *
   * ÇA MARCHE ET POURQUOI ÇA
   *
   * begin->addTransition(this, SIGNAL(signalGo()), go);
   * go->addTransition(this, SIGNAL(signalFinal()), end);
   * ÇA NE MARCHE PAS !!!!
   *
   */

  // Un état final
  end = new QFinalState(machine);

  QObject::connect(end, &QState::entered, [this](){
      qDebug()<<"Arrêt de mpv";
      emit signalMachine(kSignalPhase, false, KPhaseEndCycle);
    });

  // J'enverrai des messages à l'UI
  setupMessages();
  initDebug();
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
      qDebug()<<"go entered";
    });
  QObject::connect(go, &QState::exited, [this](){
      qDebug()<<"go exited";
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
