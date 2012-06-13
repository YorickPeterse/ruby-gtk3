#ifndef GTK3_LOOKUP_CONSTANT
#define GTK3_LOOKUP_CONSTANT

#include "gtk3.h"

extern ID gtk3_id_const_defined;
extern ID gtk3_id_const_get;

extern VALUE gtk3_lookup_constant(VALUE search, VALUE name);
extern void Init_gtk3_lookup_constant();

#endif
