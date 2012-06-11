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
 * ID for the `:new` symbol.
 *
 * @since 2012-06-10
 */
static ID gtk3_id_new;

/* Helper methods, not exposed to Ruby code. */

/**
 * Looks up an accelerator modifier and returns the value. If no modifier was
 * found `ArgumentError` is raised instead.
 *
 * @since  2012-06-10
 * @param  [VALUE] modifier The modifier to look up.
 * @raise  [ArgumentError] Raised when the specified modifier is invalid.
 * @return [VALUE]
 */
static VALUE gtk3_accel_group_lookup_modifier(VALUE modifier)
{
    VALUE modifier_type = TYPE(modifier);

    if ( modifier_type == T_STRING || modifier_type == T_SYMBOL )
    {
        modifier = rb_funcall(gtk3_mModifierType, gtk3_id_lookup, 1, modifier);
    }
    else
    {
        gtk3_check_number(modifier);
    }

    if ( NIL_P(modifier) )
    {
        rb_raise(rb_eArgError, "invalid accelerator modifier");
    }

    return modifier;
}

/**
 * Looks up an accelerator flag and returns the value. If no flag was
 * found `ArgumentError` is raised instead.
 *
 * @since  2012-06-10
 * @param  [VALUE] flag The modifier to look up.
 * @raise  [ArgumentError] Raised when the specified flag is invalid.
 * @return [VALUE]
 */
static VALUE gtk3_accel_group_lookup_flag(VALUE flag)
{
    VALUE flag_type = TYPE(flag);

    if ( flag_type == T_STRING || flag_type == T_SYMBOL )
    {
        flag = rb_funcall(gtk3_mAccelFlag, gtk3_id_lookup, 1, flag);
    }
    else
    {
        gtk3_check_number(flag);
    }

    if ( NIL_P(flag) )
    {
        rb_raise(rb_eArgError, "invalid accelerator flag");
    }

    return flag;
}

/* Class methods */

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
 * Parses a key code and modifier and returns the accelerator name (also known
 * as "path").
 *
 * @example
 *  Gtk3::AccelGroup.accelerator_name(113, :shift) => "<Shift>q"
 *
 * @since  2012-06-10
 * @param  [Fixnum|Bignum] key The accelerator key.
 * @param  [Fixnum|Bignum|String|Symbol] modifier The accelerator modifier.
 * @return [String]
 */
static VALUE gtk3_accel_group_accelerator_name(
    VALUE class,
    VALUE key,
    VALUE modifier
)
{
    modifier = gtk3_accel_group_lookup_modifier(modifier);

    return rb_str_new2(gtk_accelerator_name(NUM2INT(key), NUM2INT(modifier)));
}

/**
 * Returns a string containing a user friendly representation of an accelerator
 * key and modifier.
 *
 * @since  2012-06-10
 * @param  [Fixnum|Bignum] key The accelerator key.
 * @param  [Fixnum|Bignum|String|Symbol] modifier The accelerator modifier.
 * @return [String]
 */
static VALUE gtk3_accel_group_accelerator_label(
    VALUE class,
    VALUE key,
    VALUE modifier
)
{
    modifier = gtk3_accel_group_lookup_modifier(modifier);

    return rb_str_new2(
        gtk_accelerator_get_label(NUM2INT(key), NUM2INT(modifier))
    );
}

/**
 * Sets the default modifier mask to use.
 *
 * @since 2012-06-11
 * @param [Fixnum|Bignum] mod The accelerator modifier. Unlike other
 *  accelerator methods this method does not perform a lookup based on a symbol,
 *  thus a number should always be passed.
 */
static VALUE gtk3_accel_group_set_default_modifier(VALUE class, VALUE mod)
{
    gtk3_check_number(mod);

    gtk_accelerator_set_default_mod_mask(NUM2INT(mod));

    return Qnil;
}

/**
 * Returns the default modifier mask.
 *
 * @since  2012-06-11
 * @return [Fixnum|Bignum]
 */
static VALUE gtk3_accel_group_get_default_modifier(VALUE class)
{
    return INT2NUM(gtk_accelerator_get_default_mod_mask());
}

/* Instance methods */

/**
 * Locks the accelerator group.
 *
 * @since 2012-06-11
 */
static VALUE gtk3_accel_group_lock(VALUE self)
{
    GtkAccelGroup *group;

    Data_Get_Struct(self, GtkAccelGroup, group);

    gtk_accel_group_lock(group);

    return Qnil;
}

/**
 * Unlocks the accelerator group.
 *
 * @since 2012-06-11
 */
static VALUE gtk3_accel_group_unlock(VALUE self)
{
    GtkAccelGroup *group;

    Data_Get_Struct(self, GtkAccelGroup, group);

    gtk_accel_group_unlock(group);

    return Qnil;
}

/**
 * Returns a boolean that indicates if the accelerator group is locked or not.
 *
 * @since  2012-06-11
 * @return [TrueClass|FalseClass]
 */
