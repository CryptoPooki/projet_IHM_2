#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Redimensionnement des boutons
    pix_rewind.load(":/pics/rewind.png");
    icon_rewind.addPixmap(pix_rewind);
    ui->Rewind->setIcon(icon_rewind);
    ui->Rewind->setIconSize(size);

    pix_previous.load(":/pics/previous.png");
    icon_previous.addPixmap(pix_previous);
    ui->Previous->setIcon(icon_previous);
    ui->Previous->setIconSize(size);

    pix_play.load(":/pics/play.png");
    icon_play.addPixmap(pix_play);
    ui->Play_pause->setIcon(icon_play);
    ui->Play_pause->setIconSize(size);

    pix_next.load(":/pics/previous.png");
    //Rotation de 180° d'une flèche allant de droite à gauche = une flèche de gauche à droite
    QTransform transform_next; transform_next.rotate(180); pix_next = pix_next.transformed(transform_next);
    icon_next.addPixmap(pix_next);
    ui->Next->setIcon(icon_next);
    ui->Next->setIconSize(size);

    pix_foward.load(":/pics/rewind.png");
    //Rotation de 180° d'une flèche allant de droite à gauche = une flèche de gauche à droite
    QTransform transform_foward; transform_foward.rotate(180); pix_foward = pix_foward.transformed(transform_foward);
    icon_foward.addPixmap(pix_foward);
    ui->Foward->setIcon(icon_foward);
    ui->Foward->setIconSize(size);

    pix_sound.load(":/pics/sound.png");
    icon_sound.addPixmap(pix_sound);
    ui->Mute->setIcon(icon_sound);
    ui->Mute->setIconSize(size);

    flag_play = false;
    flag_mute = false;
    flag_radio = false;

    Automate_morceaux *automate_morceaux = new Automate_morceaux();
    Automate_radio *automate_radio = new Automate_radio();
    Automate_son *automate_son = new Automate_son();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Gestion de la connexion au serveur
void MainWindow::on_connect_toggled(bool checked)
{
    if (checked)                      // Si l'utilisateur est déjà connecté
    {
        MainWindow::deconnexion();    //On interrompt la connexion avec le serveur
    } else                            // Si l'utilisateur n'est pas connecté
    {
        MainWindow::connexion();      //On lance la connexion
    }
     return NULL;
}

//Gestion de la barre de lecture
//==> Checker le comportement de la valeur
void MainWindow::slider_lecture_moved(int valeur)
{
    //Pause de la lecture
    MainWindow::pause();

    //Déplacement de la lecture
    //Fonction avec le serveur et la valeur

    //Lancement de la lecture
    MainWindow::play();

    return NULL;
}

void MainWindow::on_rewind_pressed()
{
    int speed_factors[7] = {1,2,5,10,20,30,60}; int i = 0;
    while(ui->Rewind->pressed()) //Pas sûr
    {
        MainWindow::rewind(times[i]);
        sleep(speed_factors[id]);         //Attente de speed_factors[id] secondes avant d'augmenter la vitesse
        if (id < 6) id++;
    }
    return NULL;
}

void on_previous_clicked()
{
    //Pause de la lecture
    MainWindow::pause();

    //Envoi de la demande de previous au serveur
    MainWindow::previous();

    //Lancement de la lecture du morceau précédent
    MainWindow::play();

    return NULL;
}

void MainWindow::on_play_pause_clicked()
{
    if (flag_play)                      //Si un morceau est joué
    {
        //Arrêt de la lecture
        MainWindow::pause();

        //MAJ de l'état de lecture
        flag_play = false;

        //Changement de l'icône du bouton
        pix_play.load(":/pics/pause.png");
        icon_play.addPixmap(pix_play);
        ui->Play_pause->setIcon(icon_play);
        ui->Play_pause->setIconSize(size);
    } else                              //Le lecteur est en pause
    {
        //Lancement de la lecture
        MainWindow::play();

        //MAJ de l'état de lecture
        flag_play = true;

        //Changement de l'icône du bouton
        pix_play.load(":/pics/play.png");
        icon_play.addPixmap(pix_play);
        ui->Play_pause->setIcon(icon_play);
        ui->Play_pause->setIconSize(size);
    }
    return NULL;
}

void MainWindow::on_next_clicked()
{
    //Pause de la lecture
    MainWindow::pause();

    //Envoi de la demande de next au serveur
    MainWindow::next();

    //Lancement de la lecture du morceau précédent
    MainWindow::play();

    return NULL;
}

void MainWindow::on_foward_clicked()
{
    int speed_factors[7] = {1,2,5,10,20,30,60}; int i = 0;
    while(ui->Foward->pressed()) //Pas sûr
    {
        MainWindow::foward(times[i]);
        sleep(speed_factors[id]);         //Attente de speed_factors[id] secondes avant d'augmenter la vitesse
        if (id < 6) id++;
    }
    return NULL;
}

