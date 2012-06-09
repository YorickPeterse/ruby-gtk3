#include "accel_group.h"

/**
 * {Gtk3::AccelGroup} is a class used for creating keyboard accelerators.
 *
 * @since 2012-06-07
 */
VALUE gtk3_cAccelGroup;

/**
 * ID for the `:lookup` symbol.
 *
 * @since 2012-06-09
 */
static ID gtk3_id_lookup;

/**
 * Creates a new instance of the class.
 *
 * @since 2012-06-08
 */
static VALUE gtk3_accel_group_new(VALUE class)
{
    VALUE struct_data;
    GtkAccelGroup *group;

    group       = gtk_accel_group_new();
    struct_data = Data_Wrap_Struct(
        class,
        NULL,
        NULL,
        group
    );

    rb_obj_call_init(struct_data, 0, NULL);

    return struct_data;
}

/**
 * Installs an accelerator in the group.
 *
 * @example Using constants when connecting a callback.
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect(113, Gtk3::ModifierType::CONTROL, Gtk3::AccelFlag::VISIBLE) do
 *    puts 'You pressed <Control>q`
 *  end
 *
 * @example Using symbols when connecting a callback.
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect(113, :control, :visible) do
 *    puts 'You pressed <Control>q'
 *  end
 *
 * @since 2012-06-08
 * @param [Fixnum|Bignum] key A number of the key to bind the accelerator to.
 * @param [Fixnum|Bignum|String|Symbol] modifier A number representing the
 *  modifier to use *or* a string or symbol representing the name. For example,
 *  using `:control` is the same as {Gtk3::ModifierType::CONTROL}.
 * @param [Fixnum|Bignum|String|Symbol] flag The accelerator flag to use.
 *  Similar to the `modifier` parameter you can specify either a number, string
 *  or symbol.
 */
static VALUE gtk3_accel_group_connect(
    VALUE self,
    VALUE key,
    VALUE modifier,
    VALUE flag
)
{
    VALUE modifier_type = TYPE(modifier);
    VALUE flag_type     = TYPE(flag);
    RClosure *closure;
    GtkAccelGroup *group;

    rb_need_block();

    /**
     * Lookup the modifier and flag if they're specified as a String or Symbol.
     */
    if ( modifier_type == T_STRING || modifier_type == T_SYMBOL )
    {
        modifier = rb_funcall(gtk3_mModifierType, gtk3_id_lookup, 1, modifier);
    }
    else
    {
        gtk3_check_number(modifier);
    }

    if ( flag_type == T_STRING || flag_type == T_SYMBOL )
    {
        flag = rb_funcall(gtk3_mAccelFlag, gtk3_id_lookup, 1, flag);
    }
    else
    {
        gtk3_check_number(flag);
    }

    Data_Get_Struct(self, GtkAccelGroup, group);

    closure = gtk3_closure_new(rb_block_proc(), self);

    gtk_accel_group_connect(group, key, modifier, flag, (GClosure *) closure);

    return Qnil;
}

/**
 * Connects an accelerator by the key path.
 *
 * @example
 *  Gtk3::AccelMap.add_entry('<Control>q', 113, :control)
 *
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect('<Control>q') do
 *    puts 'You pressed <Control>q'
 *  end
 *
 * @since 2012-06-09
 * @param [String] path The "path" used to determine the accelerator key and
 *  modifier.
 */
static VALUE gtk3_accel_group_connect_by_path(VALUE self, VALUE path)
{
    RClosure *closure;
    GtkAccelGroup *group;
    const gchar *path_gchar;

    rb_need_block();

    Check_Type(path, T_STRING);

    Data_Get_Struct(self, GtkAccelGroup, group);

    path_gchar = g_intern_static_string(StringValuePtr(path));
    closure    = gtk3_closure_new(rb_block_proc(), self);

    gtk_accel_group_connect_by_path(group, path_gchar, (GClosure *) closure);

    return Qnil;
}

/**
 * Initializes the class, required variables, etc.
 *
 * @since 2012-06-07
 */
void Init_gtk3_accel_group()
{
    gtk3_cAccelGroup = rb_define_class_under(
        gtk3_mGtk3,
        "AccelGroup",
        rb_cObject
    );

    rb_define_singleton_method(
        gtk3_cAccelGroup,
        "new",
        gtk3_accel_group_new,
        0
    );

    rb_define_method(
        gtk3_cAccelGroup,
        "connect",
        gtk3_accel_group_connect,
        3
    );

    rb_define_method(
        gtk3_cAccelGroup,
        "connect_by_path",
        gtk3_accel_group_connect_by_path,
        1
    );

    gtk3_id_lookup = rb_intern("lookup");
}
