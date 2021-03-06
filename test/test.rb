#!/usr/bin/env ruby
# frozen_string_literal: true

require 'bundler/setup'
require 'numo/narray'
require 'cuda/gaussian1d'

using CudaGaussian1d

p [1, 2, 3, 4, 5].gaussian1d(1)

p [1, 2, 3, 4, 5].gaussian1d(4)

p [[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]].gaussian1d(4)

p Numo::DFloat[1, 2, 3, 4, 5].gaussian1d(1)
p Numo::SFloat[[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]].gaussian1d(4)
