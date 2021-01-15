/*
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

#if !defined(LIBEXPIDUS1PANEL_INSIDE_LIBEXPIDUS1PANEL_H) && !defined(LIBEXPIDUS1PANEL_COMPILATION)
#error "Only <libexpidus1panel/libexpidus1panel.h> can be included directly, this file may disappear or change contents"
#endif

#ifndef __EXPIDUS_PANEL_IMAGE_H__
#define __EXPIDUS_PANEL_IMAGE_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _ExpidusPanelImageClass   ExpidusPanelImageClass;
typedef struct _ExpidusPanelImage        ExpidusPanelImage;
typedef struct _ExpidusPanelImagePrivate ExpidusPanelImagePrivate;

struct _ExpidusPanelImageClass
{
  /*< private >*/
  GtkWidgetClass __parent__;

  /*< private >*/
  void (*reserved1) (void);
  void (*reserved2) (void);
  void (*reserved3) (void);
  void (*reserved4) (void);
};

/**
 * ExpidusPanelImage:
 *
 * This struct contain private data only and should be accessed by
 * the functions below.
 **/
struct _ExpidusPanelImage
{
  /*< private >*/
  GtkWidget __parent__;

  /*< private >*/
  ExpidusPanelImagePrivate *priv;
};

#define EXPIDUS_TYPE_PANEL_IMAGE            (expidus_panel_image_get_type ())
#define EXPIDUS_PANEL_IMAGE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_PANEL_IMAGE, ExpidusPanelImage))
#define EXPIDUS_PANEL_IMAGE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_TYPE_PANEL_IMAGE, ExpidusPanelImageClass))
#define EXPIDUS_IS_PANEL_IMAGE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_PANEL_IMAGE))
#define EXPIDUS_IS_PANEL_IMAGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EXPIDUS_TYPE_PANEL_IMAGE))
#define EXPIDUS_PANEL_IMAGE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_TYPE_PANEL_IMAGE, ExpidusPanelImageClass))

GType      expidus_panel_image_get_type        (void) G_GNUC_CONST;

GtkWidget *expidus_panel_image_new             (void) G_GNUC_MALLOC;

GtkWidget *expidus_panel_image_new_from_pixbuf (GdkPixbuf      *pixbuf) G_GNUC_MALLOC;

GtkWidget *expidus_panel_image_new_from_source (const gchar    *source) G_GNUC_MALLOC;

void       expidus_panel_image_set_from_pixbuf (ExpidusPanelImage *image,
                                             GdkPixbuf      *pixbuf);

void       expidus_panel_image_set_from_source (ExpidusPanelImage *image,
                                             const gchar    *source);

void       expidus_panel_image_set_size        (ExpidusPanelImage *image,
                                             gint            size);

gint       expidus_panel_image_get_size        (ExpidusPanelImage *image);

void       expidus_panel_image_clear           (ExpidusPanelImage *image);

G_END_DECLS

#endif /* !__EXPIDUS_PANEL_IMAGE_H__ */
