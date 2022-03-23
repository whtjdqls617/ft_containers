#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <exception>
#include <iostream>
#include "util.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public :
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			// typedef implementation-defined iterator;
			// typedef implementation-defined const_iterator;
			typedef typename allocator_type::size_type size_type;
			typedef typename allocator_type::difference_type difference_type;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			// typedef std::reverse_iterator<iterator> reverse_iterator;
			// typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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

		private :
			pointer _begin;
			pointer _end;
			ft::pair<pointer, allocator_type> _end_cap; // 두개의 객체(first, second)를 하나로 묶어주는 역할을 하는 struct로 데이터의 쌍을 표현할 때 사용
	};
}

#endif