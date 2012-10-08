/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_VECTOR_H
#define MLIB_VECTOR_H

#include "mlib_core.h"
#include "mlib_matrix.h"

#define mlib_vector1(T) mlib::matrix<mlib::basic_vector<mlib::vector1_t<T> > >
#define mlib_vector2(T) mlib::matrix<mlib::basic_vector<mlib::vector2_t<T> > >
#define mlib_vector3(T) mlib::matrix<mlib::basic_vector<mlib::vector3_t<T> > >
#define mlib_vector4(T) mlib::matrix<mlib::basic_vector<mlib::vector4_t<T> > >

namespace mlib {
	template <class base>
	struct basic_vector : public base {
		typedef typename base::type T;
		enum { _size = sizeof(base) / sizeof(T), };
		enum { _rows = _size, };
		enum { _cols = 1, };
		basic_vector() : base() {}
	};

	template <class T>
	struct vector1_t {
		typedef T type;
		type x;
	};
	template <class T>
	struct vector2_t {
		typedef T type;
		type x, y;
	};
	template <class T>
	struct vector3_t {
		typedef T type;
		type x, y, z;
	};
	template <class T>
	struct vector4_t {
		typedef T type;
		type x, y, z, w;
	};
}; // mlib

#endif // MLIB_VECTOR_H
