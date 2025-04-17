project('GTKMMTest', 'cpp', 'c',
  version : '0.1.0',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

gnome = import('gnome')
gtk_dep = dependency('gtkmm-4.0')
gmodule_export_dep = dependency('gmodule-export-2.0')

uiresources = gnome.compile_resources(
    'ui-resources', 'resources/ui-resources.gresource.xml',
    source_dir: 'resources',
    c_name: 'ui'
)
                 
exe = executable('GTKMMTest', uiresources, 'gtkmmtest.cpp',
  dependencies: [gtk_dep, gmodule_export_dep],
  export_dynamic : true,
  install : true)

test('basic', exe)
