require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::AccelGroup' do
  it 'Installing an accelerator requires a block' do
    group = Gtk3::AccelGroup.new
    error = should.raise?(LocalJumpError) do
      group.connect(113, Gtk3::ModifierType::CONTROL, Gtk3::AccelFlag::VISIBLE)
    end

    error.message.should == 'no block given'
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
      group.connect(113, :control, :visible) {}
    end
  end

  it 'Install an accelerator using a key path' do
    group = Gtk3::AccelGroup.new

    group.connect_by_path('<Control>q') {}
  end
end
