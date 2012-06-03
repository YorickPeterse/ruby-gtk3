require './lib/gtk3'

window = Gtk3::Window.new

window.connect(:destroy) do |window|
  puts 'First delete-event'

  Gtk3.main_quit
end

window.show_all

Gtk.main
