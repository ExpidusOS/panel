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



#ifndef __EXPIDUS_PANEL_PLUGIN_H__
#define __EXPIDUS_PANEL_PLUGIN_H__

#include <gtk/gtk.h>
#include <libexpidus1panel/libexpidus1panel-enums.h>

G_BEGIN_DECLS

typedef struct _ExpidusPanelPluginPrivate ExpidusPanelPluginPrivate;
typedef struct _ExpidusPanelPluginClass   ExpidusPanelPluginClass;
typedef struct _ExpidusPanelPlugin        ExpidusPanelPlugin;

/**
 * ExpidusPanelPluginFunc:
 * @plugin : an #ExpidusPanelPlugin
 *
 * Callback function to create the plugin contents. It should be given as
 * the argument to the registration macros.
 **/
typedef void (*ExpidusPanelPluginFunc) (ExpidusPanelPlugin *plugin);

/**
 * ExpidusPanelPluginPreInit:
 * @argc: number of arguments to the plugin
 * @argv: argument array
 *
 * Callback function that is run in an external plugin before gtk_init(). It
 * should return %FALSE if the plugin is not available for whatever reason.
 * The function can be given as argument to one of the registration macros.
 *
 * The main purpose of this callback is to allow multithreaded plugins to call
 * g_thread_init().
 *
 * Returns: %TRUE on success, %FALSE otherwise.
 *
 * Since: 4.6
 **/
typedef gboolean (*ExpidusPanelPluginPreInit) (gint    argc,
                                            gchar **argv);

/**
 * ExpidusPanelPluginCheck:
 * @screen : the #GdkScreen the panel is running on
 *
 * Callback function that is run before creating a plugin. It should return
 * %FALSE if the plugin is not available for whatever reason. The function
 * can be given as argument to one of the registration macros.
 *
 * Returns: %TRUE if the plugin can be started, %FALSE otherwise.
 **/
typedef gboolean (*ExpidusPanelPluginCheck) (GdkScreen *screen);

#define EXPIDUS_TYPE_PANEL_PLUGIN            (expidus_panel_plugin_get_type ())
#define EXPIDUS_PANEL_PLUGIN(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_PANEL_PLUGIN, ExpidusPanelPlugin))
#define EXPIDUS_PANEL_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_TYPE_PANEL_PLUGIN, ExpidusPanelPluginClass))
#define EXPIDUS_IS_PANEL_PLUGIN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_PANEL_PLUGIN))
#define EXPIDUS_IS_PANEL_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EXPIDUS_TYPE_PANEL_PLUGIN))
#define EXPIDUS_PANEL_PLUGIN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_TYPE_PANEL_PLUGIN, ExpidusPanelPluginClass))

/**
 * ExpidusPanelPluginClass:
 * @construct :               This function is for object orientated plugins and
 *                            triggered after the init function of the object.
 *                            When this function is triggered, the plugin
 *                            information like name, display name, comment and unique
 *                            id are available. This is also the place where you would
 *                            call functions like expidus_panel_plugin_menu_show_configure().
 *                            You can see this as the replacement of #ExpidusPanelPluginFunc
 *                            for object based plugins. Since 4.8.
 * @screen_position_changed : See #ExpidusPanelPlugin::screen-position-changed for more information.
 * @size_changed :            See #ExpidusPanelPlugin::size-changed for more information.
 * @orientation_changed :     See #ExpidusPanelPlugin::orientation-changed for more information.
 * @free_data :               See #ExpidusPanelPlugin::free-data for more information.
 * @save :                    See #ExpidusPanelPlugin::save for more information.
 * @about :                   See #ExpidusPanelPlugin::about for more information.
 * @configure_plugin :        See #ExpidusPanelPlugin::configure-plugin for more information.
 * @removed :                 See #ExpidusPanelPlugin::removed for more information.
 * @remote_event :            See #ExpidusPanelPlugin::remote-event for more information.
 * @mode_changed :            See #ExpidusPanelPlugin::mode-changed for more information.
 * @nrows_changed :           See #ExpidusPanelPlugin::nrows-changed for more information.
 *
 * Class of an #ExpidusPanelPlugin. The interface can be used to create GObject based plugin.
 **/
struct _ExpidusPanelPluginClass
{
  /*< private >*/
  GtkEventBoxClass __parent__;

  /*< public >*/
  /* for object oriented plugins only */
  void     (*construct)               (ExpidusPanelPlugin    *plugin);

  /* signals */
  void     (*screen_position_changed) (ExpidusPanelPlugin    *plugin,
                                       ExpidusScreenPosition  position);
  gboolean (*size_changed)            (ExpidusPanelPlugin    *plugin,
                                       gint                size);
  void     (*orientation_changed)     (ExpidusPanelPlugin    *plugin,
                                       GtkOrientation      orientation);
  void     (*free_data)               (ExpidusPanelPlugin    *plugin);
  void     (*save)                    (ExpidusPanelPlugin    *plugin);
  void     (*about)                   (ExpidusPanelPlugin    *plugin);
  void     (*configure_plugin)        (ExpidusPanelPlugin    *plugin);
  void     (*removed)                 (ExpidusPanelPlugin    *plugin);
  gboolean (*remote_event)            (ExpidusPanelPlugin    *plugin,
                                       const gchar        *name,
                                       const GValue       *value);

