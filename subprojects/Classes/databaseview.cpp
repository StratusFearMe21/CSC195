#include "databaseview.h"
#include "dbtypes/reels.h"
#include "dbtypes/shorts.h"
#include "dbtypes/tiktok.h"
#include <QtCore/QBuffer>
#include <QtWidgets/QFileDialog>

DatabaseView::DatabaseView(QWidget *widget) : QListView(widget) {
  QStandardItemModel *model = new QStandardItemModel(0, 1, this);
  model->setSortRole(Qt::UserRole);
  setModel(model);
  QObject::connect(
      model, &QAbstractItemModel::dataChanged, this,
      qOverload<const QModelIndex &, const QModelIndex &, const QList<int> &>(
          &DatabaseView::displayValueChanged));
}

void DatabaseView::createNew() {
  BaseClass *baseClass = nullptr;
  switch (createOrigin) {
  case Origin::TikTok:
    baseClass = new TikTok();
    break;
  case Origin::Reels:
    baseClass = new Reels();
    break;
  case Origin::YoutubeShorts:
    baseClass = new Shorts();
    break;
  default:
    baseClass = new BaseClass();
    break;
  }
  QStandardItemModel *model = (QStandardItemModel *)this->model();
  model->appendRow(baseClass);
  model->sort(0);
  QModelIndex newIndex = indexAt(QPoint(0, 0));
  setCurrentIndex(newIndex);
}

void DatabaseView::remove() { model()->removeRow(currentIndex().row()); }

inline BaseClass *DatabaseView::itemFromIndex(const QModelIndex &index) {
  return (BaseClass *)((QStandardItemModel *)model())->itemFromIndex(index);
}

void DatabaseView::memeTier(int tier) {
  QModelIndex index = currentIndex();
  BaseClass *baseClass = itemFromIndex(index);
  if (baseClass == nullptr) {
    return;
  }
  MemeTier::MemeTier memeTier = static_cast<MemeTier::MemeTier>(tier);
  baseClass->setMemeTier(memeTier);
  model()->sort(0);
}

void DatabaseView::displayValueChanged(const QModelIndex &topLeft,
                                       const QModelIndex &bottomRight,
                                       const QList<int> &roles) {

  if (roles.contains(Qt::DisplayRole)) {
    QAbstractItemModel *itemModel = model();
    for (int i = topLeft.row(); i < bottomRight.row() + 1; i++) {
      for (int j = topLeft.column(); j < bottomRight.column() + 1; j++) {
        itemFromIndex(itemModel->index(i, j))->setUserData();
      }
    }
    model()->sort(0);
  }
}

void DatabaseView::likes(int likes) {
  BaseClass *baseClass = itemFromIndex(currentIndex());
  if (baseClass == nullptr) {
    return;
  }
  baseClass->likes = likes;
}

void DatabaseView::comments(int comments) {
  BaseClass *baseClass = itemFromIndex(currentIndex());
  if (baseClass == nullptr) {
    return;
  }
  baseClass->comments = comments;
}

void DatabaseView::origin(int origin) {
  createOrigin = static_cast<Origin::Origin>(origin);
}

void DatabaseView::image(QPixmap pixmap) {
  BaseClass *baseClass = itemFromIndex(currentIndex());
  if (baseClass == nullptr) {
    return;
  }
  QByteArray encodedImage;
  QBuffer outputBuffer(&encodedImage);
  pixmap.toImage().save(&outputBuffer, "PNG");
  baseClass->encodedImage = encodedImage;
}

void DatabaseView::currentChanged(const QModelIndex &current,
                                  const QModelIndex &previous) {
  QListView::currentChanged(current, previous);

  BaseClass *baseClass = itemFromIndex(current);

  if (baseClass == nullptr) {
    return;
  }
  QPixmap pixmap;
  pixmap.loadFromData(baseClass->encodedImage, "PNG");
  emit setMemeTier(baseClass->getMemeTier());
  emit setLikes(baseClass->likes);
  emit setComments(baseClass->comments);
  emit setImage(pixmap);
  qDeleteAll(editorWidget->children());
  editorWidget->baseData = baseClass;
  baseClass->setupSpecializedUi(editorWidget);
}

void DatabaseView::saveAs() {
  fileOpen.clear();
  save();
}

void DatabaseView::save() {
  if (fileOpen.isEmpty()) {
    QFileDialog dialog(nullptr, "Save Database", "",
                       "Brainrot databases (*.brainrot)");
    dialog.setDefaultSuffix("brainrot");
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec() == QDialog::Accepted) {
      fileOpen = dialog.selectedFiles().first();
    } else {
      return;
    }
  }

  QFile file(fileOpen);
  file.open(QIODevice::WriteOnly);
  QDataStream out(&file);

  out << (quint32)0x69420;

  QStandardItemModel *standardModel =
      static_cast<QStandardItemModel *>(model());
  for (int i = 0; i < standardModel->rowCount(); i++) {
    QModelIndex index = standardModel->index(i, 0);
    out << index.data(Qt::DisplayRole);
    BaseClass *baseClass = itemFromIndex(index);
    out << *baseClass;
  }
  file.close();
}

void DatabaseView::open() {
  QFileDialog dialog(nullptr, "Open Database", "",
                     "Brainrot databases (*.brainrot)");
  dialog.setDefaultSuffix("brainrot");
  dialog.setAcceptMode(QFileDialog::AcceptOpen);

  if (dialog.exec() == QDialog::Accepted) {
    fileOpen = dialog.selectedFiles().first();
  } else {
    return;
  }

  QFile file(fileOpen);
  file.open(QIODevice::ReadOnly);
  QDataStream in(&file);

  quint32 magic;
  in >> magic;
  if (magic != 0x69420)
    return;

  QStandardItemModel *standardModel =
      static_cast<QStandardItemModel *>(model());
  while (!in.atEnd()) {
    QVariant name;
    in >> name;
    Origin::Origin origin;
    in >> origin;
    BaseClass *baseClass;
    switch (origin) {
    case Origin::TikTok:
      baseClass = new TikTok();
      break;
    case Origin::Reels:
      baseClass = new Reels();
      break;
    case Origin::YoutubeShorts:
      baseClass = new Shorts();
      break;
    default:
      baseClass = new BaseClass();
      break;
    }
    baseClass->setData(name, Qt::DisplayRole);
    in >> *baseClass;
    standardModel->appendRow(baseClass);
  }
  standardModel->sort(0);

  file.close();
}
