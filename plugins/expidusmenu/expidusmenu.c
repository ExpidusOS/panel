#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libexpidus1ui/libexpidus1ui.h>
#include <libexpidus1util/libexpidus1util.h>
#include <libexpidus1panel/libexpidus1panel.h>
#include <common/panel-esconf.h>
#include <common/panel-utils.h>
#include <common/panel-private.h>
#include <common/panel-debug.h>

#define WNCK_I_KNOW_THIS_IS_UNSTABLE
#include <libwnck/libwnck.h>

#include <X11/Xlib.h>
#include <gdk/gdkx.h>

#include "expidusmenu.h"
#include "expidusmenu-dialog_ui.h"

#define DEFAULT_TITLE     _("ExpidusOS")
#define DEFAULT_ICON_NAME "com.expidus.panel.expidusmenu"

struct _ExpidusMenuPluginClass
{
  ExpidusPanelPluginClass __parent__;
};

struct _ExpidusMenuPlugin
{
  ExpidusPanelPlugin __parent__;
	GtkWidget* btn;
	GtkWidget* img;
};

EXPIDUS_PANEL_DEFINE_PLUGIN (ExpidusMenuPlugin, expidus_menu_plugin)

static void expidus_menu_plugin_click(GtkButton* btn, gpointer data) {
	GdkWindow* focused = gdk_screen_get_active_window(gdk_window_get_screen(gtk_widget_get_window(GTK_WIDGET(data))));
	if (focused != NULL && gdk_window_get_type_hint(focused) == GDK_WINDOW_TYPE_HINT_DESKTOP) focused = NULL;

	if (focused == NULL) {
		GError* error = NULL;
		GAppInfo* info = g_app_info_create_from_commandline("esdashboard --toggle", NULL, G_APP_INFO_CREATE_NONE, &error);
		if (info == NULL) {
			g_error("Failed to open dashboard: %s", error->message);
			g_clear_error(&error);
			return;
		}

		GdkAppLaunchContext* ctx = gdk_display_get_app_launch_context(gdk_screen_get_display(gdk_window_get_screen(gtk_widget_get_window(GTK_WIDGET(data)))));
		if (!g_app_info_launch(info, NULL, G_APP_LAUNCH_CONTEXT(ctx), &error)) {
			g_error("Failed to open dashboard: %s", error->message);
			g_clear_error(&error);
			return;
		}
	} else {
		WnckWindow* win = wnck_window_get(GDK_WINDOW_XID(focused));
		GtkWidget* menu = wnck_action_menu_new(win);
		gtk_menu_popup_at_widget(GTK_MENU(menu), GTK_WIDGET(btn), GDK_GRAVITY_SOUTH, GDK_GRAVITY_NORTH, NULL);
	}
}

