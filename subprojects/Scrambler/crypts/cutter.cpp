#include "../mainwidget.h"

void MainWidget::cutterTextChanged() { cutter.textChanged(mainTextEdit); }
void MainWidget::cutterSetEnabled(Qt::CheckState checked) {
  cutter.setEnabled(checked, mainTextEdit);
}

void Cutter::encrypt(QString phraseToEncrypt) {
  QByteArray chars = phraseToEncrypt.toUtf8();
  QByteArray charsEncrypted(chars.length(), '\0');

  int frontHalf = chars.length() / 2;
  int iTo = chars.length() % 2 == 0 ? chars.length() - frontHalf
                                    : chars.length() - frontHalf - 1;

  for (int i = 0; i < iTo; i++) {
    if (chars.length() % 2 == 0) {
      charsEncrypted[i] = chars.at(i + frontHalf);
    } else {
      charsEncrypted[i] = chars.at(i + frontHalf + 1);
    }
  }

  for (int i = frontHalf; i < chars.length(); i++) {
    charsEncrypted[i] = chars[i - frontHalf];
  }

  inOut->setPlainText(charsEncrypted);
}

QString Cutter::decrypt() {
  QByteArray chars = inOut->toPlainText().toUtf8();
  QByteArray charsDecrypted(chars.length(), '\0');

  int frontHalf = chars.length() / 2;
  int iTo = chars.length() % 2 == 0 ? frontHalf : frontHalf + 1;

  for (int i = 0; i < iTo; i++) {
    charsDecrypted[i] = chars.at(i + frontHalf);
  }

  for (int i = iTo; i < chars.length(); i++) {
    if (chars.length() % 2 == 0) {
      charsDecrypted[i] = chars.at(i - frontHalf);
    } else {
      charsDecrypted[i] = chars.at(i - frontHalf - 1);
    }
  }

  return QString(charsDecrypted);
}
