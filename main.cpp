#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    // || Création de l'application et affichage d'une fenetre MainWindow
    MainWindow w;                  // ||
    w.show();                      // ||
                                   // ||
    return a.exec();               // \/     // (boucle)
}
