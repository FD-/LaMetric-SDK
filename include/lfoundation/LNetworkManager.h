#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>

#include "LNetworkInterface.h"

class LNetworkManagerPrivate;

class LNetworkManager : public QObject {
    Q_OBJECT

public:
	LNetworkManager(QObject *parent);
    bool isInternetAvailable() const;

signals:
	void networkStateChanged(QMap<QString, LNetworkInterface>& interfaces);
	void networkStateChanged(LNetworkInterface *interface);
	void internetStateChanged(bool connected);

private:
    LNetworkManagerPrivate *p;    
};