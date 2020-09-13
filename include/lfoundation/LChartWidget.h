#pragma once

#include <QtCore/QString>
#include <QtCore/QList>

#include <QtGui/QWidget>
#include <QtGui/QColor>
#include <QtGui/QShowEvent>
#include <QtGui/QHideEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QResizeEvent>

#include "LIcon.h"

class LChartWidgetPrivate;

class LChartWidget : public LWidgetBase {
    Q_OBJECT

public:
    LChartWidget(QWidget *parent);
    bool isPresenting();
    void resetChartBounds();
    void setBounds(int width, int height);
    void setChartColor(QColor color);
    void setChartOutlineColor(QColor color);
    void setData(const QList<int> &data);
    void setDelays(int delay1, int delay2);
    
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void hideEvent(QHideEvent *event);

signals:
	void presentationStarted();
	void presentationFinished();
    
public slots:
	void startPresentation();
	void stopPresentation();

private:
    LChartWidgetPrivate *p;    
};