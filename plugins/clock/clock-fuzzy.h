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

#ifndef __CLOCK_FUZZY_H__
#define __CLOCK_FUZZY_H__

G_BEGIN_DECLS

typedef struct _ExpidusClockFuzzyClass ExpidusClockFuzzyClass;
typedef struct _ExpidusClockFuzzy      ExpidusClockFuzzy;

#define EXPIDUS_CLOCK_TYPE_FUZZY            (expidus_clock_fuzzy_get_type ())
#define EXPIDUS_CLOCK_FUZZY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), EXPIDUS_CLOCK_TYPE_FUZZY, ExpidusClockFuzzy))
#define EXPIDUS_CLOCK_FUZZY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_CLOCK_TYPE_FUZZY, ExpidusClockFuzzyClass))
#define EXPIDUS_CLOCK_IS_FUZZY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EXPIDUS_CLOCK_TYPE_FUZZY))
#define EXPIDUS_CLOCK_IS_FUZZY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), EXPIDUS_CLOCK_TYPE_FUZZY))
#define EXPIDUS_CLOCK_FUZZY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), EXPIDUS_CLOCK_TYPE_FUZZY, ExpidusClockFuzzyClass))

GType      expidus_clock_fuzzy_get_type      (void) G_GNUC_CONST;

void       expidus_clock_fuzzy_register_type (ExpidusPanelTypeModule *type_module);

GtkWidget *expidus_clock_fuzzy_new           (ClockTime           *time) G_GNUC_MALLOC;

G_END_DECLS

#endif /* !__CLOCK_FUZZY_H__ */
