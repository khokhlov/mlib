#define CATCH_CONFIG_MAIN


#include "catch.hpp"
#include "mlib/mlib_vector.h"

struct _v1 {
		typedef float type;
		float x;
	};
typedef mlib::basic_vector<_v1> v1_t;

TEST_CASE(
		"v1",
		""
	 )
{
	v1_t v;
	REQUIRE(v.dim() == 1);
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
}
