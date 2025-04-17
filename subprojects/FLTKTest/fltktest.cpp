#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FLTKTest.h>
#include <iostream>

#define PROJECT_NAME "FLTKTest"

void buttonPress(Fl_Button *button, long bNumber) {
  std::cout << "Pressed button " << bNumber << std::endl;
}

int main(int argc, char **argv) {
  UserInterface ui;
  Fl_Double_Window *window = ui.make_window();
  window->show(argc, argv);
  return Fl::run();
}
