#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _ExpidusMenuPluginClass ExpidusMenuPluginClass;
typedef struct _ExpidusMenuPlugin      ExpidusMenuPlugin;

#define EXPIDUS_TYPE_EXPIDUS_MENU_PLUGIN            (expidus_menu_plugin_get_type ())
#define EXPIDUS_EXPIDUS_MENU_PLUGIN(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_TYPE_EXPIDUS_MENU_PLUGIN, ExpidusMenuPlugin))
#define EXPIDUS_EXPIDUS_MENU_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_TYPE_EXPIDUS_MENU_PLUGIN, ExpidusMenuPluginClass))
#define EXPIDUS_IS_EXPIDUS_MENU_PLUGIN(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_TYPE_EXPIDUS_MENU_PLUGIN))
#define EXPIDUS_IS_EXPIDUS_MENU_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), EXPIDUS_TYPE_EXPIDUS_MENU_PLUGIN))
#define EXPIDUS_EXPIDUS_MENU_PLUGIN_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_TYPE_EXPIDUS_MENU_PLUGIN, ExpidusMenuPluginClass))

GType expidus_menu_plugin_get_type(void) G_GNUC_CONST;

void expidus_menu_plugin_register_type(ExpidusPanelTypeModule *type_module);

G_END_DECLS
