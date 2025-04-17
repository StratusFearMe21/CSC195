#include "baseclass.h"
#include <ui_reels.h>

class Reels : public BaseClass {
public:
  Reels();
  void setupSpecializedUi(QWidget *) override;
  void setSpecializedNumber(QString, int) override;
  virtual void read(QDataStream &) override;
  virtual void write(QDataStream &) const override;

private:
  Ui::ReelsWidget ui;
};
