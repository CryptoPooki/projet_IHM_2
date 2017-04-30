#ifndef AUTOMATE_RADIO_H
#define AUTOMATE_RADIO_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QHistoryState>
#include <QFinalState>
#include <QSignalTransition>
#include <QDebug>

#include "automate_morceaux.h" //Pour les enums

class Automate_radio : public QObject
{
    Q_OBJECT
public:
    explicit Automate_radio(QObject *parent = 0);

private:
  // La machine
  QStateMachine *machine;

  // Les états élémentaires
  QState *begin;
  QState *play;
  QState *pause;
  QFinalState *end;

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

  // Internal
  void signalPause();
  void signalPlay();
  void signalBegin();
  void signalFinal();
  void signalModeMorceaux();

public slots:
  void setPlay(bool play);
  void setBegin(bool b);
  void changeMode(bool morceaux);
};

#endif // AUTOMATE_RADIO_H
