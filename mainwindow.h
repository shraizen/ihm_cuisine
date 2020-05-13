#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonValue>
#include <QJsonArray>
#include <QStringListModel>
#include <QListView>
#include <QLabel>
#include "Recette.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTextEdit * texte;
private:
    Ui::MainWindow *ui;
    void MenuSetup();
public slots:
    void ouvrirFichier(const QString &path = QString());
    void afficherEtapes();
    void afficherTexte();
    void lireFichier(QString);
    void AfficherDescription(Recette);
    void AfficherIngredient(Recette);
    void AfficherTemps(Recette);
    void AfficherURL(Recette);
    void MettreAJourRecette(Recette);
signals:
    void OuvrirListeIngredients();
    void OuvrirListeEtapes();
    void fichierTrouver(QString);
};

#endif // MAINWINDOW_H
