require 'rubygems'  
require 'rake'  
require 'echoe'  

Echoe.new('ruby-libappindicator', '0.1.0') do |p|  
  p.summary         = "Ruby bindings for libappindicator"
  p.url             = "http://github.com/leander256/ruby-libappindicator"
  p.author          = "Thomas Kister"
  p.email           = "leander256@gmail.com"
  p.development_dependencies = ["pkg-config", "gtk2"]
end

Dir["#{File.dirname(__FILE__)}/tasks/*.rake"].sort.each { |ext| load ext }
