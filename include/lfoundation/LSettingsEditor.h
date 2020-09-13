#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

class LSettingsEditorPrivate;
class LSettings;

class LSettingsEditor : public QObject {
    Q_OBJECT

public:
    LSettingsEditor(LSettings *settings, QObject *parent);
    LSettingsEditor(QObject *parent);
    bool commit();
    void edit();
    void insertKeyValue(const QString& key, const QVariant &value);

private:
    LSettingsEditorPrivate *p;    
};