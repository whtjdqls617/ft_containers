#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type 			difference_type; // 반복자끼리의 거리
		typedef typename Iterator::value_type 				value_type; // 반복자가 가리키는 대상체의 타입
		typedef typename Iterator::pointer 					pointer;
		typedef typename Iterator::reference 				reference;
		typedef typename Iterator::iterator_category 		iterator_category; // 반복자의 종류를 지정
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t									difference_type;
		typedef T											value_type;
		typedef	T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t									difference_type;
		typedef T											value_type;
		typedef	const T*									pointer;
		typedef const T&									reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};
}

#endif