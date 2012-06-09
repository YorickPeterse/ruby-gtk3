require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::AccelFlag' do
  it 'Lookup an accelerator flag constant' do
    Gtk3::AccelFlag.lookup(:visible).should  == Gtk3::AccelFlag::VISIBLE
    Gtk3::AccelFlag.lookup('visible').should == Gtk3::AccelFlag::VISIBLE
    Gtk3::AccelFlag.lookup(:example).should  == nil
  end
end
