#include "tiktok.h"

TikTok::TikTok() : BaseClass() {}

void TikTok::setupSpecializedUi(QWidget *widget) {
  BaseClass::setupSpecializedUi(widget);
  ui.setupUi(widget);
  ui.savesNumber->setValue(saves);
  ui.sharesNumber->setValue(shares);
}

void TikTok::setSpecializedNumber(QString name, int number) {
  if (name == "sharesNumber") {
    shares = number;
  } else if (name == "savesNumber") {
    saves = number;
  }
}

void TikTok::write(QDataStream &out) const {
  out << Origin::TikTok;
  BaseClass::write(out);
  out << saves << shares;
}

void TikTok::read(QDataStream &in) {
  BaseClass::read(in);
  in >> saves >> shares;
}
