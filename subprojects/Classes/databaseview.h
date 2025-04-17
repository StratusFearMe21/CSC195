#include "basewidget.h"
#include "dbtypes/baseclass.h"
#include <QtWidgets/QListView>

class DatabaseView : public QListView {
  Q_OBJECT

public:
  DatabaseView(QWidget *widget);

public:
  BaseWidget *editorWidget;

private:
  QString fileOpen;
  Origin::Origin createOrigin = Origin::TikTok;
  inline BaseClass *itemFromIndex(const QModelIndex &index);

public slots:
  void createNew();
  void remove();
  void currentChanged(const QModelIndex &icurrent,
                      const QModelIndex &previous) override;
  void displayValueChanged(const QModelIndex &topLeft,
                           const QModelIndex &bottomRight,
                           const QList<int> &roles);
  void memeTier(int);
  void origin(int);
  void likes(int);
  void comments(int);
  void image(QPixmap);
  void save();
  void saveAs();
  void open();

signals:
  void setMemeTier(int);
  void setOrigin(int);
  void setLikes(int);
  void setComments(int);
  void setImage(QPixmap);
};
