/* Copyright (c) 2019  Roger Ferrer <rofirrim@gmail.com>
 *
 * This file is part of libadwaitamm.
 *
 * libadwaitamm is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * libadwaitamm is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm/init.h>
#include <libadwaitamm/init.h>
#include <libadwaitamm/wrap_init.h>

void Adw::init() {
  Gtk::init_gtkmm_internals();
  wrap_init();
}
