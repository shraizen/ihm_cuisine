#include "mainwindow.h"
#include <QApplication>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonValue>
#include <QJsonArray>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //QString nomFichier = w.ouvrirFichier();

    QFile fichier("C:/Users/33783/Desktop/Projet\ Qt/RecipesReader/mousse.json");
    //QFile fichier(nomFichier);
    QJsonParseError error;

    if(fichier.open(QFile::ReadOnly)) {
       QByteArray donnees = fichier.readAll();

       QJsonDocument doc = QJsonDocument::fromJson(donnees, &error);
       if(error.error != QJsonParseError::NoError)
       {
           qCritical() << "Impossible d’interpréter le fichier : " << error.errorString();
       }
       else
       {

           QJsonObject obj=doc.object();

           qDebug() << "Nom " << (obj.value("name")).toString();

           qDebug() << "Description : " << (obj.value("description")).toString();
           QJsonValue val = obj.value("recipeIngredient");

           QJsonArray valArray = val.toArray();
           for (auto value: valArray)
               qDebug() << "ingredient " << value.toString();

           val = obj.value("recipeInstructions");
           valArray = val.toArray();
           for (auto value: valArray)
               qDebug() << "instruction " << value.toString();

           qDebug() << "Total time : " << (obj.value("totalTime")).toString();
           qDebug() << "URL : " << (obj.value("url")).toString();

       }
    }
    else {
    }

    return a.exec();
}
