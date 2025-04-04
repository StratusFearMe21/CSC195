#include "stringEncryptable.h"

void StringEncryptable::textChanged(QPlainTextEdit *mainText) {
  if (enabled->checkState() == Qt::CheckState::Checked) {
    QString decryptedPhrase = decrypt();
    mainText->setPlainText(decryptedPhrase);
  }
}

void StringEncryptable::setEnabled(Qt::CheckState enabled,
                                   QPlainTextEdit *mainText) {
  if (enabled == Qt::CheckState::Unchecked) {
    inOut->clear();
  } else {
    encrypt(mainText->toPlainText());
  }
}
