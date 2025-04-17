#include "reels.h"

Reels::Reels() : BaseClass() {}

void Reels::setupSpecializedUi(QWidget *widget) {
  BaseClass::setupSpecializedUi(widget);
  ui.setupUi(widget);
}

void Reels::setSpecializedNumber(QString name, int number) {
  Q_UNUSED(name);
  Q_UNUSED(number);
  // if (name == "commentsNumber") {
  //   comments = number;
  // }
}

void Reels::write(QDataStream &out) const {
  out << Origin::Reels;
  BaseClass::write(out);
}

void Reels::read(QDataStream &in) { BaseClass::read(in); }
