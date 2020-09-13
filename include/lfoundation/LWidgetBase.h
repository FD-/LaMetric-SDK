#pragma once

#include <QtGui/QWidget>

class LWidgetBasePrivate;

class LWidgetBase : public QWidget {
    Q_OBJECT

public:
  	LWidgetBase(QWidget *parent);

private:
	LWidgetBasePrivate *p;
};