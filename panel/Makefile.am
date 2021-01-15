
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"expidus1-panel\" \
	-DWNCK_I_KNOW_THIS_IS_UNSTABLE \
	-DDATADIR=\"$(datadir)/expidus1\" \
	-DLIBDIR=\"$(libdir)/expidus1\" \
	-DHELPERDIR=\"$(HELPER_PATH_PREFIX)/expidus1/panel\" \
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\" \
	-DDBUS_API_SUBJECT_TO_CHANGE \
	-DWNCK_I_KNOW_THIS_IS_UNSTABLE \
	$(PLATFORM_CPPFLAGS)

bin_PROGRAMS = \
	expidus1-panel

expidus1_panel_built_sources = \
	panel-gdbus-exported-service.h \
	panel-gdbus-exported-service.c \
	panel-marshal.c \
	panel-marshal.h \
	panel-plugin-external-wrapper-exported.h \
	panel-plugin-external-wrapper-exported.c \
	panel-preferences-dialog-ui.h

expidus1_panel_SOURCES = \
	$(expidus1_panel_built_sources) \
	main.c \
	panel-application.c \
	panel-application.h \
	panel-base-window.c \
	panel-base-window.h \
	panel-dbus-service.c \
	panel-dbus-service.h \
	panel-dbus-client.c \
	panel-dbus-client.h \
	panel-dialogs.c \
	panel-dialogs.h \
	panel-item-dialog.c \
	panel-item-dialog.h \
	panel-itembar.c \
	panel-itembar.h \
	panel-module.c \
	panel-module.h \
	panel-module-factory.c \
	panel-module-factory.h \
	panel-plugin-external.c \
	panel-plugin-external.h \
	panel-plugin-external-wrapper.c \
	panel-plugin-external-wrapper.h \
	panel-preferences-dialog.c \
	panel-preferences-dialog.h \
	panel-tic-tac-toe.c \
	panel-tic-tac-toe.h \
	panel-window.c \
	panel-window.h

expidus1_panel_CFLAGS = \
	$(GTK_CFLAGS) \
	$(GMODULE_CFLAGS) \
	$(GIO_UNIX_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(LIBEXPIDUS1UI_CFLAGS) \
	$(LIBWNCK_CFLAGS) \
	$(ESCONF_CFLAGS) \
	$(LIBX11_CFLAGS) \
	$(LIBWNCK_CFLAGS) \
	$(PLATFORM_CFLAGS)

expidus1_panel_LDFLAGS = \
	-no-undefined \
	$(PLATFORM_LDFLAGS)

expidus1_panel_LDADD = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la \
	$(GTK_LIBS) \
	$(GMODULE_LIBS) \
	$(GIO_UNIX_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(LIBEXPIDUS1UI_LIBS) \
	$(LIBWNCK_LIBS) \
	$(ESCONF_LIBS) \
	$(LIBX11_LIBS) \
	$(LIBWNCK_LIBS) \
	-lm

expidus1_panel_DEPENDENCIES = \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la \
	$(top_builddir)/common/libpanel-common.la

if MAINTAINER_MODE

panel-marshal.h: panel-marshal.list Makefile
	$(AM_V_GEN) glib-genmarshal --prefix=_panel_marshal --internal --header $< > $@

panel-marshal.c: panel-marshal.list Makefile
	$(AM_V_GEN) echo "#include <panel/panel-marshal.h>" > $@ \
	&& glib-genmarshal --prefix=_panel_marshal --body $< >> $@

panel-gdbus-exported-service.h:
panel-gdbus-exported-service.c: panel-dbus-service-infos.xml Makefile
	$(AM_V_GEN) $(GDBUS_CODEGEN) \
	--interface-prefix com.expidus.Panel \
	--c-namespace ExpidusPanel   \
	--generate-c-code panel-gdbus-exported-service \
	$(srcdir)/panel-dbus-service-infos.xml

panel-plugin-external-wrapper-exported.h:
panel-plugin-external-wrapper-exported.c: panel-plugin-external-wrapper-infos.xml Makefile
	$(AM_V_GEN) $(GDBUS_CODEGEN) \
	--interface-prefix com.expidus.Panel.Wrapper \
	--c-namespace ExpidusPanelPluginWrapper   \
	--generate-c-code panel-plugin-external-wrapper-exported \
	$(srcdir)/panel-plugin-external-wrapper-infos.xml

panel-preferences-dialog-ui.h: $(srcdir)/panel-preferences-dialog.glade Makefile
	$(AM_V_GEN) xdt-csource --static --strip-comments --strip-content --name=panel_preferences_dialog_ui $< >$@

#panel-marshal.h: $(srcdir)/panel-marshal.list Makefile
#	$(AM_V_GEN) glib-genmarshal --header --prefix=panel_marshal $< > $@
#
#panel-marshal.c: $(srcdir)/panel-marshal.list Makefile
#	$(AM_V_GEN) echo "#include <panel/panel-marshal.h>" > $@ \
#	&& glib-genmarshal --body --prefix=panel_marshal $< >> $@

DISTCLEANFILES = \
	$(expidus1_panel_built_sources)

BUILT_SOURCES = \
	$(expidus1_panel_built_sources)

endif

EXTRA_DIST = \
	panel-dbus-service-infos.xml \
	panel-plugin-external-wrapper-infos.xml \
	panel-preferences-dialog.glade \
	panel-marshal.list

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
