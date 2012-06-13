#include "gtk3.h"

/**
 * ID for the `:new` symbol.
 *
 * @since 2012-06-14
 */
ID gtk3_id_new;

/**
 * ID for the `:call` symbol.
 *
 * @since 2012-06-14
 */
ID gtk3_id_call;

/**
 * ID for the `:class` symbol.
 *
 * @since 2012-06-14
 */
ID gtk3_id_class;

/**
 * ID for the `:to_s` symbol.
 *
 * @since 2012-06-14
 */
ID gtk3_id_to_s;

/**
 * ID for the `:upcase` symbol.
 *
 * @since 2012-06-14
 */
ID gtk3_id_upcase;

/**
 * ID for the `:to_sym` symbol.
 *
 * @since 2012-06-14
 */
ID gtk3_id_to_sym;

/**
 * Document-module: Gtk3
 *
 * Primary Gtk3 module.
 *
 * @since 2012-05-29
 */
VALUE gtk3_mGtk3;

/**
 * Starts the main GTK event loop.
 *
 * @example
 *  Gtk3.main
 *
 * @since 2012-05-30
 */
static VALUE gtk3_main(VALUE self)
{
    gtk_main();

    return Qnil;
}

/**
 * Stops the main event loop.
 *
 * @example
 *  Gtk3.main_quit
 *
 * @since 2012-05-30
 */
static VALUE gtk3_main_quit(VALUE self)
{
    gtk_main_quit();

    return Qnil;
}

/**
 * Runs a single iteration of the GTK event loop.
 *
 * @since 2012-06-05
 */
static VALUE gtk3_main_iteration(VALUE self)
{
    gtk_main_iteration();

    return Qnil;
}

/**
 * Returns `true` if there are pending events, `false` otherwise.
 *
 * @since  2012-06-05
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_events_pending(VALUE self)
{
    return gtk3_gboolean_to_rboolean(gtk_events_pending());
}

/**
 * Sets up all the provides classes and modules.
 *
 * @since 2012-05-29
 */
void Init_gtk3()
{
    gtk_init(NULL, NULL);

    gtk3_mGtk3 = rb_define_module("Gtk3");

    rb_define_singleton_method(gtk3_mGtk3, "main", gtk3_main, 0);
    rb_define_singleton_method(gtk3_mGtk3, "main_quit", gtk3_main_quit, 0);

    rb_define_singleton_method(
        gtk3_mGtk3,
        "main_iteration",
        gtk3_main_iteration,
        0
    );

    rb_define_singleton_method(
        gtk3_mGtk3,
        "events_pending?",
        gtk3_events_pending,
        0
    );

    /* IDs for various symbols that are re-used throughout the codebase. */
    gtk3_id_new    = rb_intern("new");
    gtk3_id_call   = rb_intern("call");
    gtk3_id_class  = rb_intern("class");
    gtk3_id_to_s   = rb_intern("to_s");
    gtk3_id_upcase = rb_intern("upcase");
    gtk3_id_to_sym = rb_intern("to_sym");


    /* Set up all the other required classes and modules. */
    Init_gtk3_lookup_constant();
    Init_gtk3_accel_lookup();
    Init_gtk3_accel_flag();
    Init_gtk3_accel_key();
    Init_gtk3_accel_map();
    Init_gtk3_accel_group();
    Init_gtk3_accel_group_entry();
    Init_gtk3_modifier_type();
    Init_gtk3_widget();
    Init_gtk3_window();
}
