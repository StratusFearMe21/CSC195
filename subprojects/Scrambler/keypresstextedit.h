#ifndef KEY_PRESS_TEXT_EDIT_H
#define KEY_PRESS_TEXT_EDIT_H

#include <iostream>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPlainTextEdit>

class KeyPressTextEdit : public QPlainTextEdit {
  Q_OBJECT

public:
  KeyPressTextEdit(QWidget *widget) : QPlainTextEdit(widget) {}
  void keyPressEvent(QKeyEvent *e) override {
    QPlainTextEdit::keyPressEvent(e);
    emit keypress();
  }

signals:
  void keypress();
};

#endif
