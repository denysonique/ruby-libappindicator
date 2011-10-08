
require 'mkmf'
require 'rubygems'
require 'pkg-config'

def failure(msg)
  puts "Error: #{msg}"
  exit 1
end

package_id = 'appindicator-0.1'
PKGConfig.have_package(package_id) || failure("Couldn't find #{package_id}")

# Depending on the version of rubygems, use the appropriate block of code
proc_find_headers =
  if Gem::Version.new(Gem::VERSION) < Gem::Version.new("1.8.0")
    Proc.new { |gem, header|
      (header_fp = Gem::required_location(gem, header)) || failure("Couldn't find #{header} file in #{gem} tem")
      find_header(header, header_fp.rpartition("/")[0])
    }
  else
    Proc.new { |gem, header|
      gem_spec = Gem::Specification.find_by_name(gem)
      dirs = Dir.glob(gem_spec.lib_dirs_glob)
      dirs.each {|dir| find_header(header, dir)}
    }
  end

# Find the mandatory headers in their respective gems
[['glib2','rbgobject.h'],['gtk2','rbgtk.h']].each &proc_find_headers

create_makefile 'appindicator'

