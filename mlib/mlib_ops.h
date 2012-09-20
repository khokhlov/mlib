/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_OPS_H
#define MLIB_OPS_H

#include <cmath>

namespace mlib_ops {
	/*
	 * x = y.
	 */
	template <int size, typename T>
	inline void copy(T *x, const T *y) { for (int i = 0; i < size; i++) x[i] = y[i]; }

	/*
	 * x[i] = v.
	 */
	template <int size, typename T>
	inline void set(T *x, const T v) { for (int i = 0; i < size; i++) x[i] = v; }

	/*
	 * x[i] = 0.0.
	 */
	template <int size, typename T>
	inline void zero(T *x) { set<size, T>(x, 0); }

	/*
	 * x = a * x.
	 */
	template <int size, typename T>
	inline void scale(T *x, const T a) { for (int i = 0; i < size; i++) x[i] *= a; }

	/*
	 * x = x / a.
	 */
	template <int size, typename T>
	inline void iscale(T *x, const T a) { for (int i = 0; i < size; i++) x[i] /= a; }


	/*
	 * (x, y).
	 */
	template <int size, typename T>
	inline T dot(const T *x, const T *y) { T t = 0; for (int i = 0; i < size; i++) t += x[i] * y[i]; return t; }

	/*
	 * |x|^2.
	 */
	template <int size, typename T>
	inline T normsq(const T *x) { return dot<size, T>(x, x); }

	/*
	 * |x|.
	 */
	template <int size, typename T>
	inline T norm(const T *x) { return std::sqrt(normsq<size, T>(x)); }

	/*
	 * x += y.
	 */
	template <int size, typename T>
	inline void add(T *x, const T *y) { for (int i = 0; i < size; i++) x[i] += y[i]; }

	/*
	 * x -= y.
	 */
	template <int size, typename T>
	inline void sub(T *x, const T *y) { for (int i = 0; i < size; i++) x[i] -= y[i]; }

	/*
	 * x *= y.
	 */
	template <int size, typename T>
	inline void mul(T *x, const T *y) { for (int i = 0; i < size; i++) x[i] *= y[i]; }

	/*
	 * x /= y.
	 */
	template <int size, typename T>
	inline void div(T *x, const T *y) { for (int i = 0; i < size; i++) x[i] /= y[i]; }

	/*
	 * Matrix product.
	 * C = A * B
	 */
	template<int m, int n, int k, typename T>
	inline void mat_prod(const T *A, const T *B, T *C) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < k; j++) {
				T t = 0;
				for (int l = 0; l < n; l++) t += A[l + i * n] * B[j + k * l];
				C[i * k + j] = t;
			}
		}
	}
};

#endif // MLIB_OPS_H
