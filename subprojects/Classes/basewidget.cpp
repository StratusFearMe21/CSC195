#include "basewidget.h"
#include "dbtypes/tiktok.h"
#include <QtCore/QMimeData>
#include <QtGui/QDragEnterEvent>

void BaseWidget::setSpecializedNumber(int number) {
  QString senderName = QObject::sender()->objectName();
  baseData->setSpecializedNumber(senderName, number);
}
