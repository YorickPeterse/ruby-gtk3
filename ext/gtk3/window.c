#include "window.h"

/**
 * ID for the symbol `:toplevel`.
 *
 * @since 2012-06-03
 */
ID gtk3_id_toplevel;

/**
 * ID for the symbol `:popup`.
 *
 * @since 2012-06-03
 */
ID gtk3_id_popup;

/**
 * Document-class: Gtk3::Window
 *
 * {Gtk3::Window} is a toplevel window class which can contain other widgets
 * such as buttons and panes.
 *
 * @since 2012-05-29
 */
VALUE gtk3_cWindow;

/**
 * Creates a new instance of the class and stores the window type.
 *
 * @example
 *  toplevel = Gtk3::Window.new
 *  popup    = Gtk3::Window.new(:popup)
 *
 * @since 2012-05-29
 * @param [Symbol] type The window type. The type can either be set to
 *  `:toplevel` or `:popup`, it's set to the former by default
 */
static VALUE gtk3_window_new(int argc, VALUE *argv, VALUE class)
{
    VALUE struct_data;
    VALUE type;
    ID type_id;
    GtkWindowType window_type;
    GtkWidget *window;

    /* No more than 1 argument can be specified. */
    if ( argc > 1 )
    {
        rb_raise(
            rb_eArgError,
            "wrong number of arguments (%i for 0..1)",
            argc
        );
    }

    /* If no window type is specified the type should default to :toplevel. */
    if ( NIL_P(argv[0]) )
    {
        type = ID2SYM(gtk3_id_toplevel);
    }
    else
    {
        Check_Type(argv[0], T_SYMBOL);

        type = argv[0];
    }

    type_id = rb_to_id(type);

    /* Determine what window type to use. */
    if ( type_id == gtk3_id_toplevel )
    {
        window_type = GTK_WINDOW_TOPLEVEL;
    }
    else if ( type_id == gtk3_id_popup )
    {
        window_type = GTK_WINDOW_POPUP;
    }
    else
    {
        rb_raise(
            rb_eArgError,
            "Unrecognized window type (should be :toplevel or :popup)"
        );
    }

    window      = gtk_window_new(window_type);
    struct_data = Data_Wrap_Struct(
        class,
        NULL,
        NULL,
        window
    );

    rb_obj_call_init(struct_data, 0, NULL);

    return struct_data;
}

/**
 * Returns the title of a window.
 *
 * @example
 *  window       = Gtk3::Window.new
 *  window.title = 'Test'
 *
 *  window.title # => "Test"
 *
 * @since  2012-06-30
 * @return [String]
 */
static VALUE gtk3_window_get_title(VALUE self)
{
    const gchar *title;
    GtkWindow *window;

    Data_Get_Struct(self, GtkWindow, window);

    title = gtk_window_get_title(window);

    if ( title != NULL )
    {
        return rb_str_new2(title);
    }
    else
    {
        return Qnil;
    }
}

/**
 * Sets the title of a window.
 *
 * @since 2012-06-30
 * @param [String] title The title of the window.
 */
static VALUE gtk3_window_set_title(VALUE self, VALUE title)
{
    GtkWindow *window;

    Check_Type(title, T_STRING);

    Data_Get_Struct(self, GtkWindow, window);

    gtk_window_set_title(window, StringValuePtr(title));

    return Qnil;
}

/**
 * Sets whether the user can resize the window.
 *
 * @since 2012-06-30
 * @param [TrueClass|FalseClass] resize Boolean that indicates whether the
 *  window can be resized.
 */
static VALUE gtk3_window_set_resizable(VALUE self, VALUE resize)
{
    GtkWindow *window;

    if ( resize != Qtrue && resize != Qfalse )
    {
        rb_raise(
            rb_eTypeError,
            "expected a TrueClass or FalseClass but got %s instead",
            gtk3_get_rbclass(resize)
        );
    }

    Data_Get_Struct(self, GtkWindow, window);

    gtk_window_set_resizable(window, gtk3_rboolean_to_gboolean(resize));

    return Qnil;
}

/**
 * Returns whether the window can be resized by the user.
 *
 * @since  2012-06-30
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_window_get_resizable(VALUE self)
{
    GtkWindow *window;

    Data_Get_Struct(self, GtkWindow, window);

    return gtk3_gboolean_to_rboolean(gtk_window_get_resizable(window));
}

/**
 * Sets up the {Gtk3::Window} class.
 *
 * @since 2012-05-29
 */
void Init_gtk3_window()
{
    gtk3_cWindow = rb_define_class_under(gtk3_mGtk3, "Window", gtk3_cWidget);

    rb_define_singleton_method(gtk3_cWindow, "new", gtk3_window_new, -1);

    rb_define_method(gtk3_cWindow, "title", gtk3_window_get_title, 0);
    rb_define_method(gtk3_cWindow, "title=", gtk3_window_set_title, 1);

    rb_define_method(gtk3_cWindow, "resizable=", gtk3_window_set_resizable, 1);
    rb_define_method(gtk3_cWindow, "resizable?", gtk3_window_get_resizable, 0);

    gtk3_id_toplevel = rb_intern("toplevel");
    gtk3_id_popup    = rb_intern("popup");
}
