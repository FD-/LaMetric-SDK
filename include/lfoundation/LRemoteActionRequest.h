#pragma once

#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QVariant>

class LRemoteActionRequestPrivate;

class LRemoteActionRequest {
public:
	LRemoteActionRequest(const LRemoteActionRequest& other);
	LRemoteActionRequest(const QString& action, const QMap<QString, QVariant> &params);
	LRemoteActionRequest *operator=(const LRemoteActionRequest& other);
	QMap<QString, QVariant> *params() const;
	void setActionName(const QString& name);
	void setId(long long id);
	void setParams(const QMap<QString, QVariant> &params);

private:
	LRemoteActionRequestPrivate *p;
};