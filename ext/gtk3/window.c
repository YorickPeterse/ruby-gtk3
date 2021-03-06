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
 * ID for the symbol `:length`
 *
 * @since 2012-07-01
 */
ID gtk3_id_length;

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

    gtk3_check_boolean(resize);

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
 * Adds a new accelerator group to the window.
 *
 * @example
 *  window = Gtk3::Window.new
 *  group  = Gtk3::AccelGroup.new
 *
 *  window.add_accel_group(group)
 *
 * @since 2012-06-30
 * @param [Gtk3::AccelGroup] group The accelerator group to add.
 */
static VALUE gtk3_window_add_accel_group(VALUE self, VALUE group)
{
    GtkWindow *window;
    GtkAccelGroup *accel_group;
    char *group_type = gtk3_get_rbclass(group);

    if ( strcmp(group_type, "Gtk3::AccelGroup") )
    {
        rb_raise(
            rb_eTypeError,
            "wrong argument type %s (expected Gtk3::AccelGroup)",
            group_type
        );
    }

    Data_Get_Struct(self, GtkWindow, window);
    Data_Get_Struct(group, GtkAccelGroup, accel_group);

    gtk_window_add_accel_group(window, accel_group);

    return Qnil;
}

/**
 * Removes an accelerator group from the window.
 *
 * @example
 *  window = Gtk3::Window.new
 *  group  = Gtk3::AccelGroup.new
 *
 *  window.remove_accel_group(group)
 *
 * @since 2012-06-30
 * @param [Gtk3::AccelGroup] group The group to remove.
 */
static VALUE gtk3_window_remove_accel_group(VALUE self, VALUE group)
{
    GtkWindow *window;
    GtkAccelGroup *accel_group;
    char *group_type = gtk3_get_rbclass(group);

    if ( strcmp(group_type, "Gtk3::AccelGroup") )
    {
        rb_raise(
            rb_eTypeError,
            "wrong argument type %s (expected Gtk3::AccelGroup)",
            group_type
        );
    }

    Data_Get_Struct(self, GtkWindow, window);
    Data_Get_Struct(group, GtkAccelGroup, accel_group);

    gtk_window_remove_accel_group(window, accel_group);

    return Qnil;
}

/**
 * Activates the currently focused widget in the window. If a widget has been
 * activated `true` is returned, `false` otherwise.
 *
 * @since  2012-07-01
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_window_activate_focus(VALUE self)
{
    GtkWindow *window;

    Data_Get_Struct(self, GtkWindow, window);

    return gtk3_gboolean_to_rboolean(gtk_window_activate_focus(window));
}

/**
 * Activates the default widget for the current window, unless the currently
 * focused widget has been configured to receive the default action.
 *
 * If a widget has been activated `true` is returned, `false` otherwise.
 *
 * @since  2012-07-01
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_window_activate_default(VALUE self)
{
    GtkWindow *window;

    Data_Get_Struct(self, GtkWindow, window);

    return gtk3_gboolean_to_rboolean(gtk_window_activate_default(window));
}

/**
 * Sets the window to be a modal or non modal window. When a window is set to
 * be a modal winodw the user can not interact with other windows in the
 * application.
 *
 * @since 2012-07-01
 * @param [TrueClass|FalseClass] modal Boolean that indicates the modal state
 *  of the window.
 */
static VALUE gtk3_window_set_modal(VALUE self, VALUE modal)
{
    GtkWindow *window;

    gtk3_check_boolean(modal);

    Data_Get_Struct(self, GtkWindow, window);

    gtk_window_set_modal(window, gtk3_rboolean_to_gboolean(modal));

    return Qnil;
}

/**
 * Gets the modal state of the window.
 *
 * @since  2012-07-01
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_window_get_modal(VALUE self)
{
    GtkWindow *window;

    Data_Get_Struct(self, GtkWindow, window);

    return gtk3_gboolean_to_rboolean(gtk_window_get_modal(window));
}

/**
 * Sets the default size of the window. When setting the default size the user
 * is still able to resize the window.
 *
 * In order to set the size you must supply an array with two values. The first
 * value is used for the width, the second value for the height.
 *
 * @example
 *  window = Gtk3::Window.new
 *
 *  window.default_size = [100, 200] # sets the size to 100x200 pixels.
 *
 * @since 2012-07-01
 * @param [Array] dimensions Array containing the window dimensions.
 */
