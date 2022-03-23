#ifndef UTIL_HPP
#define UTIL_HPP

namespace ft
{
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {}
		template <typename A, typename B>
		pair(const pair<A, B> &_pair) {
			first = _pair.first;
			second = _pair.second;
		}
		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		pair &operator=(const pair& src)
		{
			this->first = src.first;
			this->second = src.second;
			return (*this);
		}
	};
}

#endif