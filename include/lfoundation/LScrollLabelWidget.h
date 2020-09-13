#pragma once

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtGui/QColor>
#include <QtGui/QShowEvent>
#include <QtGui/QHideEvent>

#include "LIcon.h"
#include "LWidgetBase.h"

enum TextLableScrollType {
    TextLableScrollTypePlain = 1,
    TextLableScrollTypeTypewriter = 2
};

enum TextScrollType {
    TextScrollTypeDefault = 0, // User set
    TextScrollTypePlain = 1,
    TextScrollTypeTypewriter = 2
};

class LScrollLabelWidgetPrivate;

class LScrollLabelWidget : public LWidgetBase {
    Q_OBJECT

public:
    enum Scroll {
        Scroll0 = 0,
        Scroll1 = 1
    };

    LScrollLabelWidget(QWidget *parent);
    void adjustSpeed(double speed);
    TextScrollType globalScrollTypeFromLabelScrollType(TextLableScrollType type);
    TextLableScrollType labelScrollTypeFromGlobalScrollType(TextScrollType type);

    void removeIcon(bool keepGeometry);
    LIcon *icon();
    void setIcon(const QString& path, bool unknown);
    void setIcon(const QByteArray& data, const QString& mime, bool animated);
    void setIconText(const QString &path, const QString &text, bool animated);
    void setScrollEndFlag(Scroll flag);
    void setText(const QString &text, bool unknown);
    void resetPositions();
    void setDelays(int delay1, int delay2);
    void setScrollStyle(TextLableScrollType type);
    void setTextColor(QColor color);
    void setWaitForIconAnimationEndBeforeScroll(bool wait);
    QString* text();
    int textAlignment();
    bool isAnimating() const;
    bool isIconNull() const;
    bool isScrolling() const;
    /** Returns true if the set text is too long to fit on the display as a whole. **/
    bool willScroll() const;

    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    
signals:
    void scrollAboutToStart();
    void scrollStarted();
    void scrolLAboutToFinish();
    void scrollFinished();
    
public slots:
    /* Calling this in your application's createEvent() method
    doesn't work! Call it at a later point in your app (e.g. a LWidgetFramePage's becomeVisible() signal). */
    void startScrolling();
    void stopScrolling();

private:
    LScrollLabelWidgetPrivate *p;    
};