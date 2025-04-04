#include "stringEncryptable.h"
#include <stdexcept>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

class Cutter : public StringEncryptable {
public:
  Cutter() {}
  Cutter(QWidget *widget) {
    inOut = widget->findChild<QPlainTextEdit *>("cutterInOut");
    enabled = widget->findChild<QCheckBox *>("cutterEnabled");
  }

  void encrypt(QString phraseToEncrypt) override;
  QString decrypt() override;
};
