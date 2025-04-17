#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QtWidgets/QLabel>

// From this StackOverflow answer https://stackoverflow.com/a/43936590

class ImageLabel : public QLabel {
  Q_OBJECT

public:
  ImageLabel(QWidget *widget) : QLabel(widget) {}
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dropEvent(QDropEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  QSize sizeHint() const override;

signals:
  void image(QPixmap);

public slots:
  void setImage(QPixmap);

private:
  QPixmap currentImage;
};

#endif // IMAGELABEL_H
