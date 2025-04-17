#include <QtWidgets/QApplication>
#include <iostream>
#include <ui_main.h>

#define PROJECT_NAME "Classes"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QMainWindow window;

  Ui::MainWindow ui;
  ui.setupUi(&window);
  ui.databaseItems->editorWidget = ui.editorWidget;

  window.show();
  return app.exec();
}
