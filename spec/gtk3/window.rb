require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::Window' do
  it 'Set the title of a window' do
    window = Gtk3::Window.new

    window.title.should == nil

    window.title = 'My Window'

    window.title.should == 'My Window'
  end
end
