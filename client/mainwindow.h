#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "automate_morceaux.h"
#include "automate_radio.h"
#include "automate_son.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:

  //"void on_mode_clicked()"; ==> On utilise des QActions
  //"void on_language_clicked()"; ==> On utilise des QActions
  void on_connect_toggled(bool checked);
  //void on_list_clicked(); ==> J'attends de voir comment tout se goupille pour coder cette fonction
  //void on_music_clicked(); ==> J'attends de voir comment tout se goupille pour coder cette fonction
  void slider_lecture_moved(int);
  void on_rewind_clicked();             // I<<
  void on_previous_clicked();           // I<
  void on_play_pause_clicked();         // > II
  void on_next_clicked();               // >I
  void on_foward_clicked();             // >>I
  void on_mute_clicked();
  void slider_sound_moved(int);

private:
  Ui::MainWindow *ui;
  Automate_morceaux *automate_morceaux;
  Automate_radio *automate_radio;
  Automate_son *automate_son;

  void change_languages(int language_id);   //Fonction qui change le langage d'affichage
  void change_mode(int mode);               //Fonction que change le mode de lecture et d'affichage
  void connexion();                         //Fonction de connexion au serveur
  QString user_name();                      //Fonction qui revoit le nom de l'utilisateur inscrit dans le LineEdit
  void get_list_metadata();                 //Fonction qui demande les métadonnées des listes proposées
  void get_music_metadata();                //Finction qui demande les métadonnées d'un morceau
  void show_list_metadata();                //Fonction qui affiche les métadonnées d'une liste
  void show_music_metadata();               //Fonction qui affiche les métadonnées d'un morceau
  // Gestion des menus déroulants ???
  void rewind();                            //Fonction qui fait un retour en arrière sur le morceau
  void previous();                          //Fonction qui joue le morceau précédent au morceau actuellement lu dans la liste
                                            //         qui joue la chaine de radio précédente dans la liste
  void play();                              //Fonction qui joue un morceau sélectionné
  void pause();                             //Fonction qui arrête de jouer le morceau actuellement joué
  void next();                              //Fonction qui joue le morceau suivant au morceau actuellement lu dans la liste
                                            //         qui joue la chaine de radio suivante
  /*Remarque : Si on clique sur Next et que le morceau est le dernier de la liste, est-ce que:
  1) on revient au début de la liste ?
  2) on passe au premier morceau de la liste suivante ?
  3) La lecture s'arrête ?
  4) on définit d'autres boutons pour gérer cette ambiguité ?

  Si tu penses avoir la réponse, envoie le numéro de ta réponse suivi de "jeu concours" au 0648525442 (75.0 € + prix du sms) pour tenter de gagner
  une fantastique figurine de mouton en plastique d'une valeur de 3 Pokédollars (jeu sans obligation d'achat, pas de remboursement possible)
  */
  void foward();                            //Fonction qui fait une avance rapide sur le morceau
  void mute();                              //Fonction qui mute
  void change_sound(int pourcentage);       //Fonctoin qui modifie le son en fonction de sa puissance maximale

public slots:
  // Messages reçus de l'automate
  void message(signalType, bool, int param1, int param2);
};

#endif // MAINWINDOW_H
