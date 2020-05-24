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
    MenuSetup();                                                                     /// Lance la fonction MenuSetup()
    /// Mise en place d'un texte "glisser et déposer"
    label = new QLabel();
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("glisser et déposer possible");
    label->setFont(titre);
    label->setAlignment(Qt::AlignCenter);
    setCentralWidget(label);

    setGeometry(500,300,800,559);                                                     /// Geometrie de la fenetre
    setAcceptDrops(true);                                                             /// Autorise le depot de fichier
    connect(this,SIGNAL(fichierTrouver(QString)),this,SLOT(LectureFichier(QString))); /// Détection qu'un fichier est trouvé et lecture du fichier
}

/**
 * \fn MainWindow::~MainWindow()
 * \brief Fonction de supression de l'instance d'une fenetre principal (MainWindow).
 *
 */

MainWindow::~MainWindow()
{
    delete ui;    ///Supprime l'UI
}

/**
 * \fn void MainWindow::MachineSetup()
 * \brief Fonction de paramétrage de la machine à état pour la navigation dans les Etapes d'une recette
 *
 */

void MainWindow::MachineSetup()
{
    machine = new QStateMachine(this);                                   /// Création d'une instance de QStateMachine
    QList<QState*> Listetat;                                             /// Création d'une liste d'états
    ui->tempLabel->hide();                                               /// Cache le label nommé "teamLabel"
    for(int i = 0; i <= R.getEtapes().size()-1; i++)                     /// Repete la boucle autant de fois que d'étapes
    {
        QState *etat = new QState();                                     /// Allocation dynamique d'un etat
        etat->assignProperty(ui->tempLabel, "text", R.getEtape(i));      /// L'état créer prend une étape
        machine->addState(etat);                                         /// L'état est ajouté à la machine
        Listetat.append(etat);                                           /// La liste d'état rajoute l'état créer
        if(i==0)                                                         /// Si c'est la première fois que l'on parcours la boucle, alors :
        {
            machine->setInitialState(etat);                              /// L'état devient l'état initial
        }
    }
    for(int i = 0; i <= R.getEtapes().size()-1; i++)                     /// Repete la boucle autant de fois que d'étapes
    {
        if (i!=0)                                                        /// Si ce n'est pas la première fois que l'on parcours la boucle, alors :
            Listetat[i]->addTransition(ui->boutonGauche, SIGNAL(clicked()),Listetat[i-1]);  /// Ajoute la transition qui passe à l'étape précédente
        if (i!=R.getEtapes().size()-1)                                   /// Si ce n'est pas la dernière fois que l'on parcours la boucle, alors :
            Listetat[i]->addTransition(ui->boutonDroite, SIGNAL(clicked()),Listetat[i+1]);  /// Ajoute la transition qui passe à l'étape suivante
        connect(Listetat[i], SIGNAL(entered()), this, SLOT(AfficherEtape()));
    }
    machine->start();                                                   /// Lancement de la machine
}

/**
 * \fn void MainWindow::MenuSetup()
 * \brief Fonction de paramétrage du menu d'une fenetre
 *
 */

void MainWindow::MenuSetup()
{
    ui->setupUi(this);                                                                      /// Initialise l'interface
    QMenu *fileMenu = new QMenu(tr("&Fichier"), this);                                      /// Création d'un menu Fichier sur le mainWindow
    menuBar()->addMenu(fileMenu);                                                           /// Affectation de ce menu à la bar de menu

    fileMenu->addAction(tr("&Ouvrir..."), this, SLOT(OuvrirFichier()),QKeySequence::Open);  /// Création d'un bouton Ouvrir sur le menu, qui lance la fonction ouvrirfichier()
    fileMenu->addAction(tr("&Quitter"), qApp, SLOT(quit()),QKeySequence::Quit);             /// Création d'un bouton Quitter sur le menu, qui lance la fonction quit()
}

/**
 * \fn void MainWindow::TabInfoCompSetup(Recette R)
 * \brief Fonction de paramétrage du tableau d'affichage des information complémentaires
 *
 */

