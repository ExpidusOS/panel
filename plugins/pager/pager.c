/*
 * Copyright (c) 2005-2007 Jasper Huijsmans <jasper@expidus.org>
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include <gtk/gtk.h>
#include <libexpidus1panel/libexpidus1panel.h>
#include <libexpidus1util/libexpidus1util.h>
#include <libexpidus1ui/libexpidus1ui.h>
#include <common/panel-esconf.h>
#include <common/panel-utils.h>
#include <common/panel-private.h>
#include <common/panel-debug.h>
#include <libwnck/libwnck.h>

#include "pager.h"
#include "pager-buttons.h"
#include "pager-dialog_ui.h"



#define WORKSPACE_SETTINGS_COMMAND "xfwm4-workspace-settings"



static void     pager_plugin_get_property                 (GObject           *object,
                                                           guint              prop_id,
                                                           GValue            *value,
                                                           GParamSpec        *pspec);
static void     pager_plugin_set_property                 (GObject           *object,
                                                           guint              prop_id,
                                                           const GValue      *value,
                                                           GParamSpec        *pspec);
static gboolean pager_plugin_scroll_event                 (GtkWidget         *widget,
                                                           GdkEventScroll    *event);
static void     pager_plugin_drag_begin_event             (GtkWidget         *widget,
                                                           GdkDragContext    *context,
                                                           gpointer           user_data);
static void     pager_plugin_drag_end_event               (GtkWidget         *widget,
                                                           GdkDragContext    *context,
                                                           gpointer           user_data);
static void     pager_plugin_screen_changed               (GtkWidget         *widget,
                                                           GdkScreen         *previous_screen);
static void     pager_plugin_construct                    (ExpidusPanelPlugin   *panel_plugin);
static void     pager_plugin_style_updated                (GtkWidget         *pager,
                                                           gpointer           user_data);
static void     pager_plugin_free_data                    (ExpidusPanelPlugin   *panel_plugin);
static gboolean pager_plugin_size_changed                 (ExpidusPanelPlugin   *panel_plugin,
                                                           gint               size);
static void     pager_plugin_mode_changed                 (ExpidusPanelPlugin     *panel_plugin,
                                                           ExpidusPanelPluginMode  mode);
static void     pager_plugin_configure_workspace_settings (GtkWidget         *button);
static void     pager_plugin_configure_plugin             (ExpidusPanelPlugin   *panel_plugin);
static void     pager_plugin_screen_layout_changed        (PagerPlugin       *plugin);
static void     pager_plugin_get_preferred_width          (GtkWidget           *widget,
                                                           gint                *minimum_width,
                                                           gint                *natural_width);
static void     pager_plugin_get_preferred_height         (GtkWidget           *widget,
                                                           gint                *minimum_height,
                                                           gint                *natural_height);
static void     pager_plugin_get_preferred_width_for_height (GtkWidget           *widget,
                                                             gint                 height,
                                                             gint                *minimum_width,
                                                             gint                *natural_width);
static void     pager_plugin_get_preferred_height_for_width (GtkWidget           *widget,
                                                             gint                 width,
                                                             gint                *minimum_height,
                                                             gint                *natural_height);



struct _PagerPluginClass
{
  ExpidusPanelPluginClass __parent__;
};

struct _PagerPlugin
{
  ExpidusPanelPlugin __parent__;

  GtkWidget     *pager;
  GObject       *numbering_switch;
  GObject       *numbering_label;
  GObject       *scrolling_switch;
  GObject       *scrolling_label;

  WnckScreen    *wnck_screen;

  /* settings */
  guint          scrolling : 1;
  guint          wrap_workspaces : 1;
  guint          miniature_view : 1;
  gint           rows;
  gboolean       numbering;
  gfloat         ratio;
};

