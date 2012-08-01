/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_VECTOR_H
#define MLIB_VECTOR_H

#include <cmath>

#include "mlib_ops.h"
#include "mlib_core.h"

namespace mlib {
	template <class base>
	struct basic_vector : public base {
		typedef typename base::type T;
		enum {
			_dim = sizeof(base) / sizeof(T),
		};
		basic_vector() { zero(); }
		basic_vector(const basic_vector<base> &v) { mlib_ops::copy<_dim, T>(begin(), v.begin()); }
		basic_vector(const T x) {
			MLIB_STATIC_CHECK(_dim == 1);
			begin()[0] = x;
		}
		basic_vector(const T x, const T y) {
			MLIB_STATIC_CHECK(_dim == 2);
			begin()[0] = x;
			begin()[1] = y;
		}
		basic_vector(const T x, const T y, const T z) {
			MLIB_STATIC_CHECK(_dim == 3);
			begin()[0] = x;
			begin()[1] = y;
			begin()[2] = z;
		}

		inline int dim() const { return _dim; }
		inline int size() const { return dim(); }

		inline T *begin() { return (T*)this; }
		inline T *end() { return begin() + dim(); }
		inline const T *begin() const { return (T*)this; }
		inline const T *end() const { return begin() + dim(); }

		inline basic_vector &zero() { mlib_ops::zero<_dim, T>(begin()); return *this; }

		inline T &operator()(const int index) { return * (begin() + index); }
		inline const T &operator()(const int index) const { return * (begin() + index); }
		inline T &operator[](const int index) { return begin()[index]; }

		inline T normsq() const { return mlib_ops::normsq<_dim, T>(begin()); }
		inline T norm() const { return mlib_ops::norm<_dim, T>(begin()); }
		inline basic_vector & normalize() { return *this /= norm(); }

		inline basic_vector & operator  = (const basic_vector<base> &v) { mlib_ops::copy<_dim, T>(begin(), v.begin()); return *this; }

		inline basic_vector & operator += (const basic_vector<base> &v) { mlib_ops::add<_dim, T>(begin(), v.begin()); return *this; }
		inline basic_vector & operator -= (const basic_vector<base> &v) { mlib_ops::sub<_dim, T>(begin(), v.begin()); return *this; }
		inline basic_vector & operator *= (const basic_vector<base> &v) { mlib_ops::mul<_dim, T>(begin(), v.begin()); return *this; }
		inline basic_vector & operator /= (const basic_vector<base> &v) { mlib_ops::div<_dim, T>(begin(), v.begin()); return *this; }

		inline basic_vector & operator *= (const T a) { mlib_ops::scale<_dim, T>(begin(), a); return *this; }
		inline basic_vector & operator /= (const T a) { mlib_ops::iscale<_dim, T>(begin(), a); return *this; }

		inline basic_vector operator + (const basic_vector<base> &v) const { return basic_vector<base>(*this) += v; }
		inline basic_vector operator - (const basic_vector<base> &v) const { return basic_vector<base>(*this) -= v; }
		inline basic_vector operator * (const basic_vector<base> &v) const { return basic_vector<base>(*this) *= v; }
		inline basic_vector operator / (const basic_vector<base> &v) const { return basic_vector<base>(*this) /= v; }
	};
}; // mlib

#endif // MLIB_VECTOR_H