void MainWindow::TabInfoCompSetup()
{
    ui->tableInformations->setColumnCount(2);                                     /// Ajoute 2 collones au tableau
    ui->tableInformations->setRowCount(4);                                        /// Ajoute 4 lignes au tableau
    ui->tableInformations->setEditTriggers(QAbstractItemView::NoEditTriggers);    /// Empèche l'utilisateur de modifier une case du tableau
    ui->tableInformations->setSelectionBehavior(QAbstractItemView::SelectRows);   /// Permet à l'utilisateur de ne selectionner que les lignes
    ui->tableInformations->setSelectionMode(QAbstractItemView::SingleSelection);  /// Empèche l'utilisateur de sélectionner plus d'une ligne du tableau
    ui->tableInformations->resizeColumnToContents(1);                             /// Ajuste la taille des case au contenu de la première colonne
    ui->tableInformations->horizontalHeader()->setStretchLastSection(true);       /// Permet à l'utilisateur d'élargir les colonne
    ui->tableInformations->horizontalHeader()->setVisible(true);                  /// Affiche les titres de colonnes
    ui->tableInformations->verticalHeader()->setVisible(false);                   /// Cache les titres de lignes
    connect(ui->tableInformations->horizontalHeader(),SIGNAL(sectionResized(int, int, int)),ui->tableInformations,SLOT(resizeRowsToContents()));  /// Ajuste constamment la taille des case au contenu de la première colonne
    AfficherInformation();                                                        /// Affiche la liste des informations complémentaires
    for(int i = 0 ; i < ui->tableInformations->rowCount() ; i++)                  /// Repete la boucle atant de fois qu'il y a de lignes
    {
        ui->tableInformations->item(i,0)->setFont(style4);                        /// Ajoute un font au texte dans les première case des lignes
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
    R = newRecette;                 /// Ajoute une nouvelle recette
}

/**
 * \fn void MainWindow::LectureFichier(QString nomFichier)
 * \brief Fonction de lecture d'un fichier JSON qui apelle la fonction JSON.Lecture(nomFichier, R)
 *
 * \param nomFichier QString qui stoque le nom du fichier à lire, ne peut être NULL.
 */

void MainWindow::LectureFichier(QString nomFichier)
{
    Recette newRecette;           /// Instancie une nouvelle recette
    setRecette(newRecette);       /// Ajoute la recette dans le programme
    ui->setupUi(this);            /// Instancie l'ui
    MenuSetup();                  /// Lance la fonction de setup du menu
    JSON.Lecture(nomFichier, R);  /// Lance la fonction qui lit le fichier JSON
    MettreAJourRecette();         /// Lance la fonction qui met à jour la recette
    MachineSetup();               /// Lance la fonction qui paramètre une machine
}

/**
 * \fn void MainWindow::OuvrirFichier(const QString &path)
 * \brief Fonction qui permet d'ouvrir une fenetre de recherche de fichier JSON dans l'arborescence de l'ordinateur de l'utilisateur
 *
 * \param path const QString qui stoque le chemin vers un fichier.
 */

void MainWindow::OuvrirFichier(const QString &path)
{
    QString nomFichier = path;             /// Création d'une varaiable contenant le nom du fichier
    if (nomFichier.isNull())               /// Si le fichier n'existe pas, alors :
        nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier"), "", tr("Fichiers JSON (*.json)"));   ///Ouvre une fenetre de dialoque et de recherche de fichier JSON
    if (!nomFichier.isNull())              /// Si le fichier existe, alors :
        emit fichierTrouver(nomFichier);   /// emet le signal comme quoi le fichier est trouvé
}

/**
 * \fn void MainWindow::AfficherDescription()
 * \brief Fonction qui permet d'afficher la description d'une recette
 *
 */

void MainWindow::AfficherDescription()
{
    ///création du style de texte :
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
    ///création du style de texte :
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
    ///efface la listeEtape
    ui->listeEtapes->clear();
    ///ajoute un item contenant l'étape courante
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
    for(int i=0;i<(ui->tableInformations->rowCount() * ui->tableInformations->columnCount());i++)     /// Boucle qui se repete autant de fois qu'il y as de case dans le tableau
    {
        ui->tableInformations->setItem(i/2,(i)%2,new QTableWidgetItem(R.getInformation().at(i)));     /// Ajoute à la case, les informations qu'elle doit afficher
    }
}

/**
 * \fn void MainWindow::AfficherTemps()
 * \brief Fonction qui permet d'afficher le temps d'une recette
 *
 */

void MainWindow::AfficherTemps()
{
    QStringListModel *modeleTemps = new QStringListModel(Trait.traitementVueTemps(R.getTemps()));   /// Création d'un QStringList qui stock un modele d'affichage du temps
    ui->VueTemps->setModel(modeleTemps);                                                            /// Ajoute le modele à l'UI
}

/**
 * \fn void MainWindow::AfficherURL()
 * \brief Fonction qui permet d'afficher l'e temps'URL d'une recette
 *
 */

void MainWindow::AfficherURL()
{
    QStringListModel *modeleURL = new QStringListModel(R.getURL());                             /// Création d'un QStringList qui stock un modele d'affichage de l'URL
    ui->VueURL->setModel(modeleURL);                                                            /// Ajoute le modele à l'UI
}

/**
 * \fn void MainWindow::MettreAJourRecette()
 * \brief Fonction qui permet de mettre à jour l'affichage d'une recette
 *
 */

void MainWindow::MettreAJourRecette()
{
    /// Affiche les informations de recette
    AfficherDescription();
    AfficherIngredient();
    AfficherEtape();
    TabInfoCompSetup();  ///la fonction AfficherInformation() est appelé dans cette fonction
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





