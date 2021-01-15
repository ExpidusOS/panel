
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libwindowmenu\" \
	-DWNCK_I_KNOW_THIS_IS_UNSTABLE \
	$(PLATFORM_CPPFLAGS)

plugindir = $(libdir)/expidus1/panel/plugins

plugin_LTLIBRARIES = \
	libwindowmenu.la

libwindowmenu_built_sources = \
	windowmenu-dialog_ui.h

libwindowmenu_la_SOURCES = \
	$(libwindowmenu_built_sources) \
	windowmenu.c \
	windowmenu.h

libwindowmenu_la_CFLAGS = \
	$(GTK_CFLAGS) \
	$(ENDO_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(LIBWNCK_CFLAGS) \
	$(PLATFORM_CFLAGS)

libwindowmenu_la_LDFLAGS = \
	-avoid-version \
	-module \
	-no-undefined \
	-export-symbols-regex '^expidus_panel_module_(preinit|init|construct)' \
	$(PLATFORM_LDFLAGS)

libwindowmenu_la_LIBADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la \
	$(GTK_LIBS) \
	$(ENDO_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS) \
	$(LIBWNCK_LIBS) \
	$(ESCONF_LIBS)

libwindowmenu_la_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la

#
# expidus1-popup-windowmenu script
#
bin_SCRIPTS = \
	expidus1-popup-windowmenu

expidus1-popup-windowmenu: expidus1-popup-windowmenu.sh Makefile
	$(AM_V_GEN) $(SED) -e "s,\@bindir\@,$(bindir),g" \
	-e "s,\@localedir\@,$(localedir),g" $< >$@

#
# .desktop file
#
desktopdir = $(datadir)/expidus1/panel/plugins
desktop_in_files = windowmenu.desktop.in.in
desktop_DATA = $(desktop_in_files:.desktop.in.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST = \
	windowmenu-dialog.glade \
	expidus1-popup-windowmenu.sh \
	$(desktop_in_files)

DISTCLEANFILES = \
	$(desktop_DATA) \
	expidus1-popup-windowmenu

if MAINTAINER_MODE
BUILT_SOURCES = \
	$(libwindowmenu_built_sources)

DISTCLEANFILES += \
	$(libwindowmenu_built_sources)

windowmenu-dialog_ui.h: windowmenu-dialog.glade
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=windowmenu_dialog_ui $< >$@
endif

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
