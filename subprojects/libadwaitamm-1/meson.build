# This file is part of libadwaitamm.

project('libadwaitamm', 'cpp',
  version: '1.4.0',
  license: 'LGPLv2.1+',
  default_options: [
    'cpp_std=c++17',
    'warning_level=1',
  ],
  meson_version: '>= 0.62.0', # required for variables in pkgconfig.generate()
)

libadwaitamm_api_version = '1'
libadwaitamm_pcname = meson.project_name() + '-' + libadwaitamm_api_version

libadwaitamm_version_array = meson.project_version().split('.')
libadwaitamm_major_version = libadwaitamm_version_array[0].to_int()
libadwaitamm_minor_version = libadwaitamm_version_array[1].to_int()
libadwaitamm_micro_version = libadwaitamm_version_array[2].to_int()

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
# The relation between libtool's current:revison:age interface versioning
# and the .so filename, .so.x.y.z, is
# x = current - age
# y = age
# z = revision
# If libtool_soversion is updated as described in libtool's documentation,
# x.y.z will usually *not* be equal to meson.project_version().
libtool_soversion = [0, 0, 0]
libadwaitamm_libversion = '@0@.@1@.@2@'.format(
  libtool_soversion[0] - libtool_soversion[2],
  libtool_soversion[2],
  libtool_soversion[1]
)
macos_darwin_versions = [
  libtool_soversion[0] + 1,
  '@0@.@1@'.format(libtool_soversion[0] + 1, libtool_soversion[1])
]

# Source and build root directories of the current (sub)project.
project_source_root = meson.project_source_root()
project_build_root = meson.project_build_root()

# Use the Python installation that Meson uses. Its version is >= 3.7.
python3 = import('python').find_installation()

# Do we build from a git repository?
# Suppose we do if and only if the meson.build file is tracked by git.
cmd_py = '''
import shutil, subprocess, sys
git_exe = shutil.which('git')
if not git_exe:
  sys.exit(1)
cmd = [ git_exe, 'ls-files', '--error-unmatch', 'meson.build' ]
sys.exit(subprocess.run(cmd, cwd=sys.argv[1], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode)
'''
is_git_build = run_command(
  python3, '-c', cmd_py,
  project_source_root,
  check: false,
).returncode() == 0

# Are we testing a dist tarball while it's being built?
is_dist_check = project_source_root.contains('dist-unpack') and \
                project_build_root.contains('dist-build')

# Options.
maintainer_mode_opt = get_option('maintainer-mode')
maintainer_mode = maintainer_mode_opt == 'true' or \
                 (maintainer_mode_opt == 'if-git-build' and is_git_build)
if is_dist_check
  message('Looks like a tarball is being tested. ' + \
          'Option "dist-warnings" is used instead of "warnings".')
  cpp_warnings = get_option('dist-warnings')
else
  cpp_warnings = get_option('warnings')
endif
if get_option('warning_level') in ['0','1','2','3','4','5']
  warning_level = get_option('warning_level').to_int()
else
  # For instance get_option('warning_level') == 'everything'
  warning_level = 99
endif
werror = get_option('werror')
build_deprecated_api = get_option('build-deprecated-api')
build_documentation_opt = get_option('build-documentation')
build_documentation = build_documentation_opt == 'true' or \
                     (build_documentation_opt == 'if-maintainer-mode' and maintainer_mode)
build_examples = get_option('build-examples')
build_tests = get_option('build-tests')

# Installation directories are relative to {prefix}.
install_prefix = get_option('prefix')
install_includedir = get_option('includedir')
install_libdir = get_option('libdir')
install_datadir = get_option('datadir')
install_pkgconfigdir = install_libdir / 'pkgconfig'

