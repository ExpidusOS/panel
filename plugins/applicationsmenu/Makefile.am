
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libapplicationsmenu\" \
	$(PLATFORM_CPPFLAGS)

plugindir = $(libdir)/expidus1/panel/plugins

plugin_LTLIBRARIES = \
	libapplicationsmenu.la

libapplicationsmenu_built_sources = \
	applicationsmenu-dialog_ui.h

libapplicationsmenu_la_SOURCES = \
	$(libapplicationsmenu_built_sources) \
	applicationsmenu.c \
	applicationsmenu.h

libapplicationsmenu_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(ENDO_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(MARKON_CFLAGS) \
	$(MARKON_GTK3_CFLAGS) \
	$(PLATFORM_CFLAGS)

libapplicationsmenu_la_LDFLAGS = \
	-avoid-version \
	-module \
	-no-undefined \
	-export-symbols-regex '^expidus_panel_module_(preinit|init|construct)' \
	$(PLATFORM_LDFLAGS)

libapplicationsmenu_la_LIBADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la \
	$(GTK_LIBS) \
	$(ENDO_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS) \
	$(MARKON_LIBS) \
	$(MARKON_GTK3_LIBS) \
	$(ESCONF_LIBS)

libapplicationsmenu_la_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la

#
# expidus1-popup-applicationsmenu script
#
bin_SCRIPTS = \
	expidus1-popup-applicationsmenu

expidus1-popup-applicationsmenu: expidus1-popup-applicationsmenu.sh Makefile
	$(AM_V_GEN) $(SED) -e "s,\@bindir\@,$(bindir),g" \
	-e "s,\@localedir\@,$(localedir),g" $< >$@

#
# .desktop file
#
desktopdir = $(datadir)/expidus1/panel/plugins
desktop_in_files = applicationsmenu.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	applicationsmenu-dialog.glade \
	expidus1-popup-applicationsmenu.sh \
	$(desktop_in_files)

DISTCLEANFILES = \
	$(desktop_DATA) \
	expidus1-popup-applicationsmenu

if MAINTAINER_MODE
BUILT_SOURCES = \
	$(libapplicationsmenu_built_sources)

DISTCLEANFILES += \
	$(libapplicationsmenu_built_sources)

applicationsmenu-dialog_ui.h: applicationsmenu-dialog.glade
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=applicationsmenu_dialog_ui $< >$@
endif

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
