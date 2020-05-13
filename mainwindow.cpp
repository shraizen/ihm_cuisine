#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MenuSetup();
    texte = new QTextEdit;
    texte->setReadOnly(true);
    setCentralWidget(texte);
    setGeometry(500,300,800,559);
    connect(this,SIGNAL(fichierTrouver(QString)),this,SLOT(lireFichier(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MenuSetup()
{
    QMenu *fileMenu = new QMenu(tr("&Fichier"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&Ouvrir..."), this, SLOT(ouvrirFichier()),QKeySequence::Open);
    fileMenu->addAction(tr("&Quitter"), qApp, SLOT(quit()),QKeySequence::Quit);

    emit OuvrirListeEtapes();
    emit OuvrirListeIngredients();
}

void MainWindow::ouvrirFichier(const QString &path)
{
    QString nomFichier = path;
    if (nomFichier.isNull())
        nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier"), "", tr("Fichiers JSON (*.json)"));
    emit fichierTrouver(nomFichier);
}

void MainWindow::afficherEtapes()
{
}

void MainWindow::afficherTexte()
{
  //  ui->textExplications->append("lol");
}

void MainWindow::lireFichier(QString nomFichier)
{
    ui->setupUi(this);
    MenuSetup();
    QFile fichier(nomFichier);
    QJsonParseError error;
    QString texteAAfficher;
    Recette R;

    if(fichier.open(QFile::ReadOnly)) {
       QByteArray donnees = fichier.readAll();

       QJsonDocument doc = QJsonDocument::fromJson(donnees, &error);
       if(error.error != QJsonParseError::NoError)
       {
           qCritical() << "Impossible d’interpréter le fichier : " << error.errorString();
       }
       else
       {

           QJsonObject obj=doc.object();

           qDebug() << "Nom : " << (obj.value("name")).toString();

           qDebug() << "Description : " << (obj.value("description")).toString();
           QJsonValue val = obj.value("recipeIngredient");
           texteAAfficher = "Nom : \n";
           texteAAfficher += (obj.value("name")).toString();
           texteAAfficher += "\nDescription : \n";
           texteAAfficher += (obj.value("description")).toString();
           QStringList listeDescription;
           listeDescription << "Nom : \n" << (obj.value("name")).toString() << "\nDescription : \n" << (obj.value("description")).toString();
           R.setDescription(listeDescription);
           QJsonArray valArray = val.toArray();
           QStringList listeIngredient;
           listeIngredient << "ingredients : ";
           for (auto value: valArray)
           {
               qDebug() << "ingredient : " << value.toString();
               listeIngredient << "_ " + value.toString();
           }
           R.setIngredient(listeIngredient);
           val = obj.value("recipeInstructions");
           valArray = val.toArray();
           for (auto value: valArray)
           {
               qDebug() << "instruction " << value.toString();
           }
           QStringList temps;
           QStringList URL;
           qDebug() << "Temps de préparation : " << (obj.value("prepTime")).toString();
           temps << (obj.value("prepTime")).toString();
           qDebug() << "Temps de cuisson : " << (obj.value("cookTime")).toString();
           temps << (obj.value("cookTime")).toString();
           qDebug() << "Total time : " << (obj.value("totalTime")).toString();
           temps << (obj.value("totalTime")).toString();
           R.setTemps(temps);
           qDebug() << "URL : " << (obj.value("url")).toString();
           URL << "URL : " << (obj.value("url")).toString();
           R.setURL(URL);
           MettreAJourRecette(R);
       }
    }
    else {
        qDebug() << "lol";
    }
}

void MainWindow::AfficherDescription(Recette R)
{
    QStringListModel *modeleDescription = new QStringListModel(R.getDescription());
    ui->listeDescription->setModel(modeleDescription);
}

void MainWindow::AfficherIngredient(Recette R)
{
    QStringListModel *modeleIngredient = new QStringListModel(R.getIngredient());
    ui->listeIngredient->setModel(modeleIngredient);
}

void MainWindow::AfficherTemps(Recette R)
{
    QStringListModel *modeleTemps = new QStringListModel(R.getTemps());
    ui->VueTemps->setModel(modeleTemps);
}

void MainWindow::AfficherURL(Recette R)
{
    QStringListModel *modeleURL = new QStringListModel(R.getURL());
    ui->VueURL->setModel(modeleURL);
}

void MainWindow::MettreAJourRecette(Recette R)
{
    AfficherDescription(R);
    AfficherIngredient(R);
    AfficherTemps(R);
    AfficherURL(R);
}





