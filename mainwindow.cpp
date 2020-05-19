/**
 * \file mainWindow.cpp
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Programme permettant l'implémentation de la fenetre principal (MainWindow)
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * \fn MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
 * \brief Fonction de création d'une nouvelle instance d'une fenetre principal (MainWindow).
 *
 * \param parent Pointeur sur QWidget à stocker dans l'objet MainWindow.
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MenuSetup();                                                                         // Lance la fonction MenuSetup()
    numeroEtapeCourante = 0;
    //Création d'une zone de texte accessible seulement en lecture :
    texte = new QTextEdit;
    texte->setReadOnly(true);
    setCentralWidget(texte);
    setGeometry(500,300,800,559);                                                        // Initialise la taille de la fenetre
    setAcceptDrops(true);
    connect(this,SIGNAL(fichierTrouver(QString)),this,SLOT(LectureFichier(QString)));    // Détection qu'un fichier est trouvé et lecture du fichier
    MachineSetup();
}

/**
 * \fn MainWindow::~MainWindow()
 * \brief Fonction de supression de l'instance d'une fenetre principal (MainWindow).
 *
 */

MainWindow::~MainWindow()
{
    delete ui;    //Supprime l'UI
}

/**
 * \fn void MainWindow::MachineSetup()
 * \brief Fonction de paramétrage de la machine à état pour la navigation dans les Etapes d'une recette
 *
 */

void MainWindow::MachineSetup()
{
    machine = new QStateMachine(this);
    etat = new QList<QState>;
    for()
    {
        machine->addState(etat->at(1));
    }
    machine->addState(etat->at(1));
    etat->addTransition(ui->boutonDroite, SIGNAL(clicked()),etatDroite);
    machine->setInitialState(etatGauche);
    machine->start();
}

/**
 * \fn void MainWindow::MenuSetup()
 * \brief Fonction de paramétrage du menu d'une fenetre
 *
 */

void MainWindow::MenuSetup()
{
    ui->setupUi(this);                                                                      // Initialise l'interface
    QMenu *fileMenu = new QMenu(tr("&Fichier"), this);                                      // Création d'un menu Fichier sur le mainWindow
    menuBar()->addMenu(fileMenu);                                                           // Affectation de ce menu à la bar de menu

    fileMenu->addAction(tr("&Ouvrir..."), this, SLOT(OuvrirFichier()),QKeySequence::Open);  // Création d'un bouton Ouvrir sur le menu, qui lance la fonction ouvrirfichier()
    fileMenu->addAction(tr("&Quitter"), qApp, SLOT(quit()),QKeySequence::Quit);             // Création d'un bouton Quitter sur le menu, qui lance la fonction quit()
}

/**
 * \fn void MainWindow::setRecette(Recette newRecette)
 * \brief Fonction d'insertion d'une recette dans le programme
 *
 * \param newRecette Recette qui stoque le contenu d'une recette présent dans la classe Recette, ne peut être NULL.
 */

void MainWindow::setRecette(Recette newRecette)
{
    R = newRecette;
}

/**
 * \fn void MainWindow::LectureFichier(QString nomFichier)
 * \brief Fonction de lecture d'un fichier JSON qui apelle la fonction JSON.Lecture(nomFichier, R)
 *
 * \param nomFichier QString qui stoque le nom du fichier à lire, ne peut être NULL.
 */

void MainWindow::LectureFichier(QString nomFichier)
{
    Recette newRecette;
    setRecette(newRecette);
    ui->setupUi(this);
    MenuSetup();
    JSON.Lecture(nomFichier, R);
    MettreAJourRecette();
    connect(etatGauche, SIGNAL(entered()), this, SLOT(AfficherEtapePrecedente()));
    connect(etatDroite, SIGNAL(entered()), this, SLOT(AfficherEtapeSuivante()));
}

/**
 * \fn void MainWindow::OuvrirFichier(const QString &path)
 * \brief Fonction qui permet d'ouvrir une fenetre de recherche de fichier JSON dans l'arborescence de l'ordinateur de l'utilisateur
 *
 * \param path const QString qui stoque le chemin vers un fichier.
 */

void MainWindow::OuvrirFichier(const QString &path)
{
    QString nomFichier = path;
    if (nomFichier.isNull())
        nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier"), "", tr("Fichiers JSON (*.json)"));
    if (!nomFichier.isNull())
        emit fichierTrouver(nomFichier);
}

/**
 * \fn void MainWindow::AfficherDescription()
 * \brief Fonction qui permet d'afficher la description d'une recette
 *
 */

