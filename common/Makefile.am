
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libpanel-common\" \
	-DLIBEXPIDUS1PANEL_COMPILATION \
	-DHELPDIR=\"$(docdir)/html\" \
	$(PLATFORM_CPPFLAGS)

noinst_LTLIBRARIES = \
	libpanel-common.la

libpanel_common_la_SOURCES = \
	panel-debug.c \
	panel-debug.h \
	panel-utils.c \
	panel-utils.h \
	panel-esconf.c \
	panel-esconf.h

libpanel_common_la_CFLAGS = \
	$(ESCONF_CFLAGS) \
	$(GTK_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(PLATFORM_CFLAGS)

libpanel_common_la_LDFLAGS = \
	-no-undefined \
	$(PLATFORM_LDFLAGS)

libpanel_common_la_LIBADD = \
	$(ESCONF_LIBS) \
	$(GTK_LIBS) \
	$(LIBEXPIDUS1UI_LIBS)

EXTRA_DIST = \
	panel-dbus.h \
	panel-private.h

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
