#include "../mainwidget.h"

void MainWidget::vowelReplacerTextChanged() {
  vowelReplacer.textChanged(mainTextEdit);
}
void MainWidget::vowelReplacerSetEnabled(Qt::CheckState checked) {
  vowelReplacer.setEnabled(checked, mainTextEdit);
}

void VowelReplacer::encrypt(QString phraseToEncrypt) {
  inOut->setPlainText(replaceMultiple(phraseToEncrypt, "EAIEOIUOAUeaieoiuoau"));
}

QString VowelReplacer::decrypt() {
  QString phraseToDecrypt = inOut->toPlainText();
  return replaceMultiple(phraseToDecrypt, "AEEIIOOUUAaeeiioouua");
}

QString replaceMultiple(QString phrase, QString replaceStr) {
  if (phrase == nullptr || replaceStr == nullptr) {
    return QString();
  }

  if (replaceStr.length() % 2 != 0) {
    throw std::invalid_argument("replaceStr not valid");
  }

  QByteArray chars = phrase.toUtf8();
  QByteArray replaceChars = replaceStr.toUtf8();

  for (qsizetype charOn = 0; charOn < chars.length(); charOn++) {
    for (qsizetype replaceCharOn = 0; replaceCharOn < replaceChars.length();
         replaceCharOn += 2) {
      if (chars.at(charOn) == replaceChars.at(replaceCharOn)) {
        chars[charOn] = replaceChars.at(replaceCharOn + 1);
        break;
      }
    }
  }

  return QString(chars);
}
