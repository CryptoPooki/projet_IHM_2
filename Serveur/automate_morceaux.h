#ifndef AUTOMATE_MORCEAUX_H
#define AUTOMATE_MORCEAUX_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QHistoryState>
#include <QFinalState>
#include <QSignalTransition>
#include <QDebug>

// Types de signaux envoyés à l'UI
enum signalType {
  //kSignalAction,
  kSignalPhase,
  kSignalEndOfPhase
};

// Phases, communiquées à l'UI
enum phase {
  kPhasePlay,
  kPhasePause,
  kPhaseMute,
  kPhaseSound,
  KPhaseEndCycle
};

class Automate_morceaux : public QObject
{
    Q_OBJECT
public:
    explicit Automate_morceaux(QObject *parent = 0);

private:
  // La machine
  QStateMachine *machine;

  // Les états élémentaires
  QState *begin;
  QState *play;
  QState *pause;
  QFinalState *Final;

  // Et leurs historiques
  QHistoryState *playHistory;
  QHistoryState *pauseHistory;

  // Et puis nous avons des transitions.
  QSignalTransition *Begin_to_Play;
  QSignalTransition *Play_to_Pause;
  QSignalTransition *Pause_to_Play;
  QSignalTransition *Play_to_Final;
  QSignalTransition *Pause_to_Final;

  // Les messages envoyés à l'UI
  void setupMessages();
  void initDebug();

signals:
  // Le format de communication vers l'UI
  void signalMachine(signalType, bool on=true, int param1=0, int param2=0);

  void signalPause();
  void signalPlay();
  void signalBegin();
  void signalFinal();
  void signalModeMorceaux();

public slots:
  void setPlay(bool play);
  void setBegin(bool begin);
  void changeMode(bool radio);
};

#endif // AUTOMATE_MORCEAUX_H
