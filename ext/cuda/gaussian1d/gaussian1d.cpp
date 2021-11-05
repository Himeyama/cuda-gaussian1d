/*
 *  (c) 2021 Murata Mitsuharu
 *  Licensed under the MIT License.
 */

#include <gaussian1d.hpp>
#include <iostream>
#include <ruby.h>
#include <vector>
#include <numo/narray.h>

extern VALUE numo_cDFloat;
extern VALUE numo_cSFloat;

template <typename T>
static VALUE
rb_ary_cuda_gaussian1d_multi(VALUE input, VALUE sigma, VALUE mode, VALUE truncate){
  std::vector<std::vector<T>> r;
  VALUE _r = rb_ary_new();
  T t = NUM2DBL(truncate);
  T sd = NUM2DBL(sigma);
  long m = NUM2LONG(mode);
  std::vector<std::vector<T>> _input;
  long input_row, input_col;
  VALUE input_shape;

  if(CLASS_OF(input) == rb_cArray){
    input_row = RARRAY_LEN(input);
    input_col = RARRAY_LEN(rb_ary_entry(input, 0));
    _input = std::vector<std::vector<T>>(input_row, std::vector<T>(input_col));
    for(long i = 0; i < _input.size(); i++)
      for(long j = 0; j < _input[0].size(); j++)
        _input[i][j] = (T)NUM2DBL(rb_ary_entry(rb_ary_entry(input, i), j));
  }else if(CLASS_OF(input) == numo_cDFloat || CLASS_OF(input) == numo_cSFloat){
    input_shape = rb_funcall(input, rb_intern("shape"), 0);
    input_row = NUM2LONG(rb_ary_entry(input_shape, 0));
    input_col = NUM2LONG(rb_ary_entry(input_shape, 1));
    _input = std::vector<std::vector<T>>(input_row, std::vector<T>(input_col));
    for(long i = 0; i < input_row; i++)
      memcpy(_input[i].data(), (T*)na_get_pointer(input) + input_col * i, sizeof(T) * input_col);
  }else
    rb_raise(rb_eTypeError, "");
  

  if(m == 0) // reflect
    r = gaussian1d_multi<T>(_input, t, sd);
  else
    rb_raise(rb_eTypeError, "");

  if(CLASS_OF(input) == rb_cArray){
    for(long i = 0; i < _input.size(); i++){
      rb_ary_store(_r, i, rb_ary_new());
      for(long j = 0; j < _input[0].size(); j++)
        rb_ary_store(rb_ary_entry(_r, i), j, DBL2NUM(r[i][j]));
    }
  }else if(CLASS_OF(input) == numo_cDFloat || CLASS_OF(input) == numo_cSFloat){
    _r = rb_funcall(CLASS_OF(input), rb_intern("zeros"), 1, input_shape);
    for(long i = 0; i < input_row; i++)
      memcpy((T*)na_get_pointer(_r) + input_col * i, r[i].data(), sizeof(T) * input_col);
  }else
    rb_raise(rb_eTypeError, "");

  return _r;
}

extern "C" {
  void Init_gaussian1d() {
    rb_define_private_method(rb_cArray, "gpu_gaussian1d_multi_double", rb_ary_cuda_gaussian1d_multi<double>, 3);
    rb_define_private_method(rb_cArray, "gpu_gaussian1d_multi_float", rb_ary_cuda_gaussian1d_multi<float>, 3);
    rb_define_private_method(numo_cDFloat, "gpu_gaussian1d_multi", rb_ary_cuda_gaussian1d_multi<double>, 3);
    rb_define_private_method(numo_cSFloat, "gpu_gaussian1d_multi", rb_ary_cuda_gaussian1d_multi<float>, 3);
  }
}
