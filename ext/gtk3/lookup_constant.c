#include "lookup_constant.h"

/**
 * ID of the `:class` symbol.
 *
 * @since 2012-06-09
 */
static ID gtk3_id_class;

/**
 * ID for the `:to_s` symbol.
 *
 * @since 2012-06-09
 */
static ID gtk3_id_to_s;

/**
 * ID for the `:upcase` symbol.
 *
 * @since 2012-06-09
 */
static ID gtk3_id_upcase;

/**
 * ID for the `:to_sym` symbol.
 *
 * @since 2012-06-09
 */
static ID gtk3_id_to_sym;

/**
 * ID for the `:const_defined?` symbol.
 *
 * @since 2012-06-09
 */
static ID gtk3_id_const_defined;

/**
 * ID for the `:const_get` symbol.
 *
 * @since 2012-06-09
 */
static ID gtk3_id_const_get;

/**
 * Looks up a constant in a given class or module. If the given constant exists
 * then its value is returned, otherwise Qnil is returned.
 *
 * @since  2012-06-09
 * @param  [VALUE] search The class or module to use for the lookup.
 * @param  [VALUE] name A String or Symbol containing the (case insensitive)
 *  name of the constant.
 * @return [Fixnum|NilClass]
 */
VALUE gtk3_lookup_constant(VALUE search, VALUE name)
{
    VALUE name_type = TYPE(name);
    VALUE constant = Qnil;
    VALUE constant_defined;

    if ( name_type != T_STRING && name_type != T_SYMBOL )
    {
        rb_raise(
            rb_eTypeError,
            "wrong argument type %s (expected String or Symbol)",
            gtk3_get_rbclass(name)
        );
    }

    name             = rb_funcall(name, gtk3_id_upcase, 0);
    name             = rb_funcall(name, gtk3_id_to_sym, 0);
    constant_defined = rb_funcall(search, gtk3_id_const_defined, 1, name);

    if ( RTEST(constant_defined) )
    {
        constant = rb_funcall(search, gtk3_id_const_get, 1, name);
    }

    return constant;
}

/**
 * Sets up the required variables.
 *
 * @since 2012-06-09
 */
void Init_gtk3_lookup_constant()
{
    gtk3_id_class         = rb_intern("class");
    gtk3_id_to_s          = rb_intern("to_s");
    gtk3_id_upcase        = rb_intern("upcase");
    gtk3_id_to_sym        = rb_intern("to_sym");
    gtk3_id_const_defined = rb_intern("const_defined?");
    gtk3_id_const_get     = rb_intern("const_get");
}
