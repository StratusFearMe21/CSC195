/* Copyright (c) 2025  Isaac Mills <imills@student.neumont.edu>
 *
 * This file is part of libadwaitamm.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
 */

// We always need to generate the .defs for all types because the code
// using deprecated API is generated unconditionally and only disabled
// at compile time.
#undef LIBADWAITA_DISABLE_DEPRECATED

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include <iostream>
#include <libadwaita-1/adwaita.h>

int main(int, char **) {
  adw_init();

  std::cout << get_defs(ADW_TYPE_APPLICATION_WINDOW);
  std::cout << get_defs(ADW_TYPE_APPLICATION);

  return 0;
}
