#include "accel_map.h"

/**
 * Document-module: Gtk3::AccelMap
 *
 * Accelerator maps are used for defining accelerators that can be changed
 * during runtime.
 *
 * @since 2012-06-12
 */
VALUE gtk3_mAccelMap;

/* Helper methods */

/**
 * Function that is called for each accelerator map entry when using
 * {Gtk3::AccelMap.foreach}.
 *
 * @since 2012-06-16
 * @param [gpointer] data The proc to call.
 * @param [const gchar *] path The accelerator path of the current entry.
 * @param [guint] key The accelerator key of the current entry.
 * @param [GdkModifierType] modifier The modifier type of the current entry.
 * @param [gboolean] changed When set to TRUE the entry has been changed uring
 *  runtime.
 */
void gtk3_accel_map_foreach_callback(
    gpointer data,
    const gchar *path,
    guint key,
    GdkModifierType modifier,
    gboolean changed
)
{
    VALUE proc       = (VALUE) data;
    VALUE rb_path    = rb_str_new2(path);
    VALUE rb_key     = INT2NUM(key);
    VALUE rb_mod     = INT2NUM(modifier);
    VALUE rb_changed = gtk3_gboolean_to_rboolean(changed);

    rb_funcall(proc, gtk3_id_call, 4, rb_path, rb_key, rb_mod, rb_changed);
}

/* Class methods */

/**
 * Registers a new accelerator.
 *
 * @example
 *  Gtk3::AccelMap.add_entry('<Ruby>/Test', 113, :control)
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
 * @example
 *  Gtk3::AccelMap.add_entry('<Ruby>/Test', 113, :control)
 *
 *  accelerator = Gtk3::AccelMap.lookup_entry('<Ruby>/Test')
 *
 *  puts accelerator.key      # => 113
 *  puts accelerator.modifier # => Gtk3::ModifierType::CONTROL
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
 * Changes an accelerator entry.
 *
 * @example
 *  Gtk3::AccelMap.add_entry('<Ruby>/Test', 113, :control)
 *  Gtk3::AccelMap.change_entry('<Ruby>/Test', 113, :shift) # => true
 *
 * @since 2012-06-14
 * @param [String] path The accelerator path to change.
 * @param [Fixnum|Bignum] key The new key for the accelerator.
 * @param [Fixnum|Bignum|String|Symbol] modifier The new accelerator modifier.
 * @param [TrueClass|FalseClass] replace When set to `true` other accelerators
 *  may be deleted in order to resolve conflicts.
 */
static VALUE gtk3_accel_map_change_entry(int argc, VALUE *argv, VALUE self)
{
    const gchar *gtk_path;
    guint gtk_key;
    gboolean gtk_replace;
    GdkModifierType gdk_modifier;

    if ( argc == 0 )
    {
        rb_raise(rb_eArgError, "wrong number of arguments(0 for 3..4)");
    }
    else if ( argc > 4 )
    {
        rb_raise(rb_eArgError, "wrong number of arguments(%i for 3..4", argc);
    }

    Check_Type(argv[0], T_STRING);
    gtk3_check_number(argv[1]);

    gdk_modifier = NUM2INT(gtk3_lookup_accelerator_modifier(argv[2]));
    gtk_path     = StringValuePtr(argv[0]);
    gtk_key      = NUM2INT(argv[1]);
    gtk_replace  = FALSE;

    if ( argc == 4 && RTEST(argv[3]) )
    {
        gtk_replace = TRUE;
    }

    return gtk3_gboolean_to_rboolean(
        gtk_accel_map_change_entry(
            gtk_path,
            gtk_key,
            gdk_modifier,
            gtk_replace
        )
    );
}

/**
 * Saves the current accelerator speifications in a file. Once saved these
 * specifications can be loaded using {Gtk3::AccelMap.load}.
 *
 * @since 2012-06-16
 * @param [String] path The file path to use for saving the file.
 */
static VALUE gtk3_accel_map_save(VALUE self, VALUE path)
{
    Check_Type(path, T_STRING);

    gtk_accel_map_save(StringValuePtr(path));

    return Qnil;
}

/**
 * Loads a set of accelerator specifications that were saved using
 * {Gtk3::AccelMap.save}.
 *
 * @since 2012-06-16
 * @param [String] path The file path of the file to load.
 */
static VALUE gtk3_accel_map_load(VALUE self, VALUE path)
{
    Check_Type(path, T_STRING);

    gtk_accel_map_load(StringValuePtr(path));

    return Qnil;
}

/**
 * Loops through the entries in the accelerator map and executes the specified
 * block for each unfiltered entry. See {Gtk3::AccelMap.add_filter} for adding
 * filters.
 *
 * @since 2012-06-16
 */
static VALUE gtk3_accel_map_foreach(VALUE self)
{
    gpointer proc;

    rb_need_block();

    proc = (gpointer) rb_block_proc();

    gtk_accel_map_foreach(proc, gtk3_accel_map_foreach_callback);

    return Qnil;
}

/**
 * Loops through the entries in the accelerator map and executes the specified
 * block for each entry regardless of the added filters.
 *
 * @since 2012-06-16
 */
static VALUE gtk3_accel_map_foreach_unfiltered(VALUE self)
{
    gpointer proc;

    rb_need_block();

    proc = (gpointer) rb_block_proc();

    gtk_accel_map_foreach_unfiltered(proc, gtk3_accel_map_foreach_callback);

    return Qnil;
}

/**
 * Adds a filter to the global list of accelerator path filters.
 *
 * @since 2012-06-16
 * @param [String] filter The filter to add.
 */
static VALUE gtk3_accel_map_add_filter(VALUE self, VALUE filter)
{
    Check_Type(filter, T_STRING);

    gtk_accel_map_add_filter(StringValuePtr(filter));

    return Qnil;
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

    rb_define_singleton_method(
        gtk3_mAccelMap,
        "change_entry",
        gtk3_accel_map_change_entry,
        -1
    );

    rb_define_singleton_method(gtk3_mAccelMap, "save", gtk3_accel_map_save, 1);
    rb_define_singleton_method(gtk3_mAccelMap, "load", gtk3_accel_map_load, 1);

    rb_define_singleton_method(
        gtk3_mAccelMap,
        "foreach",
        gtk3_accel_map_foreach,
        0
    );

    rb_define_singleton_method(
        gtk3_mAccelMap,
        "foreach_unfiltered",
        gtk3_accel_map_foreach_unfiltered,
        0
    );

    rb_define_singleton_method(
        gtk3_mAccelMap,
        "add_filter",
        gtk3_accel_map_add_filter,
        1
    );
}
