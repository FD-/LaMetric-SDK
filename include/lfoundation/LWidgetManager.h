#pragma once

#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QObject>

#include "LRemoteActionRequest.h"
#include "LRemoteActionResponse.h"
#include "LRemoteEvent.h"
#include "LPackageEvent.h"

class LWidgetManagerPrivate;

namespace Lm {
	enum NotificationPriority {
		NotificationPriorityNormal = 0,
		NotificationPriorityWarning = 1,
		NotificationPriorityCritical = 2
	};
	enum NotificationIconType {
		NotificationIconTypeNone = 0,
		NotificationIconTypeInfo = 1,
		NotificationIconTypeAlert = 2
	};
}

using namespace Lm;

class LWidgetManager : public QObject {
    Q_OBJECT

    enum Mode {
    	ModeUnknown = 0,
    	ModeManual = 1,
    	ModeAuto = 2,
    	ModeKiosk = 4,
    	ModeSetup = 8,
    	ModeTest = 0x10,
    	ModeScreenSaver = 0x20,
    	ModeRetail = 0x40,
    	ModeSchedule = 0x80
    };

public:
	static LWidgetManager *instance();

    LWidgetManager(QString *unknown, QObject *parent);
	bool areArrowKeysGrabbed();
	void cancelRemoteActionRequest();
	void changeFrameRate(uint rate);
	/** Returns success **/
	bool displayMeAsNotification(NotificationPriority priority);
	/** Returns success **/
	bool displayMeAsNotificationWithType(NotificationPriority priority, NotificationIconType iconType);
	void exposeInternalProperty(const QString& property);
	void exposeWebProperty(const QString& property);
	bool isAutoscrollLocked();
	Mode mode();
	void removeInternalProperty(const QString& property);
	void removeWebProperty(const QString& property);
	bool restoreFrameRate();
	bool restoreSavedMode();
	void sendRemoteActionRequest(const QString& unknown, LRemoteActionRequest *request);
	void sendRemoteActionResponse(const QString& unknown, LRemoteActionResponse *response);
	void sendRemoteEvent(LRemoteEvent *event);
	void setMode(Mode mode);
	void subscribeForEvents(const QString &events);
	void subscribeForPackageEvents(const QString &events);
	void unsubscribeFromEvents(const QString &events);
	void unsubscribeFromPackageEvents(const QString &events);
	void updateInternalProperty(const QString& property, const QVariant& value);
	void updateWebProperty(const QString& property, const QVariant& value);
	LRemoteActionRequest *widgetIdsForAction(LRemoteActionRequest *request);
	QString *widgetIdsForPackage(const QString& package);

signals:
    void modeChanged(Mode mode);
    void gotPackageEvent(LPackageEvent *event);

public slots:    
    bool autoscrollLock();
    void autoscrollUnlock();
    void grabArrowKeys();
    void releaseArrowKeys();
    void dismissMe();
    void displayMeIfPossible();
    void setDisplayPrivileged();
    void unsetDisplayPrivileged();
    void renewUserInteractionBlock();

private:
    LWidgetManagerPrivate *p;
};