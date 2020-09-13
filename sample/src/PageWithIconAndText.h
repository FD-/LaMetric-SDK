#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtGui/QColor>

#include <lfoundation/LApplication.h>
#include <lfoundation/LWidgetFrame.h>
#include <lfoundation/LWidgetBase.h>
#include <lfoundation/LWidgetFramePage.h>
#include <lfoundation/LScrollLabelWidget.h>
#include <lfoundation/LNotification.h>
#include <lfoundation/LNotificationManager.h>
#include <lfoundation/LWidgetManager.h>

#include <llog/LLog.h>

class PageWithIconAndText : public LWidgetFramePage {
	Q_OBJECT

public:
    PageWithIconAndText(LWidgetFrame *frame) : LWidgetFramePage(frame) {
        timer = new QTimer(this);
        scrollLabelWidget = new LScrollLabelWidget(this);
        timer->setSingleShot(true);
        timer->setInterval(5000);
        connect(timer, SIGNAL(timeout()), this, SIGNAL(finishedScrolling()));
        scrollLabelWidget->setScrollEndFlag(LScrollLabelWidget::Scroll1);
        scrollLabelWidget->setDelays(1000, 500);
        scrollLabelWidget->setGeometry(this->geometry());
        scrollLabelWidget->move(QPoint(0, 0));
        connect(scrollLabelWidget, SIGNAL(scrollFinished()), this, SIGNAL(finishedScrolling()));
        connect(this, SIGNAL(becomeVisible()), this, SLOT(pageBecomeVisisble()));
        connect(this, SIGNAL(becomeInvisible()), this, SLOT(pageBecomeInvisisble()));
        connect(this, SIGNAL(startScrollText()), this, SLOT(requestForTextScroll()));
    }

    ~PageWithIconAndText() {
        delete timer;
        delete scrollLabelWidget;
    }

    LScrollLabelWidget *getContent() {
        return scrollLabelWidget;
    }

    bool isTextScrolling() {
        return scrollLabelWidget->isScrolling();
    }

    void removeIcon(bool unknown) {
        scrollLabelWidget->removeIcon(unknown);
    }

    virtual void setIcon(const QString& path, bool unknown) {
        scrollLabelWidget->setIcon(path, unknown);
    }

    virtual void setText(const QString& text, bool unknown) {
        labelText = text;

        if (scrollLabelWidget->isScrolling()) scrollLabelWidget->stopScrolling();
        scrollLabelWidget->setText(text.toUpper(), unknown);

        if (scrollLabelWidget->willScroll() && !scrollLabelWidget->isScrolling()) {
            scrollLabelWidget->startScrolling();
            timer->stop();
        } else if (!scrollLabelWidget->willScroll()) {
            timer->stop();
            timer->start(displayDuration());
        }
    }

    virtual QString escapeUnknownSymbols(const QString &text) {
        return QString(text);
    }

    void setTextColor(QColor color) {
        scrollLabelWidget->setTextColor(color);
    }

    const QString *text() const {
        return &labelText;
    }

    bool textWillScroll() {
        return scrollLabelWidget->willScroll();
    }

signals:
    void finishedScrolling();
    void startScrollText();    

public slots:
    void pageBecomeVisisble() {
        if (!scrollLabelWidget->willScroll()) {
            timer->start();
        } else {
            scrollLabelWidget->startScrolling();
            timer->stop();
        }
    }

    void pageBecomeInvisisble() {
        timer->stop();
        if (!scrollLabelWidget->isScrolling()) return;
        scrollLabelWidget->stopScrolling();
    }
    void requestForTextScroll() {
        if (!scrollLabelWidget->willScroll()) return;
        scrollLabelWidget->startScrolling();
    }

private:
    QTimer *timer;
    QString labelText;
    LScrollLabelWidget *scrollLabelWidget;
};