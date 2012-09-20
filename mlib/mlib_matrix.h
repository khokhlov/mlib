/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_ARRAY_H
#define MLIB_ARRAY_H

#include <iostream>

#include "mlib_ops.h"
#include "mlib_core.h"

#define MATRIX_CHECK_SIZE MLIB_STATIC_CHECK(_cols * _rows == nrows1 * ncols1);

namespace mlib {
	template <class base, int nrows = base::_rows, int ncols = base::_cols>
	struct matrix : public base {
		//TODO: add check (size == nrows * ncols)
		typedef typename base::type T;
		enum { _size = sizeof(base) / sizeof(T), };
		enum { _rows = nrows, };
		enum { _cols = ncols, };
		
		matrix() : base() {}
		matrix(const T x) {
			MLIB_STATIC_CHECK(_size == 1);
			begin()[0] = x;
		}
		matrix(const T x, const T y) {
			MLIB_STATIC_CHECK(_size == 2);
			begin()[0] = x;
			begin()[1] = y;
		}
		matrix(const T x, const T y, const T z) {
			MLIB_STATIC_CHECK(_size == 3);
			begin()[0] = x;
			begin()[1] = y;
			begin()[2] = z;
		}

		template <class base1, int nrows1, int ncols1>
		matrix(const matrix<base1, nrows1, ncols1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::copy<_size, T>(begin(), v.begin());
		}

		inline int size() const { return _size; }
		inline int rows() const { return _rows; }
		inline int cols() const { return _cols; }

		inline T *begin() { return (T*)this; }
		inline T *end() { return begin() + size(); }
		inline const T *begin() const { return (T*)this; }
		inline const T *end() const { return begin() + size(); }

		inline matrix &zero() { mlib_ops::zero<_size, T>(begin()); return *this; }

		inline T &operator()(const int index) { return * (begin() + index); }
		inline const T &operator()(const int index) const { return * (begin() + index); }
		inline T &operator[](const int index) { return begin()[index]; }

		inline T &operator()(const int m, const int n) { return * (begin() + n * _rows + m); }
		inline const T &operator()(const int m, const int n) const { return * (begin() + n * _rows + m); }

		inline T normsq() const { return mlib_ops::normsq<_size, T>(begin()); }
		inline T norm() const { return mlib_ops::norm<_size, T>(begin()); }
		inline matrix & normalize() { return *this /= norm(); }

		template <class base1, int nrows1, int ncols1>
		inline matrix & operator = (const matrix<base1, nrows1, ncols1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::copy<_size, T>(begin(), v.begin()); return *this;
		}

		template <class base1, int nrows1, int ncols1>
		inline matrix & operator += (const matrix<base1, nrows1, ncols1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::add<_size, T>(begin(), v.begin()); return *this;
		}
		template <class base1, int nrows1, int ncols1>
		inline matrix & operator -= (const matrix<base1, nrows1, ncols1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::sub<_size, T>(begin(), v.begin()); return *this;
		}
		template <class base1, int nrows1, int ncols1>
		inline matrix & operator *= (const matrix<base1, nrows1, ncols1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::mul<_size, T>(begin(), v.begin()); return *this;
		}
		template <class base1, int nrows1, int ncols1>
		inline matrix & operator /= (const matrix<base1, nrows1, ncols1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::div<_size, T>(begin(), v.begin()); return *this;
		}

		inline matrix & operator *= (const T a) { mlib_ops::scale<_size, T>(begin(), a); return *this; }
		inline matrix & operator /= (const T a) { mlib_ops::iscale<_size, T>(begin(), a); return *this; }

		template <class base1, int nrows1, int ncols1>
		inline matrix operator + (const matrix<base1, nrows1, ncols1> &v) const {
			MATRIX_CHECK_SIZE;
			return matrix<base, nrows, ncols>(*this) += v;
		}
		template <class base1, int nrows1, int ncols1>
		inline matrix operator - (const matrix<base1, nrows1, ncols1> &v) const {
			MATRIX_CHECK_SIZE;
			return matrix<base, nrows, ncols>(*this) -= v;
		}
		template <class base1, int nrows1, int ncols1>
		inline matrix operator * (const matrix<base1, nrows1, ncols1> &v) const {
			MATRIX_CHECK_SIZE;
			return matrix<base, nrows, ncols>(*this) *= v;
		}
		template <class base1, int nrows1, int ncols1>
		inline matrix operator / (const matrix<base1, nrows1, ncols1> &v) const {
			MATRIX_CHECK_SIZE;
			return matrix<base, nrows, ncols>(*this) /= v;
		}
		
		friend std::ostream & operator << (std::ostream &out, const matrix<base, nrows, ncols> &a) {
			for (int i = 0; i < _rows; i++) {
				for (int j = 0; j < _cols; j++) {
					out << a(i, j) << " ";
				}
				out << "\n";
			}
			return out;
		}
		/*
		 * Transpose matrix.
		 */
		inline matrix<base, ncols, nrows> tr() {
			matrix<base, ncols, nrows> a;
			for (int i = 0; i < _rows; i++) {
				for (int j = 0; j < _cols; j++) {
					a(j, i) = (*this)(i, j);
				}
			}
			return a;
		}

	};
}; // mlib

#endif // MLIB_ARRAY_H
