
require 'mkmf'
require 'rubygems'
require 'pkg-config'

def failure(msg)
  puts "Error: #{msg}"
  exit 1
end

package_id = 'appindicator-0.1'
PKGConfig.have_package(package_id) || failure("Couldn't find #{package_id}")

[['glib2','rbgobject.h'],['gtk2','rbgtk.h']].each do |gem,header|
  gem_spec = Gem::Specification.find_by_name(gem)
  dirs = Dir.glob(gem_spec.lib_dirs_glob)
  dirs.each {|dir| find_header(header, dir)}
end

create_makefile 'appindicator'

