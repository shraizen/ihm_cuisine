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
#include <QDropEvent>
#include <QMimeData>
#include "Recette.h"
#include "traitement.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    QTextEdit * texte;
    Traitement Trait;
    void MenuSetup();
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);

public slots:

    void OuvrirFichier(const QString &path = QString());
    void LectureFichier(QString);

    void AfficherDescription(Recette);
    void AfficherIngredient(Recette);
    void AfficherEtapes(Recette);
    void AfficherTemps(Recette);
    void AfficherURL(Recette);
    void MettreAJourRecette(Recette);

signals:

    void OuvrirListeIngredients();
    void OuvrirListeEtapes();
    void fichierTrouver(QString);
};

#endif // MAINWINDOW_H
