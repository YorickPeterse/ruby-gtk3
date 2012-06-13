require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::AccelMap' do
  it 'Add and lookup an accelerator mapping' do
    should.raise?(TypeError) do
      Gtk3::AccelMap.add_entry(10, 113, :control)
    end

    should.raise?(TypeError) do
      Gtk3::AccelMap.add_entry('<Test>/Test', '113', :control)
    end

    error = should.raise?(ArgumentError) do
      Gtk3::AccelMap.add_entry('<Test>/Test', 113, :testing)
    end

    error.message.should == 'invalid accelerator modifier'

    Gtk3::AccelMap.add_entry('<Test>/Test', 113, :control)

    key = Gtk3::AccelMap.lookup_entry('<Test>/Test')

    key.key.should      == 113
    key.modifier.should == Gtk3::ModifierType::CONTROL
  end
end