enum
{
  PROP_0,
  PROP_WORKSPACE_SCROLLING,
  PROP_WRAP_WORKSPACES,
  PROP_MINIATURE_VIEW,
  PROP_ROWS,
  PROP_NUMBERING
};



/* define the plugin */
EXPIDUS_PANEL_DEFINE_PLUGIN_RESIDENT (PagerPlugin, pager_plugin,
    pager_buttons_register_type)



static void
pager_plugin_class_init (PagerPluginClass *klass)
{
  ExpidusPanelPluginClass *plugin_class;
  GObjectClass         *gobject_class;
  GtkWidgetClass       *widget_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->get_property = pager_plugin_get_property;
  gobject_class->set_property = pager_plugin_set_property;

  widget_class = GTK_WIDGET_CLASS (klass);
  widget_class->scroll_event = pager_plugin_scroll_event;
  widget_class->get_preferred_width = pager_plugin_get_preferred_width;
  widget_class->get_preferred_width_for_height  = pager_plugin_get_preferred_width_for_height;
  widget_class->get_preferred_height = pager_plugin_get_preferred_height;
  widget_class->get_preferred_height_for_width  = pager_plugin_get_preferred_height_for_width;

  plugin_class = EXPIDUS_PANEL_PLUGIN_CLASS (klass);
  plugin_class->construct = pager_plugin_construct;
  plugin_class->free_data = pager_plugin_free_data;
  plugin_class->size_changed = pager_plugin_size_changed;
  plugin_class->mode_changed = pager_plugin_mode_changed;
  plugin_class->configure_plugin = pager_plugin_configure_plugin;

  g_object_class_install_property (gobject_class,
                                   PROP_WORKSPACE_SCROLLING,
                                   g_param_spec_boolean ("workspace-scrolling",
                                                         NULL, NULL,
                                                         TRUE,
                                                         G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class,
                                   PROP_WRAP_WORKSPACES,
                                   g_param_spec_boolean ("wrap-workspaces",
                                                         NULL, NULL,
                                                         FALSE,
                                                         G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class,
                                   PROP_MINIATURE_VIEW,
                                   g_param_spec_boolean ("miniature-view",
                                                         NULL, NULL,
                                                         TRUE,
                                                         G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class,
                                   PROP_ROWS,
                                   g_param_spec_uint ("rows",
                                                      NULL, NULL,
                                                      1, 50, 1,
                                                      G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class,
                                   PROP_NUMBERING,
                                   g_param_spec_boolean ("numbering",
                                                         NULL, NULL,
                                                         FALSE,
                                                         G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
}



static void
pager_plugin_init (PagerPlugin *plugin)
{
  plugin->wnck_screen = NULL;
  plugin->scrolling = TRUE;
  plugin->wrap_workspaces = FALSE;
  plugin->miniature_view = TRUE;
  plugin->rows = 1;
  plugin->numbering = FALSE;
  plugin->ratio = 1.0;
  plugin->pager = NULL;
}



static void
pager_plugin_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  PagerPlugin *plugin = EXPIDUS_PAGER_PLUGIN (object);

  switch (prop_id)
    {
    case PROP_WORKSPACE_SCROLLING:
      g_value_set_boolean (value, plugin->scrolling);
      break;

    case PROP_WRAP_WORKSPACES:
      g_value_set_boolean (value, plugin->wrap_workspaces);
      break;

    case PROP_MINIATURE_VIEW:
      g_value_set_boolean (value, plugin->miniature_view);

      if (G_IS_OBJECT (plugin->numbering_label))
        gtk_widget_set_visible (GTK_WIDGET (plugin->numbering_label), !plugin->miniature_view);
      if (G_IS_OBJECT (plugin->numbering_switch))
        gtk_widget_set_visible (GTK_WIDGET (plugin->numbering_switch), !plugin->miniature_view);
      if (G_IS_OBJECT (plugin->scrolling_label))
        gtk_widget_set_visible (GTK_WIDGET (plugin->scrolling_label), !plugin->miniature_view);
      if (G_IS_OBJECT (plugin->scrolling_switch))
        gtk_widget_set_visible (GTK_WIDGET (plugin->scrolling_switch), !plugin->miniature_view);

      pager_plugin_screen_layout_changed (plugin);
      break;

    case PROP_ROWS:
      g_value_set_uint (value, plugin->rows);
      break;

    case PROP_NUMBERING:
      g_value_set_boolean (value, plugin->numbering);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}



static void
pager_plugin_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  PagerPlugin *plugin = EXPIDUS_PAGER_PLUGIN (object);

  switch (prop_id)
    {
    case PROP_WORKSPACE_SCROLLING:
      plugin->scrolling = g_value_get_boolean (value);
      break;

    case PROP_WRAP_WORKSPACES:
      plugin->wrap_workspaces = g_value_get_boolean (value);
      break;

    case PROP_MINIATURE_VIEW:
      plugin->miniature_view = g_value_get_boolean (value);
      break;

    case PROP_ROWS:
      plugin->rows = g_value_get_uint (value);

      if (plugin->pager != NULL)
        {
          if (plugin->miniature_view)
            {
              if (!wnck_pager_set_n_rows (WNCK_PAGER (plugin->pager), plugin->rows))
                g_message ("Failed to set the number of pager rows. You probably "
                           "have more than 1 pager in your panel setup.");
            }
          else
            pager_buttons_set_n_rows (EXPIDUS_PAGER_BUTTONS (plugin->pager), plugin->rows);
        }
      break;

    case PROP_NUMBERING:
      plugin->numbering = g_value_get_boolean (value);

      if (plugin->pager != NULL
          && !plugin->miniature_view)
        pager_buttons_set_numbering (EXPIDUS_PAGER_BUTTONS (plugin->pager), plugin->numbering);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}



static void
pager_plugin_style_updated (GtkWidget *pager,
                            gpointer   user_data)
{
  GtkWidget               *toplevel = gtk_widget_get_toplevel (pager);
  GtkStyleContext         *context;
  GtkCssProvider          *provider;
  GdkRGBA                 *bg_color;
  gchar                   *css_string;
  gchar                   *color_string;

  g_return_if_fail (gtk_widget_is_toplevel (toplevel));

  /* Get the background color of the panel to draw selected and hover states */
  provider = gtk_css_provider_new ();
  context = gtk_widget_get_style_context (GTK_WIDGET (toplevel));
  gtk_style_context_get (context, GTK_STATE_FLAG_NORMAL,
                         GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                         &bg_color, NULL);
  color_string = gdk_rgba_to_string(bg_color);
  // FIXME: The shade value only works well visually for bright themes/panels
  css_string = g_strdup_printf ("wnck-pager { background: %s; }"
                                "wnck-pager:selected { background: shade(%s, 0.7); }"
                                "wnck-pager:hover { background: shade(%s, 0.9); }",
                                color_string, color_string, color_string);
  context = gtk_widget_get_style_context (pager);
  gtk_css_provider_load_from_data (provider, css_string, -1, NULL);
  gtk_style_context_add_provider (context,
                               GTK_STYLE_PROVIDER (provider),
                               GTK_STYLE_PROVIDER_PRIORITY_THEME);
  gdk_rgba_free (bg_color);
  g_free (color_string);
  g_free (css_string);
  g_object_unref (provider);
}



static gboolean
pager_plugin_scroll_event (GtkWidget      *widget,
                           GdkEventScroll *event)
{
  PagerPlugin        *plugin = EXPIDUS_PAGER_PLUGIN (widget);
  WnckWorkspace      *active_ws;
  WnckWorkspace      *new_ws;
  gint                active_n;
  gint                n_workspaces;
  GdkScrollDirection  scrolling_direction;

  panel_return_val_if_fail (WNCK_IS_SCREEN (plugin->wnck_screen), FALSE);

  /* leave when scrolling is not enabled */
  if (plugin->scrolling == FALSE)
    return TRUE;

  if (event->direction != GDK_SCROLL_SMOOTH)
    scrolling_direction = event->direction;
  else if (event->delta_y < 0)
    scrolling_direction = GDK_SCROLL_UP;
  else if (event->delta_y > 0)
    scrolling_direction = GDK_SCROLL_DOWN;
  else if (event->delta_x < 0)
    scrolling_direction = GDK_SCROLL_LEFT;
  else if (event->delta_x > 0)
    scrolling_direction = GDK_SCROLL_RIGHT;
  else
    {
      panel_debug_filtered (PANEL_DEBUG_PAGER, "Scrolling event with no delta happened.");
      return TRUE;
    }

  active_ws = wnck_screen_get_active_workspace (plugin->wnck_screen);
  active_n = wnck_workspace_get_number (active_ws);

  if (scrolling_direction == GDK_SCROLL_UP
      || scrolling_direction == GDK_SCROLL_LEFT)
    active_n--;
  else
    active_n++;

  n_workspaces = wnck_screen_get_workspace_count (plugin->wnck_screen) - 1;

  if (plugin->wrap_workspaces == TRUE)
  {
    /* wrap around */
    if (active_n < 0)
      active_n = n_workspaces;
    else if (active_n > n_workspaces)
      active_n = 0;
  }
  else if (active_n < 0 || active_n > n_workspaces )
  {
    /* we do not need to do anything */
    return TRUE;
  }

  new_ws = wnck_screen_get_workspace (plugin->wnck_screen, active_n);
  if (new_ws != NULL && active_ws != new_ws)
    wnck_workspace_activate (new_ws, event->time);

  return TRUE;
}



static void
pager_plugin_drag_begin_event (GtkWidget      *widget,
                               GdkDragContext *context,
                               gpointer        user_data)
{
  PagerPlugin *plugin = user_data;

  panel_return_if_fail (EXPIDUS_IS_PAGER_PLUGIN (plugin));
  expidus_panel_plugin_block_autohide (EXPIDUS_PANEL_PLUGIN (plugin), TRUE);
}



static void
pager_plugin_drag_end_event (GtkWidget      *widget,
                             GdkDragContext *context,
                             gpointer        user_data)
{
  PagerPlugin *plugin = user_data;

  panel_return_if_fail (EXPIDUS_IS_PAGER_PLUGIN (plugin));
  expidus_panel_plugin_block_autohide (EXPIDUS_PANEL_PLUGIN (plugin), FALSE);
}



static void
pager_plugin_screen_layout_changed (PagerPlugin *plugin)
{
  ExpidusPanelPluginMode mode;
  GtkOrientation      orientation;

  panel_return_if_fail (EXPIDUS_IS_PAGER_PLUGIN (plugin));
  panel_return_if_fail (WNCK_IS_SCREEN (plugin->wnck_screen));

  if (G_UNLIKELY (plugin->pager != NULL))
    {
      gtk_widget_destroy (GTK_WIDGET (plugin->pager));
      wnck_screen_force_update (plugin->wnck_screen);
    }

  mode = expidus_panel_plugin_get_mode (EXPIDUS_PANEL_PLUGIN (plugin));
  orientation =
    (mode != EXPIDUS_PANEL_PLUGIN_MODE_VERTICAL) ?
    GTK_ORIENTATION_HORIZONTAL : GTK_ORIENTATION_VERTICAL;

  if (plugin->miniature_view)
    {
      plugin->pager = wnck_pager_new ();
      wnck_pager_set_display_mode (WNCK_PAGER (plugin->pager), WNCK_PAGER_DISPLAY_CONTENT);
      if (!wnck_pager_set_n_rows (WNCK_PAGER (plugin->pager), plugin->rows))
        g_message ("Setting the pager rows returned false. Maybe the setting is not applied.");

      wnck_pager_set_orientation (WNCK_PAGER (plugin->pager), orientation);
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
      plugin->ratio = (gfloat) gdk_screen_width () / (gfloat) gdk_screen_height ();
G_GNUC_END_IGNORE_DEPRECATIONS
      g_signal_connect_after (G_OBJECT (plugin->pager), "drag-begin",
                              G_CALLBACK (pager_plugin_drag_begin_event), plugin);
      g_signal_connect_after (G_OBJECT (plugin->pager), "drag-end",
                              G_CALLBACK (pager_plugin_drag_end_event), plugin);
    }
  else
    {
      plugin->pager = pager_buttons_new (plugin->wnck_screen);
      pager_buttons_set_n_rows (EXPIDUS_PAGER_BUTTONS (plugin->pager), plugin->rows);
      pager_buttons_set_orientation (EXPIDUS_PAGER_BUTTONS (plugin->pager), orientation);
      pager_buttons_set_numbering (EXPIDUS_PAGER_BUTTONS (plugin->pager), plugin->numbering);
    }

  gtk_container_add (GTK_CONTAINER (plugin), plugin->pager);
  gtk_widget_show (plugin->pager);

  /* Poke the style-updated signal to set the correct background color for the newly
     created widget. Otherwise it may sometimes end up transparent. */
  pager_plugin_style_updated (plugin->pager, NULL);
}



static void
pager_plugin_screen_changed (GtkWidget *widget,
                             GdkScreen *previous_screen)
{
  PagerPlugin *plugin = EXPIDUS_PAGER_PLUGIN (widget);
  GdkScreen   *screen;
  WnckScreen  *wnck_screen;

  screen = gtk_widget_get_screen (widget);
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  wnck_screen = wnck_screen_get (gdk_screen_get_number (screen));
G_GNUC_END_IGNORE_DEPRECATIONS

  if (plugin->wnck_screen != wnck_screen)
    {
      plugin->wnck_screen = wnck_screen;

      pager_plugin_screen_layout_changed (plugin);

      g_signal_connect_swapped (G_OBJECT (screen), "monitors-changed",
         G_CALLBACK (pager_plugin_screen_layout_changed), plugin);
      g_signal_connect_swapped (G_OBJECT (screen), "size-changed",
         G_CALLBACK (pager_plugin_screen_layout_changed), plugin);
    }
}



static void
pager_plugin_construct (ExpidusPanelPlugin *panel_plugin)
{
  PagerPlugin         *plugin = EXPIDUS_PAGER_PLUGIN (panel_plugin);
  GtkWidget           *mi, *image;
  const PanelProperty  properties[] =
  {
    { "workspace-scrolling", G_TYPE_BOOLEAN },
    { "wrap-workspaces", G_TYPE_BOOLEAN },
    { "miniature-view", G_TYPE_BOOLEAN },
    { "rows", G_TYPE_UINT },
    { "numbering", G_TYPE_BOOLEAN },
    { NULL }
  };

  expidus_panel_plugin_menu_show_configure (panel_plugin);

G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  mi = gtk_image_menu_item_new_with_mnemonic (_("Workspace _Settings..."));
G_GNUC_END_IGNORE_DEPRECATIONS
  expidus_panel_plugin_menu_insert_item (panel_plugin, GTK_MENU_ITEM (mi));
  g_signal_connect (G_OBJECT (mi), "activate",
      G_CALLBACK (pager_plugin_configure_workspace_settings), NULL);
  gtk_widget_show (mi);

  image = gtk_image_new_from_icon_name ("com.expidus.panel.pager", GTK_ICON_SIZE_MENU);
G_GNUC_BEGIN_IGNORE_DEPRECATIONS
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (mi), image);
G_GNUC_END_IGNORE_DEPRECATIONS
  gtk_widget_show (image);

  panel_properties_bind (NULL, G_OBJECT (plugin),
                         expidus_panel_plugin_get_property_base (panel_plugin),
                         properties, FALSE);

  g_signal_connect (G_OBJECT (plugin), "screen-changed",
      G_CALLBACK (pager_plugin_screen_changed), NULL);
  pager_plugin_screen_changed (GTK_WIDGET (plugin), NULL);
  g_signal_connect (G_OBJECT (plugin->pager), "style-updated",
      G_CALLBACK (pager_plugin_style_updated), NULL);
}



static void
pager_plugin_free_data (ExpidusPanelPlugin *panel_plugin)
{
  PagerPlugin *plugin = EXPIDUS_PAGER_PLUGIN (panel_plugin);

  g_signal_handlers_disconnect_by_func (G_OBJECT (plugin),
      pager_plugin_screen_changed, NULL);
}



static gboolean
pager_plugin_size_changed (ExpidusPanelPlugin *panel_plugin,
                           gint             size)
{
  gtk_widget_queue_resize (GTK_WIDGET (panel_plugin));

  /* do not set fixed size */
  return TRUE;
}



static void
pager_plugin_mode_changed (ExpidusPanelPlugin     *panel_plugin,
                           ExpidusPanelPluginMode  mode)
{
  PagerPlugin       *plugin = EXPIDUS_PAGER_PLUGIN (panel_plugin);
  GtkOrientation     orientation;

  orientation =
    (mode != EXPIDUS_PANEL_PLUGIN_MODE_VERTICAL) ?
    GTK_ORIENTATION_HORIZONTAL : GTK_ORIENTATION_VERTICAL;

  if (plugin->miniature_view)
    wnck_pager_set_orientation (WNCK_PAGER (plugin->pager), orientation);
  else
    pager_buttons_set_orientation (EXPIDUS_PAGER_BUTTONS (plugin->pager), orientation);
}



static void
pager_plugin_configure_workspace_settings (GtkWidget *button)
{
  GdkScreen *screen;
  GError    *error = NULL;
  GtkWidget *toplevel;

  panel_return_if_fail (GTK_IS_WIDGET (button));

  screen = gtk_widget_get_screen (button);
  if (G_UNLIKELY (screen == NULL))
    screen = gdk_screen_get_default ();

  /* try to start the settings dialog */
  if (!expidus_spawn_command_line (screen, WORKSPACE_SETTINGS_COMMAND,
                                FALSE, FALSE, TRUE, &error))
    {
      /* show an error dialog */
      toplevel = gtk_widget_get_toplevel (button);
      expidus_dialog_show_error (GTK_WINDOW (toplevel), error,
          _("Unable to open the workspace settings"));
      g_error_free (error);
    }
}



static void
pager_plugin_configure_n_workspaces_changed (WnckScreen    *wnck_screen,
                                             WnckWorkspace *workspace,
                                             GtkBuilder    *builder)
{
  GObject       *object;
  gdouble        upper, value;
  WnckWorkspace *active_ws;

  panel_return_if_fail (WNCK_IS_SCREEN (wnck_screen));
  panel_return_if_fail (GTK_IS_BUILDER (builder));

  object = gtk_builder_get_object (builder, "rows");

  upper = wnck_screen_get_workspace_count (wnck_screen);
  if (upper == 1)
    {
      /* check if we ware in viewport mode */
      active_ws = wnck_screen_get_active_workspace (wnck_screen);
      if (wnck_workspace_is_virtual (active_ws))
        {
          /* number of rows * number of columns */
          upper = (wnck_workspace_get_width (active_ws) / wnck_screen_get_width (wnck_screen))
                  * (wnck_workspace_get_height (active_ws) / wnck_screen_get_height (wnck_screen));
        }
    }

  value = MIN (gtk_adjustment_get_value (GTK_ADJUSTMENT (object)), upper);

  g_object_set (G_OBJECT (object), "upper", upper, "value", value, NULL);
}



static void
pager_plugin_configure_destroyed (gpointer  data,
                                  GObject  *where_the_object_was)
{
  PagerPlugin *plugin = EXPIDUS_PAGER_PLUGIN (data);

  g_signal_handlers_disconnect_by_func (G_OBJECT (plugin->wnck_screen),
                                        pager_plugin_configure_n_workspaces_changed,
                                        where_the_object_was);
}



static void
pager_plugin_configure_plugin (ExpidusPanelPlugin *panel_plugin)
{
  PagerPlugin *plugin = EXPIDUS_PAGER_PLUGIN (panel_plugin);
  GtkBuilder  *builder;
  GObject     *dialog, *object;

  panel_return_if_fail (EXPIDUS_IS_PAGER_PLUGIN (plugin));

  /* setup the dialog */
  PANEL_UTILS_LINK_4UI
  builder = panel_utils_builder_new (panel_plugin, pager_dialog_ui,
                                     pager_dialog_ui_length, &dialog);
  if (G_UNLIKELY (builder == NULL))
    return;

  /* signals to monitor number of workspace changes */
  g_signal_connect (G_OBJECT (plugin->wnck_screen), "workspace-created",
      G_CALLBACK (pager_plugin_configure_n_workspaces_changed), builder);
  g_signal_connect (G_OBJECT (plugin->wnck_screen), "workspace-destroyed",
      G_CALLBACK (pager_plugin_configure_n_workspaces_changed), builder);
  g_object_weak_ref (G_OBJECT (builder), pager_plugin_configure_destroyed, plugin);

  object = gtk_builder_get_object (builder, "settings-button");
  panel_return_if_fail (GTK_IS_BUTTON (object));
  g_signal_connect (G_OBJECT (object), "clicked",
      G_CALLBACK (pager_plugin_configure_workspace_settings), dialog);

  plugin->scrolling_label = gtk_builder_get_object (builder, "workspace-scrolling-label");
  plugin->scrolling_switch = gtk_builder_get_object (builder, "workspace-scrolling");
  panel_return_if_fail (GTK_IS_SWITCH (plugin->scrolling_switch));
  g_object_bind_property (G_OBJECT (plugin), "workspace-scrolling",
                          G_OBJECT (plugin->scrolling_switch), "active",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);

  object = gtk_builder_get_object (builder, "appearance");
  panel_return_if_fail (GTK_IS_COMBO_BOX (object));
  g_object_bind_property (G_OBJECT (plugin), "miniature-view",
                          G_OBJECT (object), "active",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);

  object = gtk_builder_get_object (builder, "rows");
  panel_return_if_fail (GTK_IS_ADJUSTMENT (object));
  g_object_bind_property (G_OBJECT (plugin), "rows",
                          G_OBJECT (object), "value",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);

  plugin->numbering_label = gtk_builder_get_object (builder, "numbering-label");
  plugin->numbering_switch = gtk_builder_get_object (builder, "numbering");
  panel_return_if_fail (GTK_IS_SWITCH (plugin->numbering_switch));
  g_object_bind_property (G_OBJECT (plugin), "numbering",
                          G_OBJECT (plugin->numbering_switch), "active",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);

  gtk_widget_set_visible (GTK_WIDGET (plugin->numbering_label), !plugin->miniature_view);
  gtk_widget_set_visible (GTK_WIDGET (plugin->numbering_switch), !plugin->miniature_view);
  gtk_widget_set_visible (GTK_WIDGET (plugin->scrolling_label), !plugin->miniature_view);
  gtk_widget_set_visible (GTK_WIDGET (plugin->scrolling_switch), !plugin->miniature_view);

  /* update the rows limit */
  pager_plugin_configure_n_workspaces_changed (plugin->wnck_screen, NULL, builder);

  gtk_widget_show (GTK_WIDGET (dialog));
}


static void
pager_plugin_get_preferred_width (GtkWidget *widget,
                                  gint      *minimum_width,
                                  gint      *natural_width)
{
  PagerPlugin         *plugin = EXPIDUS_PAGER_PLUGIN (widget);
  ExpidusPanelPluginMode  mode;
  gint                 n_workspaces, n_cols;
  gint                 min_width = 0;
  gint                 nat_width = 0;

  if (plugin->pager != NULL)
    gtk_widget_get_preferred_width (plugin->pager, &min_width, &nat_width);

  mode = expidus_panel_plugin_get_mode (EXPIDUS_PANEL_PLUGIN (plugin));
  if (mode == EXPIDUS_PANEL_PLUGIN_MODE_VERTICAL ||
      mode == EXPIDUS_PANEL_PLUGIN_MODE_DESKBAR)
    min_width = nat_width = expidus_panel_plugin_get_size (EXPIDUS_PANEL_PLUGIN (plugin));
  else if (plugin->miniature_view)
    {
      n_workspaces = wnck_screen_get_workspace_count (plugin->wnck_screen);
      n_cols = MAX (1, (n_workspaces + plugin->rows - 1) / plugin->rows);
      min_width = nat_width = (gint) (expidus_panel_plugin_get_size (EXPIDUS_PANEL_PLUGIN (plugin)) / plugin->rows * plugin->ratio * n_cols);
    }

  if (minimum_width != NULL)
    *minimum_width = min_width;

  if (natural_width != NULL)
    *natural_width = nat_width;
}

static void
pager_plugin_get_preferred_height (GtkWidget *widget,
                                   gint      *minimum_height,
                                   gint      *natural_height)
{
  PagerPlugin         *plugin = EXPIDUS_PAGER_PLUGIN (widget);
  ExpidusPanelPluginMode  mode;
  gint                 n_workspaces, n_cols;
  gint                 min_height = 0;
  gint                 nat_height = 0;

  if (plugin->pager != NULL)
    gtk_widget_get_preferred_height (plugin->pager, &min_height, &nat_height);

  mode = expidus_panel_plugin_get_mode (EXPIDUS_PANEL_PLUGIN (plugin));
  if (mode == EXPIDUS_PANEL_PLUGIN_MODE_HORIZONTAL)
    min_height = nat_height = expidus_panel_plugin_get_size (EXPIDUS_PANEL_PLUGIN (plugin));
  else if (plugin->miniature_view)
    {
      n_workspaces = wnck_screen_get_workspace_count (plugin->wnck_screen);
      n_cols = MAX (1, (n_workspaces + plugin->rows - 1) / plugin->rows);
      if (mode == EXPIDUS_PANEL_PLUGIN_MODE_VERTICAL)
        min_height = nat_height = (gint) (expidus_panel_plugin_get_size (EXPIDUS_PANEL_PLUGIN (plugin)) / plugin->rows / plugin->ratio * n_cols);
      else /* (mode == EXPIDUS_PANEL_PLUGIN_MODE_DESKBAR) */
        min_height = nat_height = (gint) (expidus_panel_plugin_get_size (EXPIDUS_PANEL_PLUGIN (plugin)) / n_cols / plugin->ratio * plugin->rows);
    }

  if (minimum_height != NULL)
    *minimum_height = min_height;

  if (natural_height != NULL)
    *natural_height = nat_height;
}

static void
pager_plugin_get_preferred_width_for_height (GtkWidget *widget,
                                             gint       height,
                                             gint      *minimum_width,
                                             gint      *natural_width)
{
  pager_plugin_get_preferred_width (widget, minimum_width, natural_width);
}

static void
pager_plugin_get_preferred_height_for_width (GtkWidget *widget,
                                             gint       width,
                                             gint      *minimum_height,
                                             gint      *natural_height)
{
  pager_plugin_get_preferred_height (widget, minimum_height, natural_height);
}
