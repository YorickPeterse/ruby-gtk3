#include "type.h"

/**
 * Converts a `gboolean` to a Ruby boolean.
 *
 * @since  2012-06-05
 * @param  [gboolean] boolean The boolean to convert.
 * @return [VALUE]
 */
VALUE gtk3_gboolean_to_rboolean(gboolean boolean)
{
    if ( boolean == TRUE )
    {
        return Qtrue;
    }
    else
    {
        return Qfalse;
    }
}

/**
 * Converts a Ruby boolean to a GTK boolean.
 *
 * @since  2012-06-30
 * @param  [VALUE] rbool The Ruby boolean to convert.
 * @return [gboolean]
 */
VALUE gtk3_rboolean_to_gboolean(VALUE rbool)
{
    if ( rbool == Qtrue )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

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

    if ( type != T_FIXNUM && type != T_BIGNUM )
    {
        rb_raise(
            rb_eTypeError,
            "wrong argument type %s (expected Fixnum or Bignum)",
            gtk3_get_rbclass(number)
        );
    }
}

/**
 * Returns the class name of a Ruby object as a C string.
 *
 * @since  2012-06-09
 * @param  [VALUE] object The object for which to retrieve the class.
 * @return [char *]
 */
char *gtk3_get_rbclass(VALUE object)
{
    VALUE object_class;

   object_class = rb_funcall(object, gtk3_id_class, 0);
   object_class = rb_funcall(object_class, gtk3_id_to_s, 0);

   return StringValuePtr(object_class);
}
