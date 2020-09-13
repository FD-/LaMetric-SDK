#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

class LApplicationInfoPrivate;

class LApplicationInfo : public QObject {
    Q_OBJECT

public:
    LApplicationInfo(const QString& manifest, QObject *parent);
    bool contains(const QString& unknown);
    int getVersionCode();
    QString *getVersionStr() const;
    bool isEmpty();
    QString *package() const;
    void *settingsDescriptor() const;
    void *settingsDescriptorRules() const;
    void *settingsSchema() const;
    QString *title() const;
    QVariant *value(const QString &key) const;
    QString *value(const QString &key, const QVariant &unknown);

private:
    LApplicationInfoPrivate *p;    
};