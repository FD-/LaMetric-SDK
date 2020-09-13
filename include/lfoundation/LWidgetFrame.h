#pragma once

#include <QtGui/QWidget>
#include <QtGui/QKeyEvent>
#include <QtGui/QShowEvent>
#include <QtGui/QHideEvent>

#include "LWidgetBase.h"

class LWidgetFramePrivate;
class LApplication;
class LWidgetFramePage;

class LWidgetFrame : public LWidgetBase {
    Q_OBJECT

public:
	LWidgetFrame(LApplication *app, QWidget *parent);

    LApplication *application();
    void *rootPageContainer();

    void addPage(LWidgetFramePage *page, int displayDuration);
    void removePage(LWidgetFramePage *page);
    void removePageAtIndex(int index);

    bool autoPageRolling();
    bool isIgnoreAutorepeat();
    LWidgetFramePage *currentPage();
    int currentPageIdx();
    LWidgetFramePage *pageAt(int index);
    int pageCount();
    void setAutoPageRolling(bool enabled);
    void setCurrentPage(int index, bool animate);
    void setCurrentPage(LWidgetFramePage *page, bool animate);
    void setIgnoreAutorepeat(bool ignore);
    void setPageRollingLockEnabled(bool enabled);
    
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void start(bool unknownSetFalse);
    virtual void stop(bool unknownSetFalse);

signals:	
    void srarted();
    void stopped();
    void pageDisplayed(LWidgetFramePage *page);
    void pageRollingCycleWillStart();
    void pageRollingCycleStarted();
    void pageRollingCycleFinished();
    void shortClick(int key, bool isAutorepeat);
    void longAction(int key);

public slots:    
    virtual void startedEvent();
    virtual void stoppedEvent();
    void notifyStarted();
    void notifyStopped();
    void toNextPage();
    void toPrevPage();
    bool isPagesSwitching();

protected:
    virtual void shortKeyClickEvent(int key);
    virtual void longKeyClickEvent(int key);
    virtual void appeared();
    virtual void disappeared();    

private:
	LWidgetFramePrivate *p;
};