# libadwaita

# Input: install_includedir, libadwaitamm_pcname, install_libdir,
#        build_deprecated_api, libadwaitamm_major_version,
#        libadwaitamm_minor_version, libadwaitamm_micro_version
# Output: install_includeconfigdir

pkg_conf_data = configuration_data()
if not build_deprecated_api
  pkg_conf_data.set('LIBADWAITAMM_DISABLE_DEPRECATED', true)
endif
pkg_conf_data.set('LIBADWAITAMM_MAJOR_VERSION', libadwaitamm_major_version)
pkg_conf_data.set('LIBADWAITAMM_MINOR_VERSION', libadwaitamm_minor_version)
pkg_conf_data.set('LIBADWAITAMM_MICRO_VERSION', libadwaitamm_micro_version)
pkg_conf_data.set('LIBADWAITAMM_MODULES', libadwaitamm_requires)

install_includeconfigdir = install_libdir / libadwaitamm_pcname / 'include'
configure_file(
  input: 'libadwaitammconfig.h.in',
  output: '@BASENAME@',
  configuration: pkg_conf_data,
  install: true,
  install_dir: install_includeconfigdir,
  install_tag: 'devel',
)

subdir('libadwaitamm')
