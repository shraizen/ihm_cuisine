#ifndef RECETTE_H
#define RECETTE_H

#include <string>
#include <QStringListModel>

class Recette
{

private:
    QStringList Description;
    QStringList Ingredient;
    QStringList Etapes;
    QStringList temps;
    QStringList URL;

public:
    Recette();

    QStringList getDescription();
    QStringList getIngredient();
    QStringList getTemps();
    QStringList getURL();

    void setDescription(const QStringList&);
    void setIngredient(const QStringList&);
    void setTemps(const QStringList&);
    void setURL(const QStringList&);

    QStringList traitementVueTemps(QStringList&);

};

#endif // RECETTE_H
