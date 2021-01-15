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



#ifndef __LIBEXPIDUS1PANEL_ENUMS_H__
#define __LIBEXPIDUS1PANEL_ENUMS_H__

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * SECTION: enums
 * @title: Standard Enumerations
 * @short_description: Standard enumerations used by the Expidus Panel.
 * @include: libexpidus1panel/libexpidus1panel.h
 *
 * Currently only contains the definition of #ExpidusScreenPosition.
 **/

/**
 * ExpidusPanelPluginMode
 * @EXPIDUS_PANEL_PLUGIN_MODE_HORIZONTAL : Horizontal panel and plugins
 * @EXPIDUS_PANEL_PLUGIN_MODE_VERTICAL   : Vertical rotated panel and plugins
 * @EXPIDUS_PANEL_PLUGIN_MODE_DESKBAR    : Vertical panel with horizontal plugins
 *
 * Orientation of the plugin in the panel.
 *
 * Since: 4.10
 **/
typedef enum /*<enum,prefix=EXPIDUS_PANEL_PLUGIN_MODE >*/
{
  EXPIDUS_PANEL_PLUGIN_MODE_HORIZONTAL,
  EXPIDUS_PANEL_PLUGIN_MODE_VERTICAL,
  EXPIDUS_PANEL_PLUGIN_MODE_DESKBAR
}
ExpidusPanelPluginMode;

/**
 * ExpidusScreenPosition
 * @EXPIDUS_SCREEN_POSITION_NONE       : No position has been set.
 * @EXPIDUS_SCREEN_POSITION_NW_H       : North West Horizontal
 * @EXPIDUS_SCREEN_POSITION_N          : North
 * @EXPIDUS_SCREEN_POSITION_NE_H       : North East Horizontal
 * @EXPIDUS_SCREEN_POSITION_NW_V       : North West Vertical
 * @EXPIDUS_SCREEN_POSITION_W          : West
 * @EXPIDUS_SCREEN_POSITION_SW_V       : South West Vertical
 * @EXPIDUS_SCREEN_POSITION_NE_V       : North East Vertical
 * @EXPIDUS_SCREEN_POSITION_E          : East
 * @EXPIDUS_SCREEN_POSITION_SE_V       : South East Vertical
 * @EXPIDUS_SCREEN_POSITION_SW_H       : South West Horizontal
 * @EXPIDUS_SCREEN_POSITION_S          : South
 * @EXPIDUS_SCREEN_POSITION_SE_H       : South East Horizontal
 * @EXPIDUS_SCREEN_POSITION_FLOATING_H : Floating Horizontal
 * @EXPIDUS_SCREEN_POSITION_FLOATING_V : Floating Vertical
 *
 * There are three screen positions for each side of the screen:
 * LEFT/TOP, CENTER and RIGHT/BOTTOM. The ExpidusScreenPosition is expressed
 * as navigational direction, with possible addition of H or V to denote
 * horizontal and vertical orientation. Additionally there are two floating
 * positions, horizontal and vertical.
 **/
typedef enum /*<enum,prefix=EXPIDUS_SCREEN_POSITION >*/
{
    EXPIDUS_SCREEN_POSITION_NONE,

    /* top */
    EXPIDUS_SCREEN_POSITION_NW_H,          /* North West Horizontal */
    EXPIDUS_SCREEN_POSITION_N,             /* North                 */
    EXPIDUS_SCREEN_POSITION_NE_H,          /* North East Horizontal */

    /* left */
    EXPIDUS_SCREEN_POSITION_NW_V,          /* North West Vertical   */
    EXPIDUS_SCREEN_POSITION_W,             /* West                  */
    EXPIDUS_SCREEN_POSITION_SW_V,          /* South West Vertical   */

    /* right */
    EXPIDUS_SCREEN_POSITION_NE_V,          /* North East Vertical   */
    EXPIDUS_SCREEN_POSITION_E,             /* East                  */
    EXPIDUS_SCREEN_POSITION_SE_V,          /* South East Vertical   */

    /* bottom */
    EXPIDUS_SCREEN_POSITION_SW_H,          /* South West Horizontal */
    EXPIDUS_SCREEN_POSITION_S,             /* South                 */
    EXPIDUS_SCREEN_POSITION_SE_H,          /* South East Horizontal */

    /* floating */
    EXPIDUS_SCREEN_POSITION_FLOATING_H,    /* Floating Horizontal */
    EXPIDUS_SCREEN_POSITION_FLOATING_V     /* Floating Vertical */
}
ExpidusScreenPosition;

