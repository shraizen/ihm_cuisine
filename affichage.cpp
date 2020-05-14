#include "affichage.h"

Affichage::Affichage()
{
}

Affichage::~Affichage()
{
    delete ui;
}

void Affichage::MenuSetup()
{
    ui->setupUi(this);                                                                      // Initialise l'interface
    QMenu *fileMenu = new QMenu(tr("&Fichier"), this);                                      // Création d'un menu Fichier sur le mainWindow
    menuBar()->addMenu(fileMenu);                                                           // Affectation de ce menu à la bar de menu

    fileMenu->addAction(tr("&Ouvrir..."), this, SLOT(OuvrirFichier()),QKeySequence::Open);  // Création d'un bouton Ouvrir sur le menu, qui lance la fonction ouvrirfichier()
    fileMenu->addAction(tr("&Quitter"), qApp, SLOT(quit()),QKeySequence::Quit);             // Création d'un bouton Quitter sur le menu, qui lance la fonction quit()

    emit OuvrirListeEtapes();                   // Envoie le signal OuvrirListeEtapes()
    emit OuvrirListeIngredients();              // Envoie le signal OuvrirListeIngredients()
}

void Affichage::AfficherDescription(Recette R)
{
    QStringListModel *modeleDescription = new QStringListModel(R.getDescription());
    ui->listeDescription->setModel(modeleDescription);
}

void Affichage::AfficherIngredient(Recette R)
{
    QStringListModel *modeleIngredient = new QStringListModel(R.getIngredient());
    ui->listeIngredient->setModel(modeleIngredient);
}

void Affichage::AfficherEtapes(Recette R)
{

}

void Affichage::AfficherTemps(Recette R)
{
    QStringListModel *modeleTemps = new QStringListModel(R.getTemps());
    ui->VueTemps->setModel(modeleTemps);
}

void Affichage::AfficherURL(Recette R)
{
    QStringListModel *modeleURL = new QStringListModel(R.getURL());
    ui->VueURL->setModel(modeleURL);
}
