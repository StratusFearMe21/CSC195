#include "application.h"
#include "mathlib/mathlib.h"
#include <iostream>

const char ui::ApplicationWindow::class_name[] = "ApplicationWindow";

void ui::ApplicationWindow::setup_template(Gtk::TemplateWidgetSetup &s) {
  s.set_resource("/edu/neumont/csc195/fractions/ui/testproject.ui");

  s.bind_widget("toast_overlay");
  s.bind_widget("first_numerator_input");
  s.bind_widget("second_numerator_input");
  s.bind_widget("operation_input");
  s.bind_widget("algebra_switch");
  s.bind_widget("first_denominator_input");
  s.bind_widget("second_denominator_input");
  s.bind_widget("output");

  s.bind_callback("frac_changed",
                  Gtk::ptr_fun_to_mem_fun<&ui::ApplicationWindow::changed>());

  s.bind_callback(
      "copy_result",
      Gtk::ptr_fun_to_mem_fun<&ui::ApplicationWindow::copy_result>());
}

void ui::ApplicationWindow::init_widget(Gtk::TemplateWidgetInit &i) {
  i.init_template();

  i.bind_widget(toast_overlay, "toast_overlay");
  i.bind_widget(first_numerator, "first_numerator_input");
  i.bind_widget(second_numerator, "second_numerator_input");
  i.bind_widget(operation_input, "operation_input");
  i.bind_widget(algebra_switch, "algebra_switch");
  i.bind_widget(first_denominator, "first_denominator_input");
  i.bind_widget(second_denominator, "second_denominator_input");
  i.bind_widget(output, "output");

  auto application_ag = Gio::SimpleActionGroup::create();

  application_ag->add_action(
      "about", sigc::mem_fun(*this, &ui::ApplicationWindow::show_about));

  insert_action_group("app", application_ag);

  giac::logptr(&log, giac::context0);
}

double to_double(giac::fraction g_fraction) {
  return giac::_simplify(g_fraction.num, giac::context0)
             .to_double(giac::context0) /
         giac::_simplify(g_fraction.den, giac::context0)
             .to_double(giac::context0);
}

namespace giac {
std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &os,
                                        const gen &g) {
  // Same as g.wprint but uses C++ functions instead of heap-overflowing
  std::string s = g.print(context0);
  std::wstring w(s.begin(), s.end());
  return os << w;
}
} // namespace giac

template <typename T>
Glib::ustring calc_fraction(giac::Tfraction<T> first_term,
                            giac::Tfraction<T> second_term,
                            mathlib::Operation operation) {
  Glib::ustring result;
  giac::Tfraction<T> g_result = giac::Tfraction(T(0));
  double d_first_term;
  double d_second_term;
  bool b_result = false;
  std::string s_result;
  switch (operation) {
  case mathlib::Operation::ADD:
    g_result = first_term + second_term;
    // uses operator<< under the hood
    result = Glib::ustring::format(g_result.num, '/', g_result.den);
    break;
  case mathlib::Operation::SUBTRACT:
    g_result = first_term - second_term;
    result = Glib::ustring::format(g_result.num, '/', g_result.den);
    break;
  case mathlib::Operation::MULTIPLY:
    g_result = first_term * second_term;
    result = Glib::ustring::format(g_result.num, '/', g_result.den);
    break;
  case mathlib::Operation::DIVIDE:
    g_result = first_term / second_term;
    result = Glib::ustring::format(g_result.num, '/', g_result.den);
    break;
  case mathlib::Operation::SIMPLIFY:
    simplify(first_term.num, first_term.den);
    result = Glib::ustring::format(first_term.num, '/', first_term.den);
    break;
  case mathlib::Operation::GREATER_THAN:
    d_first_term = to_double(first_term);
    d_second_term = to_double(second_term);
    b_result = d_first_term > d_second_term;
    result.append(b_result ? "True" : "False");
    break;
  case mathlib::Operation::LESS_THAN:
    d_first_term = to_double(first_term);
    d_second_term = to_double(second_term);
    b_result = d_first_term < d_second_term;
    result.append(b_result ? "True" : "False");
    break;
  case mathlib::Operation::EQUAL_TO:
    d_first_term = to_double(first_term);
    d_second_term = to_double(second_term);
    b_result = d_first_term == d_second_term;
    result.append(b_result ? "True" : "False");
    break;
  case mathlib::Operation::GREATER_THAN_EQUAL_TO:
    d_first_term = to_double(first_term);
    d_second_term = to_double(second_term);
    b_result = d_first_term >= d_second_term;
    result.append(b_result ? "True" : "False");
    break;
  case mathlib::Operation::LESS_THEN_EQUAL_TO:
    d_first_term = to_double(first_term);
    d_second_term = to_double(second_term);
    b_result = d_first_term <= d_second_term;
    result.append(b_result ? "True" : "False");
    break;
  case mathlib::Operation::NOT_EQUAL_TO:
    d_first_term = to_double(first_term);
    d_second_term = to_double(second_term);
    b_result = d_first_term != d_second_term;
    result.append(b_result ? "True" : "False");
    break;
  }

  return result;
}

