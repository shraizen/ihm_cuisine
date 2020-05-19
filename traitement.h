/**
 * \file traitement.h
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Traitement des données du programme
 *
 */

#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QMainWindow>
#include <QTextEdit>
#include <string>
#include <QStringListModel>
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
#include <QFont>
#include "recette.h"

/*! \class Traitement
   * \brief classe permettant de traiter les données du programme
   *
   */

class Traitement
{

public:

    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe Traitement
         */

    Traitement();

public slots:

    /**
     * \fn Traitement du temps pour l'affichage
     * \brief Fonction qui renvoie le temps sous forme compréhensible et lisible
     *
     * \param QStringList qui contient le temps sous forme non lisible
     * \return QStringList qui contient le temps sous forme lisible et compréhensible
     */

    QStringList traitementVueTemps(QStringList);

};

#endif // TRAITEMENT_H
