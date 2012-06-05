require File.expand_path('../../helper', __FILE__)

describe 'Gtk3::Widget' do
  it 'Widget#connect with incorrect argument numbers' do
    window = Gtk3::Window.new

    should.raise?(ArgumentError) { window.connect } \
      .message.should =~ %r{0 for 1..2}

    should.raise?(ArgumentError) { window.connect(:destroy, :before, 10) } \
      .message.should =~ %r{3 for 1..2}
  end

  it 'Widget#connect with an invalid signal name' do
    window = Gtk3::Window.new

    should.raise?(ArgumentError) { window.connect('does-not-exist') {} } \
      .message.should == 'invalid signal name'
  end

  it 'Widget#connect without a block' do
    window = Gtk3::Window.new

    should.raise?(LocalJumpError) { window.connect(:destroy) } \
      .message.should == 'no block given'
  end

  it 'Widget#connect with an invalid position' do
    window = Gtk3::Window.new

    error = should.raise?(ArgumentError) do
      window.connect(:destroy, 'does-not-exist') {}
    end

    error.message.should =~ /invalid signal position/
  end

  it 'Widget#connect should return a valid handler ID' do
    window = Gtk3::Window.new
    id     = window.connect(:destroy) {}

    id.is_a?(Fixnum).should == true
    id.should > 0
  end

  it 'Map and unmap a widget' do
    window = Gtk3::Window.new

    window.show

    window.mapped?.should == true
    window.unmap
    window.mapped?.should == false
    window.map
    window.mapped?.should == true

    window.destroy
  end

  it 'Realize and unrealize a widget' do
    window = Gtk3::Window.new

    window.realized?.should == false
    window.realize
    window.realized?.should == true
    window.unrealize
    window.realized?.should == false

    window.destroy
  end

  it 'Show a widget' do
    window = Gtk3::Window.new

    window.visible?.should == false

    window.show

    window.visible?.should == true

    window.destroy
  end

  it 'Show a widget along with all child widgets' do
    window = Gtk3::Window.new

    window.visible?.should == false

    # TODO: add some child widgets.
    window.show_all

    window.visible?.should == true

    window.destroy
  end

  it 'Show an unmapped widget and start the main loop' do
    window = Gtk3::Window.new

    window.unmap

    window.mapped?.should == false

    window.show_now

    window.visible?.should == true
    window.mapped?.should  == true

    window.destroy
  end
end
