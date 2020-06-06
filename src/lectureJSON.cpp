/**
 * \file lectureJSON.cpp
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief Programme permettant la lecture d'un fichier JSON
 *
 */

#include "headers/lectureJSON.h"

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
    /// Déclaration de variables
    QFile fichier(nomFichier);
    QJsonParseError error;
    QString texteAAfficher;

    if(fichier.open(QFile::ReadOnly)) {                                                       ///test la lecture du fichier

       QByteArray donnees = fichier.readAll();                                                /// Récupération du document JSON et de son contenu
       QJsonDocument doc = QJsonDocument::fromJson(donnees, &error);

       if(error.error != QJsonParseError::NoError)                                            /// Si la récupération des données contient une erreur
       {
           qCritical() << "Impossible d’interpréter le fichier : " << error.errorString();
       }
       else                                                                                   /// Sinon :
       {
           /// Déclaration de variables
           QJsonObject obj=doc.object();
           QJsonValue val = obj.value("recipeIngredient");
           QStringList listeDescription;
           QStringList listeIngredient;
           QStringList listeEtape;
           QStringList listeInformation;
           QStringList temps ;
           QStringList URL;
           QJsonArray valArray = val.toArray();

           ///Récupère la description
           listeDescription << "\n" + (obj.value("name")).toString() + "\n"
                            << "\nDescription : \n" << (obj.value("description")).toString();

           /// Récupère les ingrédient
           listeIngredient << "Ingredients : \n";
           for (auto value: valArray)
           {
               listeIngredient << "_ " + value.toString();
           }

           /// Récupère les instructions
           val = obj.value("recipeInstructions");
           valArray = val.toArray();
           int compteur = 0;
           for (auto value: valArray)
           {
               compteur ++;
               listeEtape << "instruction n°" + QString::number(compteur) + " :\n" + value.toString();
           }

           /// Récupère les informations complémentaires
           listeInformation << "Image : " << (obj.value("image")).toString();
           listeInformation << "Catégorie de recette : " << (obj.value("recipeCategory")).toString();
           listeInformation << "Tag : " << (obj.value("keywords")).toString();
           double tmp = Trait.traitementNombreJson(obj, "recipeYield");
           listeInformation << "Rendement estimé : " << QString::number(tmp) + " €";

           /// Récupère les temps
           temps << (obj.value("prepTime")).toString();
           temps << (obj.value("cookTime")).toString();
           temps << (obj.value("totalTime")).toString();
           URL << "URL : " << (obj.value("url")).toString();

           /// Met à jour les données de la recette
           R.setDescription(listeDescription);
           R.setIngredient(listeIngredient);
           R.setEtape(listeEtape);
           R.setInformation(listeInformation);
           R.setTemps(temps);
           R.setURL(URL);
       }
    }
    else {
        qCritical() << "Impossible d’ouvrir le fichier : " << error.errorString(); ///Erreur de lecture du fichier
    }
}
