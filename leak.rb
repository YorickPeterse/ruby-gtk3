require './lib/gtk3'

def memory(name)
  puts "Memory in kilobytes (#{name}): " + `ps -o rss= #{Process.pid}`.strip
end

def create_window
  window = Gtk3::Window.new
  window.show_all
end

memory('start')

100.times do
  create_window

  sleep(0.1)
end

memory('end')

GC.start
sleep(2)

memory('after gc')
