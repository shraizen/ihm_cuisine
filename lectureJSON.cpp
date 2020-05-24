/**
 * \file lectureJSON.cpp
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Programme permettant la lecture d'un fichier JSON
 *
 */

#include "lectureJSON.h"

/**
 * \fn LectureJSON::LectureJSON()
 * \brief Fonction de création d'une nouvelle instance de la classe LectureJSON
 *
 */

LectureJSON::LectureJSON()
{

}

/**
 * \fn void LectureJSON::Lecture(QString nomFichier, Recette& R)
 * \brief Fonction de lecture d'une fichier JSON.
 *
 * \param nomFichier QString qui contient le nom du fichier JSON à lire.
 * \param R classe du nom de recette en passage par adresse, qui contient la recette à lire.
 */

void LectureJSON::Lecture(QString nomFichier, Recette& R)
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
           QJsonValue val = obj.value("recipeIngredient");                                    // ||
           QStringList listeDescription;                                                      // ||
           QStringList listeIngredient;                                                       // ||
           QStringList listeEtape;                                                            // ||
           QStringList listeInformation;                                                      // ||
           QStringList temps ;                                                                // ||
           QStringList URL;                                                                   // ||
           QJsonArray valArray = val.toArray();                                               // \/


           listeDescription << "\n" + (obj.value("name")).toString() + "\n"
                            << "\nDescription : \n" << (obj.value("description")).toString(); //Récupère la description

           listeIngredient << "Ingredients : \n";                                             // || Récupère les ingrédient
           for (auto value: valArray)                                                         // ||
           {                                                                                  // ||
               listeIngredient << "_ " + value.toString();                                    // ||
           }                                                                                  // \/

           val = obj.value("recipeInstructions");                                                     // || Récupère les instructions
           valArray = val.toArray();                                                                  // ||
           int compteur = 0;                                                                          // ||
           for (auto value: valArray)                                                                 // ||
           {                                                                                          // ||
               compteur ++;                                                                           // ||
               listeEtape << "instruction n°" + QString::number(compteur) + " :\n" + value.toString();// ||
           }                                                                                          // \/

           listeInformation << "Image : " << (obj.value("image")).toString();                           // || Récupère les informations complémentaires
           listeInformation << "Catégorie de recette : " << (obj.value("recipeCategory")).toString();   // ||
           listeInformation << "Tag : " << (obj.value("keywords")).toString();                          // ||
           double tmp = Trait.traitementNombreJson(obj, "recipeYield");                                 // ||
           listeInformation << "Rendement estimé : " << QString::number(tmp) + " €";                    // \/

           temps << (obj.value("prepTime")).toString();                                       // ||Récupère les temps
           temps << (obj.value("cookTime")).toString();                                       // ||
           temps << (obj.value("totalTime")).toString();                                      // \/
           URL << "URL : " << (obj.value("url")).toString();                                  // Récupère l'URL

           R.setDescription(listeDescription);                                                // || Met à jour les données de la recette
           R.setIngredient(listeIngredient);                                                  // ||
           R.setEtape(listeEtape);                                                            // ||
           R.setInformation(listeInformation);                                                // ||
           R.setTemps(temps);                                                                 // ||
           R.setURL(URL);                                                                     // \/
       }
    }
    else {
        qCritical() << "Impossible d’ouvrir le fichier : " << error.errorString();
    }
}
