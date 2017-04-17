#include "automate_son.h"
#include "automate_morceaux.h"


Automate_son::Automate_son(QObject *parent) : QObject(parent)
{
  // Une machine
  machine =new QStateMachine(this);

  // 2 états
  // Un état "sound"
  sound = new QState(machine);
  soundHistory = new QHistoryState(sound);

  // Un état "mute"
  mute = new QState(machine);


  // Nos transitions (BUG)
  mute->addTransition(sound);
  sound->addTransition(mute);

  // J'enverrai des messages à l'UI
  setupMessages();

  initDebug();
}

/*
 * Messages pour l'UI
 */
void Automate_son::setupMessages()
{
  QObject::connect(sound, &QState::entered, [this](){
      emit signalMachine(kSignalPhase, true, kPhaseSound);
    });
  QObject::connect(sound, &QState::exited, [this](){
      emit signalMachine(kSignalPhase, false, kPhaseSound);
    });
  QObject::connect(mute, &QState::entered, [this](){
      emit signalMachine(kSignalPhase, true, kPhaseMute);
    });
  QObject::connect(mute, &QState::exited, [this](){
      emit signalMachine(kSignalPhase, false, kPhaseMute);
    });
}

/*
 * Quelques debugs utiles
 */
void Automate_son::initDebug()
{
  machine->setObjectName("machine") ;
  mute->setObjectName("mute");
  sound->setObjectName("sound");
  soundHistory->setObjectName("soundHistory");

  QObject::connect(machine, &QStateMachine::started, [this](){
      qDebug()<<"Machine started";
    });
  QObject::connect(machine, &QStateMachine::stopped, [this](){
      qDebug()<<"Machine stopped";
    });
  QObject::connect(sound, &QState::entered, [this](){
      qDebug()<<"Sound entered";
    });
  QObject::connect(sound, &QState::exited, [this](){
      qDebug()<<"Sound exited";
    });
  QObject::connect(mute, &QState::entered, [this](){
      qDebug()<<"Mute entered";
    });
  QObject::connect(mute, &QState::exited, [this](){
      qDebug()<<"Mute exited";
    });
}

void Automate_son::setMute(bool mute)
{
  if(mute)
  {
      emit signalMute();
  } else
  {
      emit signalSound();
  }
}

