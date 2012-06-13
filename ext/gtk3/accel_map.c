#include "accel_map.h"

/**
 * Document-module: Gtk3::AccelMap
 *
 * @since 2012-06-12
 */
VALUE gtk3_mAccelMap;

/**
 * Registers a new accelerator.
 *
 * @since 2012-06-13
 * @param [String] path The accelerator path.
 * @param [Fixnum|Bignum] key The key to bind the accelerator to.
 * @param [Fixnum|Bignum|String|Symbol] modifier The accelerator modifier.
 */
static VALUE gtk3_accel_map_add_entry(
    VALUE class,
    VALUE path,
    VALUE key,
    VALUE modifier
)
{
    const gchar *gtk_path;
    guint gtk_key;
    GdkModifierType gdk_modifier;

    Check_Type(path, T_STRING);
    gtk3_check_number(key);

    gdk_modifier = NUM2INT(gtk3_lookup_accelerator_modifier(modifier));
    gtk_path     = StringValuePtr(path);
    gtk_key      = NUM2INT(key);

    gtk_accel_map_add_entry(gtk_path, gtk_key, gdk_modifier);

    return Qnil;
}

/**
 * Looks up an accelerator mapping. If the mapping was found an instance of
 * {Gtk3::AccelKey} is returned, otherwise `nil` is returned.
 *
 * @since  2012-06-13
 * @param  [String] path The accelerator path to look up.
 * @return [Gtk3::AccelKey|NilClass]
 */
static VALUE gtk3_accel_map_lookup_entry(VALUE class, VALUE path)
{
    const gchar *gtk_path;
    GtkAccelKey gtk_key;

    Check_Type(path, T_STRING);

    gtk_path = StringValuePtr(path);

    if ( gtk_accel_map_lookup_entry(gtk_path, &gtk_key) == TRUE )
    {
        return rb_funcall(
            gtk3_cAccelKey,
            gtk3_id_new,
            3,
            INT2NUM(gtk_key.accel_key),
            INT2NUM(gtk_key.accel_mods),
            INT2NUM(gtk_key.accel_flags)
        );
    }
    else
    {
        return Qnil;
    }
}

/**
 * Initializes the module.
 *
 * @since 2012-06-12
 */
void Init_gtk3_accel_map()
{
    gtk3_mAccelMap = rb_define_module_under(gtk3_mGtk3, "AccelMap");

    rb_define_singleton_method(
        gtk3_mAccelMap,
        "add_entry",
        gtk3_accel_map_add_entry,
        3
    );

    rb_define_singleton_method(
        gtk3_mAccelMap,
        "lookup_entry",
        gtk3_accel_map_lookup_entry,
        1
    );
}
