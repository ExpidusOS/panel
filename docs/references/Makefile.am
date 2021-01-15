## Process this file with automake to produce Makefile.in

# The name of the module.
DOC_MODULE=libexpidus1panel

# Uncomment for versioned docs and specify the version of the module, e.g. '2'.
DOC_MODULE_VERSION=$(LIBEXPIDUS1PANEL_VERSION_API)

# The top-level SGML file.
DOC_MAIN_SGML_FILE=$(DOC_MODULE)-docs.xml

# Extra options to supply to gtkdoc-scan
SCAN_OPTIONS=--deprecated-guards="LIBEXPIDUS1PANEL_DEPRECATED"

# The directory containing the source code. Relative to $(srcdir)
DOC_SOURCE_DIR=../../libexpidus1panel

# Extra options to supply to gtkdoc-mkdb
MKDB_OPTIONS=--output-format=xml --sgml-mode --name-space=expidus

# Extra options to supply to gtkdoc-fixxref
FIXXREF_OPTIONS=

# Used for dependencies
HFILE_GLOB=$(top_srcdir)/libexpidus1panel/*.h
CFILE_GLOB=$(top_srcdir)/libexpidus1panel/*.c

# Header files to ignore when scanning
IGNORE_HFILES= \
	libexpidus1panel-alias.h \
	libexpidus1panel-marshal.h \
	expidus-panel-plugin-provider.h \
	libexpidus1panel-enum-types.h

# Extra files to add when scanning (relative to $srcdir)
EXTRA_HFILES=

# Images to copy into HTML directory
HTML_IMAGES =

# Extra SGML files that are included by DOC_MAIN_SGML_FILE
content_files = \
	version.xml

# CFLAGS and LDFLAGS for compiling scan program. Only needed
# if $(DOC_MODULE).types is non-empty.
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-I$(top_builddir) \
	$(GTK_CFLAGS) \
	$(LIBEXPIDUS1UTIL_CFLAGS) \
	$(GTK_DOC_EXTRA_CFLAGS)

GTKDOC_LIBS = \
	$(GTK_LIBS) \
	$(LIBEXPIDUS1UTIL_LIBS) \
	$(top_builddir)/libexpidus1panel/libexpidus1panel-$(LIBEXPIDUS1PANEL_VERSION_API).la

include $(top_srcdir)/gtk-doc.make

# Other files to distribute
EXTRA_DIST += \
	version.xml.in

if MAINTAINER_MODE
%.1: %.xml
	xsltproc -nonet http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $<
endif

# required for gtk-doc
dist-hook: all

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
