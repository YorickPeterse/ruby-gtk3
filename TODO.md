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
