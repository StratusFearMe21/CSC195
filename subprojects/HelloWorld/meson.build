project('HelloWorld', 'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

exe = executable('HelloWorld', ['HelloWorld.cpp', 'Student.cpp'],
  install : true)

test('basic', exe)
