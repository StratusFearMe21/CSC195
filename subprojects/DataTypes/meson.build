project('DataTypes', 'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3',
                     'cpp_std=c++14'])

crossline = subproject('crossline')
crossline_dep = crossline.get_variable('crossline_dep')

exe = executable('DataTypes', 'DataTypes.cpp',
  dependencies : [crossline_dep],
  install : true)

test('basic', exe)
