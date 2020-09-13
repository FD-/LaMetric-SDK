#pragma once

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtGui/QWidget>
#include <QtGui/QHideEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QShowEvent>

#include "LWidgetBase.h"  

class LIconPrivate;

class LIcon : public LWidgetBase {
    Q_OBJECT

public:
    LIcon(QWidget *parent);
    LIcon(const QString &icon, QWidget *parent);
    void adjustSize();
    bool hasAnimation() const;
    bool hasContent() const;
    bool isAnimating() const;
    bool isIconAnimationInProgress() const;
    bool isNull() const;
    void removeIcon(bool unknown);
    void restartIconAnimation();
    void setIcon(const QString& path, bool animated);
    void setIcon(const QByteArray& data, const QString& mime, bool animated);

    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);

signals:
	void animationFinished();
	void startedIconAnimation();
	void stopedIconAnimation();
	void iconAnimationCycleFinished();

private:
    LIconPrivate *p;    
};