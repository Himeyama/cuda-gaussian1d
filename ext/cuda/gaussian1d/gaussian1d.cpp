/*
 *  (c) 2021 Murata Mitsuharu
 *  Licensed under the MIT License.
 */

#include <cuda-gaussian1d.hpp>
#include <ruby.h>
#include <vector>

extern "C" {
void Init_gaussian1d(void) { puts("hello, world"); }
}
