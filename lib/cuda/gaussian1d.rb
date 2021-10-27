# frozen_string_literal: true

require_relative 'gaussian1d/version'

# Convolve
module CudaGaussian1d
  require 'cuda/gaussian1d.so'

  # Array
  refine Array do
    1
  end
end
