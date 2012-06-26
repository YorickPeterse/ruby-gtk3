#include "accel_lookup.h"

/**
 * ID for the `:lookup` symbol.
 *
 * @since 2012-06-14
 */
ID gtk3_id_lookup;

/**
 * ID for the `:ord` symbol.
 *
 * @since 2012-06-26
 */
ID gtk3_id_ord;

/**
 * Looks up an accelerator key. Fout types can be specified: Fixnum, Bignum
 * String and Symbol. In the case of the first two types the numeric values
 * will be used directly.
 *
 * When a String or Symbol object is specified the method `#ord()` is called on
 * the object to retrieve the ordinal value of the string.
 *
 * The return value is a Fixnum or Bignum stored in a VALUE object.
 *
 * @since  2012-06-26
 * @param  [VALUE] key The key as a Ruby VALUE object.
 * @return [VALUE]
 */
VALUE gtk3_lookup_accelerator_key(VALUE key)
{
    VALUE key_type = TYPE(key);

    if ( key_type == T_STRING || key_type == T_SYMBOL )
    {
        key = rb_funcall(key, gtk3_id_to_s, 0);
        key = rb_funcall(key, gtk3_id_ord, 0);
    }
    else
    {
        gtk3_check_number(key);
    }

    return key;
}

/**
 * Looks up an accelerator modifier and returns the value. If no modifier was
 * found `ArgumentError` is raised instead.
 *
 * @since  2012-06-10
 * @param  [VALUE] modifier The modifier to look up.
 * @raise  [ArgumentError] Raised when the specified modifier is invalid.
 * @return [VALUE]
 */
VALUE gtk3_lookup_accelerator_modifier(VALUE modifier)
{
    VALUE modifier_type = TYPE(modifier);

    if ( modifier_type == T_STRING || modifier_type == T_SYMBOL )
    {
        modifier = rb_funcall(gtk3_mModifierType, gtk3_id_lookup, 1, modifier);
    }
    else
    {
        gtk3_check_number(modifier);
    }

    if ( NIL_P(modifier) )
    {
        rb_raise(rb_eArgError, "invalid accelerator modifier");
    }

    return modifier;
}

/**
 * Looks up an accelerator flag and returns the value. If no flag was
 * found `ArgumentError` is raised instead.
 *
 * @since  2012-06-10
 * @param  [VALUE] flag The modifier to look up.
 * @raise  [ArgumentError] Raised when the specified flag is invalid.
 * @return [VALUE]
 */
VALUE gtk3_lookup_accelerator_flag(VALUE flag)
{
    VALUE flag_type = TYPE(flag);

    if ( flag_type == T_STRING || flag_type == T_SYMBOL )
    {
        flag = rb_funcall(gtk3_mAccelFlag, gtk3_id_lookup, 1, flag);
    }
    else
    {
        gtk3_check_number(flag);
    }

    if ( NIL_P(flag) )
    {
        rb_raise(rb_eArgError, "invalid accelerator flag");
    }

    return flag;
}

/**
 * Sets up the required variables for the helper functions in this files.
 *
 * @since 2012-06-13
 */
void Init_gtk3_accel_lookup()
{
    gtk3_id_lookup = rb_intern("lookup");
    gtk3_id_ord    = rb_intern("ord");
}
