desc 'Runs all the tests using Bacon'
task :test => ['clobber', 'default'] do
  Dir.glob(File.expand_path('../../spec/gtk3/**/*.rb', __FILE__)).each do |f|
    require(f)
  end
end
