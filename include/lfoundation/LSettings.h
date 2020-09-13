#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "LSettingsEditor.h"

class LSettingsPrivate;

class LSettings : public QObject {
    Q_OBJECT

public:
    LSettings(const QString &path, QObject *parent);
    LSettings(QObject *parent);
    bool contains(const QString &key);
    LSettingsEditor *edit();
    bool isEmpty();
    QVariant value(const QString& key, const QVariant& fallback);
    QVariant value(const QString& key);

signals:
	void changed();

private:
    LSettingsPrivate *p;    
};