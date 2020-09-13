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
#include <lfoundation/LChartWidget.h>

#include <llog/LLog.h>

class ChartPage : public LWidgetFramePage {
	Q_OBJECT

public:
    ChartPage(LWidgetFrame *frame) : LWidgetFramePage(frame) {
        chartWidget = new LChartWidget(this);
        chartWidget->setDelays(1000, 500);
        chartWidget->setGeometry(this->geometry());
        chartWidget->move(QPoint(0, 0));
        connect(this, SIGNAL(becomeVisible()), chartWidget, SLOT(startPresentation()));
        connect(chartWidget, SIGNAL(presentationFinished()), this, SIGNAL(animationFinished()));
    }

    ~ChartPage() {
        free(chartWidget);
    }

    void setData(const QList<int> &data) {
        chartWidget->setData(data);
    }

signals:
    void animationFinished();

private:
    LChartWidget *chartWidget;
};