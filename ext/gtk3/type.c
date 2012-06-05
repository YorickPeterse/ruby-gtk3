#include "type.h"

/**
 * ID for the `:class` symbol.
 *
 * @since 2012-06-05
 */
static ID gtk3_id_class;

/**
 * ID for the `:to_s` symbol.
 *
 * @since 2012-06-05
 */
static ID gtk3_id_to_s;

/**
 * Converts a Ruby value to a GValue.
 *
 * TODO: currently the amount of types this function can handle is rather
 * limited. Based on whether or not it's needed this function should be capable
 * of handling more types (e.g. hashes).
 *
 * @since 2012-06-03
 * @param [VALUE] rbvalue The Ruby value to convert.
 * @param [GValue] gvalue A GValue object to store the converted value in.
 */
void gtk3_rbvalue_to_gvalue(VALUE rbvalue, GValue *gvalue)
{
    switch ( TYPE(rbvalue) )
    {
        case T_FLOAT:
            g_value_set_double(gvalue, NUM2DBL(rbvalue));
            break;

        case T_STRING:
        case T_SYMBOL:
            rbvalue = rb_funcall(rbvalue, gtk3_id_to_s, 0);
            g_value_set_string(gvalue, StringValuePtr(rbvalue));
            break;

        case T_FIXNUM:
            g_value_set_int(gvalue, NUM2INT(rbvalue));
            break;

        case T_BIGNUM:
            g_value_set_int64(gvalue, NUM2LONG(rbvalue));
            break;

        case T_TRUE:
            g_value_set_boolean(gvalue, TRUE);
            break;
        case T_FALSE:
            g_value_set_boolean(gvalue, FALSE);
            break;
    }
}

/**
 * Checks if the specified Ruby value is a Fixnum or Bignum.
 *
 * @since 2012-06-05
 * @raise TypeError Raised when the specified value is not a Fixnum or Bignum.
 */
void gtk3_check_number(VALUE number)
{
    VALUE type = TYPE(number);
    VALUE rb_class;
    char *class;

    if ( type != T_FIXNUM && type != T_BIGNUM )
    {
        rb_class = rb_funcall(number, gtk3_id_class, 0);
        rb_class = rb_funcall(rb_class, gtk3_id_to_s, 0);
        class    = StringValuePtr(rb_class);

        rb_raise(
            rb_eTypeError,
            "wrong argument type %s (expected Fixnum or Bignum)",
            class
        );
    }
}

/**
 * Initializes the required variables.
 *
 * @since 2012-06-05
 */
void Init_gtk3_type()
{
    gtk3_id_class = rb_intern("class");
    gtk3_id_to_s  = rb_intern("to_s");
}
