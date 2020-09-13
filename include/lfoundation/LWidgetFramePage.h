#pragma once

#include <QtGui/QWidget>
#include <QtGui/QShowEvent>
#include <QtGui/QHideEvent>

#include "LWidgetBase.h"
#include "LWidgetFrame.h"

class LWidgetFramePage : public LWidgetBase {
    Q_OBJECT

public:    
    LWidgetFramePage(QWidget *parent);
    LWidgetFramePage(LWidgetFrame *parent);
    int displayDuration();
    bool isSkipped();
    void setDisplayDuration(int duration);
    void setSkip(bool skip);
    bool shouldSkip();

    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);

signals:
    void becomeVisible();
    void becomeInvisible();
    void skipChanged();

private:
    void *unknown;
};