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
#include <lfoundation/LNotificationSound.h>
#include <lfoundation/LChartWidget.h>
#include <lfoundation/LProgressWidget.h>
#include <lfoundation/LMetricWidget.h>

#include <llog/LLog.h>

#include "PageWithIconAndText.h"
#include "ChartPage.h"

class App : public LApplication {
    Q_OBJECT

public:
    LWidgetFrame *frame;
    PageWithIconAndText *scrollPage;
    ChartPage *chartPage;
    QTimer *timer;

    App(int argc, char **argv) : LApplication(argc, argv) {
        LLog::logw("Sample started!\n");
    }

    ~App() {
        frame->removePage(scrollPage);
        delete scrollPage;

        frame->removePage(chartPage);
        delete chartPage;

        removeFrame(frame);
        delete frame;

        timer->stop();
        delete timer;
    }

    virtual void createEvent() {
        LApplication::createEvent();
        LLog::logw("Create!\n");

        frame = new LWidgetFrame(this, NULL);
        
        scrollPage = new PageWithIconAndText(frame);
        scrollPage->setText("SDK Sample working!", false);
        // You can also pass base64-encoded icon data to setIcon():
        scrollPage->setIcon("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAgAAAAICAYAAADED76LAAAAOklEQVQYlWNUVFBgwAeYcEncv//gP04FMEmsCmCSiooKjHAFMEF0SRQTsEnCFcAE0SUZGBgYGAl5EwA+6RhuHb9bggAAAABJRU5ErkJggg==", true);
        // scrollPage->setIcon(QCoreApplication::applicationDirPath() + "/res/icon.png", false);
        frame->addPage(scrollPage, 0);
        connect(scrollPage, SIGNAL(finishedScrolling()), this, SLOT(scrollPageFinishedScrolling()));

        chartPage = new ChartPage(frame);
        QList<int> data({10, 15, 20, 25, 30, 42, 1, 23});
        chartPage->setData(data);
        frame->addPage(chartPage, 3000);
        connect(chartPage, SIGNAL(animationFinished()), this, SLOT(chartPageFinished()));

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(timerTimedOut()));

        addFrame(frame);
    }

    virtual void destroyEvent() {
        frame->removePage(scrollPage);
        frame->removePage(chartPage);
        removeFrame(frame);
        free(scrollPage);
        free(chartPage);

        timer->stop();
        free(timer);

        free(frame);
    }

    virtual void activated() {
        LApplication::activated();
        setActiveFrame(frame, true);
        frame->setCurrentPage(0, true);

        if (activationReason() == ActivationReasonNotification) {
            QString soundName = settings()->value("sound", QVariant("knock-knock")).toString();
            LNotificationSound *sound = LNotificationSound::createFromString(QString("notifications"), soundName, this);
            sound->play(3);
        }
    }

    virtual void deactivated() {
        LApplication::deactivated();

        if (activationReason() != ActivationReasonNotification) {
            timer->start(10000);
        }
    }

public slots:
    void timerTimedOut() {
        timer->stop();
        widgetManager()->displayMeAsNotification(Lm::NotificationPriorityNormal);
    }

    void scrollPageFinishedScrolling() {
        frame->toNextPage();
    }

    void chartPageFinished() {
        if (activationReason() == ActivationReasonNotification) {
            widgetManager()->dismissMe();
        }
    }
};