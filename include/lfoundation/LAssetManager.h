#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QFile>

#include "LApplication.h"

class LAssetManagerPrivate;

class LAssetManager : public QObject {
    Q_OBJECT

public:
	LAssetManager(const QString &unknown, LApplication *app);
	QString *assetFilePath(const QString &asset);
	QList<QString> assets();
	QFile *open(const QString &asset);

private:
    LAssetManagerPrivate *p;    
};