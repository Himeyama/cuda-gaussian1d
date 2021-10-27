# frozen_string_literal: true

require_relative 'lib/cuda/gaussian1d/version'

Gem::Specification.new do |spec|
  spec.name = 'cuda-gaussian1d'
  spec.version       = CudaGaussian1d::VERSION
  spec.authors       = ['Murata Mitsuharu']
  spec.summary       = 'A GPU-based library for fast one-dimensional Gaussian filtering.'
  spec.require_paths = %w[lib ext]
  spec.extensions = %w[ext/cuda/gaussian1d/extconf.rb]
  spec.required_ruby_version = '>= 2.5'
  spec.license = 'MIT'
  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{\A(?:test|spec|features)/}) }
  end
end
