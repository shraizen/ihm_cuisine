/**
 * \file traitement.h
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Traitement des données du programme
 *
 */

#ifndef TRAITEMENT_H
#define TRAITEMENT_H


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

    /**
     * \fn Traitement d'une données(nombre) d'un fichier JSon
     * \brief Fonction qui traite un nombre d'un fichier Json pour le recupérer dans un double
     *
     * \param obj qui contient un QJsonObject
     * \param param qui contient le nom du nombre à récupérer
     * \return double qui contient un nombre
     */

    double traitementNombreJson(QJsonObject, QString);

};

#endif // TRAITEMENT_H
