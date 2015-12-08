#define CATCH_CONFIG_MAIN


#include "catch.hpp"
#include "mlib/mlib_matrix.h"
#include "mlib/mlib_vector.h"

#include <iostream>

using namespace std;

struct _v1 {
		typedef float type;
		float x1;
	};
typedef mlib::matrix<mlib::basic_vector<_v1> > v1_t;

struct _v2 {
		typedef float type;
		float x1, y1;
	};
struct _v22 {
		typedef float type;
		float x1, y1;
	};
typedef mlib::matrix<mlib::basic_vector<_v2> > v2_t;
typedef mlib::matrix<mlib::basic_vector<_v22> > v22_t;

template <int N>
struct aN {
	typedef float type;
	type a[N];
};

TEST_CASE(
		"v1",
		""
	 )
{
	v1_t v;
	REQUIRE(v.size() == 1);
	REQUIRE(v.x() == Approx(0));
	REQUIRE(v.norm() == Approx(0));
	v1_t v1(5);
	REQUIRE(v1.x() == Approx(5));
	v1_t v2(v1);
	REQUIRE(v1.x() == Approx(v2.x()));
	REQUIRE(v1(0) == Approx(v2(0)));
	REQUIRE(v1[0] == Approx(v2[0]));
	REQUIRE(v1.norm() == Approx(5));
	v1 *= 5;
	REQUIRE(v1.x() == Approx(25));
	v1.normalize();
	REQUIRE(v1.x() == Approx(1.0));
	v1 += v1;
	REQUIRE(v1.x() == Approx(2.0));
	REQUIRE(v1.isvector());
	v1.x() = 5.0;
	REQUIRE(v1.x() == Approx(5.0));
	REQUIRE(v1.i() == Approx(5.0));
}

TEST_CASE(
		"matrix",
		"transpose"
	 )
{
	mlib::matrix<aN<6>, 2, 3> m1;
	m1 << 1, 2, 3,
		4, 5, 6;
	cout << m1 << endl;
	cout << m1.tr() << endl;
	cout << m1.isvector() << endl;
}


TEST_CASE(
		"v2",
		""
	 )
{
	v2_t v;
	REQUIRE(v.size() == 2);
	REQUIRE(v.x() == Approx(0));
	REQUIRE(v.norm() == Approx(0));
	v2_t v1(3, 4);
	REQUIRE(v1.x() == Approx(3));
	v2_t v2(v1);
	REQUIRE(v1.x() == Approx(v2.x()));
	REQUIRE(v1(0) == Approx(v2(0)));
	REQUIRE(v1[0] == Approx(v2[0]));
	REQUIRE(v1.norm() == Approx(5));
	v1 *= 5;
	REQUIRE(v1.x() == Approx(15));
	v1.normalize();
	v1 += v2;
	
	cout << v1.rows() << endl;
	cout << v1.tr().rows() << endl;
	
	v2_t d = v1 - v2;
	REQUIRE(d.x() == Approx(v1.x1 - v2.x1));
	REQUIRE(d.y() == Approx(v1.y1 - v2.y1));
}

TEST_CASE(
	"dot",
	""
	)
{
	mlib::matrix<mlib::matrix_container<float, 3>, 1, 3> v1, v2;
	v1 << 1, 2, 3;
	v2 << -1, 3, -2;
	cout << v1 << endl;
	cout << v2 << endl;
	REQUIRE(v1.dot(v2) == Approx(-1));
}

TEST_CASE(
	"prod",
	""
	)
{
	mlib::matrix<mlib::matrix_container<float, 6>, 2, 3> A;
	A << 1, 2, 3, 4, 5, 6;
	mlib::matrix<mlib::matrix_container<float, 3>, 3, 1> x;
	x << 1, 1, 1;
	mlib::matrix<mlib::matrix_container<float, 2>, 1, 2> b;
	b = A.prod(x);
	REQUIRE(b[0] == Approx(6));
	REQUIRE(b[1] == Approx(15));
}

TEST_CASE(
	"LU",
	""
	)
{
	mlib::matrix<mlib::matrix_container<float, 9>, 3, 3> A, LU, L, U;
	A << 3, 6, -9,
	     2, 5, -3,
	     -4, 1, 10;
	LU = A.LU();
	L = LU.L();
	L(0, 0) = L(1, 1) = L(2, 2) = 1.0;
	U = LU.U();
	REQUIRE((L.prod(U) - A).norm() == Approx(0));
}

TEST_CASE(
	"det",
	""
	)
{
	mlib::matrix<mlib::matrix_container<float, 9>, 3, 3> A;
	A << -2, 2, 3,
	     -1, 1, 3,
	     2, 0, -1;
	cout << A.LU() << endl;
	//REQUIRE(A.det() == Approx(6));
}

#ifdef USE_LAPACK
TEST_CASE(
	"eigenproblem",
	""
	)
{
	mlib::matrix<mlib::matrix_container<float, 4>, 2, 2> A, R, L;
	mlib::matrix<mlib::matrix_container<float, 2>, 2, 1> wr, wi;
	A << 0, 1e-3,
	     3e3*3e3*1e3, 0;
	A.eigenproblem(wr.begin(), wi.begin(), R.begin(), L.begin());
	REQUIRE(wr[0] == Approx(3e3));
	REQUIRE(wr[1] == Approx(-3e3));
}
#endif
