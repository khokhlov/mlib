/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_CORE_H
#define MLIB_CORE_H

#include <stdexcept>

namespace mlib {
	template<bool> struct CompileTimeError;
	template<> struct CompileTimeError<true> {};
	enum cart_dir {
		X = 0,
		Y,
		Z,
		ALL_DIRS
	};
};


#define MLIB_STATIC_CHECK(expr) (mlib::CompileTimeError<(expr)!=0>())
#define MLIB_DYNAMIC_CHECK(expr) if(!(expr)) throw std::logic_error(#expr)

#endif //MLIB_CORE_H
