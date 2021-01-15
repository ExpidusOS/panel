
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libclock\" \
	$(PLATFORM_CPPFLAGS)

plugindir = $(libdir)/expidus1/panel/plugins

plugin_LTLIBRARIES = \
	libclock.la

libclock_built_sources = \
	clock-dialog_ui.h

libclock_la_SOURCES = \
	$(libclock_built_sources) \
	clock.c \
	clock.h \
	clock-time.c \
	clock-time.h \
	clock-analog.c \
	clock-analog.h \
	clock-binary.c \
	clock-binary.h \
	clock-digital.c \
	clock-digital.h \
	clock-fuzzy.c \
	clock-fuzzy.h \
	clock-lcd.c \
	clock-lcd.h

libclock_la_CFLAGS = \
	$(GLIB_CFLAGS) \
	$(GTK_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(CAIRO_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(PLATFORM_CFLAGS)

libclock_la_LDFLAGS =	 \
	-avoid-version \
	-module \
	-no-undefined \
	-export-symbols-regex '^expidus_panel_module_(preinit|init|construct)' \
	$(PLATFORM_LDFLAGS)

libclock_la_LIBADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la \
	$(GLIB_LIBS) \
	$(GTK_LIBS) \
	$(CAIRO_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS) \
	$(ESCONF_LIBS) \
	-lm

libclock_la_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la

#
# .desktop file
#
desktopdir = $(datadir)/expidus1/panel/plugins
desktop_in_files =	clock.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	clock-dialog.glade \
	$(desktop_in_files)

DISTCLEANFILES = \
	$(desktop_DATA)

if MAINTAINER_MODE
BUILT_SOURCES = \
	$(libclock_built_sources)

DISTCLEANFILES += \
	$(libclock_built_sources)

clock-dialog_ui.h: clock-dialog.glade
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=clock_dialog_ui $< >$@
endif

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
