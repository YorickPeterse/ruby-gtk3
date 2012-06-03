#include "gvalue.h"

/**
 * ID for the `:to_s` symbol.
 *
 * @since 2012-06-03
 */
static ID gtk3_id_to_s;

/**
 * Converts a Ruby value to a GValue.
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
 * Initializes the required variables.
 *
 * @since 2012-06-03
 */
void Init_gtk3_gvalue()
{
    gtk3_id_to_s = rb_intern("to_s");
}
