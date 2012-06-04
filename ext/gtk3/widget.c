#include "widget.h"

/**
 * ID for the `:to_s` symbol.
 *
 * @since 2012-06-03
 */
static ID gtk3_id_to_s;

/**
 * ID for the `:to_sym` symbol.
 *
 * @since 2012-06-04
 */
static ID gtk3_id_to_sym;

/**
 * ID for the `:before` symbol.
 *
 * @since 2012-06-03
 */
static ID gtk3_id_before;

/**
 * ID for the `:after` symbol.
 *
 * @since 2012-06-03
 */
static ID gtk3_id_after;

/**
 * {Gtk3::Widget} is a base class for all the widgets in the GTK+ toolkit.
 *
 * @since 2012-05-30
 */
VALUE gtk3_cWidget;

/**
 * Binds the specified block to the given event name.
 *
 * @example
 *  window = Gtk3::Window.new
 *
 *  window.connect('destroy') { Gtk.main_quit }
 *
 * @example Executing a proc before the default handler.
 *  window = Gtk3::Window.new
 *
 *  window.connect(:destroy, :before) do
 *    puts 'This proc is executed before the default handler'
 *  end
 *
 * @since 2012-05-31
 * @param [String|Symbol] signal The name of the signal to bind to.
 * @param [String|Symbol] position A symbol used to specify if the proc should
 *  be executed before or after the default signal handler. Set to `:after` by
 *  default.
 * @raise [TypeError] Raised when the signal name wasn't a String or Symbol.
 * @raise [ArgumentError] Raised when an invalid position name was specified.
 */
static VALUE gtk3_widget_connect(int argc, VALUE *argv, VALUE self)
{
    char *signal_char;
    ID position_id;
    VALUE signal;
    VALUE position = Qnil;
    VALUE signal_to_s;
    VALUE proc;

    gboolean after = FALSE;
    GQuark detail;
    guint signal_id;
    gulong handler_id;
    GtkWidget *widget;
    RClosure *closure;

    if ( argc == 0 )
    {
        rb_raise(
            rb_eArgError,
            "wrong number of arguments(0 for 1..2)"
        );
    }
    else if ( argc > 2 )
    {
        rb_raise(
            rb_eArgError,
            "wrong number of arguments(%i for 1..2)",
            argc
        );
    }

    signal = argv[0];

    if ( TYPE(signal) != T_STRING && TYPE(signal) != T_SYMBOL )
    {
        rb_raise(
            rb_eTypeError,
            "expected a String or Symbol as the signal name"
        );
    }

    /* Get and validate the position if one is specified manually. */
    if ( argv[1] )
    {
        position = argv[1];
    }

    if ( !NIL_P(position) )
    {
        if ( TYPE(position) != T_STRING && TYPE(position) != T_SYMBOL )
        {
            rb_raise(
                rb_eTypeError,
                "expected a String or Symbol for the signal position"
            );
        }

        position    = rb_funcall(position, gtk3_id_to_sym, 0);
        position_id = SYM2ID(position);

        if ( position_id == gtk3_id_before )
        {
            after = FALSE;
        }
        else if ( position_id == gtk3_id_after )
        {
            after = TRUE;
        }
        else
        {
            rb_raise(
                rb_eArgError,
                "invalid signal position (should be :before or :after)"
            );
        }
    }


    Data_Get_Struct(self, GtkWidget, widget);

    signal_to_s = rb_funcall(signal, gtk3_id_to_s, 0);
    signal_char = StringValuePtr(signal_to_s);

    /* Validate the signal name. */
    if ( g_signal_lookup(signal_char, G_OBJECT_TYPE(widget)) == 0 )
    {
        rb_raise(rb_eArgError, "invalid signal name");
    }

    rb_need_block();

    proc    = rb_block_proc();
    closure = gtk3_closure_new(proc, self);

    g_signal_parse_name(
        signal_char,
        G_OBJECT_TYPE(widget),
        &signal_id,
        &detail,
        TRUE
    );

    handler_id = g_signal_connect_closure_by_id(
        widget,
        signal_id,
        detail,
        (GClosure *) closure,
        after
    );

    return INT2NUM(handler_id);
}

