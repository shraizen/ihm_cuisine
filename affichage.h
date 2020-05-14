#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <string>
#include <QStringListModel>
#include "Recette.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Affichage; }
QT_END_NAMESPACE

class Affichage
{
private:
    Ui::Affichage *ui;

public:
    Affichage();
    ~Affichage();
    void MenuSetup();
    void AfficherDescription(Recette);
    void AfficherIngredient(Recette);
    void AfficherEtapes(Recette);
    void AfficherTemps(Recette);
    void AfficherURL(Recette);

};

#endif // AFFICHAGE_H
