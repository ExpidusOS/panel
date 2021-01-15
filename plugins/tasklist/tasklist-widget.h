/*
 * Copyright (C) 2008-2010 Nick Schermer <nick@expidus.org>
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

#ifndef __EXPIDUS_TASKLIST_H__
#define __EXPIDUS_TASKLIST_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _ExpidusTasklistClass     ExpidusTasklistClass;
typedef struct _ExpidusTasklist          ExpidusTasklist;
typedef enum   _ExpidusTasklistGrouping  ExpidusTasklistGrouping;
typedef enum   _ExpidusTasklistSortOrder ExpidusTasklistSortOrder;
typedef enum   _ExpidusTasklistMClick    ExpidusTasklistMClick;

#define EXPIDUS_TYPE_TASKLIST            (expidus_tasklist_get_type ())
#define EXPIDUS_TASKLIST(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_TASKLIST, ExpidusTasklist))
#define EXPIDUS_TASKLIST_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_TYPE_TASKLIST, ExpidusTasklistClass))
#define EXPIDUS_IS_TASKLIST(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_TASKLIST))
#define EXPIDUS_IS_TASKLIST_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EXPIDUS_TYPE_TASKLIST))
#define EXPIDUS_TASKLIST_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_TYPE_TASKLIST, ExpidusTasklistClass))



enum _ExpidusTasklistGrouping
{
  EXPIDUS_TASKLIST_GROUPING_NEVER,
  EXPIDUS_TASKLIST_GROUPING_ALWAYS,
  /*EXPIDUS_TASKLIST_GROUPING_AUTO, *//* when space is limited */

  EXPIDUS_TASKLIST_GROUPING_MIN = EXPIDUS_TASKLIST_GROUPING_NEVER,
  EXPIDUS_TASKLIST_GROUPING_MAX = EXPIDUS_TASKLIST_GROUPING_ALWAYS,
  EXPIDUS_TASKLIST_GROUPING_DEFAULT = EXPIDUS_TASKLIST_GROUPING_NEVER
};

enum _ExpidusTasklistSortOrder
{
  EXPIDUS_TASKLIST_SORT_ORDER_TIMESTAMP, /* sort by unique_id */
  EXPIDUS_TASKLIST_SORT_ORDER_GROUP_TIMESTAMP, /* sort by group and then by timestamp */
  EXPIDUS_TASKLIST_SORT_ORDER_TITLE, /* sort by window title */
  EXPIDUS_TASKLIST_SORT_ORDER_GROUP_TITLE, /* sort by group and then by title */
  EXPIDUS_TASKLIST_SORT_ORDER_DND, /* append and support dnd */

  EXPIDUS_TASKLIST_SORT_ORDER_MIN = EXPIDUS_TASKLIST_SORT_ORDER_TIMESTAMP,
  EXPIDUS_TASKLIST_SORT_ORDER_MAX = EXPIDUS_TASKLIST_SORT_ORDER_DND,
  EXPIDUS_TASKLIST_SORT_ORDER_DEFAULT = EXPIDUS_TASKLIST_SORT_ORDER_GROUP_TIMESTAMP
};

enum _ExpidusTasklistMClick
{
  EXPIDUS_TASKLIST_MIDDLE_CLICK_NOTHING, /* do nothing */
  EXPIDUS_TASKLIST_MIDDLE_CLICK_CLOSE_WINDOW, /* close the window */
  EXPIDUS_TASKLIST_MIDDLE_CLICK_MINIMIZE_WINDOW, /* minimize, never minimize with button 1 */

  EXPIDUS_TASKLIST_MIDDLE_CLICK_MIN = EXPIDUS_TASKLIST_MIDDLE_CLICK_NOTHING,
  EXPIDUS_TASKLIST_MIDDLE_CLICK_MAX = EXPIDUS_TASKLIST_MIDDLE_CLICK_MINIMIZE_WINDOW,
  EXPIDUS_TASKLIST_MIDDLE_CLICK_DEFAULT = EXPIDUS_TASKLIST_MIDDLE_CLICK_NOTHING
};



GType expidus_tasklist_get_type                (void) G_GNUC_CONST;

void  expidus_tasklist_set_mode                (ExpidusTasklist        *tasklist,
                                             ExpidusPanelPluginMode  mode);

void  expidus_tasklist_set_size                (ExpidusTasklist   *tasklist,
                                             gint            size);

void  expidus_tasklist_set_nrows               (ExpidusTasklist   *tasklist,
                                             gint            nrows);

void  expidus_tasklist_update_monitor_geometry (ExpidusTasklist   *tasklist);

G_END_DECLS

#endif /* !__EXPIDUS_TASKLIST_H__ */
