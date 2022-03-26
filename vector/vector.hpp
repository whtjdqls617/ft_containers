#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <exception>
#include <iostream>
#include "../utils.hpp"
#include "../iterator_traits.hpp"

namespace ft
{
	template <typename Iterator>
	class reverse_iterator
	{
		public :
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;

			reverse_iterator() : _it() {} // explicit : 자동으로 형변환 되는 것을 막음 
			explicit reverse_iterator(iterator_type it) : _it(it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}

			template <typename U>
			reverse_iterator &operator=(const reverse_iterator<U>& rit) {
				_it = rit.base();
				return (*this);
			}
			
			iterator_type	base() const {
				return _it;
			}

			reference operator*() const {
				iterator_type tmp;
				tmp = _it;
				tmp--;
				return *tmp;
			}

			reverse_iterator operator+(difference_type n) const {
				return reverse_iterator(_it - n);
			}

			reverse_iterator& operator++() {
				_it--;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				_it--;
				return tmp;
			}
			
			reverse_iterator& operator+=(difference_type n) {
				_it -= n;
				return *this;
			}

			reverse_iterator operator-(difference_type n) const {
				return (reverse_iterator(*(_it + n)));
			}

			reverse_iterator& operator--() {
				_it++;
				return *this;
			}

			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				_it++;
				return tmp;
			}

			reverse_iterator& operator-=(difference_type n) {
				_it += n;
				return *this;
			}

			pointer operator->() const {
				iterator_type tmp = _it;
				return (*(--tmp));
			}

			reference operator[](difference_type n) const {
				return (*(_it - (n + 1)));
			}

