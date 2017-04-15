#ifndef AUTOMATE_RADIO_H
#define AUTOMATE_RADIO_H

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
};

class Automate_radio
{
    Q_OBJECT
public:
    explicit Automate_radio(QObject *parent = 0);

private:
  // La machine
  QStateMachine *machine;

  // Les états élémentaires
  QState *play;
  QState *pause;
  QFinalState *deconnecte;

  // Et leurs historiques
  QHistoryState *playHistory;
  QHistoryState *pauseHistory;

  // Et puis nous avons des transitions.
  QSignalTransition *Play_to_Pause;
  QSignalTransition *Pause_to_Play;
  QSignalTransition *Play_to_Deconnecte;
  QSignalTransition *Pause_to_Deconnecte;

  // Les messages envoyés à l'UI
  void setupMessages();

  void cleanup();
  void initDebug();

signals:
  // Le format de communication vers l'UI
  void signalMachine(signalType, bool on=true, int param1=0, int param2=0);

  // Internal
  void signalPause();

private slots:
  void setupPlayState();
  void setupPauseState();

public slots:
  void setPlay(bool play);
  void setConnect(bool on);
  void setMode(bool);
};

#endif // AUTOMATE_RADIO_H
