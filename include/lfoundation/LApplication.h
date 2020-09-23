#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariantMap>

#include "LApplicationInfo.h"
#include "LWidgetFrame.h"
#include "LAssetManager.h"
#include "LBluetoothManager.h"
#include "LDeviceManager.h"
#include "LNotificationManager.h"
#include "LNetworkManager.h"
#include "LSettings.h"
#include "LWidgetManager.h"
#include "LFetchTask.h"
#include "LRemoteActionRequest.h"
#include "LRemoteActionResponse.h"
#include "LRemoteEvent.h"
#include "LDataFetcher.h"
#include "LDisplay.h"

class LApplicationPrivate;

/**
  The main class of an application has to extend from this class
**/
class LApplication : public QObject {
    Q_OBJECT

public:
    static const int ActivationReasonNormal = 0;
    static const int ActivationReasonNotification = 1;

    LApplication(int argc, char **argv);
    LApplicationInfo *appInfo(void) const;
    void *appUUID() const;
    int deactivationReason() const;

    LWidgetFrame *activeFrame() const;
    void addFrame(LWidgetFrame*);
    int frameCount() const;
    void removeAllFrames();
    void removeFrame(LWidgetFrame* frame);
    void setActiveFrame(LWidgetFrame* frame, bool unknown);
    /* Deprecated */
    void setContent(LWidgetFrame *contentFrame);

    void *getNotificationWidget() const;
    void *getRootWidget() const;
    void *contentWidget() const;

    void create();
    void destroy();

    LAssetManager *assetManager() const;
    LBluetoothManager *bluetoothManager();
    LDeviceManager *deviceManager();
    LNotificationManager* notificationManager();
    LNetworkManager* networkManager();
    LSettings* settings() const;
    LWidgetManager *widgetManager() const;
    LDisplay *display();
    LDataFetcher *dataFetcher() const;

    void exec();

    int notificationPriority() const;
    void registerForRemoteNotification(QString const&);
    void unregisterFromCustomRemoteNotifications(QString const&);
    void unregisterFromRemoteNotification();
    int windowManagerNotificationIconTypeToFoundationIconType(int);
    int windowManagerNotificationPriorityToLocalPriority(int);
    
    virtual void destroyEvent();
    /** The place to initialize and add your app’s frames **/
    virtual void createEvent();
    virtual void remoteNotificationReceived(QMap<QString,QVariant>const&);

signals:
    void renewSubscriptionOnRemoteNotifications();

public slots:
    virtual void activated();
    virtual void deactivated();
    virtual void messageReceivedEvent(QString& name, QVariantMap& params);
    /** Will be called when any of your settings values changed **/
    virtual void settingsChanged();
    /** Will be called when any of your LFetchTasks completed **/
    virtual bool dataUpdated(bool success, LFetchTask* task);
    virtual void remoteActionRequest(const LRemoteActionRequest &request);
    virtual void remoteActionResponse(const LRemoteActionResponse &response);
    virtual void remoteActionCancelRequest(const LRemoteActionRequest &action);
    virtual void remoteEventNotify(const LRemoteEvent &event);
    virtual void remoteEventSubscriberDeleted(const QString &deletedUuid);
    /** Whether your app was activated due to a notification request or 
        as part of normal operation **/
    int activationReason() const;

private:
    LApplicationPrivate* p;
    /** We get some strange initial values in the first member of subclasses without this **/
    void* unknown;
};
