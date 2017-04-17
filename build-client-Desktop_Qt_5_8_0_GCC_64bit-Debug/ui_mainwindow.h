/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QListWidget *Liste;
    QListWidget *Morceaux;
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1005, 618);
        actionMorceaux = new QAction(MainWindow);
        actionMorceaux->setObjectName(QStringLiteral("actionMorceaux"));
        actionRadio = new QAction(MainWindow);
        actionRadio->setObjectName(QStringLiteral("actionRadio"));
        actionAnglais = new QAction(MainWindow);
        actionAnglais->setObjectName(QStringLiteral("actionAnglais"));
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        actionFran_ais = new QAction(MainWindow);
        actionFran_ais->setObjectName(QStringLiteral("actionFran_ais"));
        actionOccitan = new QAction(MainWindow);
        actionOccitan->setObjectName(QStringLiteral("actionOccitan"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 985, 481));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Infos_connexion = new QHBoxLayout();
        Infos_connexion->setSpacing(6);
        Infos_connexion->setObjectName(QStringLiteral("Infos_connexion"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Infos_connexion->addItem(horizontalSpacer);

        Nom_utilisateur = new QLineEdit(verticalLayoutWidget);
        Nom_utilisateur->setObjectName(QStringLiteral("Nom_utilisateur"));

        Infos_connexion->addWidget(Nom_utilisateur);

        Connexion = new QRadioButton(verticalLayoutWidget);
        Connexion->setObjectName(QStringLiteral("Connexion"));

        Infos_connexion->addWidget(Connexion);


        verticalLayout->addLayout(Infos_connexion);

        Infos_musique = new QHBoxLayout();
        Infos_musique->setSpacing(6);
        Infos_musique->setObjectName(QStringLiteral("Infos_musique"));
        Image = new QLabel(verticalLayoutWidget);
        Image->setObjectName(QStringLiteral("Image"));
        Image->setEnabled(true);

        Infos_musique->addWidget(Image);

        Liste = new QListWidget(verticalLayoutWidget);
        Liste->setObjectName(QStringLiteral("Liste"));

        Infos_musique->addWidget(Liste);

        Morceaux = new QListWidget(verticalLayoutWidget);
        Morceaux->setObjectName(QStringLiteral("Morceaux"));

        Infos_musique->addWidget(Morceaux);


        verticalLayout->addLayout(Infos_musique);

        Infos_temps_lecture = new QHBoxLayout();
        Infos_temps_lecture->setSpacing(6);
        Infos_temps_lecture->setObjectName(QStringLiteral("Infos_temps_lecture"));
        Temps_restant = new QLabel(verticalLayoutWidget);
        Temps_restant->setObjectName(QStringLiteral("Temps_restant"));

        Infos_temps_lecture->addWidget(Temps_restant);

        Progression = new QSlider(verticalLayoutWidget);
        Progression->setObjectName(QStringLiteral("Progression"));
        Progression->setOrientation(Qt::Horizontal);

        Infos_temps_lecture->addWidget(Progression);

        Temps_lu = new QLabel(verticalLayoutWidget);
        Temps_lu->setObjectName(QStringLiteral("Temps_lu"));

        Infos_temps_lecture->addWidget(Temps_lu);


        verticalLayout->addLayout(Infos_temps_lecture);

        Commandes = new QHBoxLayout();
        Commandes->setSpacing(6);
        Commandes->setObjectName(QStringLiteral("Commandes"));
        Rewind = new QPushButton(verticalLayoutWidget);
        Rewind->setObjectName(QStringLiteral("Rewind"));

        Commandes->addWidget(Rewind);

        Previous = new QPushButton(verticalLayoutWidget);
        Previous->setObjectName(QStringLiteral("Previous"));

        Commandes->addWidget(Previous);

        Play_pause = new QPushButton(verticalLayoutWidget);
        Play_pause->setObjectName(QStringLiteral("Play_pause"));

        Commandes->addWidget(Play_pause);

        Next = new QPushButton(verticalLayoutWidget);
        Next->setObjectName(QStringLiteral("Next"));

        Commandes->addWidget(Next);

        Foward = new QPushButton(verticalLayoutWidget);
        Foward->setObjectName(QStringLiteral("Foward"));

        Commandes->addWidget(Foward);

        Mute = new QPushButton(verticalLayoutWidget);
        Mute->setObjectName(QStringLiteral("Mute"));

        Commandes->addWidget(Mute);

        Volume = new QSlider(verticalLayoutWidget);
        Volume->setObjectName(QStringLiteral("Volume"));
        Volume->setOrientation(Qt::Horizontal);

        Commandes->addWidget(Volume);


        verticalLayout->addLayout(Commandes);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1005, 28));
        menuModes = new QMenu(menuBar);
        menuModes->setObjectName(QStringLiteral("menuModes"));
        menuLangues = new QMenu(menuBar);
        menuLangues->setObjectName(QStringLiteral("menuLangues"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionMorceaux->setText(QApplication::translate("MainWindow", "Morceaux", Q_NULLPTR));
        actionRadio->setText(QApplication::translate("MainWindow", "Radio", Q_NULLPTR));
        actionAnglais->setText(QApplication::translate("MainWindow", "Deutsch", Q_NULLPTR));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", Q_NULLPTR));
        actionFran_ais->setText(QApplication::translate("MainWindow", "Fran\303\247ais", Q_NULLPTR));
        actionOccitan->setText(QApplication::translate("MainWindow", "Occitan", Q_NULLPTR));
        Connexion->setText(QApplication::translate("MainWindow", "Connexion", Q_NULLPTR));
        Image->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        Temps_restant->setText(QApplication::translate("MainWindow", "--:--:--", Q_NULLPTR));
        Temps_lu->setText(QApplication::translate("MainWindow", "--:--:--", Q_NULLPTR));
        Rewind->setText(QString());
        Previous->setText(QString());
        Play_pause->setText(QString());
        Next->setText(QString());
        Foward->setText(QString());
        Mute->setText(QString());
        menuModes->setTitle(QApplication::translate("MainWindow", "Modes", Q_NULLPTR));
        menuLangues->setTitle(QApplication::translate("MainWindow", "Langues", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
