
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libexpidusmenu\" \
	$(PLATFORM_CPPFLAGS)

plugindir = $(libdir)/expidus1/panel/plugins

plugin_LTLIBRARIES = \
	libexpidusmenu.la

libexpidusmenu_built_sources = \
	expidusmenu-dialog_ui.h

libexpidusmenu_la_SOURCES = \
	$(libexpidusmenu_built_sources) \
	expidusmenu.c \
	expidusmenu.h

libexpidusmenu_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(ENDO_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(MARKON_CFLAGS) \
	$(MARKON_GTK3_CFLAGS) \
	$(LIBWNCK_CFLAGS) \
	$(PLATFORM_CFLAGS)

libexpidusmenu_la_LDFLAGS = \
	-avoid-version \
	-module \
	-no-undefined \
	-export-symbols-regex '^expidus_panel_module_(preinit|init|construct)' \
	$(PLATFORM_LDFLAGS)

libexpidusmenu_la_LIBADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la \
	$(GTK_LIBS) \
	$(ENDO_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS) \
	$(MARKON_LIBS) \
	$(MARKON_GTK3_LIBS) \
	$(LIBWNCK_LIBS) \
	$(ESCONF_LIBS)

libexpidusmenu_la_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la

#
# .desktop file
#
desktopdir = $(datadir)/expidus1/panel/plugins
desktop_in_files = expidusmenu.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	expidusmenu-dialog.glade \
	$(desktop_in_files)

DISTCLEANFILES = \
	$(desktop_DATA)

if MAINTAINER_MODE
BUILT_SOURCES = \
	$(libexpidusmenu_built_sources)

DISTCLEANFILES += \
	$(libexpidusmenu_built_sources)

expidusmenu-dialog_ui.h: expidusmenu-dialog.glade
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=expidusmenu_dialog_ui $< >$@
endif

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
