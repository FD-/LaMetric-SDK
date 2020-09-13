#pragma once

#include <QtCore/QString>
#include <QtCore/QFlags>
#include <QtGui/QWidget>
#include <QtGui/QColor>
#include <QtGui/WindowType>

#include "LWidgetBase.h"  

class LLabelPrivate;

class LLabel : public LWidgetBase {
    Q_OBJECT

public:
    LLabel(QWidget *parent);
    LLabel(const QString &text, QWidget *parent, QFlags<Qt::WindowType> flags);
    bool isBlinking();
    void setBlink(bool blink);
    void setBlinkParams(int param1, int param2, int param3);
    void setTextColor(QColor color);
    QColor textColor();

private:
    LLabelPrivate *p;    
};