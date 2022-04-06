#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QPair>
#include <QtCore/QUrl>
#include <QtNetwork/QHttpResponseHeader>

#include "LWidgetBase.h"  

class LFetchTaskPrivate;

enum LFetchTaskMethod {
    LFetchTaskMethodGet = 0,
    LFetchTaskMethodPost = 1,
    LFetchTaskMethodPut = 2,
    LFetchTaskMethodPostForm = 3,
    LFetchTaskMethodDelete = 4,
    LFetchTaskMethodCustom = 5
};

// SDK: Added helper
inline int generateNextId() {
    static int LFetchTaskNextTaskId = 0;
    return LFetchTaskNextTaskId++;
}
#define LFetchTask_NextId() LFetchTask(generateNextId())

class LFetchTask : public QObject {
    Q_OBJECT

public:
    enum LFetchTaskType {
        LFetchTaskTypeOneShot = 0,
        LFetchTaskTypeRepeated = 1
    };

    LFetchTask(int id);
    void clearHeader();
    int connectionTimeout() const;
    LFetchTaskMethod fetchMethod();
    bool headerContains(const QString& key);
    void headerInsert(const QString& key, const QString& value);
    QString headerValue(const QString& key);
    int id();
    int invokeInterval();
    bool isRetryOnErrorEnabled();
    bool isRetryWhenInternetAvailableEnabled();
    bool isRunning();
    QString *methodName();
    QMap<QString, QVariant> *postData() const;
    void removeHeaderValue(const QString& key);
    QHttpResponseHeader *responseHeader() const;
    void setConnectionTimeout(int timeout);
    void setCustomFetchMethod(const QByteArray& method);
    void setFetchMethod(LFetchTaskMethod method);
    void setFormData(const QMap<QString, QPair<QString, QVariant>>& data);
    void setInvokeInterval(int seconds);
    void setPostData(const QMap<QString, QVariant>& data);
    void setRawPostData(const QByteArray& data);
    void setRetryOnError(bool retry);
    void setRetryWhenInternetAvailable(bool retry);
    void setType(LFetchTaskType type);
    int statusCode();
    LFetchTaskType type() const;
    QUrl *url() const;

    /** Setting the URL clears the headers, so make sure you set it before adding any headers! **/
    virtual void setUrl(QUrl& url);
    virtual void setUrl(const QString& url);
    virtual void *getParsedData();

public slots:
    virtual bool prepare();
    virtual void run();

signals:
    /** Emitted at the interval set via setInvokeInterval(). The DataFetcher
	    connects on the signal to run the FetchTask. **/
    void doUpdate();
    void success(QByteArray *body);
    void failure(int code, QByteArray *body);
    void invokeIntervalChanged(int newInterval);
    void typeChanged(LFetchTaskType type);	

protected:
    /** Implement this method in your subclasses to parse the retrieved 
        data into the type returned by getParsedData() **/
    virtual void processResult(QByteArray& data);	

private:
    LFetchTaskPrivate *p;
};
