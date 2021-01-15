DISTCLEANFILES =

AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-DG_LOG_DOMAIN=\"libexpidus1panel\" \
	-DLIBEXPIDUS1PANEL_COMPILATION \
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\" \
	$(PLATFORM_CPPFLAGS)

lib_LTLIBRARIES = \
	libexpidus1panel-2.0.la

libexpidus1panel_public_built_sources = \
	libexpidus1panel-enum-types.h

libexpidus1panel_built_sources = \
	$(libexpidus1panel_public_built_sources) \
	libexpidus1panel-alias.h \
	libexpidus1panel-aliasdef.c \
	libexpidus1panel-enum-types.c \
	libexpidus1panel-marshal.c \
	libexpidus1panel-marshal.h

libexpidus1panel_headers = \
	libexpidus1panel.h \
	libexpidus1panel-config.h \
	libexpidus1panel-enums.h \
	expidus-arrow-button.h \
	expidus-panel-convenience.h \
	expidus-panel-macros.h \
	expidus-panel-plugin.h \
	expidus-panel-plugin-provider.h \
	expidus-panel-image.h

libexpidus1panel_includedir = \
	$(includedir)/expidus1/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API)/libexpidus1panel

libexpidus1panel_include_HEADERS = \
	$(libexpidus1panel_public_built_sources) \
	$(libexpidus1panel_headers)

libexpidus1panel_2_0_la_SOURCES = \
	$(libexpidus1panel_built_sources) \
	$(libexpidus1panel_headers) \
	libexpidus1panel-config.c \
	expidus-arrow-button.c \
	expidus-panel-convenience.c \
	expidus-panel-plugin.c \
	expidus-panel-plugin-provider.c \
	expidus-panel-image.c

