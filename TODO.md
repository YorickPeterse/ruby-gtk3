# TODO

* Implement whatever is worth implementing. A lot of the GTK functions don't
  make any sense in Ruby code so there's no point in implementing them. As a
  baseline I'm using the Python implementation.
* Instance methods should be chainable (when this is useful) instead of
  returning `nil`.
* Documentation, examples (lots of them), etc.
* Memory management (test using Valgrind). Currently I'm not paying any
  attention to this (other than what's required so that Make plays along
  nicely). Once the Gem is in a decent state the code should be checked for
  memory leaks, optimized for better performance, etc.
* Find a nice way of defining constants for keys. The GTK2 binding does this by
  parsing the header file that defines all `GDK_KEY_*` constants and then
  generating the required code to define these constants as Ruby constants.
  Since these keys don't always change I think it's best to do this in a Rake
  task and keep track of the resulting file in Git. A way of working around
  this would be to allow strings and call `#ord()` on these strings to convert
  them to integers.
