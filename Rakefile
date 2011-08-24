require 'rubygems'  
require 'rake'  
require 'echoe'  

Echoe.new('ruby-libappindicator') do |p|  
  p.summary         = "Ruby bindings for libappindicator"
  p.url             = "http://github.com/leander256/ruby-libappindicator"
  p.author          = [ "Thomas Kister" , "romario333" ]
  p.email           = "leander256@gmail.com"
  p.runtime_dependencies = ["gtk2"]
  p.development_dependencies = ["pkg-config", "gtk2"]
end

Dir["#{File.dirname(__FILE__)}/tasks/*.rake"].sort.each { |ext| load ext }
