#include "stringEncryptable.h"
#include <stdexcept>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

class XorCrypt : public StringEncryptable {
public:
  int key = 1;
  XorCrypt() {}
  XorCrypt(QWidget *widget) {
    inOut = widget->findChild<QPlainTextEdit *>("xorCryptInOut");
    enabled = widget->findChild<QCheckBox *>("xorCryptEnabled");
  }

  void encrypt(QString phraseToEncrypt) override;
  QString decrypt() override;
};
