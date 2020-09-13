#pragma once

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtGui/QWidget>

#include "LNotificationSound.h"

class LNotificationPrivate;

enum NotificationAnimationType {
    NotificationAnimationTypeUnknown = 0,
    NotificationAnimationTypeFade = 1,
    NotificationAnimationTypeMoveUp = 2,
    NotificationAnimationTypeMoveDown = 3,
    NotificationAnimationTypeMoveLeft = 4,
    NotificationAnimationTypeMoveRight = 5
};

class LNotification : public QObject {
    Q_OBJECT

public:
    LNotification(int unknown, QObject *parent);
  	NotificationAnimationType apearAnimationType();
    NotificationAnimationType disapearAnimationType();
    QFile *icon();
    int id();
    QString* imageResource() const;
    QString* messageText() const;
    LNotificationSound *notificationSound() const;
    QFile *notificationSoundFile() const;
    int notificationSoundRepeatCount();
    void setApearAnimationType(const NotificationAnimationType &type);
    void setDisapearAnimationType(NotificationAnimationType type);
    void setIcon(QFile *file);
    void setImageResource(QString *resource);
    void setMessageText(const QString &text);
    void setNotificationSound(NotificationSoundId id, int unknown);
    void setNotificationSound(const QString &sound, int unknown);
    void setWidget(QWidget *widget);
    QWidget *widget();
    
private:
	LNotificationPrivate *p;
};