/**
 * Returns `true` if the widget is being destroyed. If this is not the case
 * `false` is returned instead.
 *
 * @example
 *  window = Gtk3::Window.new
 *
 *  p window.in_destruction? # => false
 *
 *  window.connect(:destroy) do |window|
 *    p window.in_destruction # => true
 *  end
 *
 * @since  2012-06-04
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_widget_in_destruction(VALUE self)
{
    GtkWidget *widget;
    gboolean destruction = FALSE;

    Data_Get_Struct(self, GtkWidget, widget);

    destruction = gtk_widget_in_destruction(widget);

    if ( destruction == TRUE )
    {
        return Qtrue;
    }
    else
    {
        return Qfalse;
    }
}

/**
 * Destroys a widget and frees the associated memory.
 *
 * @example
 *  window = Gtk3::Window.new
 *  window.destroy
 *
 * @since 2012-05-31
 */
static VALUE gtk3_widget_destroy(VALUE self)
{
    GtkWidget *widget;

    Data_Get_Struct(self, GtkWidget, widget);

    gtk_widget_destroy(widget);

    return Qnil;
}

/**
 * Shows the widget along with all child widgets.
 *
 * @example
 *  window = Gtk3::Window.new
 *  window.show_all
 *
 * @since 2012-05-31
 */
static VALUE gtk3_widget_show_all(VALUE self)
{
    GtkWidget *widget;

    Data_Get_Struct(self, GtkWidget, widget);

    gtk_widget_show_all(widget);

    return Qnil;
}

/**
 * Only shows the current widget, ignoring child widgets.
 *
 * @example
 *  window = Gtk3::Window.new
 *  window.show
 *
 * @since 2012-06-04
 */
static VALUE gtk3_widget_show(VALUE self)
{
    GtkWidget *widget;

    Data_Get_Struct(self, GtkWidget, widget);

    gtk_widget_show(widget);

    return Qnil;
}

/**
 * Dissociates a widget from its parent container.
 *
 * @since 2012-06-04
 */
static VALUE gtk3_widget_unparent(VALUE self)
{
    GtkWidget *widget;

    Data_Get_Struct(self, GtkWidget, widget);

    gtk_widget_unparent(widget);

    return Qnil;
}

/**
 * Returns `true` if the widget is visible, `false` otherwise.
 *
 * @since  2012-06-04
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_widget_get_visible(VALUE self)
{
    GtkWidget *widget;

    Data_Get_Struct(self, GtkWidget, widget);

    if ( gtk_widget_get_visible(widget) == TRUE )
    {
        return Qtrue;
    }
    else
    {
        return Qfalse;
    }
}

/**
 * Sets up the {Gtk3::Widget} class.
 *
 * @since 2012-05-30
 */
void Init_gtk3_widget()
{
    gtk3_cWidget = rb_define_class_under(gtk3_mGtk3, "Widget", rb_cObject);

    rb_define_method(gtk3_cWidget, "connect", gtk3_widget_connect, -1);
    rb_define_method(gtk3_cWidget, "destroy", gtk3_widget_destroy, 0);

    rb_define_method(
        gtk3_cWidget,
        "in_destruction?",
        gtk3_widget_in_destruction,
        0
    );

    rb_define_method(gtk3_cWidget, "show", gtk3_widget_show, 0);
    rb_define_method(gtk3_cWidget, "show_all", gtk3_widget_show_all, 0);
    rb_define_method(gtk3_cWidget, "unparent", gtk3_widget_unparent, 0);
    rb_define_method(gtk3_cWidget, "visible?", gtk3_widget_get_visible, 0);

    gtk3_id_to_s   = rb_intern("to_s");
    gtk3_id_before = rb_intern("before");
    gtk3_id_after  = rb_intern("after");
    gtk3_id_to_sym = rb_intern("to_sym");
}
