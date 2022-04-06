#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

class LDisplayPrivate;

namespace Lm {
	typedef unsigned int DisplayFeature;
}

class LDisplay : public QObject {
    Q_OBJECT

public:
    static LDisplay *instance();

    LDisplay(QObject *parent);
    void *firmwareVersion() const;
    void flushBufferAndDisablBuffering();
    bool hasFeature(DisplayFeature feature);
    int height() const;
    bool isFeatureEnabled(DisplayFeature feature);
    QString *name() const;
    unsigned int scanRate() const;
    void setFeatureEnabled(DisplayFeature feature, bool enabled);
    void setScanRate(unsigned int rate);
    int width() const;

signals:
	void scanRateChanged();

private:
    LDisplayPrivate *p;    
};