void ui::ApplicationWindow::changed() {
  auto operation =
      static_cast<mathlib::Operation>(operation_input->get_selected());

  Glib::ustring result;

  try {
    if (algebra_switch->get_active()) {
      giac::fraction first_term = giac::fraction(
          giac::gen(first_numerator->get_text(), giac::context0),
          giac::gen(first_denominator->get_text(), giac::context0));
      giac::fraction second_term = giac::fraction(
          giac::gen(second_numerator->get_text(), giac::context0),
          giac::gen(second_denominator->get_text(), giac::context0));

      result = calc_fraction<giac::gen>(first_term, second_term, operation);
    } else {
      giac::Tfraction first_term = giac::Tfraction(
          mathlib::SimpleNumber<int>(std::stoi(first_numerator->get_text())),
          mathlib::SimpleNumber<int>(std::stoi(first_denominator->get_text())));
      giac::Tfraction second_term = giac::Tfraction(
          mathlib::SimpleNumber<int>(std::stoi(second_numerator->get_text())),
          mathlib::SimpleNumber<int>(
              std::stoi(second_denominator->get_text())));

      result = calc_fraction<mathlib::SimpleNumber<int>>(
          first_term, second_term, operation);
    }
  } catch (std::invalid_argument) {
    result = "undef";
  }

  if (log.str().length() > 0) {
    Adw::Toast *toast = new Adw::Toast(log.str());
    log.str(std::string());
    toast->set_timeout(2);
    toast_overlay->dismiss_all();
    toast_overlay->add_toast(toast);
  }

  output->set_label(result);
}

void ui::ApplicationWindow::copy_result() {
  Glib::RefPtr<Gdk::Display> display = Gdk::Display::get_default();
  Glib::RefPtr<Gdk::Clipboard> clipboard = display->get_clipboard();

  Glib::ustring label = output->get_label();
  clipboard->set_text(label);

  Adw::Toast *toast = new Adw::Toast("Result copied");
  toast->set_timeout(2);
  toast_overlay->add_toast(toast);
}

ui::ApplicationWindow *ui::ApplicationWindow::create(
    const Glib::RefPtr<Gtk::Application> &application) {
  Glib::ConstructParams params(type_class_.init(), "application",
                               Glib::unwrap(application), nullptr);
  GObject *obj = g_object_new_with_properties(
      ApplicationWindow::get_type(), params.n_parameters,
      params.parameter_names, params.parameter_values);
  return ApplicationWindow::wrap(obj);
}

void ui::ApplicationWindow::show_about() {
  setup_about();
  adw_dialog_present(about, GTK_WIDGET(gobj()));
}

void ui::ApplicationWindow::setup_about() {

  about = adw_about_dialog_new();

  adw_about_dialog_set_application_name(ADW_ABOUT_DIALOG(about), "Fractions");

  adw_about_dialog_set_version(ADW_ABOUT_DIALOG(about), "0.1.0");

  adw_about_dialog_set_developer_name(ADW_ABOUT_DIALOG(about), "Isaac Mills");

  adw_about_dialog_set_license_type(ADW_ABOUT_DIALOG(about),
                                    GTK_LICENSE_MIT_X11);

  adw_about_dialog_set_copyright(ADW_ABOUT_DIALOG(about),
                                 "Mills © All rights reserved");

  adw_about_dialog_set_issue_url(
      ADW_ABOUT_DIALOG(about),
      "https://github.com/StratusFearMe21/CSC195/issues");
  adw_about_dialog_set_website(ADW_ABOUT_DIALOG(about),
                               "https://github.com/StratusFearMe21/CSC195/tree/"
                               "master/subprojects/Fractions");
}
