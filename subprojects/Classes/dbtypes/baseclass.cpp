#include "baseclass.h"
#include <QtCore/QBuffer>
#include <QtWidgets/QWidget>

void BaseClass::setupSpecializedUi(QWidget *widget) {
  widget->setObjectName("");
}

void BaseClass::setSpecializedNumber(QString, int) {}

MemeTier::MemeTier BaseClass::getMemeTier() const { return memeTier; }

void BaseClass::setMemeTier(MemeTier::MemeTier tier) {
  QIcon icon;
  switch (tier) {
  case MemeTier::SkibidiOhioRizzler:
    setData(QIcon::fromTheme(QString::fromUtf8("face-cool")),
            Qt::DecorationRole);
    break;
  case MemeTier::Sigma:
    setData(QIcon::fromTheme(QString::fromUtf8("face-smile-big")),
            Qt::DecorationRole);
    break;
  case MemeTier::Based:
    setData(QIcon::fromTheme(QString::fromUtf8("face-smile")),
            Qt::DecorationRole);
    break;
  case MemeTier::Cringe:
    setData(QIcon::fromTheme(QString::fromUtf8("face-sick")),
            Qt::DecorationRole);
    break;
  case MemeTier::None:
    setData(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout), Qt::DecorationRole);
    break;
  }
  memeTier = tier;
  setUserData();
}

void BaseClass::setUserData() {
  QString sortKey;
  sortKey.append(QChar(memeTier + 97));
  QVariant displayData = data(Qt::DisplayRole);
  sortKey.append(displayData.toString());
  setData(sortKey, Qt::UserRole);
}

void BaseClass::write(QDataStream &out) const {
  out << memeTier << likes << comments << encodedImage;
}

void BaseClass::read(QDataStream &in) {
  MemeTier::MemeTier tier;
  in >> tier >> likes >> comments >> encodedImage;
  setMemeTier(tier);
}
