#include "traitement.h"

Traitement::Traitement()
{
}

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
    TexteVueTemps << "Temps de Préparation : " << CalcHeures.cap(1) << "heures et " << CalcMinutes.cap(1) << "minutes";                         // \/
    tempsTotalHeures = (CalcHeures.cap(1)).toInt();        // || Pour calculer le temps total
    tempsTotalMinutes = (CalcMinutes.cap(1)).toInt();      // \/
    CalcMinutes.indexIn(tempsCuisson);                                                                                                          // || Récupère le temps de cuisson
    CalcHeures.indexIn(tempsCuisson);                                                                                                           // ||
    TexteVueTemps << "Temps de Cuisson : " << CalcHeures.cap(1) << "heures et " << CalcMinutes.cap(1) << "minutes";                             // \/
    tempsTotalHeures += (CalcHeures.cap(1)).toInt();       // || Pour calculer le temps total
    tempsTotalMinutes += (CalcMinutes.cap(1)).toInt();     // \/
    TexteVueTemps << "Temps total : " << QString::number(tempsTotalHeures) << "heures et " << QString::number(tempsTotalMinutes) << "minutes";  // Récupère le temps total
    return(TexteVueTemps);
}

void Traitement::LireFichier(QString nomFichier, Recette& R)
{

    QFile fichier(nomFichier);                          // || Déclaration de variables
    QJsonParseError error;                              // ||
    QString texteAAfficher;                             // \/

    if(fichier.open(QFile::ReadOnly)) {                                                       //test la lecture du fichier

       QByteArray donnees = fichier.readAll();                                                // || Récupération du document JSON et de son contenu
       QJsonDocument doc = QJsonDocument::fromJson(donnees, &error);                          // \/

       if(error.error != QJsonParseError::NoError)                                            // || Si la récupération des données contient une erreur
       {                                                                                      // ||
           qCritical() << "Impossible d’interpréter le fichier : " << error.errorString();    // ||
       }                                                                                      // \/
       else                                                                                   // Sinon :
       {

           QJsonObject obj=doc.object();                                                      // || Déclaration de variables
           QStringList listeDescription;                                                      // ||
           QStringList listeIngredient;                                                       // ||
           QStringList temps;                                                                 // ||
           QStringList URL;                                                                   // ||
           QJsonValue val = obj.value("recipeIngredient");                                    // ||
           QJsonArray valArray = val.toArray();                                               // \/


           listeDescription << "Nom : \n" << (obj.value("name")).toString()
                            << "\nDescription : \n" << (obj.value("description")).toString(); //Récupère la description

           listeIngredient << "ingredients : ";                                               // || Récupère les ingrédient
           for (auto value: valArray)                                                         // ||
           {                                                                                  // ||
               listeIngredient << "_ " + value.toString();                                    // ||
           }                                                                                  // \/

           val = obj.value("recipeInstructions");                                             // || Récupère les instructions
           valArray = val.toArray();                                                          // ||
           for (auto value: valArray)                                                         // ||
           {                                                                                  // ||
               qDebug() << "instruction " << value.toString();                                // ||
           }                                                                                  // \/

           temps << (obj.value("prepTime")).toString();                                       // ||Récupère les temps
           temps << (obj.value("cookTime")).toString();                                       // ||
           temps << (obj.value("totalTime")).toString();                                      // \/
           URL << "URL : " << (obj.value("url")).toString();                                  // Récupère l'URL

           R.setDescription(listeDescription);                                                // || Met à jour les données de la recette
           R.setIngredient(listeIngredient);                                                  // ||
           R.setTemps(temps);                                                                 // ||
           R.setURL(URL);                                                                     // \/
       }
    }
    else {
        qDebug() << "lol";
    }
}
