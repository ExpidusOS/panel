
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libdirectorymenu\" \
	$(PLATFORM_CPPFLAGS)

plugindir = $(libdir)/expidus1/panel/plugins

plugin_LTLIBRARIES = \
	libdirectorymenu.la

libdirectorymenu_built_sources = \
	directorymenu-dialog_ui.h

libdirectorymenu_la_SOURCES = \
	$(libdirectorymenu_built_sources) \
	directorymenu.c \
	directorymenu.h

libdirectorymenu_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(ENDO_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(GIO_CFLAGS) \
	$(GIO_UNIX_CFLAGS) \
	$(PLATFORM_CFLAGS)

libdirectorymenu_la_LDFLAGS = \
	-avoid-version \
	-module \
	-no-undefined \
	-export-symbols-regex '^expidus_panel_module_(preinit|init|construct)' \
	$(PLATFORM_LDFLAGS)

libdirectorymenu_la_LIBADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la \
	$(GTK_LIBS) \
	$(ENDO_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS) \
	$(GIO_LIBS) \
	$(GIO_UNIX_LIBS) \
	$(ESCONF_LIBS)

libdirectorymenu_la_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la

#
# expidus1-popup-directorymenu script
#
bin_SCRIPTS = \
	expidus1-popup-directorymenu

expidus1-popup-directorymenu: expidus1-popup-directorymenu.sh Makefile
	$(AM_V_GEN) $(SED) -e "s,\@bindir\@,$(bindir),g" \
	-e "s,\@localedir\@,$(localedir),g" $< >$@

#
# .desktop file
#
desktopdir = $(datadir)/expidus1/panel/plugins
desktop_in_files = directorymenu.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	directorymenu-dialog.glade \
	expidus1-popup-directorymenu.sh \
	$(desktop_in_files)

DISTCLEANFILES = \
	$(desktop_DATA) \
	expidus1-popup-directorymenu

if MAINTAINER_MODE
BUILT_SOURCES = \
	$(libdirectorymenu_built_sources)

DISTCLEANFILES += \
	$(libdirectorymenu_built_sources)

directorymenu-dialog_ui.h: directorymenu-dialog.glade
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=directorymenu_dialog_ui $< >$@
endif

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
