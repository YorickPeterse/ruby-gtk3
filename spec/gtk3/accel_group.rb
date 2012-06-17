require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::AccelGroup' do
  it 'Retrieve an accelerator name' do
    Gtk3::AccelGroup.accelerator_name(113, :control).should == '<Primary>q'
    Gtk3::AccelGroup.accelerator_name(113, :shift).should   == '<Shift>q'
  end

  it 'Retrieve an accelerator label' do
    Gtk3::AccelGroup.accelerator_label(113, :control).should == 'Ctrl+Q'
    Gtk3::AccelGroup.accelerator_label(113, :shift).should   == 'Shift+Q'
  end

  it 'Set the default accelerator modifier' do
    default = Gtk3::AccelGroup.default_modifier

    Gtk3::AccelGroup.default_modifier = Gtk3::ModifierType::CONTROL | \
      Gtk3::ModifierType::SHIFT | \
      Gtk3::ModifierType::MOD1

    Gtk3::AccelGroup.default_modifier.should == Gtk3::ModifierType::CONTROL | \
      Gtk3::ModifierType::SHIFT | \
      Gtk3::ModifierType::MOD1

    Gtk3::AccelGroup.default_modifier = Gtk3::ModifierType::CONTROL | \
      Gtk3::ModifierType::SHIFT | \
      Gtk3::ModifierType::MOD1 | \
      Gtk3::ModifierType::MOD2

    Gtk3::AccelGroup.default_modifier.should == Gtk3::ModifierType::CONTROL | \
      Gtk3::ModifierType::SHIFT | \
      Gtk3::ModifierType::MOD1 | \
      Gtk3::ModifierType::MOD2

    Gtk3::AccelGroup.default_modifier = default
  end

  it 'Lock an accelerator group' do
    group = Gtk3::AccelGroup.new

    group.locked?.should == false

    group.lock

    group.locked?.should == true

    group.unlock

    group.locked?.should == false
  end

  it 'Installing an accelerator requires a block' do
    group = Gtk3::AccelGroup.new
    error = should.raise?(LocalJumpError) do
      group.connect(113, Gtk3::ModifierType::CONTROL, Gtk3::AccelFlag::VISIBLE)
    end

    error.message.should                     == 'no block given'
    group.query(113, :control).length.should == 0
  end

  it 'Install an accelerator group' do
    group = Gtk3::AccelGroup.new

    # TODO: do more than just checking if this doesn't raise an exception as
    # this is rather useless.
    should.raise?(TypeError) do
      group.connect(113, [], []) {}
    end

    should.not.raise?(TypeError) do
      group.connect(
        113,
        Gtk3::ModifierType::CONTROL,
        Gtk3::AccelFlag::VISIBLE
      ) {}
    end

    should.not.raise?(TypeError) do
      group.connect(112, :control, :visible) {}
    end

    group.query(112, :control).length.should == 1
    group.query(113, :control).length.should == 1
  end

  it 'Install an accelerator using a key path' do
    group = Gtk3::AccelGroup.new

    group.connect_by_path('<AccelGroup>/Test') {}

    group.query(113, :control).length.should == 0

    Gtk3::AccelMap.add_entry('<AccelGroup>/Test', 113, :control)
    group.connect_by_path('<AccelGroup>/Test') {}

    group.query(113, :control).length.should == 2
  end

  it 'Query an accelerator group' do
    group   = Gtk3::AccelGroup.new
    entries = []

    group.connect(113, :control, :visible) {}

    entries = group.query(113, :control)

    entries.length.should      == 1
    entries[0].key.should      == 113
    entries[0].modifier.should == Gtk3::ModifierType::CONTROL
    entries[0].flags.should    == Gtk3::AccelFlag::VISIBLE
    entries[0].path.should     == '<Primary>q'
  end

  it 'Install and disconnect and accelerator' do
    group = Gtk3::AccelGroup.new

    group.connect(113, :control, :visible) {}

    group.query(113, :control).length.should == 1

    group.disconnect_key(113, :control).should == true
    group.disconnect_key(113, :control).should == false

    group.query(113, :control).length.should == 0
  end
end
