#include "baseclass.h"
#include <ui_tiktok.h>

class TikTok : public BaseClass {
public:
  TikTok();
  void setupSpecializedUi(QWidget *) override;
  void setSpecializedNumber(QString, int) override;
  virtual void read(QDataStream &) override;
  virtual void write(QDataStream &) const override;

public:
  int saves = 0;
  int shares = 0;

private:
  Ui::TikTokWidget ui;
};
