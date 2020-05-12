#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "ui_etapes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MenuSetup();

    texte = new QTextEdit;
    texte->setReadOnly(true);
    setCentralWidget(texte);
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

QString MainWindow::ouvrirFichier(const QString &path)
{
    QString nomFichier = path;
    if (nomFichier.isNull())
        nomFichier = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier"), "", tr("Fichiers JSON (*.json)"));
    return nomFichier;
}

void MainWindow::afficherEtapes()
{
}

void MainWindow::afficherTexte()
{
    ui->textExplications->append("lol");
}
