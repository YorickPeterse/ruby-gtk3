#include "accel_group.h"

/**
 * Document-class: Gtk3::AccelGroup
 *
 * {Gtk3::AccelGroup} is a class used for creating keyboard accelerators. These
 * accelerators are typically attached to a toplevel widget such as
 * {Gtk3::Window}.
 *
 * Note that accelerators are different from mnemonics. Accelerators are
 * shortcuts for activating menu items while mnemonics are shortcuts for GUI
 * elements such as buttons or text fields.
 *
 * @since 2012-06-07
 */
VALUE gtk3_cAccelGroup;

/**
 * Creates a new instance of the class.
 *
 * @example
 *  group = Gtk3::AccelGroup.new
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
 * as "path"). If no accelerator name is found an empty string is returned
 * instead.
 *
 * @example
 *  Gtk3::AccelGroup.accelerator_name(:q, :shift) => "<Shift>q"
 *
 * @since  2012-06-10
 * @param  [Fixnum|Bignum|String|Symbol] key The accelerator key.
 * @param  [Fixnum|Bignum|String|Symbol] modifier The accelerator modifier.
 * @return [String]
 */
static VALUE gtk3_accel_group_accelerator_name(
    VALUE class,
    VALUE key,
    VALUE modifier
)
{
    key      = gtk3_lookup_accelerator_key(key);
    modifier = gtk3_lookup_accelerator_modifier(modifier);

    return rb_str_new2(gtk_accelerator_name(NUM2INT(key), NUM2INT(modifier)));
}

/**
 * Returns a string containing a user friendly representation of an accelerator
 * key and modifier. If no label is found an empty string is returned.
 *
 * @since  2012-06-10
 * @param  [Fixnum|Bignum|String|Symbol] key The accelerator key.
 * @param  [Fixnum|Bignum|String|Symbol] modifier The accelerator modifier.
 * @return [String]
 */
static VALUE gtk3_accel_group_accelerator_label(
    VALUE class,
    VALUE key,
    VALUE modifier
)
{
    key      = gtk3_lookup_accelerator_key(key);
    modifier = gtk3_lookup_accelerator_modifier(modifier);

    return rb_str_new2(
        gtk_accelerator_get_label(NUM2INT(key), NUM2INT(modifier))
    );
}

/**
 * Sets the default modifier mask to use. Modifiers are set using the bitwise
 * OR operator (`|`):
 *
 *     Gtk3::AccelGroup.default_modifier = Gtk3::ModifierType::CONTROL | \
 *       Gtk3::ModifierType::SHIFT | \
 *       Gtk3::ModifierType::MOD1
 *
 * When setting the modifier you must *at least* set the following modifiers:
 *
 * * {Gtk3::ModifierType::CONTROL}
 * * {Gtk3::ModifierType::SHIFT}
 * * {Gtk3::ModifierType::MOD1}
 *
 * @example
 *  Gtk3::AccelGroup.default_modifier = Gtk3::ModifierType::CONTROL | \
 *    Gtk3::ModifierType::SHIFT | \
 *    Gtk3::ModifierType::MOD1 | \
 *    Gtk3::ModifierType::MOD2
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
 * Returns a number indicating the default modifier mask to use. This value is
 * based on the modifiers set using bitwise OR operators.
 *
 * @example
 *  Gtk3::AccelGroup.default_modifier = Gtk3::ModifierType::CONTROL | \
 *    Gtk3::ModifierType::SHIFT | \
 *    Gtk3::ModifierType::MOD1 | \
 *    Gtk3::ModifierType::MOD2
 *
 *  Gtk3::AccelGroup.default_modifier # => 13
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
 * Locks the accelerator group. Locking an accelerator group prevents installed
 * accelerators from being modifier.
 *
 * @example
 *  group = Gtk3::AccelGroup.new
 *
 *  group.lock
 *  group.locked? # => true
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
 * Unlocks the accelerator group. Unlocking a group makes it possible again to
 * modify installed accelerators.
 *
 * @example
 *  group = Gtk3::AccelGroup.new
 *
 *  group.lock
 *  group.locked? # => true
 *
 *  group.unlock
 *  group.locked? # => false
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
 * @example
 *  group = Gtk3::AccelGroup.new
 *
 *  group.locked? # => false
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
 * Returns the modifier mask of the accelerator group.
 *
 * @since  2012-06-20
 * @return [Fixnum|Bignum]
 */
