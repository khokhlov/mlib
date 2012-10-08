/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_ARRAY_H
#define MLIB_ARRAY_H

#include <iostream>

#include "mlib_ops.h"
#include "mlib_core.h"
#include "mlib_comma.h"

#define MATRIX_CHECK_SIZE MLIB_STATIC_CHECK(_cols * _rows == m1 * n1);

namespace mlib {
	template <typename T, int size>
	struct matrix_container {
		typedef T type;
		type a[size];
	};

	template <class base, int m = base::_rows, int n = base::_cols>
	struct matrix : public base {
		//TODO: add check (size == m * n)
		typedef typename base::type T;
		enum { _size = sizeof(base) / sizeof(T), };
		enum { _rows = m, };
		enum { _cols = n, };
		enum { _isvector = ((n == 1) || (m == 1)), };
		enum { _issq = (m == n), };
		
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
		matrix(const cart_dir &ind) {
			MLIB_DYNAMIC_CHECK(_size > ind);
			zero();
			begin()[ind] = 1.0;
		}

		template <class base1, int m1, int n1>
		matrix(const matrix<base1, m1, n1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::copy<_size, T>(begin(), v.begin());
		}

		inline static int size() { return _size; }
		inline static int rows() { return _rows; }
		inline static int cols() { return _cols; }
		inline static int isvector() { return _isvector; }

		inline T *begin() { return (T*)this; }
		inline T *end() { return begin() + size(); }
		inline const T *begin() const { return (T*)this; }
		inline const T *end() const { return begin() + size(); }

		inline matrix &zero() { mlib_ops::zero<_size, T>(begin()); return *this; }
		inline matrix &null() { return zero(); }

		inline T &operator()(const int index) { return * (begin() + index); }
		inline const T &operator()(const int index) const { return * (begin() + index); }
		inline T &operator[](const int index) { return begin()[index]; }

		inline T &operator()(const int i, const int j) { return * (begin() + i * _cols + j); }
		inline const T &operator()(const int i, const int j) const { return * (begin() + i * _cols + j); }

		inline T normsq() const { return mlib_ops::normsq<_size, T>(begin()); }
		inline T norm() const { return mlib_ops::norm<_size, T>(begin()); }
		inline matrix & normalize() { return *this /= norm(); }

		template <class base1, int m1, int n1>
		inline matrix & operator = (const matrix<base1, m1, n1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::copy<_size, T>(begin(), v.begin()); return *this;
		}

		template <class base1, int m1, int n1>
		inline matrix & operator += (const matrix<base1, m1, n1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::add<_size, T>(begin(), v.begin()); return *this;
		}
		template <class base1, int m1, int n1>
		inline matrix & operator -= (const matrix<base1, m1, n1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::sub<_size, T>(begin(), v.begin()); return *this;
		}
		template <class base1, int m1, int n1>
		inline matrix & operator *= (const matrix<base1, m1, n1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::mul<_size, T>(begin(), v.begin()); return *this;
		}
		template <class base1, int m1, int n1>
		inline matrix & operator /= (const matrix<base1, m1, n1> &v) {
			MATRIX_CHECK_SIZE;
			mlib_ops::div<_size, T>(begin(), v.begin()); return *this;
		}

		inline matrix & operator *= (const T a) { mlib_ops::scale<_size, T>(begin(), a); return *this; }
		inline matrix & operator /= (const T a) { mlib_ops::iscale<_size, T>(begin(), a); return *this; }

		template <class base1, int m1, int n1>
		inline matrix operator + (const matrix<base1, m1, n1> &v) const {
			MATRIX_CHECK_SIZE;
			return matrix<base, m, n>(*this) += v;
		}
		template <class base1, int m1, int n1>
		inline matrix operator - (const matrix<base1, m1, n1> &v) const {
			MATRIX_CHECK_SIZE;
			return matrix<base, m, n>(*this) -= v;
		}
		template <class base1, int m1, int n1>
		inline matrix operator * (const matrix<base1, m1, n1> &v) const {
			MATRIX_CHECK_SIZE;
			return matrix<base, m, n>(*this) *= v;
		}
		template <class base1, int m1, int n1>
		inline matrix operator / (const matrix<base1, m1, n1> &v) const {
			MATRIX_CHECK_SIZE;
			return matrix<base, m, n>(*this) /= v;
		}
		
