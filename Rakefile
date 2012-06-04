require 'rubygems/package_task'
require 'rake/extensiontask'

GEMSPEC = Gem::Specification.load('gtk3.gemspec')

Dir['./task/*.rake'].each do |task|
  import(task)
end

Rake::ExtensionTask.new('gtk3', GEMSPEC)

Gem::PackageTask.new(GEMSPEC) do |pkg|
  pkg.need_tar = false
  pkg.need_zip = false
end

task :default => :compile
