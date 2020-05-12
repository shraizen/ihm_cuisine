#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QFileDialog>
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
    QString ouvrirFichier(const QString &path = QString());
    void afficherEtapes();
    void afficherTexte();
signals:
    void OuvrirListeIngredients();
    void OuvrirListeEtapes();
};

#endif // MAINWINDOW_H
