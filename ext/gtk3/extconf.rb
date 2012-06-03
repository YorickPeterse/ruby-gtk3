require 'mkmf'

have_header('ruby.h')

have_library('gtk-3', 'gtk_init')
have_library('gdk-3', 'gdk_init')

$CFLAGS << ' -Wextra -Wall -pedantic '

if ENV['DEBUG']
  $CFLAGS << ' -O0 '
end

$CFLAGS << " " << `pkg-config gtk+-3.0 --cflags`

create_makefile('gtk3/gtk3')
