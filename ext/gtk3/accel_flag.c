#include "accel_flag.h"

/**
 * Document-module: Gtk3::AccelFlag
 *
 * {Gtk3::AccelFlag} is a module that's used for storing and retrieving GTK
 * accelerator flags.
 *
 * @since 2012-06-09
 */
VALUE gtk3_mAccelFlag;

/**
 * Similar to {Gtk3::ModifierType.lookup} this method can be used for looking
 * up accelerator flag constants.
 *
 * @example
 *  Gtk3::AccelFlag.lookup(:visible) => Gtk3::AccelFlag::VISIBLE
 *  Gtk3::AccelFlag.lookup(:example) => nil
 *
 * @since  2012-06-09
 * @param  [String|Symbol] modifier The name of the modifier.
 * @return [Fixnum|NilClass]
 */
static VALUE gtk3_accel_flag_lookup(VALUE class, VALUE name)
{
    return gtk3_lookup_constant(class, name);
}

/**
 * Initializes the module.
 *
 * @since 2012-06-09
 */
void Init_gtk3_accel_flag()
{
    gtk3_mAccelFlag = rb_define_module_under(gtk3_mGtk3, "AccelFlag");

    rb_define_singleton_method(
        gtk3_mAccelFlag,
        "lookup",
        gtk3_accel_flag_lookup,
        1
    );

    rb_define_const(gtk3_mAccelFlag, "VISIBLE", INT2NUM(GTK_ACCEL_VISIBLE));
    rb_define_const(gtk3_mAccelFlag, "LOCKED", INT2NUM(GTK_ACCEL_LOCKED));
    rb_define_const(gtk3_mAccelFlag, "MASK", INT2NUM(GTK_ACCEL_MASK));
}
