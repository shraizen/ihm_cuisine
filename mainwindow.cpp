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
    // Lance la fonction MenuSetup()
    MenuSetup();
    //Mise en place d'un texte "glisser et déposer"
    label = new QLabel();
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("glisser et déposer possible");
    label->setFont(titre);
    label->setAlignment(Qt::AlignCenter);
    setCentralWidget(label);
    //Geometrie de la fenetre
    setGeometry(500,300,800,559);
    //autorise le depot de fichier
    setAcceptDrops(true);
    // Détection qu'un fichier est trouvé et lecture du fichier
    connect(this,SIGNAL(fichierTrouver(QString)),this,SLOT(LectureFichier(QString)));
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
    QList<QState*> Listetat;
    ui->tempLabel->hide();
    for(int i = 0; i <= R.getEtapes().size()-1; i++)
    {
        QState *etat = new QState();
        etat->assignProperty(ui->tempLabel, "text", R.getEtape(i));
        machine->addState(etat);
        Listetat.append(etat);
        if(i==0)
        {
            machine->setInitialState(etat);
        }
    }
    for(int i = 0; i <= R.getEtapes().size()-1; i++)
    {
        if (i!=0)
            Listetat[i]->addTransition(ui->boutonGauche, SIGNAL(clicked()),Listetat[i-1]);
        if (i!=R.getEtapes().size()-1)
            Listetat[i]->addTransition(ui->boutonDroite, SIGNAL(clicked()),Listetat[i+1]);
        connect(Listetat[i], SIGNAL(entered()), this, SLOT(AfficherEtape()));
    }
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
 * \fn void MainWindow::TabInfoCompSetup(Recette R)
 * \brief Fonction de paramétrage du tableau d'affichage des information complémentaires
 *
 */

void MainWindow::TabInfoCompSetup()
{
    ui->tableInformations->setColumnCount(2);
    ui->tableInformations->setRowCount(4);
    ui->tableInformations->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableInformations->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableInformations->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableInformations->resizeColumnToContents(1);
    ui->tableInformations->horizontalHeader()->setStretchLastSection(true);
    ui->tableInformations->horizontalHeader()->setVisible(true);
    ui->tableInformations->verticalHeader()->setVisible(false);
    connect(ui->tableInformations->horizontalHeader(),SIGNAL(sectionResized(int, int, int)),ui->tableInformations,SLOT(resizeRowsToContents()));
    AfficherInformation();
    for(int i = 0 ; i < ui->tableInformations->rowCount() ; i++)
    {
        ui->tableInformations->item(i,0)->setFont(style4);
    }
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
    MachineSetup();
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
    ui->listeDescription->setStyleSheet(style2);
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
    ui->listeIngredient->setStyleSheet(style1);
    ui->listeIngredient->addItems(R.getIngredient());
    ui->listeIngredient->itemAt(1,0)->setTextAlignment(Qt::AlignCenter);
    ui->listeIngredient->itemAt(1,0)->setFont(titre);
}

/**
 * \fn void MainWindow::AfficherEtape()
 * \brief Fonction qui permet d'afficher une étape d'une recette
 *
 */

void MainWindow::AfficherEtape()
{
    //efface la listeEtape
    ui->listeEtapes->clear();
    //ajoute un item contenant l'étape courante
    ui->listeEtapes->addItem(ui->tempLabel->text());
    ui->listeEtapes->setFont(style3);
    ui->listeEtapes->itemAt(1,0)->setTextAlignment(Qt::AlignCenter);
}

/**
 * \fn void MainWindow::AfficherInformation();
 * \brief Fonction qui permet d'afficher la liste des informations complémentaires d'une recette
 *
 */

void MainWindow::AfficherInformation()
{
    for(int i=0;i<(ui->tableInformations->rowCount() * ui->tableInformations->columnCount());i++)
    {
        ui->tableInformations->setItem(i/2,(i)%2,new QTableWidgetItem(R.getInformation().at(i)));
    }
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
    TabInfoCompSetup();  //la fonction AfficherInformation() est appelé dans cette fonction
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





