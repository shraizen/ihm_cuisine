/**
 * \file traitement.cpp
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Programme permettant de traiter les données du programme
 *
 */

#include "headers/traitement.h"

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
    QString tempsPreparation = temps[0];                                                                 /// Récupère le temps de préparation
    QString tempsCuisson = temps[1];                                                                     /// Récupère le temps de cuisson
    int tempsTotalHeures;                                                                                /// Choix de le calculer car le temps total n'est pas toujours spécifié
    int tempsTotalMinutes;                                                                               /// Choix de le calculer car le temps total n'est pas toujours spécifié
    QStringList TexteVueTemps;
    QRegExp CalcHeures("([0-9]*)H");                                                                     /// Expréssion régulière pour récupérer les heures
    QRegExp CalcMinutes("([0-9]*)M");                                                                    /// Expréssion régulière pour récupérer les minutes
    /// Récupère le temps de préparation
    CalcMinutes.indexIn(tempsPreparation);
    CalcHeures.indexIn(tempsPreparation);
    TexteVueTemps << "  Temps de Préparation : " + CalcHeures.cap(1) + " heures et " + CalcMinutes.cap(1) + " minutes  ";
    /// Pour calculer le temps total
    tempsTotalHeures = (CalcHeures.cap(1)).toInt();
    tempsTotalMinutes = (CalcMinutes.cap(1)).toInt();
    /// Récupère le temps de cuisson
    CalcMinutes.indexIn(tempsCuisson);
    CalcHeures.indexIn(tempsCuisson);
    TexteVueTemps << "  Temps de Cuisson : " + CalcHeures.cap(1) + " heures et " + CalcMinutes.cap(1) + " minutes  ";
    /// Calcule le temps total
    tempsTotalHeures += (CalcHeures.cap(1)).toInt();
    tempsTotalMinutes += (CalcMinutes.cap(1)).toInt();
    TexteVueTemps << "  Temps total : " + QString::number(tempsTotalHeures) + " heures et " + QString::number(tempsTotalMinutes) + " minutes  ";/// Récupère le temps total
    return(TexteVueTemps);
}

/**
 * \fn double Traitement::traitementNombreJson(QJsonObject obj, QString param)
 * \brief Fonction qui traite un nombre d'un fichier Json pour le recupérer dans un double
 *
 * \param obj qui contient un QJsonObject
 * \param param qui contient le nom du nombre à récupérer
 * \return double qui contient un nombre
 */

double Traitement::traitementNombreJson(QJsonObject obj, QString param)
{
    QJsonValue recipeYield = obj.value(param);   /// Création d'une QJsonValue contenant le valeur du paramètre indiquer (param)
    double tmp = recipeYield.toDouble();        /// Convertie la valeur en double
    return(tmp);                                /// Renvoie un double
}

