#ifndef GTK3_CLOSURE
#define GTK3_CLOSURE

#include "gtk3.h"

/**
 * Closure structure that is used for binding procs to signals in Ruby code.
 * This structure has the following members:
 *
 * * closure
 * * proc: the proc to call.
 * * object: the Ruby object of the event.
 *
 * @since 2012-06-03
 */
typedef struct RClosure
{
    GClosure closure;
    VALUE proc;
    VALUE object;
} RClosure;

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
