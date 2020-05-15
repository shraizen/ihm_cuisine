#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MenuSetup();                                                                         // Lance la fonction MenuSetup()
    texte = new QTextEdit;          // || Création d'une zone de texte accessible seulement en lecture
    texte->setReadOnly(true);       // ||
    setCentralWidget(texte);        // \/
    setGeometry(500,300,800,559);                                                        // Initialise la taille de la fenetre
    setAcceptDrops(true);
    connect(this,SIGNAL(fichierTrouver(QString)),this,SLOT(LectureFichier(QString)));    // Détection qu'un fichier est trouvé et lecture du fichier
}

MainWindow::~MainWindow()
{
    delete ui;    //Supprime l'UI
}

void MainWindow::MenuSetup()
{
    ui->setupUi(this);                                                                      // Initialise l'interface
    QMenu *fileMenu = new QMenu(tr("&Fichier"), this);                                      // Création d'un menu Fichier sur le mainWindow
    menuBar()->addMenu(fileMenu);                                                           // Affectation de ce menu à la bar de menu

    fileMenu->addAction(tr("&Ouvrir..."), this, SLOT(OuvrirFichier()),QKeySequence::Open);  // Création d'un bouton Ouvrir sur le menu, qui lance la fonction ouvrirfichier()
    fileMenu->addAction(tr("&Quitter"), qApp, SLOT(quit()),QKeySequence::Quit);             // Création d'un bouton Quitter sur le menu, qui lance la fonction quit()

    emit OuvrirListeEtapes();                   // Envoie le signal OuvrirListeEtapes()
    emit OuvrirListeIngredients();              // Envoie le signal OuvrirListeIngredients()
}

void MainWindow::LectureFichier(QString nomFichier)
{
    Recette R;                                          // Créer une recette
    ui->setupUi(this);                                  //
    MenuSetup();                                        // Lance la fonction MenuSetup()
    Trait.LireFichier(nomFichier, R);                   // Lance la lecture du fichier()
    MettreAJourRecette(R);                              // Met à jour les données
}

void MainWindow::OuvrirFichier(const QString &path)
{
    QString nomFichier = path;                                                                                       // || Ouverture d'un fichier ou d'une fenetre de recherche de fichier
    if (nomFichier.isNull())                                                                                         // ||
        nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier"), "", tr("Fichiers JSON (*.json)"));  // \/
    if (!nomFichier.isNull())                                                                                               // || Emmision du signal pour indiquer qu'un fichier à été trouvé
        emit fichierTrouver(nomFichier);                                                                                    // \/
}

void MainWindow::AfficherDescription(Recette R)
{
    QStringListModel *modeleDescription = new QStringListModel(R.getDescription());                                  // || Affichage de la description
    ui->listeDescription->setModel(modeleDescription);                                                               // \/
}

void MainWindow::AfficherIngredient(Recette R)
{
    QStringListModel *modeleIngredient = new QStringListModel(R.getIngredient());                                    // || Affichage des Ingrédient
    ui->listeIngredient->setModel(modeleIngredient);                                                                 // \/
}

void MainWindow::AfficherEtapes(Recette R)
{

}

void MainWindow::AfficherTemps(Recette R)
{
    QStringListModel *modeleTemps = new QStringListModel(Trait.traitementVueTemps(R.getTemps()));                     // || Affichage du temps
    ui->VueTemps->setModel(modeleTemps);                                                                              // \/
}

void MainWindow::AfficherURL(Recette R)
{
    QStringListModel *modeleURL = new QStringListModel(R.getURL());                                                   // || Affichage de l'a description'URL
    ui->VueURL->setModel(modeleURL);                                                                                  // \/
}

void MainWindow::MettreAJourRecette(Recette R)
{
    AfficherDescription(R);                       // || Lance les fonctions d'affichage
    AfficherIngredient(R);                        // ||
    AfficherTemps(R);                             // ||
    AfficherURL(R);                               // \/
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        LectureFichier(fileName);
    }
}