static VALUE gtk3_accel_group_get_locked(VALUE self)
{
    GtkAccelGroup *group;

    Data_Get_Struct(self, GtkAccelGroup, group);

    return gtk3_gboolean_to_rboolean(gtk_accel_group_get_is_locked(group));
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
    RClosure *closure;
    GtkAccelGroup *group;

    int key_int;
    int modifier_int;
    int flag_int;

    rb_need_block();

    gtk3_check_number(key);

    modifier     = gtk3_accel_group_lookup_modifier(modifier);
    flag         = gtk3_accel_group_lookup_flag(flag);
    key_int      = NUM2INT(key);
    modifier_int = NUM2INT(modifier);
    flag_int     = NUM2INT(flag);

    if ( !gtk_accelerator_valid(key_int, modifier_int) )
    {
        rb_raise(rb_eArgError, "invalid key value and/or modifier");
    }

    Data_Get_Struct(self, GtkAccelGroup, group);

    closure = gtk3_closure_new(rb_block_proc(), self);

    gtk_accel_group_connect(
        group,
        key_int,
        modifier_int,
        flag_int,
        (GClosure *) closure
    );

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
    guint key;
    GdkModifierType modifier;

    rb_need_block();

    Check_Type(path, T_STRING);

    Data_Get_Struct(self, GtkAccelGroup, group);

    path_gchar = g_intern_static_string(StringValuePtr(path));

    /* Check if the specified path is valid. */
    gtk_accelerator_parse(path_gchar, &key, &modifier);

    if ( !key || !modifier )
    {
        rb_raise(rb_eArgError, "invalid accelerator path");
    }

    closure = gtk3_closure_new(rb_block_proc(), self);

    gtk_accel_group_connect_by_path(group, path_gchar, (GClosure *) closure);

    return Qnil;
}

/**
 * Disconnects an accelerator that was connected to the specified key and
 * modifier.
 *
 * @example
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect(113, :control, :visible)
 *  group.disconnect_key(113, :control) # => true
 *
 * @since 2012-06-09
 * @param [Fixnum|Bignum] key The key number to use for disconnecting a
 *  callback.
 * @param [String|Symbol|Fixnum|Bignum] mod The key modifier.
 */
static VALUE gtk3_accel_group_disconnect_key(VALUE self, VALUE key, VALUE mod)
{
    GtkAccelGroup *group;

    gtk3_check_number(key);

    mod = gtk3_accel_group_lookup_modifier(mod);

    Data_Get_Struct(self, GtkAccelGroup, group);

    return gtk3_gboolean_to_rboolean(
        gtk_accel_group_disconnect_key(
            group,
            INT2NUM(key),
            INT2NUM(mod)
        )
    );
}

/**
 * Queries an accelerator group for the given key and modifier. The return
 * value is an array of instances of {Gtk3::AccelGroupEntry} objects.
 *
 * @example
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect(113, :control, :visible) {}
 *  group.query(113, :control) => [#<Gtk3::AccelGroupEntry ...>]
 *
 * @since 2012-06-10
 * @param [Fixnum|Bignum] key The key number to query.
 * @param [Fixnum|Bignum|String|Symbol] mod The modifier to query.
 */
static VALUE gtk3_accel_group_query(VALUE self, VALUE key, VALUE mod)
{
    VALUE rb_entries = rb_ary_new();

    GtkAccelGroup *group;
    GtkAccelGroupEntry *entries;
    guint n_entries;

    /*
    Variables used when looping over the return value of
    gtk_accel_group_query().
    */
    unsigned int entry_index;
    VALUE entry;
    GtkAccelKey entry_key;
    RClosure *entry_closure;

    gtk3_check_number(key);

    mod = gtk3_accel_group_lookup_modifier(mod);

    Data_Get_Struct(self, GtkAccelGroup, group);

    entries = gtk_accel_group_query(
        group,
        NUM2INT(key),
        NUM2INT(mod),
        &n_entries
    );

    /*
    Loop through each entry and convert it to a Ruby instance of
    {Gtk3::AccelGroupEntry}.
    */
    for ( entry_index = 0; entry_index < n_entries; entry_index++ )
    {
        entry_key     = entries[entry_index].key;
        entry_closure = (RClosure *) entries[entry_index].closure;

        entry = rb_funcall(
            gtk3_cAccelGroupEntry,
            gtk3_id_new,
            4,
            INT2NUM(entry_key.accel_key),
            INT2NUM(entry_key.accel_mods),
            INT2NUM(entry_key.accel_flags),
            entry_closure->proc
        );

        rb_ary_push(rb_entries, entry);
    }

    return rb_entries;
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

    rb_define_singleton_method(
        gtk3_cAccelGroup,
        "accelerator_name",
        gtk3_accel_group_accelerator_name,
        2
    );

    rb_define_singleton_method(
        gtk3_cAccelGroup,
        "accelerator_label",
        gtk3_accel_group_accelerator_label,
        2
    );

    rb_define_singleton_method(
        gtk3_cAccelGroup,
        "default_modifier=",
        gtk3_accel_group_set_default_modifier,
        1
    );

    rb_define_singleton_method(
        gtk3_cAccelGroup,
        "default_modifier",
        gtk3_accel_group_get_default_modifier,
        0
    );

    rb_define_method(gtk3_cAccelGroup, "lock", gtk3_accel_group_lock, 0);
    rb_define_method(gtk3_cAccelGroup, "unlock", gtk3_accel_group_unlock, 0);

    rb_define_method(
        gtk3_cAccelGroup,
        "locked?",
        gtk3_accel_group_get_locked,
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

    rb_define_method(
        gtk3_cAccelGroup,
        "disconnect_key",
        gtk3_accel_group_disconnect_key,
        2
    );

    rb_define_method(gtk3_cAccelGroup, "query", gtk3_accel_group_query, 2);

    gtk3_id_lookup = rb_intern("lookup");
    gtk3_id_new    = rb_intern("new");
}
