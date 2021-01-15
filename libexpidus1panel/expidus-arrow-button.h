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



#ifndef __EXPIDUS_ARROW_BUTTON_H__
#define __EXPIDUS_ARROW_BUTTON_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _ExpidusArrowButtonPrivate ExpidusArrowButtonPrivate;
typedef struct _ExpidusArrowButtonClass   ExpidusArrowButtonClass;
typedef struct _ExpidusArrowButton        ExpidusArrowButton;

#define EXPIDUS_TYPE_ARROW_BUTTON            (expidus_arrow_button_get_type ())
#define EXPIDUS_ARROW_BUTTON(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_ARROW_BUTTON, ExpidusArrowButton))
#define EXPIDUS_ARROW_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_TYPE_ARROW_BUTTON, ExpidusArrowButtonClass))
#define EXPIDUS_IS_ARROW_BUTTON(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_ARROW_BUTTON))
#define EXPIDUS_IS_ARROW_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EXPIDUS_TYPE_ARROW_BUTTON))
#define EXPIDUS_ARROW_BUTTON_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_TYPE_ARROW_BUTTON, ExpidusArrowButtonClass))

struct _ExpidusArrowButtonClass
{
  /*< private >*/
  GtkToggleButtonClass __parent__;

  /*< signals >*/
  void (*arrow_type_changed) (ExpidusArrowButton *button,
                              GtkArrowType     type);
};

/**
 * ExpidusArrowButton:
 *
 * This struct contain private data only and should be accessed by
 * the functions below.
 **/
struct _ExpidusArrowButton
{
  /*< private >*/
  GtkToggleButton __parent__;

  /*< private >*/
  ExpidusArrowButtonPrivate *priv;
};

GType         expidus_arrow_button_get_type       (void) G_GNUC_CONST;

GtkWidget    *expidus_arrow_button_new            (GtkArrowType     arrow_type) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

GtkArrowType  expidus_arrow_button_get_arrow_type (ExpidusArrowButton *button);
void          expidus_arrow_button_set_arrow_type (ExpidusArrowButton *button,
                                                GtkArrowType     arrow_type);

gboolean      expidus_arrow_button_get_blinking   (ExpidusArrowButton *button);
void          expidus_arrow_button_set_blinking   (ExpidusArrowButton *button,
                                                gboolean         blinking);

G_END_DECLS

#endif /* !__EXPIDUS_ARROW_BUTTON_H__ */
