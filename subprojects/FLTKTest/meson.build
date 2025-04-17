project('FLTKTest', 'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

cmake = import('cmake')
fs = import('fs')

fltk = cmake.subproject('fltk')
fltk_dep = fltk.dependency('fltk')
fltk_fluid = fltk.target('fluid')


prog_python = find_program('python3')

fluid_resources = custom_target(
  'fluid-generated',
  input: ['resources/gen_headers.py', 'resources/FLTKTest.fl'],
  output: ['FLTKTest.cxx', 'FLTKTest.h'],
  command: [prog_python, '@INPUT0@', fltk_fluid, '@OUTPUT0@', '@OUTPUT1@', '@INPUT1@']
)

exe = executable('FLTKTest', 'fltktest.cpp', fluid_resources,
  dependencies : fltk_dep,
  install : true)

test('basic', exe)
