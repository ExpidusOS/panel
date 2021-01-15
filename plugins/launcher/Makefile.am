
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"liblauncher\" \
	-DSN_API_NOT_YET_FROZEN \
	$(PLATFORM_CPPFLAGS)

plugindir = $(libdir)/expidus1/panel/plugins

plugin_LTLIBRARIES = \
	liblauncher.la

liblauncher_built_sources = \
	launcher-dialog_ui.h

liblauncher_la_SOURCES = \
	$(liblauncher_built_sources) \
	launcher.c \
	launcher.h \
	launcher-dialog.c \
	launcher-dialog.h

liblauncher_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(MARKON_CFLAGS) \
	$(MARKON_GTK3_CFLAGS) \
	$(GIO_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(PLATFORM_CFLAGS)

liblauncher_la_LDFLAGS = \
	-avoid-version \
	-module \
	-no-undefined \
	-export-symbols-regex '^expidus_panel_module_(preinit|init|construct)' \
	$(PLATFORM_LDFLAGS)

liblauncher_la_LIBADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la \
	$(GTK_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS) \
	$(MARKON_LIBS) \
	$(MARKON_GTK3_LIBS) \
	$(GIO_LIBS) \
	$(ESCONF_LIBS)

liblauncher_la_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la

#
# .desktop file
#
desktopdir = $(datadir)/expidus1/panel/plugins
desktop_in_files = launcher.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	launcher-dialog.glade \
	$(desktop_in_files)

DISTCLEANFILES = \
	$(desktop_DATA)

if MAINTAINER_MODE
BUILT_SOURCES = \
	$(liblauncher_built_sources)

DISTCLEANFILES += \
	$(libclock_built_sources)

launcher-dialog_ui.h: launcher-dialog.glade
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=launcher_dialog_ui $< >$@
endif

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
