dnl Copyright (c) 2019  Roger Ferrer <rofirrim@gmail.com>
dnl This file is part of libadwaitamm.

_CONVERSION(`const Glib::RefPtr<Gtk::Application>&',`GtkApplication*',__CONVERT_REFPTR_TO_P($3))
_CONVERSION(`AdwApplicationWindow*',`Glib::RefPtr<ApplicationWindow>',`Glib::wrap($3)')
_CONVERSION(`Toast*',`AdwToast*',__FP2P)
_CONVERSION(`AdwToast*',`Toast*',__RP2P)

_CONV_INCLASS_ENUM(Adw,Toast,Priority)