  /* new in 4.10 */
  void     (*mode_changed)            (ExpidusPanelPlugin    *plugin,
                                       ExpidusPanelPluginMode mode);
  void     (*nrows_changed)           (ExpidusPanelPlugin    *plugin,
                                       guint               rows);

  /*< private >*/
  void (*reserved1) (void);
  void (*reserved2) (void);
};


/**
 * ExpidusPanelPlugin:
 *
 * This struct contain private data only and should be accessed by
 * the functions below.
 **/
struct _ExpidusPanelPlugin
{
  /*< private >*/
  GtkEventBox __parent__;

  /*< private >*/
  ExpidusPanelPluginPrivate *priv;
};



GType                 expidus_panel_plugin_get_type            (void) G_GNUC_CONST;

const gchar          *expidus_panel_plugin_get_name            (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

const gchar          *expidus_panel_plugin_get_display_name    (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

const gchar          *expidus_panel_plugin_get_comment         (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

gint                  expidus_panel_plugin_get_unique_id       (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

const gchar          *expidus_panel_plugin_get_property_base   (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

const gchar * const  *expidus_panel_plugin_get_arguments       (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

gint                  expidus_panel_plugin_get_size            (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

gboolean              expidus_panel_plugin_get_expand          (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

void                  expidus_panel_plugin_set_expand          (ExpidusPanelPlugin   *plugin,
                                                             gboolean           expand);

gboolean              expidus_panel_plugin_get_shrink          (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

void                  expidus_panel_plugin_set_shrink          (ExpidusPanelPlugin   *plugin,
                                                             gboolean           shrink);

gboolean              expidus_panel_plugin_get_small           (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

void                  expidus_panel_plugin_set_small           (ExpidusPanelPlugin   *plugin,
                                                             gboolean           small);

gint                  expidus_panel_plugin_get_icon_size       (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

GtkOrientation        expidus_panel_plugin_get_orientation     (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

ExpidusPanelPluginMode   expidus_panel_plugin_get_mode            (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

guint                 expidus_panel_plugin_get_nrows           (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

ExpidusScreenPosition    expidus_panel_plugin_get_screen_position (ExpidusPanelPlugin   *plugin) G_GNUC_PURE;

void                  expidus_panel_plugin_take_window         (ExpidusPanelPlugin   *plugin,
                                                             GtkWindow         *window);

void                  expidus_panel_plugin_add_action_widget   (ExpidusPanelPlugin   *plugin,
                                                             GtkWidget         *widget);

void                  expidus_panel_plugin_menu_insert_item    (ExpidusPanelPlugin   *plugin,
                                                             GtkMenuItem       *item);

void                  expidus_panel_plugin_menu_show_configure (ExpidusPanelPlugin   *plugin);

void                  expidus_panel_plugin_menu_show_about     (ExpidusPanelPlugin   *plugin);

void                  expidus_panel_plugin_menu_destroy        (ExpidusPanelPlugin   *plugin);

gboolean              expidus_panel_plugin_get_locked          (ExpidusPanelPlugin   *plugin);

void                  expidus_panel_plugin_remove              (ExpidusPanelPlugin   *plugin);

void                  expidus_panel_plugin_block_menu          (ExpidusPanelPlugin   *plugin);

void                  expidus_panel_plugin_unblock_menu        (ExpidusPanelPlugin   *plugin);

void                  expidus_panel_plugin_register_menu       (ExpidusPanelPlugin   *plugin,
                                                             GtkMenu           *menu);

GtkArrowType          expidus_panel_plugin_arrow_type          (ExpidusPanelPlugin   *plugin);

void                  expidus_panel_plugin_position_widget     (ExpidusPanelPlugin   *plugin,
                                                             GtkWidget         *menu_widget,
                                                             GtkWidget         *attach_widget,
                                                             gint              *x,
                                                             gint              *y);

void                  expidus_panel_plugin_position_menu       (GtkMenu           *menu,
                                                             gint              *x,
                                                             gint              *y,
                                                             gboolean          *push_in,
                                                             gpointer           panel_plugin);

void                  expidus_panel_plugin_focus_widget        (ExpidusPanelPlugin   *plugin,
                                                             GtkWidget         *widget);

void                  expidus_panel_plugin_block_autohide      (ExpidusPanelPlugin   *plugin,
                                                             gboolean           blocked);

gchar                *expidus_panel_plugin_lookup_rc_file      (ExpidusPanelPlugin   *plugin) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

gchar                *expidus_panel_plugin_save_location       (ExpidusPanelPlugin   *plugin,
                                                             gboolean           create) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

G_END_DECLS

#endif /* !__EXPIDUS_PANEL_PLUGIN_H__ */
