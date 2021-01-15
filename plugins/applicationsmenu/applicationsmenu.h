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

#ifndef __EXPIDUS_APPLICATIONS_MENU_PLUGIN_H__
#define __EXPIDUS_APPLICATIONS_MENU_PLUGIN_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _ApplicationsMenuPluginClass ApplicationsMenuPluginClass;
typedef struct _ApplicationsMenuPlugin      ApplicationsMenuPlugin;

#define EXPIDUS_TYPE_APPLICATIONS_MENU_PLUGIN            (applications_menu_plugin_get_type ())
#define EXPIDUS_APPLICATIONS_MENU_PLUGIN(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_APPLICATIONS_MENU_PLUGIN, ApplicationsMenuPlugin))
#define EXPIDUS_APPLICATIONS_MENU_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_TYPE_APPLICATIONS_MENU_PLUGIN, ApplicationsMenuPluginClass))
#define EXPIDUS_IS_APPLICATIONS_MENU_PLUGIN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_APPLICATIONS_MENU_PLUGIN))
#define EXPIDUS_IS_APPLICATIONS_MENU_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EXPIDUS_TYPE_APPLICATIONS_MENU_PLUGIN))
#define EXPIDUS_APPLICATIONS_MENU_PLUGIN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_TYPE_APPLICATIONS_MENU_PLUGIN, ApplicationsMenuPluginClass))

GType applications_menu_plugin_get_type      (void) G_GNUC_CONST;

void  applications_menu_plugin_register_type (ExpidusPanelTypeModule *type_module);

G_END_DECLS

#endif /* !__EXPIDUS_APPLICATIONS_MENU_PLUGIN_H__ */
