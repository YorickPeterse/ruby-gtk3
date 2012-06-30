require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::Window' do
  it 'Set the title of a window' do
    window = Gtk3::Window.new

    window.title.should == nil

    window.title = 'My Window'

    window.title.should == 'My Window'
  end

  it 'Sets whether the window can be resized by the user' do
    window = Gtk3::Window.new

    window.resizable = true

    window.resizable?.should == true

    window.resizable = false

    window.resizable?.should == false
  end
end
