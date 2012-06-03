#ifndef GTK3_CLOSURE
#define GTK3_CLOSURE

#include "gtk3.h"

typedef struct RClosure RClosure;

extern void gtk3_closure_invalidate(gpointer data, GClosure *closure);

extern void gtk3_closure_marshal(
    GClosure *closure,
    GValue *return_value,
    guint n_param_values,
    const GValue *param_values,
    gpointer invocation_hint,
    gpointer marshal_data
);

extern RClosure *gtk3_closure_new(VALUE proc, VALUE object);

extern void Init_gtk3_closure();

#endif
