#pragma once

#include <QtCore/QString>
#include <QtGui/QWidget>

#include "LNotification.h"
#include "LNotificationSound.h"

class LNotificationManagerPrivate;

class LNotificationManager : public QObject {
    Q_OBJECT

    enum NotificationType {
    	NotificationTypeWait = 0,
		NotificationTypeNoInternet = 1
    };

public:
    static LNotificationSound *notificationSoundById(SoundCategory category, QString *id);

    LNotificationManager(LApplication *application);
    LNotification *createBuiltinNotification(int unknown, NotificationType type);
    LNotification *createIconTextNotification(int unknown, const QString &icon, const QString &text);
    LNotification *createNotification(int unknown);
    LNotification *createSoundNotification(int unknown, NotificationSoundId sound);
    LNotification *createTextNotification(int unknown, const QString &text);
    LNotification *createWaitNotification(int unknown);
    void dismiss(LNotification *notification);
    void dismiss(int id);
    void dismissAll();
    void notify(LNotification *notification);
    void notify(LNotification *notification, int duration);

private:
	LNotificationManagerPrivate *p;
};
