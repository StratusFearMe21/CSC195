#include "imagelabel.h"
#include <QtCore/QMimeData>
#include <QtCore/QMimeDatabase>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QImageReader>
#include <QtWidgets/QFileDialog>

const float MAX_ENLARGEMENT = 1.0;

void ImageLabel::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls() || event->mimeData()->hasImage())
    event->acceptProposedAction();
  QLabel::dragEnterEvent(event);
}

void ImageLabel::setImage(QPixmap pixmap) {
  if (pixmap.isNull()) {
  }
  currentImage = pixmap;
  resize(sizeHint());
  update();
}

void ImageLabel::dropEvent(QDropEvent *event) {
  QPixmap pixmap;
  if (event->mimeData()->hasUrls()) {
    QUrl url = event->mimeData()->urls()[0];
    pixmap = QPixmap(url.toLocalFile());
  } else if (event->mimeData()->hasImage()) {
    pixmap = event->mimeData()->imageData().value<QPixmap>();
  }
  setImage(pixmap);
  emit image(pixmap);
  QLabel::dropEvent(event);
}

void ImageLabel::resizeEvent(QResizeEvent *event) {
  if (!currentImage.isNull()) {
    setPixmap(currentImage.scaled(event->size(), Qt::KeepAspectRatio));
  } else {
    setText("Load Image");
  }
  QLabel::resizeEvent(event);
}

QSize ImageLabel::sizeHint() const {
  if (currentImage.isNull()) {
    return QLabel::sizeHint();
  } else {
    return currentImage.size() * MAX_ENLARGEMENT;
  }
}

void ImageLabel::mouseDoubleClickEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  // get supported image file types
  QStringList mimeTypeFilters;
  const QByteArrayList supportedMimeTypes = QImageReader::supportedMimeTypes();
  foreach (const QByteArray &mimeTypeName, supportedMimeTypes) {
    mimeTypeFilters.append(mimeTypeName);
  }
  mimeTypeFilters.sort(Qt::CaseInsensitive);

  // From this StackOverflow answer https://stackoverflow.com/a/46534037
  // compose filter for all supported types
  QMimeDatabase mimeDB;
  QStringList allSupportedFormats;
  for (const QString &mimeTypeFilter : mimeTypeFilters) {
    QMimeType mimeType = mimeDB.mimeTypeForName(mimeTypeFilter);
    if (mimeType.isValid()) {
      allSupportedFormats.append(mimeType.globPatterns());
    }
  }
  QString allSupportedFormatsFilter =
      QString("All supported formats (%1)").arg(allSupportedFormats.join(' '));

  QUrl fileOpen;

  QFileDialog dialog(nullptr, "Set brainrot image", "", "Image files");
  dialog.setFileMode(QFileDialog::ExistingFile);
  dialog.setMimeTypeFilters(mimeTypeFilters);
  QStringList nameFilters = dialog.nameFilters();
  nameFilters.append(allSupportedFormatsFilter);
  dialog.setNameFilters(nameFilters);
  dialog.selectNameFilter(allSupportedFormatsFilter);
  dialog.setAcceptMode(QFileDialog::AcceptOpen);

  if (dialog.exec() == QDialog::Accepted) {
    fileOpen = dialog.selectedUrls().first();
  } else {
    return;
  }

  QMimeData mimeData;
  mimeData.setUrls({fileOpen});

  QDropEvent imageDropEvent(QPointF(0.0, 0.0), Qt::CopyAction, &mimeData,
                            Qt::NoButton, Qt::NoModifier);

  dropEvent(&imageDropEvent);
}
