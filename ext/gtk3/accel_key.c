#include "accel_key.h"

/**
 * Document-class: Gtk3::AccelKey
 *
 * Class that represents a single accelerator key, its modifier and flags. This
 * class is used by methods such as {Gtk3::AccelMap.lookup\_entry}, it's not
 * very useful on its own as it's merely a data container.
 *
 * @!attribute [r] key
 *  The numeric value of the accelerator key.
 *  @since  2012-06-17
 *  @return [Fixnum|Bignum]
 * @!attribute [r] modifier
 *  The accelerator modifier.
 *  @since  2012-06-17
 *  @return [Fixnum|Bignum]
 * @!attribute [r] flags
 *  The accelerator flags.
 *  @since  2012-06-17
 *  @return [Fixnum|Bignum]
 *
 * @since 2012-06-14
 */
VALUE gtk3_cAccelKey;

/**
 * Creates a new instance of the {Gtk3::AccelKey} class.
 *
 * @since 2012-06-14
 * @param [Fixnum|Bignum] key The accelerator key.
 * @param [Fixnum|Bignum] modifier The accelerator modifier.
 * @param [Fixnum|Bignum] flags A set of accelerator flags.
 */
static VALUE gtk3_accel_key_initialize(
    VALUE self,
    VALUE key,
    VALUE modifier,
    VALUE flags
)
{
    rb_iv_set(self, "@key", key);
    rb_iv_set(self, "@modifier", modifier);
    rb_iv_set(self, "@flags", flags);

    return self;
}

/**
 * Initializes the class and sets up the methods.
 *
 * @since 2012-06-14
 */
void Init_gtk3_accel_key()
{
    gtk3_cAccelKey = rb_define_class_under(gtk3_mGtk3, "AccelKey", rb_cObject);

    rb_define_method(
        gtk3_cAccelKey,
        "initialize",
        gtk3_accel_key_initialize,
        3
    );

    rb_define_attr(gtk3_cAccelKey, "key", TRUE, FALSE);
    rb_define_attr(gtk3_cAccelKey, "modifier", TRUE, FALSE);
    rb_define_attr(gtk3_cAccelKey, "flags", TRUE, FALSE);
}
