#include "Recette.h"

Recette::Recette()
{

}

QStringList Recette::getDescription()
{
    return(Description);
}

QStringList Recette::getIngredient()
{
    return(Ingredient);
}

QStringList Recette::getTemps()
{
    QStringList Temps;
    Temps = traitementVueTemps(temps);
    return(Temps);
}

QStringList Recette::getURL()
{
    return(URL);
}

void Recette::setDescription(const QStringList& v)
{
    Description << v;
}

void Recette::setIngredient(const QStringList& v)
{
    Ingredient << v;
}

void Recette::setTemps(const QStringList& v)
{
    temps << v;
}

void Recette::setURL(const QStringList& v)
{
    URL << v;
}

QStringList Recette::traitementVueTemps(QStringList& temps)
{
    QString tempsPreparation = temps[0];
    QString tempsCuisson = temps[1];
    int tempsTotalHeures;                                                                                //Choix de le calculer car le temps total n'est pas toujours spécifié
    int tempsTotalMinutes;                                                                               //Choix de le calculer car le temps total n'est pas toujours spécifié
    QStringList TexteVueTemps;
    QRegExp CalcHeures("([0-9]*)H");
    QRegExp CalcMinutes("([0-9]*)M");
    CalcMinutes.indexIn(tempsPreparation);
    CalcHeures.indexIn(tempsPreparation);
    TexteVueTemps << "Temps de Préparation : " << CalcHeures.cap(1) << "heures et " << CalcMinutes.cap(1) << "minutes";
    tempsTotalHeures = (CalcHeures.cap(1)).toInt();
    tempsTotalMinutes = (CalcMinutes.cap(1)).toInt();
    CalcMinutes.indexIn(tempsCuisson);
    CalcHeures.indexIn(tempsCuisson);
    TexteVueTemps << "Temps de Cuisson : " << CalcHeures.cap(1) << "heures et " << CalcMinutes.cap(1) << "minutes";
    tempsTotalHeures += (CalcHeures.cap(1)).toInt();
    tempsTotalMinutes += (CalcMinutes.cap(1)).toInt();
    TexteVueTemps << "Temps total : " << QString::number(tempsTotalHeures) << "heures et " << QString::number(tempsTotalMinutes) << "minutes";
    return(TexteVueTemps);
}
