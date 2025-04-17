#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include "dbtypes/baseclass.h"
#include <QtWidgets/QWidget>

class BaseWidget : public QWidget {
  Q_OBJECT

public:
  BaseClass *baseData = nullptr;

public:
  BaseWidget(QWidget *widget) : QWidget(widget) {}

public slots:
  void setSpecializedNumber(int);
};

#endif // BASEWIDGET_H
