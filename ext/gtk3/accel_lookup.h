#ifndef GTK3_ACCEL_LOOKUP
#define GTK3_ACCEL_LOOKUP

#include "gtk3.h"

extern ID gtk3_id_lookup;

extern VALUE gtk3_lookup_accelerator_key(VALUE key);
extern VALUE gtk3_lookup_accelerator_modifier(VALUE modifier);
extern VALUE gtk3_lookup_accelerator_flag(VALUE flag);

extern void Init_gtk3_accel_lookup();

#endif
