#pragma once

#include <QtCore/QString>
#include <QtCore/QFlags>
#include <QtGui/QWidget>
#include <QtGui/QResizeEvent>
#include <QtGui/QShowEvent>
#include <QtGui/QHideEvent>
#include <QtGui/AlignmentFlags>
#include <QtGui/QColor>

#include "LWidgetBase.h"  

class LTextPrivate;

class LText : public LWidgetBase {
    Q_OBJECT

public:
    LText(QWidget *parent);
    LText(const QString &text, QWidget *parent);
    void adjustSize();
    QFlags<Qt::AlignmentFlags> alignment() const;
    bool isAnimating() const;
    void setAlignment(QFlags<Qt::AlignmentFlags> alignment);
    void setColor(QColor color);
    void setText(const QString *text, bool unknown);
    QString *text() const;

    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);

signals:
	void animationFinished();

private:
    LTextPrivate *p;    
};