# Dependencies.
# libadwaitamm_build_dep: Dependencies when building the libadwaitamm library.
# libadwaitamm_own_dep (created in libadwaita/libadwaitamm/meson.build):
#   Dependencies when using the libadwaitamm library.
glibmm_req = '>= 2.68.0'
gtkmm_req = '>= 4.12.0'
libadwaita_req = '>= 1.0.0'
pangomm_req = '>= 2.50.0'
pangomm_dep = dependency('pangomm-2.48', version: pangomm_req)
glibmm_dep = dependency('glibmm-2.68', version: glibmm_req)
gtkmm_dep = dependency('gtkmm-4.0', version: gtkmm_req)
# or: glibmm_dep = dependency('glibmm-2.4', version: glibmm_req)
libadwaita_dep = dependency('libadwaita-1', version: libadwaita_req)
libadwaitamm_build_dep = [glibmm_dep, gtkmm_dep, libadwaita_dep]
libadwaitamm_requires = ' '.join([
  'glibmm-2.68', glibmm_req,
# or:  'glibmm-2.4', glibmm_req,
  'libadwaita-1', libadwaita_req,
])

gmmproc_extra_m4_dirs = [pangomm_dep.get_variable(pkgconfig: 'gmmprocm4dir', internal: 'gmmprocm4dir')] \
+ [gtkmm_dep.get_variable(pkgconfig: 'gmmprocm4dir', internal: 'gmmprocm4dir')]

gnome = import('gnome')

# Some dependencies are required only in maintainer mode and/or if
# reference documentation shall be built.
mm_common_get = find_program('mm-common-get', required: false)
if maintainer_mode and not mm_common_get.found()
  message('Maintainer mode requires the \'mm-common-get\' command. If it is not found,\n' +
          'install the \'mm-common\' package, version 1.0.0 or higher.')
  # If meson --wrap-mode != forcefallback, Meson falls back to the mm-common
  # subproject only if mm-common-get is required.
  mm_common_get = find_program('mm-common-get', required: true)
endif
m4 = find_program('m4', required: maintainer_mode) # Used by gmmproc (in glibmm)
doxygen = find_program('doxygen', required: build_documentation)
dot = find_program('dot', required: false) # Used by Doxygen, if found
xsltproc = find_program('xsltproc', required: build_documentation)

if build_documentation and not dot.found()
  message('The \'dot\' command is not found.\n  ' + \
          'This will affect the look of the inheritance diagrams in the documentation.')
endif

# Where to find gmmproc and generate_wrap_init.pl.
gmmproc_dir = glibmm_dep.get_variable(pkgconfig: 'gmmprocdir', internal: 'gmmprocdir')

[glibmm_dep.get_variable('gmmprocdir'), gtkmm_dep.get_variable(pkgconfig: 'gmmprocm4dir', internal: 'gmmprocm4dir')]

# Script files copied to 'untracked' by mm-common-get.
script_dir = project_source_root / 'untracked' / 'build_scripts'
generate_binding = script_dir / 'generate-binding.py'
doc_reference = script_dir / 'doc-reference.py'
dist_changelog = script_dir / 'dist-changelog.py'
dist_build_scripts = script_dir / 'dist-build-scripts.py'
check_dllexport_usage = script_dir / 'check-dllexport-usage.py'

if maintainer_mode
  # Copy files to untracked/build_scripts and untracked/doc.
  run_command(mm_common_get, '--force', script_dir,
    project_source_root / 'untracked' / 'doc',
    check: true,
  )
elif not import('fs').is_file(generate_binding)
  error('Missing files in untracked/. You must enable maintainer-mode.')
endif

# Check if perl is required and available.
doc_perl_prop = run_command(
  python3, doc_reference, 'get_script_property',
  '', # MMDOCTOOLDIR is not used
  'requires_perl',
  check: false,
)
doc_requires_perl = true
if doc_perl_prop.returncode() == 0 and doc_perl_prop.stdout() == 'false'
  doc_requires_perl = false
endif

perl = find_program('perl', required: maintainer_mode or \
  (build_documentation and doc_requires_perl))

cpp_compiler = meson.get_compiler('cpp')

# Set compiler warnings.
# Meson warns if any of the /W1, /W2, /W3, /W4, /Wall, -Wall, -Wextra, -Werror
# compiler options are added with add_project_arguments().
# Avoid such warnings, when possible.
# See _warn_about_builtin_args() in meson/mesonbuild/interpreter/interpreter.py.
warning_flags = []
if cpp_warnings == 'min'
  if warning_level == 0
    warning_flags = ['-Wall']
  endif
