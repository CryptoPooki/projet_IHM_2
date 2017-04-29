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
    explicit MainWindow(QWidget *parent = 0);
    void playResponse();
    void pauseResponse();
    ~MainWindow();

private slots:
    void on_Connexion_toggled(bool checked);
    void on_Progression_sliderMoved(int position);
    void on_Rewind_pressed();
    void on_Rewind_released();
    void on_Previous_clicked();
    void on_Play_pause_clicked();
    void on_Next_clicked();
    void on_Foward_pressed();
    void on_Foward_released();
    void on_Mute_clicked();
    void orderParser(QString S);
    void slot_volume();


    void on_Liste_clicked(const QModelIndex &index);
    void setPlayList( QString S);

    void on_Morceaux_clicked(const QModelIndex &index);

private:
  Ui::MainWindow *ui;
  volume_widget* volume;
  QPixmap pix_rewind, pix_previous, pix_play, pix_next, pix_foward, pix_sound, pix_music;
  QIcon icon_rewind, icon_previous, icon_play, icon_next, icon_foward, icon_sound;
  QSize size_pic, size_button;

  void change_languages(int language_id);   //Fonction qui change le langage d'affichage
  void change_mode(bool radio);             //Fonction que change le mode de lecture et d'affichage
  bool flag_radio;                          //Booléen permettant de savoir si l'interface est en mode radio
  void connexion();                         //Fonction de connexion au serveur
  void deconnexion();                       //Fonction qui déconnecte le client de serveur
  void get_list_metadata();                 //Fonction qui demande les métadonnées des listes proposées
  void get_music_metadata();                //Finction qui demande les métadonnées d'un morceau
  void show_list_metadata();                //Fonction qui affiche les métadonnées d'une liste
  void show_music_metadata();               //Fonction qui affiche les métadonnées d'un morceau
  void rewind(int speed);                   //Fonction qui fait un retour en arrière sur le morceau
  void previous();                          //Fonction qui joue le morceau précédent au morceau actuellement lu dans la liste
                                            //         qui joue la chaine de radio précédente dans la liste
  void play();                              //Fonction qui joue un morceau sélectionné
  void pause();                             //Fonction qui arrête de jouer le morceau actuellement joué
  bool flag_play;                           //Booléen permettant de savoir si l'interface est dans l'état play ou pause
  void next();                              //Fonction qui joue le morceau suivant au morceau actuellement lu dans la liste
                                            //         qui joue la chaine de radio suivante

  void foward(int speed);                   //Fonction qui fait une avance rapide sur le morceau
  void mute();                               //Fonction gère le mute
  void setVolume(int volume);               //Fonction qui change le volume
  bool flag_mute;                           //Booléen permettant de savoir si l'interface est en mode mute
  int memVolume;
  void change_sound(int pourcentage);       //Fonction qui modifie le son en fonction de sa puissance maximale
  void setPosition_lecture(int position);

  // Connexion avec le serveur
  Communication* C;
  void InitConnexion();

  void initInfo(QString S);
};

#endif // MAINWINDOW_H
