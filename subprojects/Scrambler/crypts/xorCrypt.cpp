#include "../mainwidget.h"

void MainWidget::xorCryptTextChanged() { xorCrypt.textChanged(mainTextEdit); }
void MainWidget::xorCryptSetEnabled(Qt::CheckState checked) {
  xorCrypt.setEnabled(checked, mainTextEdit);
}

void MainWidget::xorCryptKeyChanged(int newKey) {
  xorCrypt.key = newKey;
  MainWidget::mainTextChanged();
}

void XorCrypt::encrypt(QString phraseToEncrypt) {
  QByteArray phrase = phraseToEncrypt.toUtf8();
  for (int i = 0; i < phrase.length(); i++) {
    // phrase[i] &= 0b00111111;
    phrase[i] ^= key & 0b00111111;
  }
  inOut->setPlainText(QString(phrase));
}

QString XorCrypt::decrypt() {
  QByteArray phraseToDecrypt = inOut->toPlainText().toUtf8();
  for (int i = 0; i < phraseToDecrypt.length(); i++) {
    // phraseToDecrypt[i] &= 0b00111111;
    phraseToDecrypt[i] ^= key & 0b00111111;
  }
  return QString(phraseToDecrypt);
}
