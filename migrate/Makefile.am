
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"expidus1-panel-migrate\" \
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\" \
	-DXDGCONFIGDIR=\"$(sysconfdir)/xdg\" \
	$(PLATFORM_CPPFLAGS)

confdir = $(sysconfdir)/xdg/expidus1/panel
conf_DATA = \
	default.xml

migratedir = $(HELPER_PATH_PREFIX)/expidus1/panel

migrate_PROGRAMS = \
	migrate

migrate_SOURCES = \
	main.c \
	migrate-config.c \
	migrate-config.h \
	migrate-default.c \
	migrate-default.h

migrate_CFLAGS = \
	$(GTK_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(PLATFORM_CFLAGS)

migrate_LDFLAGS = \
	-no-undefined \
	$(PLATFORM_LDFLAGS)

migrate_LDADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(GTK_LIBS) \
	$(ESCONF_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS)

migrate_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la

EXTRA_DIST = \
	default.xml

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
