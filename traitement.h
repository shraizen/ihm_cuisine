#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QMainWindow>
#include <QTextEdit>
#include <string>
#include <QStringListModel>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonValue>
#include <QJsonArray>
#include <QStringListModel>
#include <QListView>
#include <QLabel>
#include <QFont>
#include "Recette.h"

class Traitement
{

public:

    Traitement();

public slots:

    QStringList traitementVueTemps(QStringList);
    void LireFichier(QString, Recette&);

};

#endif // TRAITEMENT_H
