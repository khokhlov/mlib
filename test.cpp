#define CATCH_CONFIG_MAIN


#include "catch.hpp"
#include "mlib/mlib_vector.h"

#include <iostream>

using namespace std;

struct _v1 {
		typedef float type;
		float x;
	};
typedef mlib::array<mlib::basic_vector<_v1> > v1_t;

struct _v2 {
		typedef float type;
		float x, y;
	};
typedef mlib::array<mlib::basic_vector<_v2> > v2_t;


TEST_CASE(
		"v1",
		""
	 )
{
	v1_t v;
	REQUIRE(v.size() == 1);
	REQUIRE(v.x == Approx(0));
	REQUIRE(v.norm() == Approx(0));
	v1_t v1(5);
	REQUIRE(v1.x == Approx(5));
	v1_t v2(v1);
	REQUIRE(v1.x == Approx(v2.x));
	REQUIRE(v1(0) == Approx(v2(0)));
	REQUIRE(v1[0] == Approx(v2[0]));
	REQUIRE(v1.norm() == Approx(5));
	v1 *= 5;
	REQUIRE(v1.x == Approx(25));
	v1.normalize();
	REQUIRE(v1.x == Approx(1.0));
	v1 += v1;
	REQUIRE(v1.x == Approx(2.0));
	
	cout << endl;
	cout << v1 << endl;
	cout << v1[0] << endl;
}

TEST_CASE(
		"v2",
		""
	 )
{
	v2_t v;
	REQUIRE(v.size() == 2);
	REQUIRE(v.x == Approx(0));
	REQUIRE(v.norm() == Approx(0));
	v2_t v1(3, 4);
	REQUIRE(v1.x == Approx(3));
	v2_t v2(v1);
	REQUIRE(v1.x == Approx(v2.x));
	REQUIRE(v1(0) == Approx(v2(0)));
	REQUIRE(v1[0] == Approx(v2[0]));
	REQUIRE(v1.norm() == Approx(5));
	v1 *= 5;
	REQUIRE(v1.x == Approx(15));
	v1.normalize();
	v1 += v2;
	
	cout << v1 << endl;
	cout << v1[0] << endl;
}
