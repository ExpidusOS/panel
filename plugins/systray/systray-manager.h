/*
 * Copyright (c) 2002      Anders Carlsson <andersca@gnu.org>
 * Copyright (c) 2003-2004 Benedikt Meurer <benny@expidus.org>
 * Copyright (c) 2003-2004 Olivier Fourdan <fourdan@expidus.org>
 * Copyright (c) 2003-2006 Vincent Untz
 * Copyright (c) 2007-2010 Nick Schermer <nick@expidus.org>
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

#ifndef __SYSTRAY_MANAGER_H__
#define __SYSTRAY_MANAGER_H__

#include <gtk/gtk.h>

typedef struct _SystrayManagerClass SystrayManagerClass;
typedef struct _SystrayManager      SystrayManager;
typedef struct _SystrayMessage      SystrayMessage;

#define EXPIDUS_TYPE_SYSTRAY_MANAGER            (systray_manager_get_type ())
#define EXPIDUS_SYSTRAY_MANAGER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_SYSTRAY_MANAGER, SystrayManager))
#define EXPIDUS_SYSTRAY_MANAGER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_TYPE_SYSTRAY_MANAGER, SystrayManagerClass))
#define EXPIDUS_IS_SYSTRAY_MANAGER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_SYSTRAY_MANAGER))
#define EXPIDUS_IS_SYSTRAY_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EXPIDUS_TYPE_SYSTRAY_MANAGER))
#define EXPIDUS_SYSTRAY_MANAGER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_TYPE_SYSTRAY_MANAGER, SystrayManagerClass))
#define EXPIDUS_SYSTRAY_MANAGER_ERROR           (systray_manager_error_quark())



enum
{
    EXPIDUS_SYSTRAY_MANAGER_ERROR_SELECTION_FAILED
};



GType           systray_manager_get_type             (void) G_GNUC_CONST;

void            systray_manager_register_type        (ExpidusPanelTypeModule *type_module);

GQuark          systray_manager_error_quark          (void);

SystrayManager *systray_manager_new                  (void) G_GNUC_MALLOC;

#if 0
gboolean        systray_manager_check_running        (GdkScreen           *screen);
#endif

gboolean        systray_manager_register             (SystrayManager      *manager,
                                                      GdkScreen            *screen,
                                                      GError              **error);

void            systray_manager_unregister           (SystrayManager      *manager);

void            systray_manager_set_colors           (SystrayManager *manager,
                                                      GdkColor       *fg,
                                                      GdkColor       *error,
                                                      GdkColor       *warning,
                                                      GdkColor       *success);

void            systray_manager_set_orientation      (SystrayManager      *manager,
                                                      GtkOrientation       orientation);


#endif /* !__SYSTRAY_MANAGER_H__ */
