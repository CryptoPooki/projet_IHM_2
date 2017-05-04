#ifndef AUTOMATE_MORCEAUX_H
#define AUTOMATE_MORCEAUX_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QHistoryState>
#include <QFinalState>
#include <QSignalTransition>
#include <QDebug>
#include "limits.h"

// Types de signaux envoyés à l'UI
enum signalType {
  kSignalPhase,
  kSignalEndOfPhase
};

// Phases, communiquées à l'UI
enum phase {
  kPhase,
  KPhaseEndCycle
};

class Automate_morceaux : public QObject
{
    Q_OBJECT
public:
    explicit Automate_morceaux(QObject *parent = 0);

  // La machine
  QStateMachine *machine;

  // Les états élémentaires
  QState *begin;
  QState *go;
  QFinalState *end;

  // Et leurs historiques
  QState *HistoryStack[1000];
  unsigned int HS_index;
  unsigned int pseudo_max;


  // Les messages envoyés à l'UI
  void setupMessages();
  void initDebug();

  QSignalTransition *s;

signals:
  // Le format de communication vers l'UI
  void signalMachine(signalType, bool on=true, int param1=0, int param2=0);

  //Signaux de transition vers d'autres états et d'autres modes
  void signalGo();
  void signalFinal();
  void signalModeRadio();

public slots:
  void setBegin(bool b);
  void setGo();
  void setFinal();
  void changeMode(bool radio);
};

#endif // AUTOMATE_MORCEAUX_H
