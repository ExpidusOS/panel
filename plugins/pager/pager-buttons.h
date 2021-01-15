/*
 * Copyright (C) 2010 Nick Schermer <nick@expidus.org>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __PAGER_BUTTONS_H__
#define __PAGER_BUTTONS_H__

#include <gtk/gtk.h>
#include <libwnck/libwnck.h>

G_BEGIN_DECLS

typedef struct _PagerButtonsClass PagerButtonsClass;
typedef struct _PagerButtons      PagerButtons;

#define EXPIDUS_TYPE_PAGER_BUTTONS            (pager_buttons_get_type ())
#define EXPIDUS_PAGER_BUTTONS(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_PAGER_BUTTONS, PagerButtons))
#define EXPIDUS_PAGER_BUTTONS_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_TYPE_PAGER_BUTTONS, PagerButtonsClass))
#define EXPIDUS_IS_PAGER_BUTTONS(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_PAGER_BUTTONS))
#define EXPIDUS_IS_PAGER_BUTTONS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EXPIDUS_TYPE_PAGER_BUTTONS))
#define EXPIDUS_PAGER_BUTTONS_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_TYPE_PAGER_BUTTONS, PagerButtonsClass))

GType      pager_buttons_get_type        (void) G_GNUC_CONST;

void       pager_buttons_register_type   (ExpidusPanelTypeModule *type_module);

GtkWidget *pager_buttons_new             (WnckScreen          *screen) G_GNUC_MALLOC;

void       pager_buttons_set_orientation (PagerButtons        *pager,
                                          GtkOrientation       orientation);

void       pager_buttons_set_n_rows      (PagerButtons        *pager,
                                          gint                 rows);

void       pager_buttons_set_numbering   (PagerButtons        *pager,
                                          gboolean             numbering);

G_END_DECLS

#endif /* !__PAGER_BUTTONS_H__ */
