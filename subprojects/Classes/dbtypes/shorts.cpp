#include "shorts.h"

Shorts::Shorts() : BaseClass() {}

void Shorts::setupSpecializedUi(QWidget *widget) {
  BaseClass::setupSpecializedUi(widget);
  ui.setupUi(widget);
  ui.sharesNumber->setValue(shares);
}

void Shorts::setSpecializedNumber(QString name, int number) {
  if (name == "sharesNumber") {
    shares = number;
  }
}

void Shorts::write(QDataStream &out) const {
  out << Origin::YoutubeShorts;
  BaseClass::write(out);
  out << shares;
}

void Shorts::read(QDataStream &in) {
  BaseClass::read(in);
  in >> shares;
}