		protected :
			iterator_type _it;
	};
	// ************************************ Relational operators ************************************

	template <class Iterator>
		bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
								return (lhs.base() == rhs.base());
							}
			
	template <class Iterator>
		bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
								return (lhs.base() != rhs.base());
							}

	template <class Iterator>
		bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
								return (lhs.base() < rhs.base());
							}

	template <class Iterator>
		bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
								return (lhs.base() <= rhs.base());
							}

	template <class Iterator>
		bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
								return (lhs.base() > rhs.base());
							}
			
	template <class Iterator>
		bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
								return (lhs.base() >= rhs.base());
							}
	template <typename Iterator>
  		reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
				  return (rev_it + n);
			}

	template <class Iterator>
  		typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				  return (rhs.base() - lhs.base());
			}
	
	template <typename T>
	class MyIterator : public ft::iterator<std::random_access_iterator_tag, T>
	{
		public :
			// iterator_traits는 반복자와 배열의 포인터를 구분하기 위해서 만들어진 것
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category iterator_category; // 나중에 어떤 타입인지 정보를 얻을 수 있게 하기위해 traits 사용
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type        value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type   difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer           pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference         reference;
		
			MyIterator() : ptr(NULL) {} // explicit : 자동으로 형변환 되는 것을 막음 
			explicit MyIterator(pointer p) : ptr(p) {}
			MyIterator(const MyIterator& it) : ptr(it.ptr) {}
			MyIterator &operator=(const MyIterator& mit) {
				ptr = mit.ptr;
				return (*this);
			}
			
			pointer	base() const {
				return ptr;
			}

			reference operator*() const {
				return *ptr;
			}

			MyIterator operator+(difference_type n) const {
				MyIterator tmp = *this;
				tmp.ptr += n;
				return (tmp);
			}

			MyIterator& operator++() {
				ptr++;
				return *this;
			}

			MyIterator operator++(int) {
				MyIterator tmp = *this;
				ptr++;
				return tmp;
			}
			
			MyIterator& operator+=(difference_type n) {
				ptr += n;
				return *this;
			}

			MyIterator operator-(difference_type n) const {
				MyIterator tmp = *this;
				tmp.ptr -= n;
				return tmp;
			}

			MyIterator& operator--() {
				ptr--;
				return *this;
			}

			MyIterator operator--(int) {
				MyIterator tmp = *this;
				ptr--;
				return tmp;
			}

			MyIterator& operator-=(difference_type n) {
				ptr -= n;
				return *this;
			}

			pointer operator->() const {
				return ptr;
			}

			reference operator[](difference_type n) const {
				return (*(ptr + n));
			}


		protected :
			pointer	ptr;
	};

	// ************************************ Relational operators ************************************

	template <class Iterator>
	bool operator==(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
		}
			
	template <class Iterator>
	bool operator!=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
		}

	template <class Iterator>
	bool operator<(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
		}

	template <class Iterator>
	bool operator<=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
		}

	template <class Iterator>
	bool operator>(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
		}
			
	template <class Iterator>
	bool operator>=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
		}

	template <typename Iterator>
  	MyIterator<Iterator> operator+(typename MyIterator<Iterator>::difference_type n, const MyIterator<Iterator>& it) {
		return (it + n);
		}

	template <class Iterator>
  	typename MyIterator<Iterator>::difference_type operator- (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
		return (lhs.base() - rhs.base());
		}

	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public :
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::size_type size_type;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::MyIterator<pointer> iterator;
			typedef ft::MyIterator<const_pointer> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			// ************************************ 생성자 ************************************

			// default - empty container constructor
			// allocator는 디폴트만 사용하기 때문에 뒤에 = 이렇게 표현
			explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _begin(NULL), _size(0), _capacity(0) {}

			// fill - Constructs a container with n elements. Each element is a copy of val. -> vector에 n사이즈 만큼 value를 채우는 생성자
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _begin(NULL), _size(0), _capacity(0) {
				assign(n, val);
			}

			// range - Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : _alloc(alloc), _begin(NULL), _size(0), _capacity(0) {
				assign(first, last);
			} // TODO : about Iterator

			// copy - Constructs a container with a copy of each of the elements in x, in the same order.

			vector(const vector& x) : _begin(NULL), _size(0), _capacity(0) {
				*this = x;
			}

			vector& operator=(const vector& x) {
				assign(x.begin(), x.end());
				return *this;
			}

			// ************************************ 소멸자 ************************************
			~vector() {
				_alloc.deallocate(_begin, _capacity);
			}

			// ************************************ Capacity ************************************
			size_type size() const {
				return (_size);
			}

			size_type capacity() const {
				return (_capacity);
			}

			size_type max_size() const {
				return (_alloc.max_size());
			}

			void resize(size_type n, value_type val = value_type()) {
				if (n > _capacity * 2)
					reserve(n);
				else if (n > _capacity)
					reserve(_capacity * 2);
				if (n > _size)
				{
					for (size_type i = _size; i < n; i++)
						_alloc.construct(_begin + i, val);
				}
				else
				{
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_begin + i);
				}
				_size = n;
			}

			bool empty() const {
				if (size())
					return (false);
				return (true);
			}

			void reserve(size_type n){
				if (n > _capacity)
				{
					if (n > max_size())
						throw(std::length_error("Cannot create ft::vector"));
					pointer tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(tmp + i, _begin[i]);
						_alloc.destroy(_begin + i);
					}
					_alloc.deallocate(_begin, _capacity);
					_begin = tmp;
					_capacity = n;
				}
			}

			// ************************************ Element Access ************************************

			reference operator[](size_type n) {
				return (_begin[n]);
			}

			const_reference operator[](size_type n) const {
				return (_begin[n]);
			}

			reference at(size_type n) { // abort 뜨는게 맞는거였나? 기억이 안남..ㅎ
				if (n >= size()) {
					throw std::out_of_range("Vector::at");
				}
				else
					return (_begin[n]);
			}

			const_reference at(size_type n) const {
				if (n >= size())
				{
					throw std::out_of_range("Vector::at");
				}
				else
					return (_begin[n]);
			}

			reference back() {
				return (*(_begin + _size - 1));
			}

			const_reference back() const {
				return (*(_begin + _size - 1));
			}

			reference front() {
				return (*_begin);
			}

			const_reference front() const {
				return (*_begin);
			}

			// ************************************ Modifiers ************************************

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				resize(0);
				size_type n = 0;
				InputIterator tmp = first;
				while (tmp++ != last)
					n++;
				resize(n);
				InputIterator it2 = first;
				for (iterator it1 = begin(); it2 != last; ++it1)
				{
					_alloc.construct(&(*it1), *it2);
					it2++;
				}
			}
			
			void assign(size_type n, const value_type& val)
			{
				resize(0);
				resize(n);
				for(iterator it = begin(); it != end(); it++)
					_alloc.construct(&(*it), val);
			}

			void pop_back() {
				if (size())
					resize(_size - 1);
			}

			void push_back (const value_type& val) {
				//할당했던거 풀어주고, 크기 늘려놓고 다시 대입?
				resize(_size + 1, val);
			}

			void swap(vector &x) {
				allocator_type tmp_alloc = _alloc;
				pointer tmp_begin = _begin;
				size_type tmp_size = _size;
				size_type tmp_capacity = _capacity;

				_alloc = x._alloc;
				_begin = x._begin;
				_size = x._size;
				_capacity = x._capacity;

				x._alloc = tmp_alloc;
				x._begin = tmp_begin;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}

			void clear() {
				resize(0);
			}

			// ************************************ Allocator ************************************

			allocator_type get_allocator() const {
				return _alloc;
			}

			// ************************************ Iterators ************************************

			iterator begin() {
				return iterator(_begin);
			}

			const_iterator begin() const {
				return const_iterator(_begin);
			}

			iterator end() {
				return iterator(_begin + _size);
			}

			const_iterator end() const {
				return const_iterator(_begin + _size);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(_begin + _size);
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(_begin + _size);
			}

			reverse_iterator rend() {
				return reverse_iterator(_begin);
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(_begin);
			}
			

		private :
			allocator_type	_alloc;
			pointer 		_begin;
			size_type		_size;
			size_type		_capacity;
			// ft::pair<pointer, allocator_type> _end_cap; // 두개의 객체(first, second)를 하나로 묶어주는 역할을 하는 struct로 데이터의 쌍을 표현할 때 사용
	};
}

#endif