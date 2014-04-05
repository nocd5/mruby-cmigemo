MRuby::Gem::Specification.new('mruby-cmigemo') do |spec| 
  spec.license = 'MIT'
  spec.authors = 'nocd5'

  migemo_dir = "../mrbgems/mruby-cmigemo/cmigemo"
  migemo_lib = "#{migemo_dir}/build/libmigemo.a"

  spec.linker.library_paths << [ File.dirname(migemo_lib) ]
  spec.linker.libraries << [ 'migemo' ]
end
