#include "automate_morceaux.h"

Automate_morceaux::Automate_morceaux(QObject *parent) : QObject(parent)
{
  // Une machine
  machine =new QStateMachine(this);

  // Un état initial "begin"
  begin = new QState(machine);

  // Un état "play"
  play = new QState(machine);
  playHistory = new QHistoryState(play);

  // Un état "pause"
  pause = new QState(machine);
  pauseHistory = new QHistoryState(pause);

  // Un état final
  end = new QFinalState(machine);

  // Nos transitions
  Begin_to_Play = (QSignalTransition*) begin->addTransition(play);
  Play_to_Pause = (QSignalTransition*) play->addTransition(pause);
  Pause_to_Play = (QSignalTransition*) pause->addTransition(play);
  Play_to_Final = (QSignalTransition*) play->addTransition(end);
  Pause_to_Final = (QSignalTransition*) pause->addTransition(end);


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
  QObject::connect(play, &QState::entered, [this](){
      emit signalMachine(kSignalPhase, true, kPhasePlay);
    });
  QObject::connect(play, &QState::exited, [this](){
      emit signalMachine(kSignalPhase, false, kPhasePlay);
    });
  QObject::connect(pause, &QState::entered, [this](){
      emit signalMachine(kSignalPhase, true, kPhasePause);
    });
  QObject::connect(pause, &QState::exited, [this](){
      emit signalMachine(kSignalPhase, false, kPhasePause);
    });
}

void Automate_morceaux::initDebug()
{
  machine->setObjectName("machine") ;
  play->setObjectName("play");
  playHistory->setObjectName("playHistory");
  pause->setObjectName("pause");
  pauseHistory->setObjectName("pauseHistory");

  QObject::connect(machine, &QStateMachine::started, [this](){
      qDebug()<<"Machine started";
    });
  QObject::connect(machine, &QStateMachine::stopped, [this](){
      qDebug()<<"Machine stopped";
    });
  QObject::connect(play, &QState::entered, [this](){
      qDebug()<<"play entered";
    });
  QObject::connect(play, &QState::exited, [this](){
      qDebug()<<"Play exited";
    });
  QObject::connect(pause, &QState::entered, [this](){
      qDebug()<<"Pause entered";
    });
  QObject::connect(pause, &QState::exited, [this](){
      qDebug()<<"Pause exited";
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

void Automate_morceaux::setPlay(bool play)
{
  if (play)
  {
      emit signalPlay();
  } else
  {
      emit signalPause();
  }
}

void Automate_morceaux::changeMode(bool r)
{
    if(r)
    {
        emit signalModeRadio();
    }
}
