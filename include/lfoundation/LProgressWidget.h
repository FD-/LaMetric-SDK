#pragma once

#include <QtGui/QWidget>
#include <QtGui/QPen>
#include <QtGui/QPaintEvent>

#include "LIcon.h"

class LProgressWidgetPrivate;

class LProgressWidget : public LWidgetBase {
    Q_OBJECT

public:
    LProgressWidget(QWidget *parent);
    int current();
    int rangeMax();
    int rangeMin();
    void setCurrent(int value);
    void setDarkPen(const QPen &pen);
    void setLightPen(const QPen &pen);
    void setRange(int rangeMin, int rangeMax);

    virtual void paintEvent(QPaintEvent *event);

signals:
	void presentationStarted();
	void presentationFinished();
    
public slots:
	void startPresentation();
	void stopPresentation();

private:
    LProgressWidgetPrivate *p;    
};