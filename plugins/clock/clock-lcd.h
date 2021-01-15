/*
 * Copyright (C) 2007-2010 Nick Schermer <nick@expidus.org>
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

#ifndef __CLOCK_LCD_H__
#define __CLOCK_LCD_H__

G_BEGIN_DECLS

typedef struct _ExpidusClockLcdClass ExpidusClockLcdClass;
typedef struct _ExpidusClockLcd      ExpidusClockLcd;

#define EXPIDUS_CLOCK_TYPE_LCD            (expidus_clock_lcd_get_type ())
#define EXPIDUS_CLOCK_LCD(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_CLOCK_TYPE_LCD, ExpidusClockLcd))
#define EXPIDUS_CLOCK_LCD_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_CLOCK_TYPE_LCD, ExpidusClockLcdClass))
#define EXPIDUS_CLOCK_IS_LCD(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_CLOCK_TYPE_LCD))
#define EXPIDUS_CLOCK_IS_LCD_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_CLOCK_TYPE_LCD))
#define EXPIDUS_CLOCK_LCD_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_CLOCK_TYPE_LCD, ExpidusClockLcdClass))

GType      expidus_clock_lcd_get_type      (void) G_GNUC_CONST;

void       expidus_clock_lcd_register_type (ExpidusPanelTypeModule *type_module);

GtkWidget *expidus_clock_lcd_new           (ClockTime           *time) G_GNUC_MALLOC;

G_END_DECLS

#endif /* !__CLOCK_LCD_H__ */
