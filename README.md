# cuda-convolve
[![Gem](https://img.shields.io/gem/v/cuda-gaussian1d.svg)](https://rubygems.org/gems/cuda-gaussian1d)
[![Rubocop](https://github.com/Himeyama/cuda-gaussian1d/actions/workflows/rubocop.yml/badge.svg)](https://github.com/Himeyama/cuda-gaussian1d/actions/workflows/rubocop.yml)

## Installation

### Dependency
```bash
brew install himeyama/homebrew-lib/libcuda-gaussian1d
```

### Gem or Gemfile
> Gemfile
```rb
gem 'cuda-gaussian1d'
```

and

```bash
bundle
```

> Gem
```bash
gem install cuda-gaussian1d
```

## Example
```rb
# frozen_string_literal: true

require 'cuda/gaussian1d'

using CudaGaussian1d

p [1, 2, 3, 4, 5].gaussian1d(1)

p [1, 2, 3, 4, 5].gaussian1d(4)

```
