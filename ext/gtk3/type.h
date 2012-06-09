#ifndef GTK3_TYPE
#define GTK3_TYPE

#include "gtk3.h"

extern void Init_gtk3_type();
extern void gtk3_check_number(VALUE number);
extern void gtk3_rbvalue_to_gvalue(VALUE rbvalue, GValue *gvalue);
extern VALUE gtk3_gboolean_to_rboolean(gboolean boolean);
extern char *gtk3_get_rbclass(VALUE object);

#endif
