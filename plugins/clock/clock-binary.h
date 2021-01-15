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

#ifndef __CLOCK_BINARY_H__
#define __CLOCK_BINARY_H__

G_BEGIN_DECLS

typedef struct _ExpidusClockBinaryClass ExpidusClockBinaryClass;
typedef struct _ExpidusClockBinary      ExpidusClockBinary;

#define EXPIDUS_CLOCK_TYPE_BINARY            (expidus_clock_binary_get_type ())
#define EXPIDUS_CLOCK_BINARY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_CLOCK_TYPE_BINARY, ExpidusClockBinary))
#define EXPIDUS_CLOCK_BINARY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_CLOCK_TYPE_BINARY, ExpidusClockBinaryClass))
#define EXPIDUS_CLOCK_IS_BINARY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_CLOCK_TYPE_BINARY))
#define EXPIDUS_CLOCK_IS_BINARY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_CLOCK_TYPE_BINARY))
#define EXPIDUS_CLOCK_BINARY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_CLOCK_TYPE_BINARY, ExpidusClockBinaryClass))

GType      expidus_clock_binary_get_type      (void) G_GNUC_CONST;

void       expidus_clock_binary_register_type (ExpidusPanelTypeModule *type_module);

GtkWidget *expidus_clock_binary_new           (ClockTime           *time) G_GNUC_MALLOC;

G_END_DECLS

#endif /* !__CLOCK_BINARY_H__ */
