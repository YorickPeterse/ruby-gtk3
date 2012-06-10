#include "closure.h"

/**
 * ID of the `:call` symbol.
 *
 * @since 2012-06-03
 */
static ID gtk3_id_call;

/**
 * Called whenever a closure is no longer valid. This function unsets the
 * contents of the RClosure struct and frees any allocated memory.
 *
 * @since 2012-06-03
 * @param [gpointer] data Custom data that was passed to the closure.
 * @param [GClosure] closure The closure that is no longer valid.
 */
void gtk3_closure_invalidate(gpointer data, GClosure *closure)
{
    /* RClosure *rclosure = (RClosure *) closure; */

    /* TODO: Figure out how to effectively use this function to free memory. */
}

/**
 * Marshal function that is executed whenever an event is triggered.
 *
 * @since 2012-06-03
 * @param [GClosure] closure The closure for the event.
 * @param [GValue] return_value The return value of the callback.
 * @param [guint] n_param_values The amount of parameters.
 * @param [GValue] param_values Array of arguments for the callback.
 * @param [gpointer] invocation_hint The invocation hint (before/after) of the
 *  callback.
 * @param [gpointer] marshal_data Extra data specified when setting a closure's
 *  marshal callback.
 */
void gtk3_closure_marshal(
    GClosure *closure,
    GValue *return_value,
    guint n_param_values,
    const GValue *param_values,
    gpointer invocation_hint,
    gpointer marshal_data
)
{
    VALUE rb_return_value;
    RClosure *rclosure = (RClosure *) closure;

    rb_return_value = rb_funcall(
        rclosure->proc,
        gtk3_id_call,
        1,
        rclosure->object
    );

    gtk3_rbvalue_to_gvalue(rb_return_value, return_value);
}

/**
 * Creates a new RClosure object.
 *
 * @since  2012-06-03
 * @param  [VALUE] proc The proc to call whenever an event is triggered.
 * @param  [VALUE] object The object that the closure and proc belong to.
 * @return [RClosure]
 */
RClosure *gtk3_closure_new(VALUE proc, VALUE object)
{
    GClosure *closure;
    RClosure *rclosure;

    closure = g_closure_new_simple(sizeof(RClosure), NULL);

    g_closure_set_marshal(closure, gtk3_closure_marshal);
    g_closure_add_invalidate_notifier(closure, NULL, gtk3_closure_invalidate);

    rclosure         = (RClosure *) closure;
    rclosure->proc   = proc;
    rclosure->object = object;

    rb_global_variable(&rclosure->proc);

    return rclosure;
}

/**
 * Initializes the required variables.
 *
 * @since 2012-06-03
 */
void Init_gtk3_closure()
{
    gtk3_id_call = rb_intern("call");
}
