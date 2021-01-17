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

#ifndef __EXPIDUS_PANEL_PLUGIN_PROVIDER_H__
#define __EXPIDUS_PANEL_PLUGIN_PROVIDER_H__

#include <gtk/gtk.h>
#include <libexpidus1panel/libexpidus1panel.h>

G_BEGIN_DECLS

typedef struct _ExpidusPanelPluginProviderInterface ExpidusPanelPluginProviderInterface;
typedef struct _ExpidusPanelPluginProvider          ExpidusPanelPluginProvider;

#define EXPIDUS_TYPE_PANEL_PLUGIN_PROVIDER               (expidus_panel_plugin_provider_get_type ())
#define EXPIDUS_PANEL_PLUGIN_PROVIDER(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_PANEL_PLUGIN_PROVIDER, ExpidusPanelPluginProvider))
#define EXPIDUS_IS_PANEL_PLUGIN_PROVIDER(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_PANEL_PLUGIN_PROVIDER))
#define EXPIDUS_PANEL_PLUGIN_PROVIDER_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), EXPIDUS_TYPE_PANEL_PLUGIN_PROVIDER, ExpidusPanelPluginProviderInterface))

/* plugin module functions */
typedef GtkWidget *(*PluginConstructFunc) (const gchar  *name,
                                           gint          unique_id,
                                           const gchar  *display_name,
                                           const gchar  *comment,
                                           gchar       **arguments,
                                           GdkScreen    *screen);
typedef GType      (*PluginInitFunc)      (GTypeModule  *module,
                                           gboolean     *make_resident);

struct _ExpidusPanelPluginProviderInterface
{
  /*< private >*/
  GTypeInterface __parent__;

  /*<public >*/
  const gchar *(*get_name)            (ExpidusPanelPluginProvider       *provider);
  gint         (*get_unique_id)       (ExpidusPanelPluginProvider       *provider);
  void         (*set_size)            (ExpidusPanelPluginProvider       *provider,
                                       gint                           size);
  void         (*set_icon_size)       (ExpidusPanelPluginProvider       *provider,
                                       gint                           icon_size);
  void         (*set_dark_mode)       (ExpidusPanelPluginProvider       *provider,
                                       gboolean                       dark_mode);
  void         (*set_mode)            (ExpidusPanelPluginProvider       *provider,
                                       ExpidusPanelPluginMode            mode);
  void         (*set_nrows)           (ExpidusPanelPluginProvider       *provider,
                                       guint                          rows);
  void         (*set_screen_position) (ExpidusPanelPluginProvider       *provider,
                                       ExpidusScreenPosition             screen_position);
  void         (*save)                (ExpidusPanelPluginProvider       *provider);
  gboolean     (*get_show_configure)  (ExpidusPanelPluginProvider       *provider);
  void         (*show_configure)      (ExpidusPanelPluginProvider       *provider);
  gboolean     (*get_show_about)      (ExpidusPanelPluginProvider       *provider);
  void         (*show_about)          (ExpidusPanelPluginProvider       *provider);
  void         (*removed)             (ExpidusPanelPluginProvider       *provider);
  gboolean     (*remote_event)        (ExpidusPanelPluginProvider       *provider,
                                       const gchar                   *name,
                                       const GValue                  *value,
                                       guint                         *handle);
  void         (*set_locked)          (ExpidusPanelPluginProvider       *provider,
                                       gboolean                       locked);
  void         (*ask_remove)          (ExpidusPanelPluginProvider       *provider);
};

/* signals send from the plugin to the panel (possibly through the wrapper) */
typedef enum /*< skip >*/
{
  PROVIDER_SIGNAL_MOVE_PLUGIN = 0,
  PROVIDER_SIGNAL_EXPAND_PLUGIN,
  PROVIDER_SIGNAL_COLLAPSE_PLUGIN,
  PROVIDER_SIGNAL_SMALL_PLUGIN,
  PROVIDER_SIGNAL_UNSMALL_PLUGIN,
  PROVIDER_SIGNAL_LOCK_PANEL,
  PROVIDER_SIGNAL_UNLOCK_PANEL,
  PROVIDER_SIGNAL_REMOVE_PLUGIN,
  PROVIDER_SIGNAL_ADD_NEW_ITEMS,
  PROVIDER_SIGNAL_PANEL_PREFERENCES,
  PROVIDER_SIGNAL_PANEL_LOGOUT,
  PROVIDER_SIGNAL_PANEL_ABOUT,
  PROVIDER_SIGNAL_PANEL_HELP,
  PROVIDER_SIGNAL_SHOW_CONFIGURE,
  PROVIDER_SIGNAL_SHOW_ABOUT,
  PROVIDER_SIGNAL_FOCUS_PLUGIN,
  PROVIDER_SIGNAL_SHRINK_PLUGIN,
  PROVIDER_SIGNAL_UNSHRINK_PLUGIN
}
ExpidusPanelPluginProviderSignal;

