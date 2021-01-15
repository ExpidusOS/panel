
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"expidus1-panel-wrapper\" \
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\" \
	$(PLATFORM_CPPFLAGS)

wrapperdir = $(HELPER_PATH_PREFIX)/expidus1/panel

wrapper_PROGRAMS = \
	wrapper-2.0

wrapper_2_0_SOURCES = \
	main.c \
	wrapper-module.c \
	wrapper-module.h \
	wrapper-plug.c \
	wrapper-plug.h

wrapper_2_0_CFLAGS = \
	$(GTK_CFLAGS) \
	$(GIO_CFLAGS) \
	$(GMODULE_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(PLATFORM_CFLAGS)

wrapper_2_0_LDFLAGS = \
	-no-undefined \
	$(PLATFORM_LDFLAGS)

wrapper_2_0_LDADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(GTK_LIBS) \
	$(GIO_LIBS) \
	$(GMODULE_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS)

wrapper_2_0_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la

if MAINTAINER_MODE

#wrapper-marshal.h: $(top_builddir)/panel/panel-marshal.list Makefile
#	$(AM_V_GEN)glib-genmarshal --header --prefix=wrapper_marshal $< > $@
#
#wrapper-marshal.c: $(top_builddir)/panel/panel-marshal.list Makefile
#	$(AM_V_GEN) echo "#include <wrapper/wrapper-marshal.h>" > $@ \
#	&& glib-genmarshal --body --prefix=wrapper_marshal $< >> $@

BUILT_SOURCES = \
	$(wrapper_built_sources)

DISTCLEANFILES = \
	$(wrapper_built_sources)

endif

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
