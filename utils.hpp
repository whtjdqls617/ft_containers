#ifndef UTILS_HPP
#define UTILS_HPP
#include <type_traits>

namespace ft
{
	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1!=last1)
		{
			if (first2==last2 || comp(*first2 < *first1))
				return false;
			else if (comp(*first1 < *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template <class InputIterator1, class InputIterator2>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1)
		{
    		if (!(*first1 == *first2))
      			return false;
    		++first1; ++first2;
  		}
  		return true;
	};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1)
		{
    		if (!pred(*first1, *first2))
      			return false;
    		++first1; ++first2;
  		}
  		return true;
	};

	template <bool is_integral, typename T>
	struct is_integral_base
	{
		typedef T type;
		const static bool value = is_integral;
	};

	template <class T>
	struct is_integral : public is_integral_base<false, void> {};

	template <>
	struct is_integral<bool> : public is_integral_base<true, bool> {};

	template <>
	struct is_integral<char> : public is_integral_base<true, char> {};

	template <>
	struct is_integral<char16_t> : public is_integral_base<true, char16_t> {};

	template <>
	struct is_integral<char32_t> : public is_integral_base<true, char32_t> {};

	template <>
	struct is_integral<wchar_t> : public is_integral_base<true, wchar_t> {};

	template <>
	struct is_integral<signed char> : public is_integral_base<true, signed char> {};

	template <>
	struct is_integral<short int> : public is_integral_base<true, short int> {};

	template <>
	struct is_integral<int> : public is_integral_base<true, int> {};

	template <>
	struct is_integral<long int> : public is_integral_base<true, long int> {};

	template <>
	struct is_integral<long long int> : public is_integral_base<true, long long int> {};

	template <>
	struct is_integral<unsigned char> : public is_integral_base<true, unsigned char> {};

	template <>
	struct is_integral<unsigned short int> : public is_integral_base<true, unsigned short int> {};

	template <>
	struct is_integral<unsigned int> : public is_integral_base<true, unsigned int> {};

	template <>
	struct is_integral<unsigned long int> : public is_integral_base<true, unsigned long int> {};

	template <>
	struct is_integral<unsigned long long int> : public is_integral_base<true, unsigned long long int> {};

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

	template <typename T1, typename T2>
	pair<T1, T2> make_pair (T1 a, T2 b)
	{
		return (pair<T1, T2> (a, b));
	}
}

#endif