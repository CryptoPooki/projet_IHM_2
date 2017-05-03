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

  // La machine
  QStateMachine *machine;

  // Les états élémentaires
  QState *begin;
  QState *go;
  QFinalState *end;

  // Et leurs historiques
  QState *HistoryStack[1000];
  int HS_index;

  // Les messages envoyés à l'UI
  void setupMessages();
  void initDebug();

signals:
  // Le format de communication vers l'UI
  void signalMachine(signalType, bool on=true, int param1=0, int param2=0);

  // Internal
  void signalGo();
  void signalFinal();
  void signalModeMorceaux();

public slots:
  void setBegin(bool b);
  void setGo();
  void setFinal();
  void changeMode(bool morceaux);
};

#endif // AUTOMATE_RADIO_H
