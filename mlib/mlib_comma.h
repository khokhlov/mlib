/*
 * Author: Nikolay Khokhlov <k_h@inbox.ru>, (C) 2012
 */

#ifndef MLIB_COMMA_H
#define MLIB_COMMA_H

namespace mlib {
	template <class C>
	class comma_insert {
		public:
			template<class V>
			inline comma_insert(C &container, V const &value) : container(container) {
				counter = 0;
				container[counter] = value;
				counter++;
			}
			template<class V>
			inline comma_insert<C> operator,(V const &value) {
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
