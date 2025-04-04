#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include "crypts/cutter.h"
#include "crypts/reverser.h"
#include "crypts/vowelReplacer.h"
#include "crypts/xorCrypt.h"
#include <iostream>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

class MainWidget : public QWidget {
  Q_OBJECT

public:
  QPlainTextEdit *mainTextEdit;
  Cutter cutter;
  Reverser reverser;
  VowelReplacer vowelReplacer;
  XorCrypt xorCrypt;

  MainWidget(QWidget *widget) : QWidget(widget) {}

  void setVisible(bool visible) override {
    if (visible) {
      mainTextEdit = findChild<QPlainTextEdit *>("mainTextEdit");
      cutter = Cutter(this);
      reverser = Reverser(this);
      vowelReplacer = VowelReplacer(this);
      xorCrypt = XorCrypt(this);
    }
    QWidget::setVisible(visible);
  }

public slots:
  void mainTextChanged();
  void cutterTextChanged();
  void xorCryptTextChanged();
  void vowelReplacerTextChanged();
  void reverserTextChanged();
  void cutterSetEnabled(Qt::CheckState);
  void xorCryptSetEnabled(Qt::CheckState);
  void vowelReplacerSetEnabled(Qt::CheckState);
  void reverserSetEnabled(Qt::CheckState);
  void xorCryptKeyChanged(int);
};

#endif
