project('Fail', 'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

sources = [
  'Fail.cpp',
  'Shape.cpp',
  'Rectangle.cpp',
  'Circle.cpp',
]

exe = executable('Fail', sources,
  install : true)

test('basic', exe)