static VALUE gtk3_accel_group_get_modifier_mask(VALUE self)
{
    GtkAccelGroup *group;

    Data_Get_Struct(self, GtkAccelGroup, group);

    return INT2NUM(gtk_accel_group_get_modifier_mask(group));
}

/**
 * Installs an accelerator in the group.
 *
 * @example Using constants when connecting a callback.
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect(:q, Gtk3::ModifierType::CONTROL, Gtk3::AccelFlag::VISIBLE) do
 *    puts 'You pressed <Control>q`
 *  end
 *
 * @example Using symbols when connecting a callback.
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect(:q, :control, :visible) do
 *    puts 'You pressed <Control>q'
 *  end
 *
 * @since 2012-06-08
 * @param [Fixnum|Bignum|String|Symbol] key A number of the key to bind the
 *  accelerator to.
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
    guint key_guint;
    GdkModifierType gdk_modifier;
    GtkAccelFlags gtk_flag;

    rb_need_block();

    key          = gtk3_lookup_accelerator_key(key);
    modifier     = gtk3_lookup_accelerator_modifier(modifier);
    flag         = gtk3_lookup_accelerator_flag(flag);
    key_guint    = NUM2INT(key);
    gdk_modifier = NUM2INT(modifier);
    gtk_flag     = NUM2INT(flag);

    if ( !gtk_accelerator_valid(key_guint, gdk_modifier) )
    {
        rb_raise(rb_eArgError, "invalid key value and/or modifier");
    }

    Data_Get_Struct(self, GtkAccelGroup, group);

    closure = gtk3_closure_new(rb_block_proc(), self);

    gtk_accel_group_connect(
        group,
        key_guint,
        gdk_modifier,
        gtk_flag,
        (GClosure *) closure
    );

    return Qnil;
}

/**
 * Connects an accelerator by the key path.
 *
 * @example
 *  Gtk3::AccelMap.add_entry('<Example>/Test', 113, :control)
 *
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect('<Example>/Test') do
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

    path_gchar = StringValuePtr(path);

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
 *  group.connect(:q, :control, :visible)
 *  group.disconnect_key(:q, :control) # => true
 *
 * @since 2012-06-09
 * @param [Fixnum|Bignum|String|Symbol] key The key number to use for
 *  disconnecting a callback.
 * @param [String|Symbol|Fixnum|Bignum] mod The key modifier.
 */
static VALUE gtk3_accel_group_disconnect_key(VALUE self, VALUE key, VALUE mod)
{
    guint key_guint;
    GdkModifierType gdk_modifier;
    GtkAccelGroup *group;

    key_guint    = NUM2INT(gtk3_lookup_accelerator_key(key));
    gdk_modifier = NUM2INT(gtk3_lookup_accelerator_modifier(mod));

    Data_Get_Struct(self, GtkAccelGroup, group);

    return gtk3_gboolean_to_rboolean(
        gtk_accel_group_disconnect_key(group, key_guint, gdk_modifier)
    );
}

/**
 * Queries an accelerator group for the given key and modifier. The return
 * value is an array of instances of {Gtk3::AccelGroupEntry} objects.
 *
 * @example
 *  group = Gtk3::AccelGroup.new
 *
 *  group.connect(:q, :control, :visible) {}
 *  group.query(:q, :control) => [#<Gtk3::AccelGroupEntry ...>]
 *
 * @since 2012-06-10
 * @param [Fixnum|Bignum|String|Symbol] key The key number to query.
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

    key = gtk3_lookup_accelerator_key(key);
    mod = gtk3_lookup_accelerator_modifier(mod);

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
        "modifier_mask",
        gtk3_accel_group_get_modifier_mask,
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
}
