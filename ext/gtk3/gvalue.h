#ifndef GTK3_GVALUE
#define GTK3_GVALUE

#include "gtk3.h"

extern void gtk3_rbvalue_to_gvalue(VALUE rbvalue, GValue *gvalue);
extern void Init_gtk3_gvalue();

#endif
