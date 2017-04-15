#include "automate_radio.h"

Automate_radio::Automate_radio(QObject *parent) : QObject(parent)
{
  // Une machine
  machine =new QStateMachine(this);

  // 2 états + 1 état final
  // Un état "play"
  play = new QState(machine);
  playHistory = new QHistoryState(play);

  // Un état "pause"
  pause = new QState(machine);
  pauseHistory = new QHistoryState(pause);

  // Un état final "déconnecté"
  deconnecte = new QFinalState(machine);


  // Nos transitions
  Play_to_Pause=play->addTransition(pause);
  Pause_to_Play=pause->addTransition(play);
  Play_to_Deconnecte=play->addTransition(deconnecte);
  Pause_to_Deconnecte=pause->addTransition(deconnecte);


  QObject::connect(deconnecte, &QState::entered, [this](){
      qDebug()<<"Déconnection";
      emit signalMachine(kSignalPhase, false, kPhaseEndCycle);
      cleanup();
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

//Déclenchement de la lecture
void Automate_radio::setupPlayState()
{
    //Lecture de la musique
}

//Arrêt de la lecture
void Automate_radio::setupPauseState()
{
    //Arrêt de la musique
}

/*
 * Quelques debugs utiles
 */
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

void Automate_radio::cleanup(){
  // On remet tout à zéro
  // A revoir
}

void Automate_radio::setConnect(bool on)
{
  if (!on)
  {
      // On arrête la machine
      machine->stop();
      cleanup();
      return;
  }

  // On va commencer par l'état pause le temps que la musique se charge
  machine->setInitialState(pause);
  machine->start();

  //Une fois que les informations sont chargées, on passe à l'état play
  //A coder
}

//?
void Automate_radio::setPlay(bool play)
{
  emit signalMachine(kSignalPhase);
}