static void expidus_menu_plugin_update(ExpidusMenuPlugin* self) {
	GdkWindow* focused = gdk_screen_get_active_window(gdk_window_get_screen(gtk_widget_get_window(GTK_WIDGET(self))));
	if (focused != NULL && gdk_window_get_type_hint(focused) == GDK_WINDOW_TYPE_HINT_DESKTOP) focused = NULL;

	if (focused == NULL) {
		g_debug("Resetting menu");
		gtk_button_set_label(GTK_BUTTON(self->btn), DEFAULT_TITLE);
		gtk_image_set_from_icon_name(GTK_IMAGE(self->img), "start-here", expidus_panel_plugin_get_icon_size(EXPIDUS_PANEL_PLUGIN(self)));
	} else {
		WnckWindow* win = wnck_window_get(GDK_WINDOW_XID(focused));
		WnckApplication* app = wnck_application_get(GDK_WINDOW_XID(focused));

		if (app == NULL) {
			g_debug("App not found, using window for menu");
			gtk_button_set_label(GTK_BUTTON(self->btn), wnck_window_get_name(win));

			if (wnck_window_has_icon_name(win)) {
				gtk_image_set_from_icon_name(GTK_IMAGE(self->img), wnck_window_get_icon_name(win), expidus_panel_plugin_get_icon_size(EXPIDUS_PANEL_PLUGIN(self)));
			} else if (wnck_window_get_mini_icon(win)) {
				gtk_image_set_from_pixbuf(GTK_IMAGE(self->img), wnck_window_get_mini_icon(win));
			} else {
				gtk_image_set_from_icon_name(GTK_IMAGE(self->img), "package-x-generic", expidus_panel_plugin_get_icon_size(EXPIDUS_PANEL_PLUGIN(self)));
			}
		} else {
			gtk_button_set_label(GTK_BUTTON(self->btn), wnck_application_get_name(app));
			if (wnck_application_get_icon_name(app)) {
				g_debug("Using app icon");
				gtk_image_set_from_icon_name(GTK_IMAGE(self->img), wnck_application_get_icon_name(app), expidus_panel_plugin_get_icon_size(EXPIDUS_PANEL_PLUGIN(self)));
			} else if (wnck_application_get_mini_icon(app)) {
				g_debug("App has no icon name, using pixbuf");
				gtk_image_set_from_pixbuf(GTK_IMAGE(self->img), wnck_application_get_mini_icon(app));
			} else {
				gtk_image_set_from_icon_name(GTK_IMAGE(self->img), "package-x-generic", expidus_panel_plugin_get_icon_size(EXPIDUS_PANEL_PLUGIN(self)));
			}
		}
	}

	gtk_image_set_pixel_size(GTK_IMAGE(self->img), expidus_panel_plugin_get_icon_size(EXPIDUS_PANEL_PLUGIN(self)));
}

static GdkFilterReturn expidus_menu_plugin_event(GdkXEvent* xev, GdkEvent* ev, gpointer data) {
	if (((XEvent*)xev)->type == PropertyNotify) {
		expidus_menu_plugin_update(EXPIDUS_EXPIDUS_MENU_PLUGIN(data));
	}
	return GDK_FILTER_CONTINUE;
}

static void expidus_menu_plugin_free_data(ExpidusPanelPlugin* plugin) {
	ExpidusMenuPlugin* self = EXPIDUS_EXPIDUS_MENU_PLUGIN(plugin);

	GdkWindow* root_win = gdk_screen_get_root_window(gdk_window_get_screen(gtk_widget_get_window(GTK_WIDGET(self))));
	gdk_window_remove_filter(root_win, expidus_menu_plugin_event, self);
}

static void expidus_menu_plugin_construct(ExpidusPanelPlugin* plugin) {
	ExpidusMenuPlugin* self = EXPIDUS_EXPIDUS_MENU_PLUGIN(plugin);

	expidus_panel_plugin_menu_show_configure(plugin);
	gtk_widget_show(self->img);
	gtk_widget_show(self->btn);

	GdkWindow* root_win = gdk_screen_get_root_window(gdk_window_get_screen(gtk_widget_get_window(GTK_WIDGET(self))));
	gdk_window_add_filter(root_win, expidus_menu_plugin_event, self);

	expidus_menu_plugin_update(self);
}

static void expidus_menu_plugin_class_init(ExpidusMenuPluginClass* klass) {
	ExpidusPanelPluginClass* plugin_class = EXPIDUS_PANEL_PLUGIN_CLASS(klass);

	plugin_class->construct = expidus_menu_plugin_construct;
	plugin_class->free_data = expidus_menu_plugin_free_data;
}

static void expidus_menu_plugin_init(ExpidusMenuPlugin* self) {
	self->btn = expidus_panel_create_button();
	self->img = gtk_image_new();

	expidus_panel_plugin_add_action_widget(EXPIDUS_PANEL_PLUGIN(self), self->btn);
	gtk_container_add(GTK_CONTAINER(self), self->btn);
	gtk_widget_set_name(self->btn, "expidus-menu-button");

	gtk_button_set_image(GTK_BUTTON(self->btn), self->img);
	gtk_button_set_image_position(GTK_BUTTON(self->btn), GTK_POS_LEFT);
	gtk_button_set_always_show_image(GTK_BUTTON(self->btn), TRUE);

	g_signal_connect(self->btn, "clicked", G_CALLBACK(expidus_menu_plugin_click), self);
}
