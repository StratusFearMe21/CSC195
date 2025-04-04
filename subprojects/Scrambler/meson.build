project('Scrambler', 'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Widgets'])

main_ui = qt6.compile_ui(sources : 'resources/main.ui')

moc_files = qt6.compile_moc(headers : ['mainwidget.h', 'keypresstextedit.h'],
  # extra_arguments: ['-DMAKES_MY_MOC_HEADER_COMPILE'],
  dependencies: qt6_dep)

crypts = [
  'crypts/plain.cpp',
  'crypts/cutter.cpp',
  'crypts/reverser.cpp',
  'crypts/vowelReplacer.cpp',
  'crypts/xorCrypt.cpp',
  'crypts/stringEncryptable.cpp',
]

exe = executable('Scrambler', 'Scrambler.cpp', main_ui, moc_files, crypts,
  dependencies : qt6_dep,
  install : true)

test('basic', exe)
