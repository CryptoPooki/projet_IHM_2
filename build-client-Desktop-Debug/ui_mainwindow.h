/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMorceaux;
    QAction *actionRadio;
    QAction *actionAnglais;
    QAction *actionEnglish;
    QAction *actionFran_ais;
    QAction *actionOccitan;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *Infos_connexion;
    QSpacerItem *horizontalSpacer;
    QLineEdit *Nom_utilisateur;
    QRadioButton *Connexion;
    QHBoxLayout *Infos_musique;
    QLabel *Image;
    QListView *Liste;
    QListView *Morceaux;
    QHBoxLayout *Infos_temps_lecture;
    QLabel *Temps_restant;
    QSlider *Progression;
    QLabel *Temps_lu;
    QHBoxLayout *Commandes;
    QPushButton *Rewind;
    QPushButton *Previous;
    QPushButton *Play_pause;
    QPushButton *Next;
    QPushButton *Foward;
    QPushButton *Mute;
    QSlider *Volume;
    QMenuBar *menuBar;
    QMenu *menuModes;
    QMenu *menuLangues;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1005, 618);
        actionMorceaux = new QAction(MainWindow);
        actionMorceaux->setObjectName(QString::fromUtf8("actionMorceaux"));
        actionRadio = new QAction(MainWindow);
        actionRadio->setObjectName(QString::fromUtf8("actionRadio"));
        actionAnglais = new QAction(MainWindow);
        actionAnglais->setObjectName(QString::fromUtf8("actionAnglais"));
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QString::fromUtf8("actionEnglish"));
        actionFran_ais = new QAction(MainWindow);
        actionFran_ais->setObjectName(QString::fromUtf8("actionFran_ais"));
        actionOccitan = new QAction(MainWindow);
        actionOccitan->setObjectName(QString::fromUtf8("actionOccitan"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 985, 481));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Infos_connexion = new QHBoxLayout();
        Infos_connexion->setSpacing(6);
        Infos_connexion->setObjectName(QString::fromUtf8("Infos_connexion"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Infos_connexion->addItem(horizontalSpacer);

        Nom_utilisateur = new QLineEdit(verticalLayoutWidget);
        Nom_utilisateur->setObjectName(QString::fromUtf8("Nom_utilisateur"));

        Infos_connexion->addWidget(Nom_utilisateur);

        Connexion = new QRadioButton(verticalLayoutWidget);
        Connexion->setObjectName(QString::fromUtf8("Connexion"));

        Infos_connexion->addWidget(Connexion);


        verticalLayout->addLayout(Infos_connexion);

        Infos_musique = new QHBoxLayout();
        Infos_musique->setSpacing(6);
        Infos_musique->setObjectName(QString::fromUtf8("Infos_musique"));
        Image = new QLabel(verticalLayoutWidget);
        Image->setObjectName(QString::fromUtf8("Image"));
        Image->setEnabled(true);

        Infos_musique->addWidget(Image);

        Liste = new QListView(verticalLayoutWidget);
        Liste->setObjectName(QString::fromUtf8("Liste"));

        Infos_musique->addWidget(Liste);

        Morceaux = new QListView(verticalLayoutWidget);
        Morceaux->setObjectName(QString::fromUtf8("Morceaux"));

        Infos_musique->addWidget(Morceaux);


        verticalLayout->addLayout(Infos_musique);

        Infos_temps_lecture = new QHBoxLayout();
        Infos_temps_lecture->setSpacing(6);
        Infos_temps_lecture->setObjectName(QString::fromUtf8("Infos_temps_lecture"));
        Temps_restant = new QLabel(verticalLayoutWidget);
        Temps_restant->setObjectName(QString::fromUtf8("Temps_restant"));

        Infos_temps_lecture->addWidget(Temps_restant);

        Progression = new QSlider(verticalLayoutWidget);
        Progression->setObjectName(QString::fromUtf8("Progression"));
        Progression->setOrientation(Qt::Horizontal);

        Infos_temps_lecture->addWidget(Progression);

        Temps_lu = new QLabel(verticalLayoutWidget);
        Temps_lu->setObjectName(QString::fromUtf8("Temps_lu"));

        Infos_temps_lecture->addWidget(Temps_lu);


        verticalLayout->addLayout(Infos_temps_lecture);

        Commandes = new QHBoxLayout();
        Commandes->setSpacing(6);
        Commandes->setObjectName(QString::fromUtf8("Commandes"));
        Rewind = new QPushButton(verticalLayoutWidget);
        Rewind->setObjectName(QString::fromUtf8("Rewind"));

        Commandes->addWidget(Rewind);

        Previous = new QPushButton(verticalLayoutWidget);
        Previous->setObjectName(QString::fromUtf8("Previous"));

        Commandes->addWidget(Previous);

        Play_pause = new QPushButton(verticalLayoutWidget);
        Play_pause->setObjectName(QString::fromUtf8("Play_pause"));

        Commandes->addWidget(Play_pause);

        Next = new QPushButton(verticalLayoutWidget);
        Next->setObjectName(QString::fromUtf8("Next"));

        Commandes->addWidget(Next);

        Foward = new QPushButton(verticalLayoutWidget);
        Foward->setObjectName(QString::fromUtf8("Foward"));

        Commandes->addWidget(Foward);

        Mute = new QPushButton(verticalLayoutWidget);
        Mute->setObjectName(QString::fromUtf8("Mute"));

        Commandes->addWidget(Mute);

        Volume = new QSlider(verticalLayoutWidget);
        Volume->setObjectName(QString::fromUtf8("Volume"));
        Volume->setOrientation(Qt::Horizontal);

        Commandes->addWidget(Volume);


        verticalLayout->addLayout(Commandes);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1005, 28));
        menuModes = new QMenu(menuBar);
        menuModes->setObjectName(QString::fromUtf8("menuModes"));
        menuLangues = new QMenu(menuBar);
        menuLangues->setObjectName(QString::fromUtf8("menuLangues"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuModes->menuAction());
        menuBar->addAction(menuLangues->menuAction());
        menuModes->addAction(actionMorceaux);
        menuModes->addSeparator();
        menuModes->addAction(actionRadio);
        menuLangues->addAction(actionAnglais);
        menuLangues->addSeparator();
        menuLangues->addAction(actionEnglish);
        menuLangues->addSeparator();
        menuLangues->addAction(actionFran_ais);
        menuLangues->addSeparator();
        menuLangues->addAction(actionOccitan);
        menuLangues->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionMorceaux->setText(QApplication::translate("MainWindow", "Morceaux", 0, QApplication::UnicodeUTF8));
        actionRadio->setText(QApplication::translate("MainWindow", "Radio", 0, QApplication::UnicodeUTF8));
        actionAnglais->setText(QApplication::translate("MainWindow", "Deutsch", 0, QApplication::UnicodeUTF8));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", 0, QApplication::UnicodeUTF8));
        actionFran_ais->setText(QApplication::translate("MainWindow", "Fran\303\247ais", 0, QApplication::UnicodeUTF8));
        actionOccitan->setText(QApplication::translate("MainWindow", "Occitan", 0, QApplication::UnicodeUTF8));
        Connexion->setText(QApplication::translate("MainWindow", "Connect\303\251", 0, QApplication::UnicodeUTF8));
        Image->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        Temps_restant->setText(QApplication::translate("MainWindow", "--:--:--", 0, QApplication::UnicodeUTF8));
        Temps_lu->setText(QApplication::translate("MainWindow", "--:--:--", 0, QApplication::UnicodeUTF8));
        Rewind->setText(QString());
        Previous->setText(QString());
        Play_pause->setText(QString());
        Next->setText(QString());
        Foward->setText(QString());
        Mute->setText(QString());
        menuModes->setTitle(QApplication::translate("MainWindow", "Modes", 0, QApplication::UnicodeUTF8));
        menuLangues->setTitle(QApplication::translate("MainWindow", "Langues", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
