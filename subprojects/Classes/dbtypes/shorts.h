#include "baseclass.h"
#include <ui_shorts.h>

class Shorts : public BaseClass {
public:
  Shorts();
  void setupSpecializedUi(QWidget *) override;
  void setSpecializedNumber(QString, int) override;
  virtual void read(QDataStream &) override;
  virtual void write(QDataStream &) const override;

public:
  int shares = 0;

private:
  Ui::ShortsWidget ui;
};
