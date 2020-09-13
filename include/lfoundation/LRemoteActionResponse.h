#pragma once

#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QVariant>

#include "LRemoteActionRequest.h"

class LRemoteActionResponsePrivate;

class LRemoteActionResponse {
public:
	enum Result {
		ResultFailure = 0,
		ResultSuccess = 1
	};

	LRemoteActionResponse(const LRemoteActionResponse& other);
	LRemoteActionResponse(const LRemoteActionRequest &request, Result result, const QMap<QString, QVariant> &params);
	QMap<QString, QVariant> *params() const;
	QString *remoteActionName() const;
	long long remoteActionRequestId();
	Result result();
	void setParams(const QMap<QString, QVariant> &params);
	void setRemoteActionName(const QString& name);
	void setRemoteActionRequestId(long long id);
	void setResult(Result r);

private:
	LRemoteActionResponsePrivate *p;
};