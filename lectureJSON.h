/**
 * \file lectureJSON.h
 * \author Masset Eliot - Pesquet Cedric
 *
 * \brief lecture d'un fichier JSON
 *
 */

#ifndef LECTUREJSON_H
#define LECTUREJSON_H

#include <QJsonParseError>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QFile>
#include "recette.h"

/*! \class LectureJSON
   * \brief classe permettant la lecture d'un fichier JSON
   *
   */

class LectureJSON
{

public:

    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe LectureJSON
         */

    LectureJSON();

public slots:

    /**
     * \fn Lecteur de fichiers JSON
     * \brief Fonction de lecture d'une fichier JSON.
     *
     * \param QString qui contient le nom du fichier JSON à lire.
     * \param classe du nom de recette en passage par adresse, qui contient la recette à lire.
     */

    void Lecture(QString, Recette&);

};

#endif // LECTUREJSON_H
