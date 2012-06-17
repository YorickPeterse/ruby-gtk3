#include "accel_group_entry.h"

/**
 * ID for the `:accelerator_name` symbol.
 *
 * @since 2012-06-14
 */
ID gtk3_id_accelerator_name;

/**
 * Document-class: Gtk3::AccelGroupEntry
 *
 * The {Gtk3::AccelGroupEntry} class is used for representing entries in an
 * accelerator group. Each entry contains details about the accelerator key,
 * modifier, flags, callback and path.
 *
 * Using this class on its own doesn't make a whole lot of sense since it
 * mostly acts as a data container. Internally it's used by methods such as
 * {Gtk3::AccelGroup#query}.
 *
 * @!attribute [r] key
 *   Numeric value of the key the entry is associated with.
 *   @since  2012-06-17
 *   @return [Fixnum|Bignum]
 * @!attribute [r] modifier
 *   The modifier of the accelerator entry.
 *   @since  2012-06-17
 *   @return [Fixnum|Bignum]
 * @!attribute [r] flags
 *   The accelerator flags of the entry.
 *   @since  2012-06-17
 *   @return [Fixnum|Bignum]
 * @!attribute [r] path
 *   String that represents the accelerator path. For example, if the key is
 *   set to "q" (numeric value of 113) and the modifier to "control" then the
 *   path will be "<Primary>q" ("Primary" is "Control" in GTK).
 *   @since  2012-06-17
 *   @return [String]
 * @!attribute [r] callback
 *   The proc to call when activating the entry.
 *   @since  2012-06-17
 *   @return [Proc]
 *
 * @since 2012-06-10
 */
VALUE gtk3_cAccelGroupEntry;

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