elif cpp_warnings == 'max' or cpp_warnings == 'fatal'
  if warning_level < 3
    warning_flags = ['-pedantic', '-Wall', '-Wextra']
  endif
  warning_flags += '-Wformat-security -Wsuggest-override -Wshadow -Wno-long-long'.split()
  if cpp_warnings == 'fatal'
    if not werror
      warning_flags += ['-Werror']
    endif
    deprecations = 'G LIBADWAITA GLIBMM SIGCXX'.split()
    foreach d : deprecations
      warning_flags += '-D@0@_DISABLE_DEPRECATED'.format(d)
    endforeach
  endif
endif

warning_flags = cpp_compiler.get_supported_arguments(warning_flags)
add_project_arguments(warning_flags, language: 'cpp')

subdir('tools/extra_defs_gen')
subdir('libadwaita')
subdir('examples')
subdir('tests')
subdir('doc/reference')

# Add a ChangeLog file to the distribution directory.
meson.add_dist_script(
  python3, dist_changelog,
  project_source_root,
)
# Add build scripts to the distribution directory, and delete .gitignore
# files and an empty $MESON_PROJECT_DIST_ROOT/build/ directory.
meson.add_dist_script(
  python3, dist_build_scripts,
  project_source_root,
  'untracked' / 'build_scripts',
)

if meson.is_subproject()
  pkgconfig_vars = {
    'gmmprocm4dir': project_source_root / 'tools' / 'm4',
    'htmlrefdir': install_prefix / install_docdir / 'reference' / 'html',
    'htmlrefpub': 'https://gnome.pages.gitlab.gnome.org/' + meson.project_name(),
  }
  if build_documentation
    pkgconfig_vars += {'doxytagfile': tag_file.full_path()}
    # May be used in a main project.
    global_tag_file_target = tag_file
  endif
  libadwaitamm_dep = declare_dependency(
    dependencies: libadwaitamm_own_dep,
    variables: pkgconfig_vars,
  )

  # A main project that looks for libadwaitamm_pcname.pc shall find libadwaitamm_dep.
  meson.override_dependency(libadwaitamm_pcname, libadwaitamm_dep)
endif


# Print a summary.
real_maintainer_mode = ''
if maintainer_mode_opt == 'if-git-build'
  real_maintainer_mode = ' (@0@)'.format(maintainer_mode)
endif

real_build_documentation = ''
if build_documentation_opt == 'if-maintainer-mode'
  real_build_documentation = ' (@0@)'.format(build_documentation)
endif

summary = [
  '',
  '------',
  meson.project_name() + ' ' + meson.project_version(),
  '',
  '         Maintainer mode: @0@@1@'.format(maintainer_mode_opt, real_maintainer_mode),
  '       Compiler warnings: @0@ (warning_level: @1@, werror: @2@)'. \
                             format(cpp_warnings, warning_level, werror),
  '    Build deprecated API: @0@'.format(build_deprecated_api),
  'Build HTML documentation: @0@@1@'.format(build_documentation_opt, real_build_documentation),
  '  Build example programs: @0@'.format(build_examples),
  '     Build test programs: @0@'.format(build_tests),
  'Directories:',
  '                  prefix: @0@'.format(install_prefix),
  '              includedir: @0@'.format(install_prefix / install_includedir),
  '    includelibadwaitammdir: @0@'.format(install_prefix / install_includedir / libadwaitamm_pcname),
  '                  libdir: @0@'.format(install_prefix / install_libdir),
  '        includeconfigdir: @0@'.format(install_prefix / install_includeconfigdir),
  '                   m4dir: @0@'.format(install_prefix / install_m4dir),
  '            pkgconfigdir: @0@'.format(install_prefix / install_pkgconfigdir),
  '                 datadir: @0@'.format(install_prefix / install_datadir),
  '                  docdir: @0@'.format(install_prefix / install_docdir),
  '              devhelpdir: @0@'.format(install_prefix / install_devhelpdir),
  '------'
]

message('\n'.join(summary))
