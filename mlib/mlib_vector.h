/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_VECTOR_H
#define MLIB_VECTOR_H

#include "mlib_core.h"

namespace mlib {
	template <class base>
	struct basic_vector : public base {
		typedef typename base::type T;
		enum { _size = sizeof(base) / sizeof(T), };
		enum { _rows = _size, };
		enum { _cols = 1, };
		basic_vector() : base() {}
	};
}; // mlib

#endif // MLIB_VECTOR_H
