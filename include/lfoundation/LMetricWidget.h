#pragma once

#include <QtCore/QString>
#include <QtGui/QWidget>

#include "LWidgetBase.h"  

class LMetricWidgetPrivate;

class LMetricWidget : public LWidgetBase {
    Q_OBJECT

public:
	enum Align {
		AlignCenter = 0,
		AlignRight = 1,
		AlignLeft = 2
	};

	enum Mode {
		Mode0 = 0,
		Mode1 = 1,
		Mode2 = 2
	};

    LMetricWidget(QWidget *parent);
    void setAlignment(Align align);
    void setCharFlipDuration(int duration);
    void setCharsToIgnore(const QString& string);
    void setMode(Mode mode);
    void setText(const QString& text, bool unknown);
    void setTextColor(QColor color);
    QString *text() const;
    QColor textColor() const;

    virtual bool event(QEvent *event);

public slots:
	void animationFinished();

private:
    LMetricWidgetPrivate *p;    
};