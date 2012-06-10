require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::AccelGroupEntry' do
  it 'Initialize a new accelerator group entry' do
    callback = proc {}
    entry    = Gtk3::AccelGroupEntry.new(
      113,
      Gtk3::ModifierType::CONTROL,
      Gtk3::AccelFlag::VISIBLE,
      callback
    )

    entry.key.should      == 113
    entry.modifier.should == Gtk3::ModifierType::CONTROL
    entry.flags.should    == Gtk3::AccelFlag::VISIBLE
    entry.path.should     == '<Control>q'
    entry.callback.should == callback
  end
end
