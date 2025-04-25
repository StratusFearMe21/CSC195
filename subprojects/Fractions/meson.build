project('Fractions', 'cpp', 'c',
  version : '0.1.0',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

cpp = meson.get_compiler('cpp')

gnome = import('gnome')
gtk_dep = dependency('gtkmm-4.0')
adwaitamm_dep = dependency('libadwaitamm-1')
gmodule_export_dep = dependency('gmodule-export-2.0')
giac_dep = cpp.find_library('giac',
  has_headers : ['giac/giac.h', 'giac/config.h'])

uiresources = gnome.compile_resources(
    'ui-resources', 'resources/ui-resources.gresource.xml',
    source_dir: 'resources',
    c_name: 'ui'
)

sources = [
  'fractions.cpp',
  'application.cpp',
]
                 
exe = executable('Fractions', uiresources, sources,
  dependencies: [gtk_dep, adwaitamm_dep, gmodule_export_dep, giac_dep],
  export_dynamic : true,
  install : true)

test('basic', exe)
