#ifndef GTK3_TYPE
#define GTK3_TYPE

#include "gtk3.h"

extern VALUE gtk3_gboolean_to_rboolean(gboolean boolean);
extern VALUE gtk3_rboolean_to_gboolean(VALUE rbool);
extern void gtk3_check_number(VALUE number);
extern void gtk3_check_boolean(VALUE val);
extern void gtk3_rbvalue_to_gvalue(VALUE rbvalue, GValue *gvalue);
extern char *gtk3_get_rbclass(VALUE object);

#endif
