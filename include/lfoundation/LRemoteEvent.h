#pragma once

#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QFlags>

class LRemoteEventPrivate;

namespace Lm {
	enum EventSendType {
		EventSendTypeDefault = 2
	};
}

class LRemoteEvent {
public:
	LRemoteEvent();
	LRemoteEvent(const LRemoteEvent& other);
	LRemoteEvent(const QString& event, const QMap<QString, QVariant> &params, const QFlags<Lm::EventSendType> flags);
	void addSendType(Lm::EventSendType type);
	Lm::EventSendType checkSendType(Lm::EventSendType type) const;
	int eventId() const;
	QFlags<Lm::EventSendType> flags() const;
	QMap<QString, QVariant> *params() const;
	Lm::EventSendType removeSendType(Lm::EventSendType type);

private:
	LRemoteEventPrivate *p;
};