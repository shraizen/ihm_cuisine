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
signals:
    void OuvrirListeIngredients();
    void OuvrirListeEtapes();
    void fichierTrouver(QString);
};

#endif // MAINWINDOW_H
