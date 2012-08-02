/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_VECTOR_H
#define MLIB_VECTOR_H

#include "mlib_array.h"
#include "mlib_core.h"

namespace mlib {
	template <class base>
	struct basic_vector : public array<base> {
		typedef typename array<base>::type T;
		basic_vector() : array<base>() {}
		basic_vector(const T x) {
			MLIB_STATIC_CHECK(array<base>::_size == 1);
			array<base>::begin()[0] = x;
		}
		basic_vector(const T x, const T y) {
			MLIB_STATIC_CHECK(array<base>::_size == 2);
			array<base>::begin()[0] = x;
			array<base>::begin()[1] = y;
		}
		basic_vector(const T x, const T y, const T z) {
			MLIB_STATIC_CHECK(array<base>::_size == 3);
			array<base>::begin()[0] = x;
			array<base>::begin()[1] = y;
			array<base>::begin()[2] = z;
		}
	};
}; // mlib

#endif // MLIB_VECTOR_H
