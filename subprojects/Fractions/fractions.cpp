#include <adwaita.h>
#include <gtkmm.h>
#include <iostream>

#include "application.h"

#define PROJECT_NAME "GTKMMTest"

ui::ApplicationWindow *runWindow;

static void show_window(const Glib::RefPtr<Gtk::Application> &app) {
  runWindow = ui::ApplicationWindow::create(app);
  app->add_window(*runWindow);
  runWindow->present();
  app->signal_window_removed().connect([app](Gtk::Window *window) {
    if (window == runWindow) {
      if (window)
        window->destroy();
      runWindow = nullptr;
    }
  });
}

int main(int argc, char **argv) {
  Adw::init();

  auto app = Adw::Application::create("edu.neumont.csc150.fractions",
                                      Gio::Application::Flags::NON_UNIQUE);

  app->signal_activate().connect(sigc::bind(sigc::ptr_fun(show_window), app));

  int status = app->run(argc, argv);

  return status;
}
