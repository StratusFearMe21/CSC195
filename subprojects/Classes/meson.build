project('Classes', 'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Widgets'])

ui_sources = [
  'resources/main.ui',
  'resources/tiktok.ui',
  'resources/shorts.ui',
  'resources/reels.ui',
]

main_ui = qt6.compile_ui(sources : ui_sources)

moc_files = qt6.compile_moc(headers : ['databaseview.h', 'basewidget.h', 'imagelabel.h'],
  # extra_arguments: ['-DMAKES_MY_MOC_HEADER_COMPILE'],
  dependencies: qt6_dep)

sources = [
  'Classes.cpp',
  'databaseview.cpp',
  'basewidget.cpp',
  'imagelabel.cpp',
  'dbtypes/baseclass.cpp',
  'dbtypes/tiktok.cpp',
  'dbtypes/shorts.cpp',
  'dbtypes/reels.cpp'
]

exe = executable('Classes', sources, main_ui, moc_files,
  dependencies : qt6_dep,
  install : true)

test('basic', exe)
