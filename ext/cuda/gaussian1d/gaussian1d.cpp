/*
 *  (c) 2021 Murata Mitsuharu
 *  Licensed under the MIT License.
 */

#include <gaussian1d.hpp>
#include <iostream>
#include <ruby.h>
#include <vector>

extern "C" {
void Init_gaussian1d(void) { puts("hello, world"); }
}
