project('crossline', 'c')

crossline_inc = include_directories('.')

crossline_lib = static_library('crossline', 'crossline.c')

crossline_dep = declare_dependency(
  include_directories : crossline_inc,
  link_with : crossline_lib,
)
