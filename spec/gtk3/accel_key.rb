require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::AccelKey' do
  it 'Create a new accelerator key object' do
    obj = Gtk3::AccelKey.new(1, 2, 3)

    obj.key.should      == 1
    obj.modifier.should == 2
    obj.flags.should    == 3
  end
end
