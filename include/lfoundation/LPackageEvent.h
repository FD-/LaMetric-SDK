#pragma once

#include <QtCore/QString>

class LPackageEvent {
public:
	enum EventType {
		EventTypeWidgetDeleted = 0,
		EventTypeWidgetCreated = 1
	};

	LPackageEvent();
	LPackageEvent(const QString& packageName, const QString& widgetId, EventType type);
	QString *packageName() const;
	void setEventType(const EventType& type);
	void setPackageName(const QString& packageName);
	void setWidgetId(const QString& widgetId);
	QString *widgetId() const;

private:
	LRemoteEventPrivate *p;
};