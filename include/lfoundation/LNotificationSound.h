#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QWidget>

class LNotificationSoundPrivate;

typedef unsigned int NotificationSoundId;
enum SoundCategory {
    SoundCategorySystem = 1,
    SoundCategoryAlarms = 2,
    SoundCategoryNotifications = 3,
};
typedef unsigned int NotificationSoundError;

class LNotificationSound : public QObject {
    Q_OBJECT

public:
    /* Apparently, a new LNotificationSound has to be created before an existing one can be deleted! Do something like

        LNotificationSound *newNotificationSound = createFromString("notification", "cash", this);
        delete notificationSound;
        notificationSound = newNotificationSound;
        
    Otherwise, the new sound won't play.  */
    static LNotificationSound *createFromId(NotificationSoundId id, QObject *parent);
    static LNotificationSound *createFromString(SoundCategory category, const QString &name, QObject *parent);
    static LNotificationSound *createFromString(const QString &category, const QString &name, QObject *parent);
    static NotificationSoundId soundIdFromString(const QString &category, const QString &name);

    LNotificationSound(NotificationSoundId id, QObject *parent);
    LNotificationSound(const QString &id, QObject *parent);
    bool isPlaying();
    bool isValid();
    const QString *name();

signals:
    void error(NotificationSoundError err);
    void stopped();

public slots:
    void play(int repeatCount);
    void stop();
    void seek(float duration);

private:
    LNotificationSoundPrivate *p;
};
