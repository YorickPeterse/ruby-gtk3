require File.expand_path('../lib/gtk3/version', __FILE__)

Gem::Specification.new do |s|
  s.name        = 'gtk3'
  s.version     = Gtk3::VERSION
  s.date        = '2012-05-28'
  s.authors     = ['Yorick Peterse']
  s.email       = 'yorickpeterse@gmail.com'
  s.summary     = 'Ruby bindings for GTK3 written in C.'
  s.homepage    = 'https://github.com/yorickpeterse/ruby-gtk3/'
  s.description = s.summary

  s.files = File.read(File.expand_path('../MANIFEST', __FILE__)).split("\n")

  s.extensions            = ['ext/gtk3/extconf.rb']
  s.has_rdoc              = 'yard'
  s.required_ruby_version = '>= 1.9.2'

  s.add_development_dependency('rake', ['>= 0.9.2.2'])
  s.add_development_dependency('redcarpet', ['>= 2.1.1'])
  s.add_development_dependency('bacon', ['>= 1.1.0'])
  s.add_development_dependency('yard', ['>= 0.8.1'])
  s.add_development_dependency('rake-compiler', ['>= 0.8.1'])
end
