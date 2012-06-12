#include "accel_group_entry.h"

/**
 * Document-class: Gtk3::AccelGroupEntry
 *
 * {Gtk3::AccelGroupEntry} is a class used for callbacks connected to an
 * instance of {Gtk3::AccelGroup}.
 *
 * @since 2012-06-10
 */
VALUE gtk3_cAccelGroupEntry;

/**
 * ID for the symbol `:accelerator_name`.
 *
 * @since 2012-06-10
 */
static ID gtk3_id_accelerator_name;

/**
 * Creates a new instance of the class and stores the accelerator key, callback
 * and accelerator path.
 *
 * @since 2012-06-10
 * @param [Fixnum|Bignum] key The accelerator key.
 * @param [Fixnum|Bignum] mod The accelerator modifier.
 * @param [Fixnum|Bignum] flags The accelerator flags.
 * @param [Proc] callback The accelerator callback.
 */
static VALUE gtk3_accel_group_entry_initialize(
    VALUE self,
    VALUE key,
    VALUE mod,
    VALUE flags,
    VALUE callback
)
{
    char *callback_class = gtk3_get_rbclass(callback);

    gtk3_check_number(key);
    gtk3_check_number(mod);
    gtk3_check_number(flags);

    if ( strcmp(callback_class, "Proc") )
    {
        rb_raise(
            rb_eTypeError,
            "wrong argument type %s (expected Proc)",
            callback_class
        );
    }

    rb_iv_set(self, "@key", key);
    rb_iv_set(self, "@modifier", mod);
    rb_iv_set(self, "@flags", flags);
    rb_iv_set(self, "@callback", callback);

    rb_iv_set(
        self,
        "@path",
        rb_funcall(gtk3_cAccelGroup, gtk3_id_accelerator_name, 2, key, mod)
    );

    return self;
}

/**
 * Initializes the class and required variables.
 *
 * @since 2012-06-10
 */
void Init_gtk3_accel_group_entry()
{
    gtk3_cAccelGroupEntry = rb_define_class_under(
        gtk3_mGtk3,
        "AccelGroupEntry",
        rb_cObject
    );

    rb_define_method(
        gtk3_cAccelGroupEntry,
        "initialize",
        gtk3_accel_group_entry_initialize,
        4
    );

    rb_define_attr(gtk3_cAccelGroupEntry, "key", TRUE, FALSE);
    rb_define_attr(gtk3_cAccelGroupEntry, "modifier", TRUE, FALSE);
    rb_define_attr(gtk3_cAccelGroupEntry, "flags", TRUE, FALSE);
    rb_define_attr(gtk3_cAccelGroupEntry, "path", TRUE, FALSE);
    rb_define_attr(gtk3_cAccelGroupEntry, "callback", TRUE, FALSE);

    gtk3_id_accelerator_name = rb_intern("accelerator_name");
}
