/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012, 2015
 */

#ifndef MLIB_VECTOR_H
#define MLIB_VECTOR_H

#include "mlib_core.h"
#include "mlib_matrix.h"

#define mlib_vector1(T) mlib::matrix<mlib::basic_vector<mlib::vector1_t<T> > >
#define mlib_vector2(T) mlib::matrix<mlib::basic_vector<mlib::vector2_t<T> > >
#define mlib_vector3(T) mlib::matrix<mlib::basic_vector<mlib::vector3_t<T> > >
#define mlib_vector4(T) mlib::matrix<mlib::basic_vector<mlib::vector4_t<T> > >
#define mlib_vector5(T) mlib::matrix<mlib::basic_vector<mlib::vector5_t<T> > >
#define mlib_vector6(T) mlib::matrix<mlib::basic_vector<mlib::vector6_t<T> > >
#define mlib_vector7(T) mlib::matrix<mlib::basic_vector<mlib::vector7_t<T> > >
#define mlib_vector8(T) mlib::matrix<mlib::basic_vector<mlib::vector8_t<T> > >
#define mlib_vector9(T) mlib::matrix<mlib::basic_vector<mlib::vector9_t<T> > >

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
		type x1;
	};
	template <class T>
	struct vector2_t {
		typedef T type;
		type x1, x2;
	};
	template <class T>
	struct vector3_t {
		typedef T type;
		type x1, x2, x3;
	};
	template <class T>
	struct vector4_t {
		typedef T type;
		type x1, x2, x3, x4;
	};
	template <class T>
	struct vector5_t {
		typedef T type;
		type x1, x2, x3, x4, x5;
	};
	template <class T>
	struct vector6_t {
		typedef T type;
		type x1, x2, x3, x4, x5, x6;
	};
	template <class T>
	struct vector7_t {
		typedef T type;
		type x1, x2, x3, x4, x5, x6, x7;
	};
	template <class T>
	struct vector8_t {
		typedef T type;
		type x1, x2, x3, x4, x5, x6, x7, x8;
	};
	template <class T>
	struct vector9_t {
		typedef T type;
		type x1, x2, x3, x4, x5, x6, x7, x8, x9;
	};
}; // mlib

#endif // MLIB_VECTOR_H
