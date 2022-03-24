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

			reverse_iterator() : it(0) {} // explicit : 자동으로 형변환 되는 것을 막음 
			explicit reverse_iterator(iterator_type it) : it(it) {}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : it(rev_it.base()) {}

			template <typename U>
			reverse_iterator &operator=(const reverse_iterator<U>& rit) {
				it = rit.base();
				return (*this);
			}
			
			iterator_type	base() const {
				return it;
			}

			reference operator*() const {
				iterator_type tmp;
				tmp = it;
				tmp--;
				return *tmp;
			}

			// reverse_iterator operator+(difference_type n) const {
			// 	return reverse_iterator(base() - n);
			// }

			// reverse_iterator& operator++() {
			// 	ptr++;
			// 	return *this;
			// }

			// reverse_iterator operator++(int) {
			// 	reverse_iterator tmp(*this);
			// 	ptr++;
			// 	return tmp;
			// }
			
			reverse_iterator& operator+=(difference_type n) {
				it += n;
				return *this;
			}

			// reverse_iterator operator-(difference_type n) const {
			// 	return (reverse_iterator(*(ptr - n)));
			// }

			// reverse_iterator& operator--() {
			// 	ptr--;
			// 	return *this;
			// }

			// reverse_iterator operator--(int) {
			// 	reverse_iterator tmp(*this);
			// 	ptr--;
			// 	return tmp;
			// }

			// reverse_iterator& operator-=(difference_type n) {
			// 	return (*(ptr - n));
			// }

			// pointer operator->() const {
			// 	return ptr;
			// }

			// reference operator[](difference_type n) const {
			// 	return ptr[n];
			// }

			// ************************************ Relational operators ************************************

			// template <class Iterator>
			// friend bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			// 					return (lhs.base() == rhs.base());
			// 				}
			
			// template <class Iterator>
			// friend bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			// 					return (lhs.base() != rhs.base());
			// 				}

			// template <class Iterator>
			// friend bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			// 					return (lhs.base() < rhs.base());
			// 				}

			// template <class Iterator>
			// friend bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			// 					return (lhs.base() <= rhs.base());
			// 				}

			// template <class Iterator>
			// friend bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			// 					return (lhs.base() > rhs.base());
			// 				}
			
			// template <class Iterator>
			// friend bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			// 					return (lhs.base() >= rhs.base());
			// 				}
			// template <typename Iterator>
  			// friend reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) {
			// 	  reverse_iterator tmp = it;
			// 	  tmp += n;
			// 	  return (tmp);
			// }

			// template <class Iterator>
  			// friend typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			// 	  reverse_iterator tmp1 = lhs;
			// 	  reverse_iterator tmp2 = rhs;
			// 	  return (tmp1.base() - tmp2.base());
			// }

		protected :
			iterator_type it;
	};
	
	template <typename T>
	class MyIterator
	{
		public :
			// iterator_traits는 반복자와 배열의 포인터를 구분하기 위해서 만들어진 것
			typedef T                                                     		iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category iterator_category; // 나중에 어떤 타입인지 정보를 얻을 수 있게 하기위해 traits 사용
			typedef typename iterator_traits<iterator_type>::value_type        value_type;
			typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
			typedef typename iterator_traits<iterator_type>::pointer           pointer;
			typedef typename iterator_traits<iterator_type>::reference         reference;
		
			MyIterator() : ptr(0) {} // explicit : 자동으로 형변환 되는 것을 막음 
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
				return (tmp += n);
			}

			MyIterator& operator++() {
				ptr++;
				return *this;
			}

			MyIterator operator++(int) {
				MyIterator tmp(*this);
				ptr++;
				return tmp;
			}
			
			MyIterator& operator+=(difference_type n) {
				ptr += n;
				return *this;
			}

			MyIterator operator-(difference_type n) const {
				return (MyIterator(*(ptr - n)));
			}

			MyIterator& operator--() {
				ptr--;
				return *this;
			}

			MyIterator operator--(int) {
				MyIterator tmp(*this);
				ptr--;
				return tmp;
			}

			MyIterator& operator-=(difference_type n) {
				return (*(ptr - n));
			}

			pointer operator->() const {
				return ptr;
			}

			reference operator[](difference_type n) const {
				return ptr[n];
			}

			// ************************************ Relational operators ************************************

			template <class Iterator>
			friend bool operator==(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
								return (lhs.base() == rhs.base());
							}
			
			template <class Iterator>
			friend bool operator!=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
								return (lhs.base() != rhs.base());
							}

			template <class Iterator>
			friend bool operator<(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
								return (lhs.base() < rhs.base());
							}

			template <class Iterator>
			friend bool operator<=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
								return (lhs.base() <= rhs.base());
							}

			template <class Iterator>
			friend bool operator>(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
								return (lhs.base() > rhs.base());
							}
			
			template <class Iterator>
			friend bool operator>=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
								return (lhs.base() >= rhs.base());
							}
			template <typename Iterator>
  			friend MyIterator<Iterator> operator+(typename MyIterator<Iterator>::difference_type n, const MyIterator<Iterator>& it) {
				  MyIterator tmp = it;
				  tmp += n;
				  return (tmp);
			}

			template <class Iterator>
  			friend typename MyIterator<Iterator>::difference_type operator- (const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs) {
				  MyIterator tmp1 = lhs;
				  MyIterator tmp2 = rhs;
				  return (tmp1.base() - tmp2.base());
			}

		protected :
			pointer	ptr;
	};


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
			explicit vector(const allocator_type &alloc = allocator_type()) : _begin(NULL), _end(NULL), _end_cap() {}

			// fill - Constructs a container with n elements. Each element is a copy of val. -> vector에 n사이즈 만큼 value를 채우는 생성자
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
				_end_cap.second = alloc;
				_begin = _end_cap.second.allocate(n); // allocate가 첫번째 값의 주소 반환
				_end_cap.first = _begin + n; // 마지막 주소값
				_end = _begin;
				for (_end = _begin; _end < _end_cap.first; _end++)
				{
					_end_cap.second.construct(_end, val);
				}
			}

			// range - Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.

			// template <class InputIterator>
			// vector(InputIterator first, InputIterator last, const allocator_type & = allocator_type()); // TODO : about Iterator

			// copy - Constructs a container with a copy of each of the elements in x, in the same order.

			vector(const vector& x) {
				*this = x;
			}

			vector& operator=(const vector& x) {
				*this->_begin = x._begin;
				*this->_end = x._end;
				*this->_end_cap = x._end_cap;
				return (*this);
			}

			// ************************************ 소멸자 ************************************
			~vector() {
				clear();
				_end_cap.second.deallocate(_begin, capacity()); //
			}

			// ************************************ Capacity ************************************
			size_type size() const {
				return (_end - _begin);
			}

			size_type capacity() const {
				return size_type(_end_cap.first - _begin);
			}

			size_type max_size() const {
				return (_end_cap.second.max_size());
			}

			void resize(size_type n, value_type val = value_type()) {
				if (n < size()) {
					while (size() - n) {
						_end_cap.second.destroy(--_end);
					}
				}
				else {
					reserve(n);
					while (n - size()) {
						_end_cap.second.construct(_end++, val);
					}
				}
			}

			bool empty() const {
				if (size())
					return (false);
				return (true);
			}

			void reserve(size_type n){
				if (capacity() < n) {
					pointer old_begin = _begin;
					pointer old_end = _end;
					size_type old_size = size();
					size_type old_capacity = capacity();
					_begin = _end_cap.second.allocate(n);
					_end_cap.first = _begin + n;
					_end = _begin;
					while (old_begin != old_end)
					{
						_end_cap.second.construct(_end, *old_begin);
						_end_cap.second.destroy(old_begin);
						_end++;
						old_begin++;
					}
					_end_cap.second.deallocate(old_begin - old_size, old_capacity);
					_end_cap.first = _begin + capacity();
				}
			}

			// ************************************ Element Access ************************************

			reference operator[](size_type n) {
				return (*(_begin + n));
			}

			const_reference operator[](size_type n) const {
				return (*(_begin + n));
			}

			reference at(size_type n) { // abort 뜨는게 맞는거였나? 기억이 안남..ㅎ
				if (n >= size()) {
					throw std::out_of_range("Vector::at");
				}
				else
					return (*(_begin + n));
			}

			const_reference at(size_type n) const {
				if (n >= size())
				{
					throw std::out_of_range("Vector::at");
				}
				else
					return (*(_begin + n));
			}

			reference back() {
				return (*(_end - 1));
			}

			const_reference back() const {
				return (*(_end - 1));
			}

			reference front() {
				return (*_begin);
			}

			const_reference front() const {
				return (*_begin);
			}

			// ************************************ Modifiers ************************************

			void pop_back() {
				if (size())
					_end_cap.second.destroy(--_end);
			}

			void push_back (const value_type& val) {
				//할당했던거 풀어주고, 크기 늘려놓고 다시 대입?
				size_type length;
				length = this->size();
				if (length == 0)
					length = 1;
				else
					length *= 2;
				reserve(length);
				_end_cap.second.construct(_end++, val);
			}

			void swap(vector &x) {
				pointer tmp_begin = this->_begin;
				pointer tmp_end = this->_end;
				pointer tmp_end_cap_first = this->_end_cap.first;
				allocator_type	tmp_end_cap_second = this->_end_cap.second;

				this->_begin = x._begin;
				this->_end = x._end;
				this->_end_cap.first = x._end_cap.first;
				this->_end_cap.second = x._end_cap.second;

				x._begin = tmp_begin;
				x._end = tmp_end;
				x._end_cap.first = tmp_end_cap_first;
				x._end_cap.second = tmp_end_cap_second;
			}

			void clear() {
				for (_end = _begin; _end < _end_cap.first; _end++)
					_end_cap.second.destroy(_end);
			}

			// ************************************ Allocator ************************************

			allocator_type get_allocator() const {
				return _end_cap.second;
			}

			// ************************************ Iterators ************************************

			iterator begin() {
				return iterator(_begin);
			}

			const_iterator begin() const {
				return const_iterator(_begin);
			}

			iterator end() {
				return iterator(_end);
			}

			const_iterator end() const {
				return const_iterator(_end);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(_end);
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(_end);
			}

			reverse_iterator rend() {
				return reverse_iterator(_begin);
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(_begin);
			}
			

		private :
			pointer _begin;
			pointer _end;
			ft::pair<pointer, allocator_type> _end_cap; // 두개의 객체(first, second)를 하나로 묶어주는 역할을 하는 struct로 데이터의 쌍을 표현할 때 사용
	};
}

#endif