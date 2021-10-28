/*
 *  (c) 2021 Murata Mitsuharu
 *  Licensed under the MIT License.
 */

#include <gaussian1d.hpp>
#include <iostream>
#include <ruby.h>
#include <vector>

template <typename T>
static VALUE
rb_ary_cuda_gaussian1d(VALUE input, VALUE sigma, VALUE mode, VALUE truncate){
  std::vector<T> r;
  VALUE _r = rb_ary_new();
  T t = NUM2DBL(truncate);
  T sd = NUM2DBL(sigma);
  long m = NUM2LONG(mode);
  std::vector<T> _input(RARRAY_LEN(input));
  for(long i = 0; i < _input.size(); i++)
    _input[i] = (T)NUM2DBL(rb_ary_entry(input, i));

  if(m == 0)
    r = gaussian1d<T>(_input, t, sd);

  for(long i = 0; i < r.size(); i++)
    rb_ary_store(_r, i, DBL2NUM(r[i]));

  return _r;
}

template <typename T>
static VALUE
rb_ary_cuda_gaussian1d_multi(VALUE input, VALUE sigma, VALUE mode, VALUE truncate){
  std::vector<std::vector<T>> r;
  VALUE _r = rb_ary_new();
  T t = NUM2DBL(truncate);
  T sd = NUM2DBL(sigma);
  long m = NUM2LONG(mode);
  std::vector<std::vector<T>> _input(RARRAY_LEN(input), std::vector<T>(RARRAY_LEN(rb_ary_entry(input, 0))));
  for(long i = 0; i < _input.size(); i++)
    for(long j = 0; j < _input[0].size(); j++)
      _input[i][j] = (T)NUM2DBL(rb_ary_entry(rb_ary_entry(input, i), j));

  if(m == 0)
    r = gaussian1d_multi<T>(_input, t, sd);

  for(long i = 0; i < _input.size(); i++){
    rb_ary_store(_r, i, rb_ary_new());
    for(long j = 0; j < _input[0].size(); j++)
      rb_ary_store(rb_ary_entry(_r, i), j, DBL2NUM(r[i][j]));
  }

  return _r;
}

extern "C" {
  void Init_gaussian1d() {
    rb_define_private_method(rb_cArray, "gpu_gaussian1d_double", rb_ary_cuda_gaussian1d<double>, 3);
    rb_define_private_method(rb_cArray, "gpu_gaussian1d_float", rb_ary_cuda_gaussian1d<float>, 3);
    rb_define_private_method(rb_cArray, "gpu_gaussian1d_multi_double", rb_ary_cuda_gaussian1d_multi<double>, 3);
    rb_define_private_method(rb_cArray, "gpu_gaussian1d_multi_float", rb_ary_cuda_gaussian1d_multi<float>, 3);
  }
}
