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
