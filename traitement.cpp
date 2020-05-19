/**
 * \file traitement.cpp
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Programme permettant de traiter les données du programme
 *
 */

#include "traitement.h"

/**
 * \fn Traitement::Traitement()
 * \brief Fonction de création d'une instance de la classe Traitement
 *
 */

Traitement::Traitement()
{
}

/**
 * \fn QStringList Traitement::traitementVueTemps(QStringList temps)
 * \brief Fonction qui renvoie le temps sous forme compréhensible et lisible
 *
 * \param temps QStringList qui contient le temps sous forme non lisible
 * \return QStringList qui contient le temps sous forme lisible et compréhensible
 */

QStringList Traitement::traitementVueTemps(QStringList temps)
{
    QString tempsPreparation = temps[0];                                                                 // Récupère le temps de préparation
    QString tempsCuisson = temps[1];                                                                     // Récupère le temps de cuisson
    int tempsTotalHeures;                                                                                // Choix de le calculer car le temps total n'est pas toujours spécifié
    int tempsTotalMinutes;                                                                               // Choix de le calculer car le temps total n'est pas toujours spécifié
    QStringList TexteVueTemps;
    QRegExp CalcHeures("([0-9]*)H");                                                                     // Expréssion régulière pour récupérer les heures
    QRegExp CalcMinutes("([0-9]*)M");                                                                    // Expréssion régulière pour récupérer les minutes
    CalcMinutes.indexIn(tempsPreparation);                                                                                                      // || Récupère le temps de préparation
    CalcHeures.indexIn(tempsPreparation);                                                                                                       // ||
    TexteVueTemps << "  Temps de Préparation : " + CalcHeures.cap(1) + " heures et " + CalcMinutes.cap(1) + " minutes  ";                       // \/
    tempsTotalHeures = (CalcHeures.cap(1)).toInt();        // || Pour calculer le temps total
    tempsTotalMinutes = (CalcMinutes.cap(1)).toInt();      // \/
    CalcMinutes.indexIn(tempsCuisson);                                                                                                          // || Récupère le temps de cuisson
    CalcHeures.indexIn(tempsCuisson);                                                                                                           // ||
    TexteVueTemps << "  Temps de Cuisson : " + CalcHeures.cap(1) + " heures et " + CalcMinutes.cap(1) + " minutes  ";                           // \/
    tempsTotalHeures += (CalcHeures.cap(1)).toInt();       // || Pour calculer le temps total
    tempsTotalMinutes += (CalcMinutes.cap(1)).toInt();     // \/
    TexteVueTemps << "  Temps total : " + QString::number(tempsTotalHeures) + " heures et " + QString::number(tempsTotalMinutes) + " minutes  ";// Récupère le temps total
    return(TexteVueTemps);
}

