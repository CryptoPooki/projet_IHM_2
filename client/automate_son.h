#ifndef AUTOMATE_SON_H
#define AUTOMATE_SON_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QHistoryState>
#include <QFinalState>
#include <QSignalTransition>
#include <QDebug>

#include "automate_radio.h"

class Automate_son : public QObject
{
    Q_OBJECT
public:
    explicit Automate_son(QObject *parent = 0);

private:
  // La machine
  QStateMachine *machine;

  // Les états élémentaires
  QState *sound;
  QState *mute;

  // Et leurs historiques
  QHistoryState *soundHistory;
  //Pas besoin d'historique pour le mute

  //Pas de sortie de cycle ==> cycle infiniment infini O_O'

  // Et puis nous avons des transitions.
  QSignalTransition *mute_to_sound;
  QSignalTransition *sound_to_mute;

  // Les messages envoyés à l'UI
  void setupMessages();

  void initDebug();

signals:
  // Le format de communication vers l'UI
  void signalMachine(signalType, bool on=true, int param1=0, int param2=0);

  // Internal
  void signalPause();

private slots:
  void setupSoundState();
  void setupMuteState();

public slots:
  void setMute(bool mute);
};

#endif // AUTOMATE_SON_H
