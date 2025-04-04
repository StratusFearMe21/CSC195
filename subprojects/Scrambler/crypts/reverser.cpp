#include "../mainwidget.h"
#include <algorithm>

void MainWidget::reverserTextChanged() { reverser.textChanged(mainTextEdit); }
void MainWidget::reverserSetEnabled(Qt::CheckState checked) {
  reverser.setEnabled(checked, mainTextEdit);
}

void Reverser::encrypt(QString phraseToEncrypt) {
  std::reverse(phraseToEncrypt.begin(), phraseToEncrypt.end());
  inOut->setPlainText(phraseToEncrypt);
}

QString Reverser::decrypt() {
  QString phraseToDecrypt = inOut->toPlainText();
  std::reverse(phraseToDecrypt.begin(), phraseToDecrypt.end());
  return phraseToDecrypt;
}
