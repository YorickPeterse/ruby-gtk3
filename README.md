# Ruby GTK3

A C extension that provides a Ruby binding to the GTK3 API.

**Note:** this project is currently put on hold due to the lack of available
time and the sheer size of the GTK project and all its dependencies. Maybe in
the future I'll resume work on this project but for now I'm sadly not able to
commit myself to it.

## Example

A simple "Hello world" example:

    require 'gtk3'

    window = Gtk3::Window.new
    button = Gtk3::Button.new

    window.title = 'Ruby Gtk3'
    button.label = 'Hello'

    window.connect(:destroy) do
      Gtk3.main_quit
    end

    button.connect(:clicked) do
      puts 'Hello world!'
    end

    window.add(button)
    window.show_all

    Gtk3.main

## License

All the source code is licensed under the MIT license unless stated otherwise.
A copy of this license can be found in the file "LICENSE" in the root directory
of the Git repository.

## Important

Currently the code in this repository is nowhere near alpha quality. There are
some basic working pieces (e.g. creating windows) but other than that there's
not much yet. I'm also pretty sure it will leak in several places. Once I feel
that the code is useful enough I'll update the documentation, check for leaks,
etc.
