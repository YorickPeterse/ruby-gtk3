require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::ModifierType' do
  it 'Lookup a modifier constant' do
    Gtk3::ModifierType.lookup(:shift).should  == Gtk3::ModifierType::SHIFT
    Gtk3::ModifierType.lookup('shift').should == Gtk3::ModifierType::SHIFT
    Gtk3::ModifierType.lookup(:test).should   == nil
  end
end
