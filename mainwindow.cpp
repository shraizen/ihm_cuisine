#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MenuSetup();

    texte = new QTextEdit;
    texte->setReadOnly(true);
    setCentralWidget(texte);
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
    ui->textExplications->append("lol");
}

void MainWindow::lireFichier(QString nomFichier)
{
    QFile fichier(nomFichier);
    QJsonParseError error;

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

           qDebug() << "Nom " << (obj.value("name")).toString();

           qDebug() << "Description : " << (obj.value("description")).toString();
           QJsonValue val = obj.value("recipeIngredient");

           QJsonArray valArray = val.toArray();
           for (auto value: valArray)
               qDebug() << "ingredient " << value.toString();

           val = obj.value("recipeInstructions");
           valArray = val.toArray();
           for (auto value: valArray)
               qDebug() << "instruction " << value.toString();

           qDebug() << "Total time : " << (obj.value("totalTime")).toString();
           qDebug() << "URL : " << (obj.value("url")).toString();

       }
    }
    else {
        qDebug() << "lol";
    }
}
