#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#include "LWidgetBase.h"  

class LNetworkInterfacePrivate;

class LNetworkInterface : public QObject {
    Q_OBJECT

public:
	enum State {
		StateUnknown = 0,
		StateConnected = 1,
		StateDisconnected = 2
	};

	enum Mode {
		ModeUnknown = 0,
		ModeMaster = 1,
		ModeDhcp = 2,
		ModeStatic = 3
	};

	LNetworkInterface();
	LNetworkInterface(const QString& name, QObject *parent);
	LNetworkInterface(const QString& name, QMap<QString, QVariant>& properties, QObject *parent);
	LNetworkInterface(const LNetworkInterface& other);
	bool isActive() const;
	Mode mode() const;
	QString *name() const;
	LNetworkInterface *operator=(const LNetworkInterface& other);
	State state() const;

    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(bool active READ isActive)
    Q_PROPERTY(Mode mode READ mode)

private:
    LNetworkInterfacePrivate *p;    
};