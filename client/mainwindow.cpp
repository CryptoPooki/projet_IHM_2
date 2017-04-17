#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "unistd.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Définition d'une norme (arbitraire) de taille de boutons : 70x50 pixels
    size.setWidth(50); size.setHeight(70);

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

    QSize main_size; main_size.setHeight(330); main_size.setWidth(330);
    ui->Image->setFixedSize(size);
    pix_music.load(":/pics/music.png");
    pix_music = pix_music.scaled(330,330);
    ui->Image->setPixmap(pix_music);
    ui->Image->setFixedSize(main_size);

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

void MainWindow::on_Connexion_toggled(bool checked)
{
    if (checked)                      // Si l'utilisateur est déjà connecté
    {
        deconnexion();                //On interrompt la connexion avec le serveur
    } else                            // Si l'utilisateur n'est pas connecté
    {
        connexion();                  //On lance la connexion
    }
}

void MainWindow::on_Progression_sliderMoved(int position)
{
    //Pause de la lecture
    pause();

    //Déplacement de la lecture
    //Fonction avec le serveur et la valeur

    //Lancement de la lecture
    play();
}

void MainWindow::on_Rewind_pressed()
{
    int speed_factors[7] = {1,2,5,10,20,30,60}; int i = 0;
    while(ui->Rewind->isChecked()) //Pas sûr
    {
        rewind(speed_factors[i]);
        sleep(speed_factors[i]); //Attente de speed_factors[id] secondes avant d'augmenter la vitesse
        if (i < 6) i++;
        //Déplacement de la barre
    }
}

void MainWindow::on_Rewind_released()
{

}

void MainWindow::on_Previous_clicked()
{
    //Pause de la lecture
    pause();

    //Envoi de la demande de previous au serveur
    previous();

    //Lancement de la lecture du morceau précédent
    play();
}

void MainWindow::on_Play_pause_clicked()
{
    if (flag_play)                      //Si un morceau est joué
    {
        //Arrêt de la lecture
        pause();

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
        play();

        //MAJ de l'état de lecture
        flag_play = true;

        //Changement de l'icône du bouton
        pix_play.load(":/pics/play.png");
        icon_play.addPixmap(pix_play);
        ui->Play_pause->setIcon(icon_play);
        ui->Play_pause->setIconSize(size);
    }
}

void MainWindow::on_Next_clicked()
{
    //Pause de la lecture
    pause();

    //Envoi de la demande de next au serveur
    next();

    //Lancement de la lecture du morceau précédent
    play();
}

void MainWindow::on_Foward_pressed()
{
    int speed_factors[7] = {1,2,5,10,20,30,60}; int i = 0;
    while(ui->Foward->isChecked()) //Pas sûr
    {
        foward(speed_factors[i]);
        sleep(speed_factors[i]);         //Attente de speed_factors[i] secondes avant d'augmenter la vitesse
        if (i < 6) i++;
    }
}

void MainWindow::on_Foward_released()
{

}

