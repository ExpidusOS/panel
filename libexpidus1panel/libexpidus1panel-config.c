/*
 * Copyright (C) 2009-2010 Nick Schermer <nick@expidus.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libexpidus1panel/libexpidus1panel-config.h>
#include <libexpidus1panel/libexpidus1panel-alias.h>



/**
 * SECTION: config
 * @title: Version Information
 * @short_description: Information about the panel version in use.
 * @include: libexpidus1panel/libexpidus1panel.h
 *
 * The panel library provides version information, which could be used
 * by plugins to handle new API.
 **/



/**
 * libexpidus1panel_major_version:
 *
 * The major version number of the libexpidus1panel library (e.g. in
 * version 4.8.0 this is 4).
 *
 * This variable is in the library, so represents the
 * libexpidus1panel library you have linked against. Contrast with the
 * #LIBEXPIDUS1PANEL_MAJOR_VERSION macro, which represents the major
 * version of the libexpidus1panel headers you have included.
 *
 * Since: 4.8
 **/
const guint libexpidus1panel_major_version = LIBEXPIDUS1PANEL_MAJOR_VERSION;



/**
 * libexpidus1panel_minor_version:
 *
 * The minor version number of the libexpidus1panel library (e.g. in
 * version 4.8.0 this is 8).
 *
 * This variable is in the library, so represents the
 * libexpidus1panel library you have linked against. Contrast with the
 * #LIBEXPIDUS1PANEL_MINOR_VERSION macro, which represents the minor
 * version of the libexpidus1panel headers you have included.
 *
 * Since: 4.8
 **/
const guint libexpidus1panel_minor_version = LIBEXPIDUS1PANEL_MINOR_VERSION;



/**
 * libexpidus1panel_micro_version:
 *
 * The micro version number of the libexpidus1panel library (e.g. in
 * version 4.8.0 this is 0).
 *
 * This variable is in the library, so represents the
 * libexpidus1panel library you have linked against. Contrast with the
 * #LIBEXPIDUS1PANEL_MICRO_VERSION macro, which represents the micro
 * version of the libexpidus1panel headers you have included.
 *
 * Since: 4.8
 **/
const guint libexpidus1panel_micro_version = LIBEXPIDUS1PANEL_MICRO_VERSION;



/**
 * libexpidus1panel_check_version:
 * @required_major: the required major version.
 * @required_minor: the required minor version.
 * @required_micro: the required micro version.
 *
 * Checks that the libexpidus1panel library in use is compatible with
 * the given version. Generally you would pass in the constants
 * #LIBEXPIDUS1PANEL_MAJOR_VERSION, #LIBEXPIDUS1PANEL_MINOR_VERSION and
 * #LIBEXPIDUS1PANEL_MICRO_VERSION as the three arguments to this
 * function; that produces a check that the library in use is
 * compatible with the version of libexpidus1panel the extension was
 * compiled against.
 *
 * <example>
 * <title>Checking the runtime version of the Libexpidus1panel library</title>
 * <programlisting>
 * const gchar *mismatch;
 * mismatch = libexpidus1panel_check_version (LIBEXPIDUS1PANEL_MAJOR_VERSION,
 *                                      LIBEXPIDUS1PANEL_MINOR_VERSION,
 *                                      LIBEXPIDUS1PANEL_MICRO_VERSION);
 * if (G_UNLIKELY (mismatch != NULL))
 *   g_error ("Version mismatch: %<!---->s", mismatch);
 * </programlisting>
 * </example>
 *
 * Returns: %NULL if the library is compatible with the given version,
 *          or a string describing the version mismatch. The returned
 *          string is owned by the library and must not be freed or
 *          modified by the caller.
 *
 * Since: 4.8
 **/
const gchar *
libexpidus1panel_check_version (guint required_major,
                             guint required_minor,
                             guint required_micro)
{
  if (required_major > LIBEXPIDUS1PANEL_MAJOR_VERSION)
    return "Expidus Panel version too old (major mismatch)";
  if (required_major < LIBEXPIDUS1PANEL_MAJOR_VERSION)
    return "Expidus Panel version too new (major mismatch)";
  if (required_minor > LIBEXPIDUS1PANEL_MINOR_VERSION)
    return "Expidus Panel version too old (minor mismatch)";
  if (required_minor == LIBEXPIDUS1PANEL_MINOR_VERSION
      && required_micro > LIBEXPIDUS1PANEL_MICRO_VERSION)
    return "Expidus Panel version too old (micro mismatch)";
  return NULL;
}



#define __LIBEXPIDUS1PANEL_CONFIG_C__
#include <libexpidus1panel/libexpidus1panel-aliasdef.c>
