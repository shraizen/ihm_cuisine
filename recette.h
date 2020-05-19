/**
 * \file recette.h
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Recette de cuisine
 *
 */

#ifndef RECETTE_H
#define RECETTE_H

#include <string>
#include <QStringListModel>

/*! \class Recette
   * \brief classe permettant de stocker et modifier une recette de cuisine
   *
   */

class Recette
{

private:
    QStringList Description; /*!< QStringList contenant la description*/
    QStringList Ingredient; /*!< QStringList contenant la liste des Ingrédient*/
    QStringList Etapes; /*!< QStringList contenant la liste des Etapes*/
    QStringList Temps; /*!< QStringList contenant le temps*/
    QStringList URL; /*!< QStringList contenant l'URL*/

public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe Recette
         */
    Recette();

    /**
     * \fn getter Description
     * \brief Fonction qui renvoie la description d'une recette
     *
     * \return QStringList qui contient la description d'une recette
     */

    QStringList getDescription();

    /**
     * \fn getter Ingredient
     * \brief Fonction qui renvoie la liste des ingrédient d'une recette
     *
     * \return QStringList qui contient la liste des ingrédients d'une recette
     */

    QStringList getIngredient();

    /**
     * \fn getter Etape
     * \brief Fonction qui renvoie une étape d'une recette
     *
     * \param entier qui contient le numéro de l'étape courante de la recette
     * \return QStringList qui contient une étape d'une recette
     */

    QStringList getEtape(int);

    /**
     * \fn getter temps
     * \brief Fonction qui renvoie le temps d'une recette
     *
     * \return QStringList qui contient le temps d'une recette
     */

    QStringList getTemps();

    /**
     * \fn getter URL
     * \brief Fonction qui renvoie l'URL d'une recette
     *
     * \return QStringList qui contient l'URL d'une recette
     */

    QStringList getURL();

    /**
     * \fn setter Description
     * \brief Fonction qui modifie la description d'une recette
     *
     * \param const QStringList qui contient la description d'une recette
     */

    void setDescription(const QStringList&);

    /**
     * \fn setter Ingredient
     * \brief Fonction qui modifie la liste des ingrédients d'une recette
     *
     * \param const QStringList qui contient la liste des ingrédient d'une recette
     */

    void setIngredient(const QStringList&);

    /**
     * \fn setter Etape
     * \brief Fonction qui modifie la liste des étapes d'une recette
     *
     * \param const QStringList qui contient la liste des étapes d'une recette
     */

    void setEtape(const QStringList&);

    /**
     * \fn setter Temps
     * \brief Fonction qui modifie le temps d'une recette
     *
     * \param const QStringList qui contient le temps d'une recette
     */

    void setTemps(const QStringList&);

    /**
     * \fn setter URL
     * \brief Fonction qui modifie l'URL d'une recette
     *
     * \param const QStringList qui contient l'URL d'une recette
     */

    void setURL(const QStringList&);

};

#endif // RECETTE_H