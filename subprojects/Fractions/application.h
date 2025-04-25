#ifndef APPLICATION_H
#define APPLICATION_H

#include <adwaita.h>
#include <gtkmm.h>
#include <libadwaitamm.h>
#include <libadwaitamm/private/applicationwindow_p.h>

#include <giac/config.h>
#include <giac/giac.h>

#include "templatewidget.h"

namespace ui {
class ApplicationWindow
    : public Gtk::TemplateWidget<ApplicationWindow, Adw::ApplicationWindow> {

public:
  static ApplicationWindow *
  create(const Glib::RefPtr<Gtk::Application> &application);

protected:
  explicit ApplicationWindow(GtkWidget *obj) : TemplateWidgetBase(obj) {}

  void show_about();
  void setup_about();

private:
  void changed();
  void copy_result();

  // Gets freed automatically
  std::stringstream log;
  AdwDialog *about = nullptr;
  Adw::ToastOverlay *toast_overlay = nullptr;
  Adw::EntryRow *first_numerator = nullptr;
  Adw::EntryRow *first_denominator = nullptr;
  Adw::ComboRow *operation_input = nullptr;
  Adw::SwitchRow *algebra_switch = nullptr;
  Adw::EntryRow *second_numerator = nullptr;
  Adw::EntryRow *second_denominator = nullptr;
  Gtk::Button *output = nullptr;

  static const char class_name[];
  static void setup_template(Gtk::TemplateWidgetSetup &s);
  void init_widget(Gtk::TemplateWidgetInit &i);

  // This should be managed
  static bool is_managed() { return true; }

  friend CppClassType;
};

} // namespace ui

#endif // APPLICATION_H