		friend std::ostream & operator << (std::ostream &out, const matrix<base, m, n> &a) {
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
		inline matrix<base, n, m> tr() {
			matrix<base, n, m> a;
			for (int i = 0; i < _rows; i++) {
				for (int j = 0; j < _cols; j++) {
					a(j, i) = (*this)(i, j);
				}
			}
			return a;
		}

		/*
		 * Dot product.
		 */
		template <class base1, int m1, int n1>
		inline T dot(const matrix<base1, m1, n1> &v) {
			MATRIX_CHECK_SIZE;
			MLIB_STATIC_CHECK(_isvector);
			MLIB_STATIC_CHECK((matrix<base1, m1, n1>::_isvector));
			return mlib_ops::dot<_size, T>(begin(), v.begin());
		}
		
		/*
		 * Comma-initializer operator.
		 * matrix m;
		 * m << 1, 2, 3;
		 */
		template<class V>
		inline comma_insert<matrix> operator << (V const &value) {
			return comma_insert<matrix>(*this, value);
		}

		/*
		 * Matrix product.
		 */
		template <class base1, int m1, int n1>
		inline matrix<matrix_container<T, m * n1>, m, n1> prod(const matrix<base1, m1, n1> &v) {
			MLIB_STATIC_CHECK(n == m1);
			matrix<matrix_container<T, m * n1>, m, n1> mat;
			mlib_ops::mat_prod<m, n, n1>(begin(), v.begin(), mat.begin());
			return mat;
		}
		
		inline matrix LU() {
			MLIB_STATIC_CHECK(_issq);
			matrix lu;
			for (int i = 0; i < n; i++) lu(0, i) = (*this)(0, i);
			for (int i = 1; i < n; i++) lu(i, 0) = (*this)(i, 0) / lu(0, 0);
			for (int i = 1; i < n; i++) {
				for (int j = i; j < n; j++) {
					T t = 0;
					for (int k = 0; k < i; k++) t += lu(i, k) * lu(k, j);
					lu(i, j) = (*this)(i, j) - t;
				}
				for (int j = i + 1; j < n; j++) {
					T t = 0;
					for (int k = 0; k < i; k++) t += lu(j, k) * lu(k, i);
					lu(j, i) = ((*this)(j, i) - t) / lu(i, i);
				}
			}
			return lu;
		}
		
		inline matrix L() {
			MLIB_STATIC_CHECK(_issq);
			matrix l;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < i + 1; j++) {
					l(i, j) = (*this)(i, j);
					if (i != j) l(j, i) = 0.0;
				}
			}
			return l;
		}
		inline matrix U() {
			MLIB_STATIC_CHECK(_issq);
			matrix u;
			for (int i = 0; i < m; i++) {
				for (int j = i; j < n; j++) {
					u(i, j) = (*this)(i, j);
					if (i != j) u(j, i) = 0.0;
				}
			}
			return u;
		}

		/*
		 * Determinant.
		 */
		inline T det() {
			MLIB_STATIC_CHECK(_issq);
			matrix lu = LU();
			T t = 0;
			for (int i = 0; i < n; i++) t *= lu(i, i);
			return t;
		}
		
		/*
		 * Eigenproblem.
		 */
		inline void eigenproblem(T *wr, T *wi, T *vl, T * vr) {
			MLIB_STATIC_CHECK(_issq);
			mlib_ops::eigenproblem<n>(begin(), wr, wi, vl, vr);
		}
	};
}; // mlib

#endif // MLIB_ARRAY_H
