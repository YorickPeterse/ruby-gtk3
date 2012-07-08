require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::Window' do
  it 'Set the title of a window' do
    window = Gtk3::Window.new

    window.title.should == nil

    window.title = 'My Window'

    window.title.should == 'My Window'

    window.destroy
  end

  it 'Sets whether the window can be resized by the user' do
    window = Gtk3::Window.new

    window.resizable = true

    window.resizable?.should == true

    window.resizable = false

    window.resizable?.should == false

    window.destroy
  end

  # TODO: find a proper way to test if this actually works.
  it 'Add and remove an accelerator group to a window' do
    group  = Gtk3::AccelGroup.new
    window = Gtk3::Window.new

    should.raise?(TypeError) { window.add_accel_group(10) } \
      .message.should == 'wrong argument type Fixnum (expected Gtk3::AccelGroup)'

    window.add_accel_group(group)

    should.raise?(TypeError) { window.remove_accel_group(10) } \
      .message.should == 'wrong argument type Fixnum (expected Gtk3::AccelGroup)'

    window.remove_accel_group(group)

    window.destroy
  end

  # TODO: find a proper way to test this.
  it 'Activate a focused widget' do
    window = Gtk3::Window.new

    window.activate_focus.should == false

    window.destroy
  end

  # TODO: find a proper way to test this.
  it 'Activate the default widget of a window' do
    window = Gtk3::Window.new

    window.activate_default.should == false

    window.destroy
  end

  it 'Set a window to be a modal window' do
    window = Gtk3::Window.new

    window.modal?.should == false

    window.modal = true

    window.modal?.should == true

    window.destroy
  end

  it 'Set and get the default size of a window' do
    window = Gtk3::Window.new

    should.raise?(TypeError) { window.default_size = 10 }
    should.raise?(ArgumentError) { window.default_size = [1, 2, 3] }
    should.raise?(TypeError) { window.default_size = ['a', 'b'] }

    window.default_size = [100, 200]

    window.default_size.should == [100, 200]

    window.destroy
  end

  it 'Destroy the parent of a window and the window itself' do
    window = Gtk3::Window.new

    window.destroy_with_parent?.should == false

    window.destroy_with_parent = true

    window.destroy_with_parent?.should == true

    window.destroy
  end
end
