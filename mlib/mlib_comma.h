/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_COMMA_H
#define MLIB_COMMA_H

#include "mlib_core.h"

namespace mlib {
	template <class C>
	class comma_insert {
		public:
			template<class V>
			inline comma_insert(C &container, V const &value) : container(container) {
				MLIB_DYNAMIC_CHECK(container.size() > 0 && "Container size have to be more 0");
				counter = 0;
				container[counter] = value;
				counter++;
			}
			template<class V>
			inline comma_insert<C> operator,(V const &value) {
				MLIB_DYNAMIC_CHECK(container.size() > counter && "Invalid comma-insert range.");
				container[counter] = value;
				counter++;
				return *this;
			}
		private:
			C &container;
			int counter;
	};
}; // mlib

#endif // MLIB_COMMA_H