void MainWindow::AfficherDescription()
{
    //création du style de texte :
    QString style = "";
       style += "QListView { ";
       style += "font-family: Times New Roman;font-size: 15pt;";
       style += "}";
    QFont titre("Times New Roman", 24, QFont::Bold);
    ui->listeDescription->setStyleSheet(style);
    ui->listeDescription->addItems(R.getDescription());
    ui->listeDescription->itemAt(1,0)->setTextAlignment(Qt::AlignCenter);
    ui->listeDescription->itemAt(1,0)->setFont(titre);

}

/**
 * \fn void MainWindow::AfficherIngredient()
 * \brief Fonction qui permet d'afficher la liste des ingrédients d'une recette
 *
 */

void MainWindow::AfficherIngredient()
{
    //création du style de texte :
    QString style = "";
       style += "QListView { ";
       style += "font-family: Times New Roman;font-size: 12pt;";
       style += "}";
    QFont titre("Times New Roman", 15, QFont::Bold);
    ui->listeIngredient->setStyleSheet(style);
    ui->listeIngredient->addItems(R.getIngredient());
    ui->listeIngredient->itemAt(1,0)->setTextAlignment(Qt::AlignCenter);
    ui->listeIngredient->itemAt(1,0)->setFont(titre);
}

/**
 * \fn void MainWindow::AfficherEtapePrecedente()
 * \brief Fonction qui permet d'afficher l'étape précédente d'une recette
 *
 */

void MainWindow::AfficherEtapePrecedente()
{
    numeroEtapeCourante --;
    if(numeroEtapeCourante <= 0)
    {
        numeroEtapeCourante = 1;
    }
    AfficherEtape();
}

/**
 * \fn void MainWindow::AfficherEtapeSuivante()
 * \brief Fonction qui permet d'afficher l'étape suivante d'une recette
 *
 */

void MainWindow::AfficherEtapeSuivante()
{
    numeroEtapeCourante ++;
    if(numeroEtapeCourante >= 20)
    {
        numeroEtapeCourante = 19;
    }
    AfficherEtape();
}

/**
 * \fn void MainWindow::AfficherEtape()
 * \brief Fonction qui permet d'afficher une étape d'une recette
 *
 */

void MainWindow::AfficherEtape()
{
    QString style = "";
       style += "QListView { ";
       style += "font-family: Times New Roman;font-size: 12pt;";
       style += "}";
    QFont titre("Times New Roman", 15, QFont::Bold);
    ui->listeEtapes->setStyleSheet(style);
    ui->listeEtapes->addItems(R.getEtape(numeroEtapeCourante));
    ui->listeEtapes->itemAt(1,0)->setTextAlignment(Qt::AlignCenter);
    ui->listeEtapes->itemAt(1,0)->setFont(titre);
}

/**
 * \fn void MainWindow::AfficherTemps()
 * \brief Fonction qui permet d'afficher le temps d'une recette
 *
 */

void MainWindow::AfficherTemps()
{
    QStringListModel *modeleTemps = new QStringListModel(Trait.traitementVueTemps(R.getTemps()));
    ui->VueTemps->setModel(modeleTemps);
}

/**
 * \fn void MainWindow::AfficherURL()
 * \brief Fonction qui permet d'afficher l'e temps'URL d'une recette
 *
 */

void MainWindow::AfficherURL()
{
    QStringListModel *modeleURL = new QStringListModel(R.getURL());
    ui->VueURL->setModel(modeleURL);
}

/**
 * \fn void MainWindow::MettreAJourRecette()
 * \brief Fonction qui permet de mettre à jour l'affichage d'une recette
 *
 */

void MainWindow::MettreAJourRecette()
{
    AfficherDescription();
    AfficherIngredient();
    AfficherEtape();
    AfficherTemps();
    AfficherURL();
}

/**
 * \fn void MainWindow::dragEnterEvent(QDragEnterEvent *e)
 * \brief Fonction qui lorsque qu'un fichier survol la fenetre mainWindow, l'autorise à être déposé (drop)
 *
 * \param e QDragEnterEvent qui stoque l'évenement de survol d'un fichier sur le MainWindow.
 */

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

/**
 * \fn void MainWindow::dropEvent(QDropEvent *e)
 * \brief Fonction qui lorsqu'un fichier est déposé, lance la fonction LectureFichier()
 *
 * \param e QDropEvent qui stoque l'évenement de déposition d'un fichier sur le MainWindow.
 */

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        LectureFichier(fileName);
    }
}





