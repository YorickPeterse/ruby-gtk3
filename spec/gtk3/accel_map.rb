require File.expand_path('../../helper', __FILE__)
require 'tempfile'

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

  it 'Change an accelerator mapping' do
    should.raise?(ArgumentError) { Gtk3::AccelMap.change_entry }
    should.raise?(ArgumentError) { Gtk3::AccelMap.change_entry(1, 2, 3, 4, 5) }

    Gtk3::AccelMap.add_entry('<Test>/Test', 113, :control)

    Gtk3::AccelMap.change_entry('<Test>/Test', 112, :shift).should == true

    key = Gtk3::AccelMap.lookup_entry('<Test>/Test')

    key.key.should      == 112
    key.modifier.should == Gtk3::ModifierType::SHIFT
  end

  it 'Save a set of accelerator specifications' do
    file = Tempfile.new('ruby_gtk3')

    Gtk3::AccelMap.save(file.path)

    file.read.include?('<Test>/Test').should == true
    file.close
  end

  it 'Load a set of accelerator specifications' do
    file = Tempfile.new('ruby_gtk3')

    Gtk3::AccelMap.lookup_entry('<Test>/Loaded').should == nil

    file.write('(gtk_accel_path "<Test>/Loaded" "<Control>q")')
    file.rewind

    Gtk3::AccelMap.load(file.path)

    entry = Gtk3::AccelMap.lookup_entry('<Test>/Loaded')

    entry.key.should      == 113
    entry.modifier.should == Gtk3::ModifierType::CONTROL

    file.close
  end

  it 'Loop over the accelerator mapping entries' do
    keys      = []
    paths     = []
    modifiers = []
    changes   = []

    Gtk3::AccelMap.foreach do |path, key, modifier, changed|
      keys      << key
      paths     << path
      modifiers << modifier
      changes   << changed
    end

    keys.include?(112).should == true
    keys.include?(113).should == true

    paths.include?('<Test>/Test').should   == true
    paths.include?('<Test>/Loaded').should == true

    modifiers.include?(Gtk3::ModifierType::CONTROL).should == true
    modifiers.include?(Gtk3::ModifierType::SHIFT).should   == true

    changes.include?(true).should == true
  end

  it 'Add an accelerator filter' do
    paths = []

    Gtk3::AccelMap.foreach do |path, key, modifier, changed|
      paths << path
    end

    paths.include?('<Test>/Loaded').should == true

    Gtk3::AccelMap.add_filter('<Test>/Loaded')

    paths = []

    Gtk3::AccelMap.foreach do |path, key, modifier, changed|
      paths << path
    end

    paths.include?('<Test>/Loaded').should == false
  end

  it 'Loop over accelerator entries regardless of existing filters' do
    paths = []

    Gtk3::AccelMap.foreach_unfiltered do |path, key, modifier, changed|
      paths << path
    end

    paths.include?('<Test>/Test').should   == true
    paths.include?('<Test>/Loaded').should == true
  end
end