void MainWindow::on_mute_clicked()
{
    if (flag_mute)                      //Si le mode mute est activé
    {
        //Déclenchement de la fonction mute et récupération du pourcentage de son max enregistré
        int volume_memorise = MainWindow::mute(-1);

        //MAJ de l'état de lecture
        flag_mute = false;

        //Changement de l'icône du bouton
        pix_sound.load(":/pics/sound.png");
        icon_sound.addPixmap(pix_sound);
        ui->Mute->setIcon(icon_sound);
        ui->Mute->setIconSize(size);

        //Restauration du volume
        MainWindow::change_sound(volume_memorise);

        //Repositionnement de la barre
        ui->Volume->setValue(volume_memorise);

    } else                              //Le lecteur est en pause
    {
        //Déclenchement de la fonction mute et stockage du pourcentage de son max enregistré
        MainWindow::mute(ui->Volume->value());

        //MAJ de l'état de lecture
        flag_mute = true;

        //Changement de l'icône du bouton
        pix_sound.load(":/pics/mute.png");
        icon_sound.addPixmap(pix_sound);
        ui->Mute->setIcon(icon_sound);
        ui->Mute->setIconSize(size);

        //Repositionnement de la barre
        ui->Volume->setValue(0);
    }
    return NULL;
}

void MainWindow::slider_sound_moved(int val)
{
    if (flag_mute)                        //Si le mode mute est activé, il devient désactivé automatiquement
    {
        //Déclenchement de la fonction mute
        MainWindow::mute(-1);             //Désactivation du mute

        //MAJ de l'état de lecture
        flag_mute = false;

        //Changement de l'icône du bouton
        pix_sound.load(":/pics/sound.png");
        icon_sound.addPixmap(pix_sound);
        ui->Mute->setIcon(icon_sound);
        ui->Mute->setIconSize(size);

        //Modification du volume
        MainWindow::change_sound(val);
    } else                                //Si le mode mute n'est pas activé
    {
        //Modification du volume
        MainWindow::change_sound(val);
    }
    return NULL;
}

void MainWindow::change_languages(int language_id)
{
    switch (language_id)
    {
        case 1: //Deutsch
            ui->menuModes->setTitle(QString::fromStdString("Modus"));
            ui->actionMorceaux->setText(QString::fromStdString("Musik"));
            ui->actionRadio->setText(QString::fromStdString("Radiofunk"));

            ui->menuLangues->setTitle(QString::fromStdString("Sprachen"));
            //Noms des langues non modifiées

            ui->Connexion->setText(QString::fromStdString("Verbindung"));
        break;
        case 2: //English
            ui->menuModes->setTitle(QString::fromStdString("Modes"));
            ui->actionMorceaux->setText(QString::fromStdString("Music"));
            ui->actionRadio->setText(QString::fromStdString("Radio"));

            ui->menuLangues->setTitle(QString::fromStdString("Languages"));
            //Noms des langues non modifiées

            ui->Connexion->setText(QString::fromStdString("Connection"));
        break;
        case 3: //Français
            ui->menuModes->setTitle(QString::fromStdString("Modes"));
            ui->actionMorceaux->setText(QString::fromStdString("Morceaux"));
            ui->actionRadio->setText(QString::fromStdString("Radio"));

            ui->menuLangues->setTitle(QString::fromStdString("Langues"));
            //Noms des langues non modifiées

            ui->Connexion->setText(QString::fromStdString("Connexion"));
        break;
        case 4: //Occitan
            ui->menuModes->setTitle(QString::fromStdString("Mòu"));
            ui->actionMorceaux->setText(QString::fromStdString("Musica"));
            ui->actionRadio->setText(QString::fromStdString("Radia"));

            ui->menuLangues->setTitle(QString::fromStdString("Lenga"));
            //Noms des langues non modifiées

            ui->Connexion->setText(QString::fromStdString("Noselança"));
    }
    return NULL;
}

void MainWindow::change_mode()
{
    if(flag_radio) // Si le mode radio est activé
    {
        //Affichage ce qui a été caché
        ui->Progression->show();
        ui->Temps_lu->show();
        ui->Temps_restant->show();
        ui->Rewind->show();
        ui->Foward->show();

        //MAJ du flag
        flag_radio = false;

        //Récupération de l'état précédent
        //Fonction à définir
    } else
    {
        //Cache
        ui->Progression->hide();
        ui->Temps_lu->hide();
        ui->Temps_restant->hide();
        ui->Rewind->hide();
        ui->Foward->hide();

        //MAJ du flag
        flag_radio = true;

        //Récupération de l'état précédent
        //Fonction à définir
    }
    retrun NULL;
}

void connexion();                         //Fonction de connexion au serveur
QString user_name();                      //Fonction qui revoit le nom de l'utilisateur inscrit dans le LineEdit
void get_list_metadata();                 //Fonction qui demande les métadonnées des listes proposées
void get_music_metadata();                //Finction qui demande les métadonnées d'un morceau
void show_list_metadata();                //Fonction qui affiche les métadonnées d'une liste
void show_music_metadata();               //Fonction qui affiche les métadonnées d'un morceau
// Gestion des menus déroulants ???
void rewind(int speed_factor);            //Fonction qui fait un retour en arrière sur le morceau avec un facteur de vitesse égal à speed_factor
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
une fantastique figurine de mouton en plastique d'une valeur de 3 Pokédollars
(jeu sans obligation d'achat, conditions de remboursement floues à l'avantage de l'entreprise)
*/
void foward();                            //Fonction qui fait une avance rapide sur le morceau
void mute();                              //Fonction qui mute
void change_sound(int pourcentage);       //Fonctoin qui modifie le son en fonction de sa puissance maximale

public slots:
// Messages reçus de l'automate
void message(signalType, bool, int param1, int param2);
