#include "Recette.h"

Recette::Recette()
{
}

QStringList Recette::getDescription()
{
    return(Description);  // Renvoie le temps
}

QStringList Recette::getIngredient()
{
    return(Ingredient);  // Renvoie les ingrédients
}

QStringList Recette::getTemps()
{
    return(Temps);  // Renvoie le temps
}

QStringList Recette::getURL()
{
    return(URL);  // Renvoie l'URL
}

void Recette::setDescription(const QStringList& v)
{
    Description << v;  // Définie une description
}

void Recette::setIngredient(const QStringList& v)
{
    Ingredient << v;  // Définie des ingrédients
}

void Recette::setTemps(const QStringList& v)
{
    Temps << v;  // Définie un temps
}

void Recette::setURL(const QStringList& v)
{
    URL << v;  // Définie un url
}