void MainWindow::on_Mute_clicked()
{
    if (flag_mute)                      //Si le mode mute est activé
    {
        //Déclenchement de la fonction mute et récupération du pourcentage de son max enregistré
        int volume_memorise = mute(-1);

        //MAJ de l'état de lecture
        flag_mute = false;

        //Changement de l'icône du bouton
        pix_sound.load(":/pics/sound.png");
        icon_sound.addPixmap(pix_sound);
        ui->Mute->setIcon(icon_sound);
        ui->Mute->setIconSize(size);

        //Restauration du volume
        setVolume(volume_memorise);

        //Repositionnement de la barre
        ui->Volume->setValue(volume_memorise);

    } else //Le lecteur est en pause
    {
        //Déclenchement de la fonction mute et stockage du pourcentage de son max enregistré
        mute(ui->Volume->value());

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
}

void MainWindow::on_Volume_sliderMoved(int position)
{
    if (flag_mute)                        //Si le mode mute est activé, il devient désactivé automatiquement
    {
        //Déclenchement de la fonction mute
        mute(-1);             //Désactivation du mute

        //MAJ de l'état de lecture
        flag_mute = false;

        //Changement de l'icône du bouton
        pix_sound.load(":/pics/sound.png");
        icon_sound.addPixmap(pix_sound);
        ui->Mute->setIcon(icon_sound);
        ui->Mute->setIconSize(size);

        //Modification du volume
        setVolume(position);
    } else                                //Si le mode mute n'est pas activé
    {
        //Modification du volume
        setVolume(position);
    }
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

            ui->Connexion->setText(QString::fromStdString("Verbindet"));
        break;
        case 2: //English
            ui->menuModes->setTitle(QString::fromStdString("Modes"));
            ui->actionMorceaux->setText(QString::fromStdString("Music"));
            ui->actionRadio->setText(QString::fromStdString("Radio"));

            ui->menuLangues->setTitle(QString::fromStdString("Languages"));
            //Noms des langues non modifiées

            ui->Connexion->setText(QString::fromStdString("Connected"));
        break;
        case 3: //Français
            ui->menuModes->setTitle(QString::fromStdString("Modes"));
            ui->actionMorceaux->setText(QString::fromStdString("Morceaux"));
            ui->actionRadio->setText(QString::fromStdString("Radio"));

            ui->menuLangues->setTitle(QString::fromStdString("Langues"));
            //Noms des langues non modifiées

            ui->Connexion->setText(QString::fromStdString("Connecté"));
        break;
        case 4: //Occitan
            ui->menuModes->setTitle(QString::fromStdString("Mòu"));
            ui->actionMorceaux->setText(QString::fromStdString("Musica"));
            ui->actionRadio->setText(QString::fromStdString("Radia"));

            ui->menuLangues->setTitle(QString::fromStdString("Lenga"));
            //Noms des langues non modifiées

            ui->Connexion->setText(QString::fromStdString("Noselança"));
    }
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
}

void MainWindow::connexion()
{
    //A définir une fois que la question du serveur est résolue
}

void MainWindow::deconnexion()
{
    //A définir une fois que la question du serveur est résolue
}

QString MainWindow::user_name()
{
    return ui->Nom_utilisateur->text();
}

void MainWindow::get_list_metadata()
{
    //A définir une fois que la structure des métadatas sont comprises
}

void MainWindow::get_music_metadata()
{
    //A définir une fois que la structure des métadatas sont comprises
}

void MainWindow::show_list_metadata()
{
    //A définir une fois que la structure des métadatas sont comprises
}

void MainWindow::show_music_metadata()
{
    //A définir une fois que la structure des métadatas sont comprises
}

void MainWindow::rewind(int speed)
{
    //A définir une fois que le système de messages sera établi et que le fonctionnement audio sera assimilé
}

void MainWindow::previous()
{
    //A définir une fois que le système de messages sera établi et que le fonctionnement audio sera assimilé
}

void MainWindow::play()
{
    //A définir une fois que le système de messages sera établi et que le fonctionnement audio sera assimilé
}

void MainWindow::pause()
{
    //A définir une fois que le système de messages sera établi et que le fonctionnement audio sera assimilé
}

void MainWindow::next()
{
    //A définir une fois que le système de messages sera établi et que le fonctionnement audio sera assimilé
}

void MainWindow::foward(int speed)
{
    //A définir une fois que le système de messages sera établi et que le fonctionnement audio sera assimilé
}

int MainWindow::mute(int vol)
{
    //A définir une fois que le système de messages sera établi et que le fonctionnement audio sera assimilé
    /* Fonctionnnement global :
     * mute prend comme argument le volume enregistré (ex: 42 "pourcents") quand on passe en mute et revoie -1
     * mute prend -1 comme argument quand on sort du mute et renvoie le pourcentage du volume enregistré
     * J'ai choisi -1 plutôt que 0 (qui semble un meilleur choix à première vue) pour éviter un conflit entre la barre de son, qui devient automatiquement mute
     * quand on la diminue à 0, et le mute
     */
    return -1; //Retour par défaut tant que la fonction n'est pas programmée et pour éviter les bugs de compilation
}

void MainWindow::setVolume(int volume)
{
    //A définir une fois que le système de messages sera établi et que le fonctionnement audio sera assimilé
}

/*void MainWindow::setPhase(phase p, bool on, int param)
{
  switch(p)
  {
    case kPhasePlay:

      break;
    case kPhasePause:

      break;
    case kPhaseMute:

      break;
    case kPhaseSound:

      break;
  }
}

void MainWindow::message(signalType sig, bool switchOn, int param1, int param2) //A revoir
{
    switch(sig)
    {
      case kSignalPhase:
        setPhase((phase)param1, switchOn, param2);
        break;
      default:
        break;
      }
}*/
