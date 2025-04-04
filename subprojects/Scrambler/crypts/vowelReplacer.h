#include "stringEncryptable.h"
#include <stdexcept>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QString replaceMultiple(QString phrase, QString replaceStr);

class VowelReplacer : public StringEncryptable {
public:
  VowelReplacer() {}
  VowelReplacer(QWidget *widget) {
    inOut = widget->findChild<QPlainTextEdit *>("vowelReplacerInOut");
    enabled = widget->findChild<QCheckBox *>("vowelReplacerEnabled");
  }

  void encrypt(QString phraseToEncrypt) override;
  QString decrypt() override;
};
