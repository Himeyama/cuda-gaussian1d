# frozen_string_literal: true

require 'mkmf'

create_makefile('cuda/gaussian1d') if have_library('cuda-gaussian1d')
