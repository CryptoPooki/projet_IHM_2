#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSignalMapper>
#include "string.h"

#include "volume_widget.h"
#include "communication.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);       //Constructeur
    void playResponse();                            //Modifie l'interface quand le serveur joue une musique
    void pauseResponse();                           //Modifie l'interface quand le serveur arrête une musique
    ~MainWindow();                                  //Destructeur

private slots:
    void on_Connexion_clicked();                    //Slot de gestion de la puce de connexion
    void on_Progression_sliderMoved(int position);  //Slot de gestion de la barre de progression
    void on_Rewind_pressed();                       //Slot de gestion du rewind pressé
    void on_Rewind_released();                      //Slot de gestion du rewind relaché
    void on_Previous_clicked();                     //Slot de gestion du previous
    void on_Play_pause_clicked();                   //Slot de gestion du Play/Pause
    void on_Next_clicked();                         //Slot de gestion du Next
    void on_Foward_pressed();                       //Slot de gestion du foward pressé
    void on_Foward_released();                      //Slot de gestion du foxard relaché
    void on_Mute_clicked();                         //Slot de gestion du mute
    void orderParser(QString S);                    //Slot de traitement des commandes du socket
    void slot_volume();                             //Slot de gestion du volume

    void on_Liste_clicked();                        //Slot de gestion de sélection des listes
    void setPlayList( QString S);                   //Slot de gestion de l'affichage des morceaux
    void on_Morceaux_clicked();                     //Slot de gestion de sélection des morceaux



private:
  //Variables privées pour rendre l'interface jolie avec des icônes
  Ui::MainWindow *ui;
  volume_widget* volume;                            //Widget personnalisé
  QPixmap pix_rewind, pix_previous, pix_play, pix_next, pix_foward, pix_sound, pix_music;
  QIcon icon_rewind, icon_previous, icon_play, icon_next, icon_foward, icon_sound;
  QSize size_pic, size_button;

  void change_languages(int language_id);   //Fonction qui change le langage d'affichage
  void change_mode(bool radio);             //Fonction que change le mode de lecture et d'affichage
  bool flag_radio;                          //Booléen permettant de savoir si l'interface est en mode radio
  bool connexion();                         //Fonction de connexion au serveur
  void deconnexion();                       //Fonction qui déconnecte le client de serveur
  //void get_list_metadata();               //Fonction qui demande les métadonnées des listes proposées
  //void get_music_metadata();              //Finction qui demande les métadonnées d'un morceau
  //void show_list_metadata();              //Fonction qui affiche les métadonnées d'une liste
  //void show_music_metadata();             //Fonction qui affiche les métadonnées d'un morceau
  //void rewind(int speed);                 //Fonction qui fait un retour en arrière sur le morceau
  //void previous();                        //Fonction qui joue le morceau précédent au morceau actuellement lu dans la liste
                                            //         qui joue la chaine de radio précédente dans la liste
  void play();                              //Fonction qui joue un morceau sélectionné
  void pause();                             //Fonction qui arrête de jouer le morceau actuellement joué
  bool flag_play;                           //Booléen permettant de savoir si l'interface est dans l'état play ou pause
  //void next();                            //Fonction qui joue le morceau suivant au morceau actuellement lu dans la liste
                                            //         qui joue la chaine de radio suivante

  //void foward(int speed);                 //Fonction qui fait une avance rapide sur le morceau
  int mute();                               //Fonction gère le mute
  void setVolume(int volume);               //Fonction qui change le volume
  bool flag_mute;                           //Booléen permettant de savoir si l'interface est en mode mute
  int memVolume;
  void change_sound(int pourcentage);       //Fonction qui modifie le son en fonction de sa puissance maximale
  void move(QString order);                 //Fonction qui met à jour le temps lu, restant et la barre de progression
                                            //quand le serveur met à jour ses clients

  // Connexion avec le serveur
  Communication* C;                         //Permet de réaliser une commucation entre les sockets du client et du serveur
  void InitConnexion();                     //Initialisation de la connexion
  void initInfo(QString S);                 //Initialisation d'affichage de la liste des dossiers/playlists
};

#endif // MAINWINDOW_H
