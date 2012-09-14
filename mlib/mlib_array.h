/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_ARRAY_H
#define MLIB_ARRAY_H

#include <iostream>

#include "mlib_ops.h"
#include "mlib_core.h"

namespace mlib {
	template <class base>
	struct array : public base {
		typedef typename base::type T;
		using base::_size;
		using base::_cols;
		using base::_rows;

		array() : base() {}
		array(const T x) {
			MLIB_STATIC_CHECK(_size == 1);
			begin()[0] = x;
		}
		array(const T x, const T y) {
			MLIB_STATIC_CHECK(_size == 2);
			begin()[0] = x;
			begin()[1] = y;
		}
		array(const T x, const T y, const T z) {
			MLIB_STATIC_CHECK(_size == 3);
			begin()[0] = x;
			begin()[1] = y;
			begin()[2] = z;
		}

		array(const array<base> &v) { mlib_ops::copy<_size, T>(begin(), v.begin()); }

		inline int size() const { return _size; }

		inline T *begin() { return (T*)this; }
		inline T *end() { return begin() + size(); }
		inline const T *begin() const { return (T*)this; }
		inline const T *end() const { return begin() + size(); }

		inline array &zero() { mlib_ops::zero<_size, T>(begin()); return *this; }

		inline T &operator()(const int index) { return * (begin() + index); }
		inline const T &operator()(const int index) const { return * (begin() + index); }
		inline T &operator[](const int index) { return begin()[index]; }

		inline T normsq() const { return mlib_ops::normsq<_size, T>(begin()); }
		inline T norm() const { return mlib_ops::norm<_size, T>(begin()); }
		inline array & normalize() { return *this /= norm(); }

		inline array & operator  = (const array<base> &v) { mlib_ops::copy<_size, T>(begin(), v.begin()); return *this; }

		inline array & operator += (const array<base> &v) { mlib_ops::add<_size, T>(begin(), v.begin()); return *this; }
		inline array & operator -= (const array<base> &v) { mlib_ops::sub<_size, T>(begin(), v.begin()); return *this; }
		inline array & operator *= (const array<base> &v) { mlib_ops::mul<_size, T>(begin(), v.begin()); return *this; }
		inline array & operator /= (const array<base> &v) { mlib_ops::div<_size, T>(begin(), v.begin()); return *this; }

		inline array & operator *= (const T a) { mlib_ops::scale<_size, T>(begin(), a); return *this; }
		inline array & operator /= (const T a) { mlib_ops::iscale<_size, T>(begin(), a); return *this; }

		inline array operator + (const array<base> &v) const { return array<base>(*this) += v; }
		inline array operator - (const array<base> &v) const { return array<base>(*this) -= v; }
		inline array operator * (const array<base> &v) const { return array<base>(*this) *= v; }
		inline array operator / (const array<base> &v) const { return array<base>(*this) /= v; }
		
		friend std::ostream & operator << (std::ostream &out, array<base> &a)
		{
			for (int i = 0; i < _size; i++) out << a[i] << " ";
			return out;
		}

	};
}; // mlib

#endif // MLIB_ARRAY_H
