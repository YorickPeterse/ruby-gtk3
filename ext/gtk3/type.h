#ifndef GTK3_TYPE
#define GTK3_TYPE

#include "gtk3.h"

extern void Init_gtk3_type();
extern void gtk3_rbvalue_to_gvalue(VALUE rbvalue, GValue *gvalue);
extern void gtk3_check_number(VALUE number);

#endif
