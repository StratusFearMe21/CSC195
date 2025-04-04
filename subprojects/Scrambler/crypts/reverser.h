#include "stringEncryptable.h"
#include <stdexcept>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

class Reverser : public StringEncryptable {
public:
  Reverser() {}
  Reverser(QWidget *widget) {
    inOut = widget->findChild<QPlainTextEdit *>("reverserInOut");
    enabled = widget->findChild<QCheckBox *>("reverserEnabled");
  }

  void encrypt(QString phraseToEncrypt) override;
  QString decrypt() override;
};
