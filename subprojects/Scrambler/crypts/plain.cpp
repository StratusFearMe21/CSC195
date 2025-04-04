#include "../mainwidget.h"

#include <QtWidgets/QPlainTextEdit>

void MainWidget::mainTextChanged() {
  QString phrase = mainTextEdit->toPlainText();
  if (vowelReplacer.enabled->checkState() == Qt::CheckState::Checked &&
      !vowelReplacer.inOut->hasFocus()) {
    vowelReplacer.encrypt(phrase);
  }
  if (cutter.enabled->checkState() == Qt::CheckState::Checked &&
      !cutter.inOut->hasFocus()) {
    cutter.encrypt(phrase);
  }
  if (reverser.enabled->checkState() == Qt::CheckState::Checked &&
      !reverser.inOut->hasFocus()) {
    reverser.encrypt(phrase);
  }
  if (xorCrypt.enabled->checkState() == Qt::CheckState::Checked &&
      !xorCrypt.inOut->hasFocus()) {
    xorCrypt.encrypt(phrase);
  }
}
