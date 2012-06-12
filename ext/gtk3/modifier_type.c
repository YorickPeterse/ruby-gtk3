#include "modifier_type.h"

/**
 * Document-module: Gtk3::ModifierType
 *
 * {Gtk3::ModifierType} is a module that's used for storing various constants
 * related to the GTK modifier types.
 *
 * @since 2012-06-09
 */
VALUE gtk3_mModifierType;

/**
 * Searches for a modifier type that matches the specified String or Symbol.
 * Upon success the value of the constant is returned, otherwise nil is
 * returned.
 *
 * @example
 *  Gtk3::ModifierType.lookup(:shift)   => Gtk3::ModifierType::SHIFT
 *  Gtk3::ModifierType.lookup(:example) => nil
 *
 * @since  2012-06-09
 * @param  [String|Symbol] modifier The name of the modifier.
 * @return [Fixnum|NilClass]
 */
static VALUE gtk3_modifier_type_lookup(VALUE class, VALUE modifier)
{
    return gtk3_lookup_constant(class, modifier);
}

/**
 * Initializes the module.
 *
 * @since 2012-06-09
 */
void Init_gtk3_modifier_type()
{
    gtk3_mModifierType = rb_define_module_under(gtk3_mGtk3, "ModifierType");

    rb_define_singleton_method(
        gtk3_mModifierType,
        "lookup",
        gtk3_modifier_type_lookup,
        1
    );

    rb_define_const(gtk3_mModifierType, "SHIFT", INT2NUM(GDK_SHIFT_MASK));
    rb_define_const(gtk3_mModifierType, "LOCK", INT2NUM(GDK_LOCK_MASK));
    rb_define_const(gtk3_mModifierType, "CONTROL", INT2NUM(GDK_CONTROL_MASK));

    rb_define_const(gtk3_mModifierType, "MOD1", INT2NUM(GDK_MOD1_MASK));
    rb_define_const(gtk3_mModifierType, "MOD2", INT2NUM(GDK_MOD2_MASK));
    rb_define_const(gtk3_mModifierType, "MOD3", INT2NUM(GDK_MOD3_MASK));
    rb_define_const(gtk3_mModifierType, "MOD4", INT2NUM(GDK_MOD4_MASK));
    rb_define_const(gtk3_mModifierType, "MOD5", INT2NUM(GDK_MOD5_MASK));

    rb_define_const(gtk3_mModifierType, "BUTTON1", INT2NUM(GDK_BUTTON1_MASK));
    rb_define_const(gtk3_mModifierType, "BUTTON2", INT2NUM(GDK_BUTTON2_MASK));
    rb_define_const(gtk3_mModifierType, "BUTTON3", INT2NUM(GDK_BUTTON3_MASK));
    rb_define_const(gtk3_mModifierType, "BUTTON4", INT2NUM(GDK_BUTTON4_MASK));
    rb_define_const(gtk3_mModifierType, "BUTTON5", INT2NUM(GDK_BUTTON5_MASK));

    rb_define_const(gtk3_mModifierType, "SUPER", INT2NUM(GDK_SUPER_MASK));
    rb_define_const(gtk3_mModifierType, "HYPER", INT2NUM(GDK_HYPER_MASK));
    rb_define_const(gtk3_mModifierType, "META", INT2NUM(GDK_META_MASK));

    rb_define_const(gtk3_mModifierType, "RELEASE", INT2NUM(GDK_RELEASE_MASK));
    rb_define_const(gtk3_mModifierType, "MODIFIER", INT2NUM(GDK_MODIFIER_MASK));
}
