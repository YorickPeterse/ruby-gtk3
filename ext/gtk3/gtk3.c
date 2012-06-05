#include "gtk3.h"

/**
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

    Init_gtk3_gvalue();
    Init_gtk3_closure();
    Init_gtk3_widget();
    Init_gtk3_window();
}