/**
 * expidus_screen_position_is_horizontal:
 * @position : the #ExpidusScreenPosition
 *
 * Whether the current #ExpidusScreenPosition is horizontal.
 *
 * Returns: %TRUE if horizontal, %FALSE otherwise
 **/
#define expidus_screen_position_is_horizontal(position)   \
    (position <= EXPIDUS_SCREEN_POSITION_NE_H ||          \
     (position >= EXPIDUS_SCREEN_POSITION_SW_H &&         \
      position <= EXPIDUS_SCREEN_POSITION_FLOATING_H))

/**
 * expidus_screen_position_get_orientation:
 * @position : the #ExpidusScreenPosition
 *
 * Converts the current #ExpidusScreenPosition into a #GtkOrientation.
 *
 * Returns: the #GtkOrientation corresponding to @position.
 **/
#define expidus_screen_position_get_orientation(position) \
    (expidus_screen_position_is_horizontal (position) ? \
        GTK_ORIENTATION_HORIZONTAL : GTK_ORIENTATION_VERTICAL)

/**
 * expidus_screen_position_is_floating:
 * @position : the #ExpidusScreenPosition
 *
 * Whether the current #ExpidusScreenPosition is floating on the screen.
 *
 * Returns: %TRUE if floating, %FALSE otherwise.
 **/
#define expidus_screen_position_is_floating(position) \
    (position >= EXPIDUS_SCREEN_POSITION_FLOATING_H || \
     position == EXPIDUS_SCREEN_POSITION_NONE)

/**
 * expidus_screen_position_is_top:
 * @position : the #ExpidusScreenPosition
 *
 * Whether the current #ExpidusScreenPosition is above of the center of
 * the screen.
 *
 * Returns: %TRUE if on the top of the screen, %FALSE otherwise
 **/
#define expidus_screen_position_is_top(position) \
    (position >= EXPIDUS_SCREEN_POSITION_NW_H && \
     position <= EXPIDUS_SCREEN_POSITION_NE_H)

/**
 * expidus_screen_position_is_left:
 * @position : the #ExpidusScreenPosition
 *
 * Whether the current #ExpidusScreenPosition is left of the center of
 * the screen.
 *
 * Returns: %TRUE if on the left of the screen, %FALSE otherwise
 **/
#define expidus_screen_position_is_left(position) \
    (position >= EXPIDUS_SCREEN_POSITION_NW_V && \
     position <= EXPIDUS_SCREEN_POSITION_SW_V)

/**
 * expidus_screen_position_is_right:
 * @position : the #ExpidusScreenPosition
 *
 * Whether the current #ExpidusScreenPosition is right of the center of
 * the screen.
 *
 * Returns: %TRUE if on the right of the screen, %FALSE otherwise
 **/
#define expidus_screen_position_is_right(position) \
    (position >= EXPIDUS_SCREEN_POSITION_NE_V && \
     position <= EXPIDUS_SCREEN_POSITION_SE_V)

/**
 * expidus_screen_position_is_bottom:
 * @position : the #ExpidusScreenPosition
 *
 * Whether the current #ExpidusScreenPosition is below of the center of
 * the screen.
 *
 * Returns: %TRUE if on the bottom of the screen, %FALSE otherwise
 **/
#define expidus_screen_position_is_bottom(position) \
    (position >= EXPIDUS_SCREEN_POSITION_SW_H && \
     position <= EXPIDUS_SCREEN_POSITION_SE_H)

G_END_DECLS

#endif /* !__LIBEXPIDUS1PANEL_ENUMS_H__ */
