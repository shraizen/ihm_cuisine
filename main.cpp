/**
 * \file main.cpp
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Programme principal
 *
 */

#include "mainwindow.h"
#include <QApplication>

/**
 * \fn int main(int argc, char *argv[])
 * \brief Fonction de création d'une nouvelle instance d'une fenetre principal (MainWindow).
 *
 * \param argc entier.
 * \param argv[] Pointeur sur char.
 * \return int
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    // || Création de l'application et affichage d'une fenetre MainWindow
    MainWindow w;                  // ||
    w.show();                      // ||
                                   // ||
    return a.exec();               // \/     // (boucle)
}