static VALUE gtk3_window_set_default_size(VALUE self, VALUE dimensions)
{
    GtkWindow *window;
    int array_length;
    VALUE width;
    VALUE height;

    Check_Type(dimensions, T_ARRAY);

    array_length = NUM2INT(rb_funcall(dimensions, gtk3_id_length, 0));

    if ( array_length != 2 )
    {
        rb_raise(
            rb_eArgError,
            "expected an Array with 2 elements but got %i elements instead",
            array_length
        );
    }

    width  = rb_ary_entry(dimensions, 0);
    height = rb_ary_entry(dimensions, 1);

    gtk3_check_number(width);
    gtk3_check_number(height);

    Data_Get_Struct(self, GtkWindow, window);

    gtk_window_set_default_size(window, NUM2INT(width), NUM2INT(height));

    return Qnil;
}

/**
 * Returns an array containing the default window dimensions. The first value
 * is the width, the second value the height.
 *
 * @example
 *  window = Gtk3::Window.new
 *
 *  window.default_size = [100, 200]
 *
 *  window.default_size # => [100, 200]
 *
 * @since  2012-07-01
 * @return [Array]
 */
static VALUE gtk3_window_get_default_size(VALUE self)
{
    GtkWindow *window;
    gint width;
    gint height;
    VALUE dimensions;

    Data_Get_Struct(self, GtkWindow, window);

    gtk_window_get_default_size(window, &width, &height);

    dimensions = rb_ary_new3(2, INT2NUM(width), INT2NUM(height));

    return dimensions;
}

/**
 * Sets whether the window will be destroyed when its transient parent is
 * destroyed.
 *
 * @since 2012-07-08
 * @param [TrueClass|FalseClass] destroy Whether or not the window should be
 *  destroyed.
 */
static VALUE gtk3_window_set_destroy_with_parent(VALUE self, VALUE destroy)
{
    GtkWindow *window;

    gtk3_check_boolean(destroy);

    Data_Get_Struct(self, GtkWindow, window);

    gtk_window_set_destroy_with_parent(
        window,
        gtk3_rboolean_to_gboolean(destroy)
    );

    return Qnil;
}

/**
 * Returns whether the window will be destroyed when its transient parent is
 * destroyed.
 *
 * @since  2012-07-08
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_window_get_destroy_with_parent(VALUE self)
{
    GtkWindow *window;

    Data_Get_Struct(self, GtkWindow, window);

    return gtk3_gboolean_to_rboolean(
        gtk_window_get_destroy_with_parent(window)
    );
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

    rb_define_method(
        gtk3_cWindow,
        "add_accel_group",
        gtk3_window_add_accel_group,
        1
    );

    rb_define_method(
        gtk3_cWindow,
        "remove_accel_group",
        gtk3_window_remove_accel_group,
        1
    );

    rb_define_method(
        gtk3_cWindow,
        "activate_focus",
        gtk3_window_activate_focus,
        0
    );

    rb_define_method(
        gtk3_cWindow,
        "activate_default",
        gtk3_window_activate_default,
        0
    );

    rb_define_method(
        gtk3_cWindow,
        "modal=",
        gtk3_window_set_modal,
        1
    );

    rb_define_method(
        gtk3_cWindow,
        "modal?",
        gtk3_window_get_modal,
        0
    );

    rb_define_method(
        gtk3_cWindow,
        "default_size=",
        gtk3_window_set_default_size,
        1
    );

    rb_define_method(
        gtk3_cWindow,
        "default_size",
        gtk3_window_get_default_size,
        0
    );

    rb_define_method(
        gtk3_cWindow,
        "destroy_with_parent=",
        gtk3_window_set_destroy_with_parent,
        1
    );

    rb_define_method(
        gtk3_cWindow,
        "destroy_with_parent?",
        gtk3_window_get_destroy_with_parent,
        0
    );

    gtk3_id_toplevel = rb_intern("toplevel");
    gtk3_id_popup    = rb_intern("popup");
    gtk3_id_length   = rb_intern("length");
}
