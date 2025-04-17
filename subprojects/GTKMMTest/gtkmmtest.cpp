#include <gtkmm.h>
#include <iostream>

#define PROJECT_NAME "GTKMMTest"

Gtk::Window *pDialog = nullptr;
Glib::RefPtr<Gtk::Application> app;

extern "C" {
G_MODULE_EXPORT void beautifulButton(GtkButton *button, gpointer data) {
  std::cout << "Button" << std::endl;
}
}

void on_app_activate() {
  auto builder = Gtk::Builder::create();
  builder->add_from_resource("/org/example/ui/testproject.ui");
  // builder->add_from_resource(ui_get_resource());

  // Get the GtkBuilder-instantiated dialog:
  pDialog = builder->get_widget<Gtk::Window>("MainWindow");
  if (!pDialog) {
    std::cerr << "Could not get the dialog" << std::endl;
    return;
  }

  // It's not possible to delete widgets after app->run() has returned.
  // Delete the dialog with its child widgets before app->run() returns.
  pDialog->signal_hide().connect([]() { delete pDialog; });

  app->add_window(*pDialog);
  pDialog->set_visible(true);
}

int main(int argc, char **argv) {
  app = Gtk::Application::create("org.gtkmm.example");

  app->signal_activate().connect([]() { on_app_activate(); });

  return app->run(argc, argv);
}
