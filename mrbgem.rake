MRuby::Gem::Specification.new('mruby-cmigemo') do |spec| 
  spec.license = 'MIT'
  spec.authors = 'nocd5'

  migemo_dir = "../mrbgems/mruby-cmigemo/cmigemo"

  spec.cxx.include_paths << "#{migemo_dir}/src"
  spec.linker.library_paths << "#{migemo_dir}/build"
  spec.linker.libraries << [ 'migemo' ]
end