/* properties to the plugin; with a value or as an action */
typedef enum /*< skip >*/
{
  PROVIDER_PROP_TYPE_SET_SIZE,                /* gint */
  PROVIDER_PROP_TYPE_SET_ICON_SIZE,           /* gint */
  PROVIDER_PROP_TYPE_SET_DARK_MODE,           /* gboolean */
  PROVIDER_PROP_TYPE_SET_MODE,                /* ExpidusPanelPluginMode (as gint) */
  PROVIDER_PROP_TYPE_SET_SCREEN_POSITION,     /* ExpidusScreenPosition (as gint) */
  PROVIDER_PROP_TYPE_SET_BACKGROUND_ALPHA,    /* gdouble */
  PROVIDER_PROP_TYPE_SET_NROWS,               /* gint */
  PROVIDER_PROP_TYPE_SET_LOCKED,              /* gboolean */
  PROVIDER_PROP_TYPE_SET_SENSITIVE,           /* gboolean */
  PROVIDER_PROP_TYPE_SET_BACKGROUND_COLOR,    /* string, wrapper only */
  PROVIDER_PROP_TYPE_SET_BACKGROUND_IMAGE,    /* string, wrapper only */
  PROVIDER_PROP_TYPE_ACTION_REMOVED,          /* none */
  PROVIDER_PROP_TYPE_ACTION_SAVE,             /* none */
  PROVIDER_PROP_TYPE_ACTION_QUIT,             /* none */
  PROVIDER_PROP_TYPE_ACTION_QUIT_FOR_RESTART, /* none */
  PROVIDER_PROP_TYPE_ACTION_BACKGROUND_UNSET, /* none */
  PROVIDER_PROP_TYPE_ACTION_SHOW_CONFIGURE,   /* none */
  PROVIDER_PROP_TYPE_ACTION_SHOW_ABOUT,       /* none */
  PROVIDER_PROP_TYPE_ACTION_ASK_REMOVE,       /* none */
  PROVIDER_PROP_TYPE_SET_OPACITY              /* gdouble */
}
ExpidusPanelPluginProviderPropType;

/* plugin exit values */
enum
{
  PLUGIN_EXIT_SUCCESS = 0,
  PLUGIN_EXIT_FAILURE,
  PLUGIN_EXIT_ARGUMENTS_FAILED,
  PLUGIN_EXIT_PREINIT_FAILED,
  PLUGIN_EXIT_CHECK_FAILED,
  PLUGIN_EXIT_NO_PROVIDER,
  PLUGIN_EXIT_SUCCESS_AND_RESTART
};

/* argument handling in plugin and wrapper */
enum
{
  PLUGIN_ARGV_0 = 0,
  PLUGIN_ARGV_FILENAME,
  PLUGIN_ARGV_UNIQUE_ID,
  PLUGIN_ARGV_SOCKET_ID,
  PLUGIN_ARGV_NAME,
  PLUGIN_ARGV_DISPLAY_NAME,
  PLUGIN_ARGV_COMMENT,
  PLUGIN_ARGV_ARGUMENTS
};



GType                 expidus_panel_plugin_provider_get_type            (void) G_GNUC_CONST;

const gchar          *expidus_panel_plugin_provider_get_name            (ExpidusPanelPluginProvider       *provider);

gint                  expidus_panel_plugin_provider_get_unique_id       (ExpidusPanelPluginProvider       *provider);

void                  expidus_panel_plugin_provider_set_size            (ExpidusPanelPluginProvider       *provider,
                                                                      gint                           size);

void                  expidus_panel_plugin_provider_set_icon_size       (ExpidusPanelPluginProvider       *provider,
                                                                      gint                           icon_size);

void                  expidus_panel_plugin_provider_set_dark_mode       (ExpidusPanelPluginProvider       *provider,
                                                                      gboolean                       dark_mode);

void                  expidus_panel_plugin_provider_set_mode            (ExpidusPanelPluginProvider       *provider,
                                                                      ExpidusPanelPluginMode            mode);

void                  expidus_panel_plugin_provider_set_nrows           (ExpidusPanelPluginProvider       *provider,
                                                                      guint                          rows);

void                  expidus_panel_plugin_provider_set_screen_position (ExpidusPanelPluginProvider       *provider,
                                                                      ExpidusScreenPosition             screen_position);

void                  expidus_panel_plugin_provider_save                (ExpidusPanelPluginProvider       *provider);

void                  expidus_panel_plugin_provider_emit_signal         (ExpidusPanelPluginProvider       *provider,
                                                                      ExpidusPanelPluginProviderSignal  provider_signal);

gboolean              expidus_panel_plugin_provider_get_show_configure  (ExpidusPanelPluginProvider       *provider);

void                  expidus_panel_plugin_provider_show_configure      (ExpidusPanelPluginProvider       *provider);

gboolean              expidus_panel_plugin_provider_get_show_about      (ExpidusPanelPluginProvider       *provider);

void                  expidus_panel_plugin_provider_show_about          (ExpidusPanelPluginProvider       *provider);

void                  expidus_panel_plugin_provider_removed             (ExpidusPanelPluginProvider       *provider);

gboolean              expidus_panel_plugin_provider_remote_event        (ExpidusPanelPluginProvider       *provider,
                                                                      const gchar                   *name,
                                                                      const GValue                  *value,
                                                                      guint                         *handle);

void                  expidus_panel_plugin_provider_set_locked          (ExpidusPanelPluginProvider       *provider,
                                                                      gboolean                       locked);

void                  expidus_panel_plugin_provider_ask_remove          (ExpidusPanelPluginProvider       *provider);

G_END_DECLS

#endif /* !__EXPIDUS_PANEL_PLUGIN_PROVIDER_H__ */