#include "automate_radio.h"

Automate_radio::Automate_radio(QObject *parent) : QObject(parent)
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
  Final = new QFinalState(machine);

  // Nos transitions
  Begin_to_Play = (QSignalTransition*) begin->addTransition(play);
  Play_to_Pause = (QSignalTransition*) play->addTransition(pause);
  Pause_to_Play = (QSignalTransition*) pause->addTransition(play);
  Play_to_Final = (QSignalTransition*) play->addTransition(Final);
  Pause_to_Final = (QSignalTransition*) pause->addTransition(Final);


  QObject::connect(Final, &QState::entered, [this](){
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
void Automate_radio::setupMessages()
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

void Automate_radio::initDebug()
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

void Automate_radio::setBegin(bool begin)
{
  if (!begin)
  {
      // On arrête la machine
      machine->stop();
      return;
  }

  // On va commencer par l'état initial
  machine->setInitialState(begin);
  machine->start();
}

void Automate_radio::setPlay(bool play)
{
  if (play)
  {
      emit signalPlay();
  } else
  {
      emit signalPause();
  }
}

void Automate_radio::setMode(bool morceaux)
{
    if(morceaux)
    {
        emit signalModeRadio();
    }
}
