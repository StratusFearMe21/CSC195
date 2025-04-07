#include "../mainwidget.h"

void MainWidget::xorCryptTextChanged() { xorCrypt.textChanged(mainTextEdit); }
void MainWidget::xorCryptSetEnabled(Qt::CheckState checked) {
  xorCrypt.setEnabled(checked, mainTextEdit);
}

void MainWidget::xorCryptKeyChanged(int newKey) {
  xorCrypt.key = newKey;
  MainWidget::mainTextChanged();
}

QString xorCrypt(QString cipherText, int key) {
  QByteArray phrase = cipherText.toUtf8();
  for (int i = 0; i < phrase.length(); i++) {
    // phrase[i] &= 0b00111111;
    phrase[i] ^= key & 0b00111111;
  }
  return QString(phrase);
}

void XorCrypt::encrypt(QString phraseToEncrypt) {
  inOut->setPlainText(xorCrypt(phraseToEncrypt, key));
}

QString XorCrypt::decrypt() {
  return xorCrypt(inOut->toPlainText().toUtf8(), key);
}
