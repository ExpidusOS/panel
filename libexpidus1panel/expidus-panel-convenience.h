/*
 * Copyright (C) 2006-2007 Jasper Huijsmans <jasper@expidus.org>
 * Copyright (C) 2008-2010 Nick Schermer <nick@expidus.org>
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



#ifndef __EXPIDUS_PANEL_CONVENIENCE_H__
#define __EXPIDUS_PANEL_CONVENIENCE_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

GtkWidget   *expidus_panel_create_button              (void) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

GtkWidget   *expidus_panel_create_toggle_button       (void) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

const gchar *expidus_panel_get_channel_name           (void);

GdkPixbuf   *expidus_panel_pixbuf_from_source_at_size (const gchar  *source,
                                                    GtkIconTheme *icon_theme,
                                                    gint          dest_width,
                                                    gint          dest_height) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

GdkPixbuf   *expidus_panel_pixbuf_from_source         (const gchar  *source,
                                                    GtkIconTheme *icon_theme,
                                                    gint          size) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

G_END_DECLS

#endif /* !__EXPIDUS_PANEL_CONVENIENCE_H__ */