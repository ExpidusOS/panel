/*
 * Copyright (C) 2008-2009 Nick Schermer <nick@xfce.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __PANEL_PRIVATE_H__
#define __PANEL_PRIVATE_H__

/* support macros for debugging (improved macro for better position indication) */
#ifndef NDEBUG
#define panel_assert(expr)                 g_assert (expr)
#define panel_assert_not_reached()         g_assert_not_reached ()
#define panel_return_if_fail(expr)         G_STMT_START { \
  if (G_UNLIKELY (!(expr))) \
    { \
      g_log (G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, \
             "%s (%s): expression '%s' failed.", G_STRLOC, G_STRFUNC, \
             #expr); \
      return; \
    }; }G_STMT_END
#define panel_return_val_if_fail(expr,val) G_STMT_START { \
  if (G_UNLIKELY (!(expr))) \
    { \
      g_log (G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, \
             "%s (%s): expression '%s' failed.", G_STRLOC, G_STRFUNC, \
             #expr); \
      return (val); \
    }; }G_STMT_END
#else
#define panel_assert(expr)                 G_STMT_START{ (void)0; }G_STMT_END
#define panel_assert_not_reached()         G_STMT_START{ (void)0; }G_STMT_END
#define panel_return_if_fail(expr)         G_STMT_START{ (void)0; }G_STMT_END
#define panel_return_val_if_fail(expr,val) G_STMT_START{ (void)0; }G_STMT_END
#endif

/* handling flags */
#define PANEL_SET_FLAG(flags,flag) G_STMT_START{ ((flags) |= (flag)); }G_STMT_END
#define PANEL_UNSET_FLAG(flags,flag) G_STMT_START{ ((flags) &= ~(flag)); }G_STMT_END
#define PANEL_HAS_FLAG(flags,flag) (((flags) & (flag)) != 0)

/* check if the string is not empty */
#define IS_STRING(string) ((string) != NULL && *(string) != '\0')

/* relative path to the plugin directory */
#define PANEL_PLUGIN_RELATIVE_PATH "xfce4" G_DIR_SEPARATOR_S "panel"

/* relative plugin's rc filename (printf format) */
#define PANEL_PLUGIN_RC_RELATIVE_PATH PANEL_PLUGIN_RELATIVE_PATH G_DIR_SEPARATOR_S "%s-%d.rc"

/* xfconf property base (printf format) */
#define PANEL_PLUGIN_PROPERTY_BASE "/plugins/plugin-%d"

/* quick GList and GSList counting without traversing */
#define LIST_HAS_ONE_ENTRY(l)           ((l) != NULL && (l)->next == NULL)
#define LIST_HAS_ONE_OR_NO_ENTRIES(l)   ((l) == NULL || (l)->next == NULL)
#define LIST_HAS_TWO_OR_MORE_ENTRIES(l) ((l) != NULL && (l)->next != NULL)

/* make this easier to read */
#define PANEL_GDKCOLOR_TO_DOUBLE(gdk_color) gdk_color->red / 65535.00, \
                                            gdk_color->green / 65535.00, \
                                            gdk_color->blue / 65535.00

/* wrapper exit values */
#define WRAPPER_EXIT_SUCCESS     (0)
#define WRAPPER_EXIT_FAILURE     (1)
#define WRAPPER_EXIT_PREINIT     (2)
#define WRAPPER_EXIT_NO_PROVIDER (3)

#endif /* !__PANEL_PRIVATE_H__ */
