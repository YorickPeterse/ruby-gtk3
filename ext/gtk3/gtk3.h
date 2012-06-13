#ifndef GTK3_NATIVE
#define GTK3_NATIVE

#include <ruby.h>
#include <gtk/gtk.h>
#include "closure.h"
#include "type.h"
#include "lookup_constant.h"
#include "accel_lookup.h"
#include "accel_flag.h"
#include "accel_map.h"
#include "accel_key.h"
#include "accel_group.h"
#include "accel_group_entry.h"
#include "modifier_type.h"
#include "widget.h"
#include "window.h"

extern ID gtk3_id_new;
extern ID gtk3_id_call;
extern ID gtk3_id_class;
extern ID gtk3_id_to_s;
extern ID gtk3_id_upcase;
extern ID gtk3_id_to_sym;

extern VALUE gtk3_mGtk3;

extern void Init_gtk3();

#endif
