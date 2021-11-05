# frozen_string_literal: true

require 'mkmf'

narray = Gem::Specification.find_by_name('numo-narray')
raise 'Gem `numo-narray` not found' unless narray

narray_dir = narray.require_path
dir_config('numo-narray', "#{narray_dir}/numo", "#{narray_dir}/numo")
raise '`numo/narray.h` not found' unless have_header('numo/narray.h')

narray_lib = "#{narray_dir}/numo/narray.so"
raise '`narray.so` not found' unless File.exist? narray_lib

# rubocop:disable Style/GlobalVars
$libs += narray_lib if $libs.empty?
# rubocop:enable Style/GlobalVars

create_makefile('cuda/gaussian1d') if have_library('gaussian1d')
