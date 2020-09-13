#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

#include "LIcon.h"

class LDeviceManagerPrivate;
class LVersion;
class LLightSensorManager;

class LDeviceManager : public QObject {
    Q_OBJECT

public:
    LDeviceManager(QObject *parent);
    QString *apiKey() const;
    LVersion *firmwareVersion();
    LLightSensorManager *lightSensorManager();
    QString *locale() const;
	QString *mode() const;
	QString *model() const;
	QString *name() const;
	void restoreUserVolumeLevel();
	QString *serialNumber();
	void setSystemVolume(int volume);
	void setVolume(int volume);
	int systemVolume();
	QString *timeZone();
	int timeZoneOffset();
	int volume();

signals:
	void timeZoneChanged(const QString& timeZone);
	void timeZoneOffsetChanged(int offset);
	void localeChanged(const QString& locale);
	void nameChanged(const QString& name);
	void ready();
	void modeChanged(const QString& mode);
	void apiKeyChanged(const QString& apiKey);
	void systemVolumeChanged(int volume);
	void volumeChanged(int volume);

private:
    LDeviceManagerPrivate *p;    
};