# frozen_string_literal: true

require_relative 'gaussian1d/version'

# Convolve
module CudaGaussian1d
  require 'cuda/gaussian1d.so'

  # Array
  refine Array do
    def gaussian1d(sigma, mode: :reflect, truncate: 4.0, type: :float)
      modes = { reflect: 0 }
      mode_n = modes[mode]
      raise "mode should be 'reflect'" unless mode_n

      if self[0].instance_of?(Array)
        case type
        when :float
          gpu_gaussian1d_multi_float(sigma, mode_n, truncate)
        when :double
          gpu_gaussian1d_multi_double(sigma, mode_n, truncate)
        else
          raise "type should be 'double' or 'float'"
        end
      else
        [self].gaussian1d(sigma, mode: :reflect, truncate: 4.0, type: :float)
      end
    end
  end
end
