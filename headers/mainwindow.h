/**
 * \file mainwindow.h
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief implémentation de la fenetre principal (MainWindow)
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include "traitement.h"
#include "lectureJSON.h"
QT_BEGIN_NAMESPACE

/*! \namespace ui
 *
 * espace de nommage regroupant les composants de mainWindow.ui
 */

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*! \class MainWindow
   * \brief classe permettant la création d'une fenetre principal
   *
   */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe MainWindow
         * \param parent Pointeur sur QWidget à stocker dans l'objet MainWindow.
         */

    MainWindow(QWidget *parent = 0);

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe MainWindow
         */

    ~MainWindow();

private:

    Ui::MainWindow *ui; /*!< Ui::MainWindow contenant l'UI*/
    Traitement Trait; /*!< Traitement contenant une instance de Traitement*/
    LectureJSON JSON; /*!< LectureJSON contenant une instance de LectureJSON*/
    Recette R; /*!< Recette contenant une instance de Recette*/
    QStateMachine * machine; /*!< QStateMachine contenant une machine à état*/
    QString style1 = "QListView { font-family: Times New Roman;font-size: 12pt;}";/*!< QString contenant le style de text numéro 1*/
    QString style2 = "QListView { font-family: Times New Roman;font-size: 15pt;}";/*!< QString contenant le style de text numéro 2*/
    QFont style3{"Times New Roman", 15, QFont::Bold};/*!< QFont contenant le style de text numéro 3*/
    QFont style4{"Times New Roman", 11, QFont::Bold};/*!< QFont contenant le style de text numéro 4*/
    QFont titre{"Times New Roman", 24, QFont::Bold};/*!< QFont contenant le font des titres*/

    /**
     * \fn setup de la machine à état
     * \brief Fonction de paramétrage de la machine à état pour la navigation dans les Etapes d'une recette
     *
     */

    void MachineSetup();

    /**
     * \fn setup du menu
     * \brief Fonction de paramétrage du menu d'une fenetre
     *
     */

    void MenuSetup();

    /**
     * \fn setup du tableau des informations complémentaires
     * \brief Fonction de paramétrage du tableau d'affichage des informations complémentaires
     *
     */

    void TabInfoCompSetup();

    /**
     * \fn survol évenement
     * \brief Fonction qui lorsque qu'un fichier survol la fenetre mainWindow, l'autorise à être déposé (drop)
     *
     * \param QDragEnterEvent qui stoque l'évenement de survol d'un fichier sur le MainWindow.
     */

    void dragEnterEvent(QDragEnterEvent*);

    /**
     * \fn désurvol évenement
     * \brief Fonction qui lorsque qu'un fichier désurvol la fenetre mainWindow, enlève l'image "drag and drop" (drop)
     *
     * \param e QDragLeaveEvent qui stoque l'évenement de désurvol d'un fichier sur le MainWindow.
     */

    void dragLeaveEvent(QDragLeaveEvent *event);

    /**
     * \fn dépose évenement
     * \brief Fonction qui lorsqu'un fichier est déposé, lance la fonction LectureFichier()
     *
     * \param QDropEvent qui stoque l'évenement de déposition d'un fichier sur le MainWindow.
     */

    void dropEvent(QDropEvent*);

    /**
     * \fn setter Recette
     * \brief Fonction d'insertion d'une recette dans le programme
     *
     * \param Recette qui stoque le contenu d'une recette présent dans la classe Recette, ne peut être NULL.
     */

    void setRecette(Recette);

public slots:

    /**
     * \fn ouvrir Fichier
     * \brief Fonction qui permet d'ouvrir une fenetre de recherche de fichier JSON dans l'arborescence de l'ordinateur de l'utilisateur
     *
     * \param path const QString qui stoque le chemin vers un fichier.
     */

    void OuvrirFichier(const QString &path = QString());

    /**
     * \fn lire Fichier
     * \brief Fonction de lecture d'un fichier JSON qui apelle la fonction JSON.Lecture(nomFichier, R)
     *
     * \param QString qui stoque le nom du fichier à lire, ne peut être NULL.
     */

    void LectureFichier(QString);

    /**
     * \fn affiche Decription
     * \brief Fonction qui permet d'afficher la description d'une recette
     *
     */

    void AfficherDescription();

    /**
     * \fn affiche ingrédients
     * \brief Fonction qui permet d'afficher la liste des ingrédients d'une recette
     *
     */

    void AfficherIngredient();

    /**
     * \fn affiche étape courante
     * \brief Fonction qui permet d'afficher une étape d'une recette
     *
     */

    void AfficherEtape();

    /**
     * \fn affiche informations
     * \brief Fonction qui permet d'afficher la liste des informations complémentaires d'une recette
     *
     */

    void AfficherInformation();

    /**
     * \fn affiche temps
     * \brief Fonction qui permet d'afficher le temps d'une recette
     *
     */

    void AfficherTemps();

    /**
     * \fn affiche URL
     * \brief Fonction qui permet d'afficher l'e temps'URL d'une recette
     *
     */

    void AfficherURL();

    /**
     * \fn met à jour recette
     * \brief Fonction qui permet de mettre à jour l'affichage d'une recette
     *
     */

    void MettreAJourRecette();

signals:

    /**
     * \sa signal fichier trouver
     * \brief Signal qui indique qu'un fichier à été trouver
     *
     * \param QString qui contient le nom du fichier
     */

    void fichierTrouver(QString);
};

#endif // MAINWINDOW_H
