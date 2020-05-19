/**
 * \file recette.cpp
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Programme permettant de stocker et modifier une recette
 *
 */

#include "Recette.h"

/**
 * \fn Recette::Recette()
 * \brief Fonction de création d'une instance d'une classe Recette
 *
 */

Recette::Recette()
{
}

/**
 * \fn QStringList Recette::getDescription()
 * \brief Fonction qui renvoie la description d'une recette
 *
 * \return QStringList qui contient la description d'une recette
 */

QStringList Recette::getDescription()
{
    return(Description);  // Renvoie le temps
}

/**
 * \fn QStringList Recette::getIngredient()
 * \brief Fonction qui renvoie la liste des ingrédient d'une recette
 *
 * \return QStringList qui contient la liste des ingrédients d'une recette
 */

QStringList Recette::getIngredient()
{
    return(Ingredient);  // Renvoie les ingrédients
}

/**
 * \fn QStringList Recette::getEtape(int numero)
 * \brief Fonction qui renvoie une étape d'une recette
 *
 * \param numero entier qui contient le numéro de l'étape courante de la recette
 * \return QStringList qui contient une étape d'une recette
 */

QStringList Recette::getEtape(int numero)
{
    QStringList EtapeAAfficher;
    EtapeAAfficher << Etapes.at(numero);
    return(EtapeAAfficher);
}

/**
 * \fn QStringList Recette::getTemps()
 * \brief Fonction qui renvoie le temps d'une recette
 *
 * \return QStringList qui contient le temps d'une recette
 */

QStringList Recette::getTemps()
{
    return(Temps);  // Renvoie le temps
}

/**
 * \fn QStringList Recette::getURL()
 * \brief Fonction qui renvoie l'URL d'une recette
 *
 * \return QStringList qui contient l'URL d'une recette
 */

QStringList Recette::getURL()
{
    return(URL);  // Renvoie l'URL
}

/**
 * \fn void Recette::setDescription(const QStringList& v)
 * \brief Fonction qui modifie la description d'une recette
 *
 * \param v const QStringList qui contient la description d'une recette
 */

void Recette::setDescription(const QStringList& v)
{
    Description << v;  // Définie une description
}

/**
 * \fn void Recette::setIngredient(const QStringList& v)
 * \brief Fonction qui modifie la liste des ingrédients d'une recette
 *
 * \param v const QStringList qui contient la liste des ingrédient d'une recette
 */

void Recette::setIngredient(const QStringList& v)
{
    Ingredient << v;  // Définie des ingrédients
}

/**
 * \fn void Recette::setEtape(const QStringList& v)
 * \brief Fonction qui modifie la liste des étapes d'une recette
 *
 * \param v const QStringList qui contient la liste des étapes d'une recette
 */

void Recette::setEtape(const QStringList& v)
{
    Etapes << v;
}

/**
 * \fn void Recette::setTemps(const QStringList& v)
 * \brief Fonction qui modifie le temps d'une recette
 *
 * \param v const QStringList qui contient le temps d'une recette
 */

void Recette::setTemps(const QStringList& v)
{
    Temps << v;  // Définie un temps
}

/**
 * \fn void Recette::setURL(const QStringList& v)
 * \brief Fonction qui modifie l'URL d'une recette
 *
 * \param v const QStringList qui contient l'URL d'une recette
 */

void Recette::setURL(const QStringList& v)
{
    URL << v;  // Définie un url
}
