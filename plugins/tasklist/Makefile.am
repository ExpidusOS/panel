
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libtasklist\" \
	-DWNCK_I_KNOW_THIS_IS_UNSTABLE \
	$(PLATFORM_CPPFLAGS)

plugindir = $(libdir)/expidus1/panel/plugins

plugin_LTLIBRARIES = \
	libtasklist.la

libtasklist_built_sources = \
	tasklist-dialog_ui.h

libtasklist_la_SOURCES = \
	$(libtasklist_built_sources) \
	tasklist.c \
	tasklist-widget.c \
	tasklist-widget.h

libtasklist_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(ENDO_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(LIBWNCK_CFLAGS) \
	$(LIBX11_CFLAGS) \
	$(PLATFORM_CFLAGS)

libtasklist_la_LDFLAGS = \
	-avoid-version \
	-module \
	-no-undefined \
	-export-symbols-regex '^expidus_panel_module_(preinit|init|construct)' \
	$(PLATFORM_LDFLAGS)

libtasklist_la_LIBADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la \
	$(GTK_LIBS) \
	$(ENDO_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS) \
	$(LIBWNCK_LIBS) \
	$(LIBX11_LIBS) -lXext \
	$(ESCONF_LIBS)

libtasklist_la_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la

#
# .desktop file
#
desktopdir = $(datadir)/expidus1/panel/plugins
desktop_in_files = tasklist.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	tasklist-dialog.glade \
	$(desktop_in_files)

DISTCLEANFILES = \
	$(desktop_DATA)

if MAINTAINER_MODE
BUILT_SOURCES = \
	$(libtasklist_built_sources)

DISTCLEANFILES += \
	$(libtasklist_built_sources)

tasklist-dialog_ui.h: tasklist-dialog.glade
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=tasklist_dialog_ui $< >$@
endif

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
