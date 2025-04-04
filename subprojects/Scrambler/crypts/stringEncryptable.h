#ifndef STRING_ENCRYPTABLE_H
#define STRING_ENCRYPTABLE_H

#include <QtCore/QString>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPlainTextEdit>

class StringEncryptable {
public:
  QCheckBox *enabled;
  QPlainTextEdit *inOut;
  virtual void encrypt(QString phraseToEncrypt) = 0;
  virtual QString decrypt() = 0;

  void textChanged(QPlainTextEdit *mainText);
  void setEnabled(Qt::CheckState enabled, QPlainTextEdit *mainText);
};

#endif
