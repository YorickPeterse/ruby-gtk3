require 'rubygems/package_task'
require 'rake/extensiontask'

tasks   = ['build']
GEMSPEC = Gem::Specification.load('gtk3.gemspec')

tasks.each do |task|
  import(File.expand_path("../task/#{task}.rake", __FILE__))
end

Rake::ExtensionTask.new('gtk3', GEMSPEC)

Gem::PackageTask.new(GEMSPEC) do |pkg|
  pkg.need_tar = false
  pkg.need_zip = false
end

task :default => :compile
