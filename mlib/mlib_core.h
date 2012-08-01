/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_CORE_H
#define MLIB_CORE_H

namespace mlib {
	template<bool> struct CompileTimeError;
	template<> struct CompileTimeError<true> {};
};

#define MLIB_STATIC_CHECK(expr) (mlib::CompileTimeError<(expr)!=0>())

#endif //MLIB_CORE_H