libexpidus1panel_2_0_la_CFLAGS =	 \
	$(GTK_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(PLATFORM_CFLAGS)

libexpidus1panel_2_0_la_LDFLAGS = \
	-no-undefined \
	-export-dynamic \
	-version-info $(LIBEXPIDUS1PANEL_VERINFO) \
	-export-symbols-regex '^[^_].*' \
	$(PLATFORM_LDFLAGS)

libexpidus1panel_2_0_la_LIBADD = \
	$(GTK_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	-lm

#
# Pkg-config file
#
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).pc

#
# Build sources
#
if MAINTAINER_MODE

libexpidus1panel-marshal.h: libexpidus1panel-marshal.list Makefile
	$(AM_V_GEN) glib-genmarshal --prefix=_libexpidus1panel_marshal --internal --header $< > $@

libexpidus1panel-marshal.c: libexpidus1panel-marshal.list Makefile
	$(AM_V_GEN) echo "#include <libexpidus1panel/libexpidus1panel-marshal.h>" > $@ \
	&& glib-genmarshal --prefix=_libexpidus1panel_marshal --body $< >> $@

libexpidus1panel-alias.h: make-libexpidus1panel-alias.pl libexpidus1panel.symbols
	$(AM_V_GEN) $(PERL) $(srcdir)/make-libexpidus1panel-alias.pl $(srcdir)/libexpidus1panel.symbols > $@

libexpidus1panel-aliasdef.c: make-libexpidus1panel-alias.pl libexpidus1panel.symbols
	$(AM_V_GEN) $(PERL) $(srcdir)/make-libexpidus1panel-alias.pl -def < $(srcdir)/libexpidus1panel.symbols > $@

libexpidus1panel-enum-types.h: $(libexpidus1panel_headers) Makefile
	$(AM_V_GEN) ( cd $(srcdir) && glib-mkenums \
		--fhead "#ifndef __LIBEXPIDUS1PANEL_ENUM_TYPES_H__\n#define __LIBEXPIDUS1PANEL_ENUM_TYPES_H__\n#include <glib-object.h>\nG_BEGIN_DECLS\n" \
		--fprod "/* enumerations from \"@filename@\" */\n" \
		--vhead "GType @enum_name@_get_type (void) G_GNUC_CONST;\n#define EXPIDUS_TYPE_@ENUMSHORT@ (@enum_name@_get_type())\n" \
		--ftail "G_END_DECLS\n\n#endif /* !__LIBEXPIDUS1PANEL_ENUM_TYPES_H__ */" \
		$(libexpidus1panel_headers) ) > $@

libexpidus1panel-enum-types.c:  $(libexpidus1panel_headers) Makefile
	$(AM_V_GEN) ( cd $(srcdir) && glib-mkenums \
		--fhead "#include <libexpidus1panel/libexpidus1panel-enums.h>\n#include <libexpidus1panel/libexpidus1panel-enum-types.h>\n#include <libexpidus1panel/libexpidus1panel-alias.h>" \
		--fprod "\n/* enumerations from \"@filename@\" */" \
		--vhead "GType\n@enum_name@_get_type (void)\n{\n\tstatic GType type = 0;\n\tif (type == 0) {\n\tstatic const G@Type@Value values[] = {"\
		--vprod "\t{ @VALUENAME@, \"@VALUENAME@\", \"@valuenick@\" }," \
		--vtail "\t{ 0, NULL, NULL }\n\t};\n\ttype = g_@type@_register_static (\"@EnumName@\", values);\n  }\n\treturn type;\n}\n" \
		--ftail "\n#define __LIBEXPIDUS1PANEL_ENUM_TYPES_C__\n#include <libexpidus1panel/libexpidus1panel-aliasdef.c>\n" \
		$(libexpidus1panel_headers) ) > $@

DISTCLEANFILES += \
	$(libexpidus1panel_built_sources)

BUILT_SOURCES = \
	$(libexpidus1panel_built_sources)

CLEANFILES = \
	actual-abi \
	expected-abi

endif
# endif MAINTAINER_MODE


# GObject Introspection
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ENV = CC="$(CC)"
INTROSPECTION_SCANNER_ARGS = \
	--add-include-path=$(srcdir) \
	--add-include-path=$(prefix)/share/gir-1.0 \
	--warn-all \
	--identifier-prefix=Expidus \
	--identifier-prefix=expidus \
	--identifier-prefix=LIBEXPIDUS1PANEL \
	--identifier-prefix=libexpidus1panel \
	--identifier-prefix=Plugin \
	--c-include=libexpidus1panel/libexpidus1panel.h
INTROSPECTION_COMPILER_ARGS = \
	--includedir=$(srcdir) \
	--includedir=$(prefix)/share/gir-1.0 \
	--includedir=.

if HAVE_INTROSPECTION
introspection_sources = $(libexpidus1panel_2_0_la_SOURCES)

Libexpidus1panel-2.0.gir: libexpidus1panel-2.0.la Makefile
Libexpidus1panel_2_0_gir_INCLUDES = GObject-2.0 GLib-2.0 Gio-2.0 Gtk-3.0 Libexpidus1util-1.0
Libexpidus1panel_2_0_gir_CFLAGS = $(AM_CPPFLAGS)
Libexpidus1panel_2_0_gir_LIBS = libexpidus1panel-2.0.la
Libexpidus1panel_2_0_gir_FILES = $(introspection_sources)
Libexpidus1panel_2_0_gir_EXPORT_PACKAGES = libexpidus1panel-2.0
INTROSPECTION_GIRS += Libexpidus1panel-2.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

DISTCLEANFILES += $(gir_DATA) $(typelib_DATA)
endif
# endif HAVE_INTROSPECTION

EXTRA_DIST = \
	abicheck.sh \
	libexpidus1panel.symbols \
	libexpidus1panel-2.0.deps \
	Libexpidus1panel-2.0.metadata \
	libexpidus1panel-alias.h \
	libexpidus1panel-aliasdef.c \
	libexpidus1panel-marshal.list \
	make-libexpidus1panel-alias.pl

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

libexpidus1panel-2.0.vapi: Libexpidus1panel-2.0.gir libexpidus1panel-2.0.deps

VAPIGEN_VAPIS = libexpidus1panel-2.0.vapi
VAPIGEN_GIRDIRS = $(prefix)/share/gir-1.0

##libexpidus1panel_2_0_vapi_DEPS = libexpidus1panel-2.0 GObject-2.0 GLib-2.0 Gtk-3.0 libexpidus1util-1.0
libexpidus1panel_2_0_vapi_METADATADIRS = .
libexpidus1panel_2_0_vapi_FILES = Libexpidus1panel-2.0.gir

vapidir = $(datadir)/vala/vapi
vapi_DATA = $(VAPIGEN_VAPIS) $(VAPIGEN_VAPIS:.vapi=.deps)
endif

if HAVE_GNUC_VISIBILITY
TESTS =	abicheck.sh
endif

# required for gtk-doc
dist-hook: all

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
