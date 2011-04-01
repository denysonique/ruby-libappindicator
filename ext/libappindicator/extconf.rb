
require 'mkmf'
require 'rubygems'
require 'pkg-config'

def failure(msg)
  puts "Error: #{msg}"
  exit 1
end

package_id = 'appindicator-0.1'
PKGConfig.have_package(package_id) || failure("Couldn't find #{package_id}")

[['glib2','rbgobject.h'],['gtk2','rbgtk.h']].each do |g,h|
  (h_fp = Gem::required_location(g,h)) || failure("Couldn't find #{h} file in #{g} gem")
  find_header(h, h_fp.rpartition("/")[0])
end

create_makefile 'appindicator'

