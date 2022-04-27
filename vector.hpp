#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <exception>
#include <iostream>
#include "utils.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template <class T>
	class MyIterator
	{
		public :
			typedef typename iterator_traits<T*>::iterator_category iterator_category;
			typedef typename iterator_traits<T*>::value_type        value_type;
			typedef typename iterator_traits<T*>::difference_type   difference_type;
			typedef typename iterator_traits<T*>::pointer           pointer;
			typedef typename iterator_traits<T*>::reference         reference;

			MyIterator() : ptr(NULL) {} // explicit : 자동으로 형변환 되는 것을 막음

			MyIterator(pointer p) : ptr(p) {}

			template <class Iter>
			MyIterator(const MyIterator<Iter>& it) : ptr(it.base()) {}

			MyIterator &operator=(const MyIterator& mit)
			{
				ptr = mit.base();
				return (*this);
			}

			template<class T1, class T2>
			friend bool	operator==(MyIterator<T1> const &lhs, MyIterator<T2> const &rhs);

			template<class T1, class T2>
			friend bool	operator!=(MyIterator<T1> const &lhs, MyIterator<T2> const &rhs);

			template<class T1, class T2>
			friend bool	operator<(MyIterator<T1> const &lhs, MyIterator<T2> const &rhs);

			template<class T1, class T2>
			friend bool	operator>(MyIterator<T1> const &lhs, MyIterator<T2> const &rhs);

			template<class T1, class T2>
			friend bool	operator<=(MyIterator<T1> const &lhs, MyIterator<T2> const &rhs);

			template<class T1, class T2>
			friend bool	operator>=(MyIterator<T1> const &lhs, MyIterator<T2> const &rhs);

			template<class T1, class T2>
			friend typename MyIterator<T1>::difference_type	operator-(MyIterator<T1> const &lhs, MyIterator<T2> const &rhs);

			pointer	base() const
			{
				return ptr;
			}

			reference operator*() const
			{
				return *ptr;
			}

			MyIterator operator+(difference_type n) const
			{
				MyIterator tmp = *this;
				tmp.ptr += n;
				return (tmp);
			}

			MyIterator& operator++()
			{
				ptr++;
				return *this;
			}

			MyIterator operator++(int)
			{
				MyIterator tmp = *this;
				ptr++;
				return tmp;
			}

			MyIterator& operator+=(difference_type n)
			{
				ptr += n;
				return *this;
			}

			MyIterator operator-(difference_type n) const
			{
				MyIterator tmp = *this;
				tmp.ptr -= n;
				return tmp;
			}

			MyIterator& operator--()
			{
				ptr--;
				return *this;
			}

			MyIterator operator--(int)
			{
				MyIterator tmp = *this;
				ptr--;
				return tmp;
			}

			MyIterator& operator-=(difference_type n)
			{
				ptr -= n;
				return *this;
			}

			pointer operator->() const
			{
				return ptr;
			}

			reference operator[](difference_type n) const
			{
				return (*(ptr + n));
			}

		protected :
			pointer	ptr;
	};

	// ************************************ MyIterator Relational operators ************************************

	template <class Iterator>
	bool operator==(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator<=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	bool operator>(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator>=(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator>
  	MyIterator<Iterator> operator+(typename MyIterator<Iterator>::difference_type n, const MyIterator<Iterator>& it)
	{
		return (it + n);
	}

	template <class Iterator>
  	typename MyIterator<Iterator>::difference_type operator-(const MyIterator<Iterator>& lhs, const MyIterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference; // 중첩의존이름
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::difference_type				difference_type;
			typedef typename allocator_type::size_type						size_type;
			typedef MyIterator<value_type>									iterator;
			typedef MyIterator<const value_type>							const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;


			// ************************************ 생성자 ************************************

			explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _begin(NULL), _size(0), _capacity(0) {}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _begin(NULL), _size(0), _capacity(0)
			{
				assign(n, val);
			}

			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL) : _alloc(alloc), _begin(NULL), _size(0), _capacity(0)
			{
				assign(first, last);
			}

			vector(const vector& x) : _begin(NULL), _size(0), _capacity(0)
			{
				*this = x;
			}

			vector&	operator=(const vector& x) {
				assign(x.begin(), x.end());
				return (*this);
			}

			// ************************************ 소멸자 ************************************

			~vector() { _alloc.deallocate(_begin, _capacity); }

			// ************************************ Capacity ************************************

			size_type	size() const
			{
				return (_size);
			}

			size_type	capacity() const
			{
				return (_capacity);
			}

			size_type	max_size() const
			{
				return (_alloc.max_size());
			}

			void 		resize(size_type n, value_type val = value_type())
			{
				if (n > max_size())
					throw std::length_error("cannot resize ft::vector larger than max_size()");
				if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_begin + i);
				}
				else
				{
					if (n > 2 * _capacity)
						reserve(n);
					else if (n < 2 * _capacity && n > _capacity)
						reserve(2 * _capacity);
					for (size_type i = _size; i < n; i++)
						_alloc.construct(_begin + i, val);
				}
				_size = n;
			}


			bool		empty() const
			{
				return(_size == 0);
			}

			void		reserve(size_type n)
			{
				if (n > _capacity)
				{
					if (n > max_size())
						throw (std::length_error("reserve : over max size"));
					pointer	tmp = _alloc.allocate(n);
					for(size_type i = 0; i < _size; ++i)
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

			reference		operator[](size_type n)
			{
				return (_begin[n]);
			}

			const_reference	operator[](size_type n) const
			{
				return (_begin[n]);
			}

			reference		at(size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("at : over size"));
				return (_begin[n]);
			}
			const_reference	at(size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("const at : over size"));
				return (_begin[n]);
			}

			reference		back()
			{
				return (*(_begin + _size - 1));
			}

			const_reference	back() const
			{
				return (*(_begin + _size - 1));
			}

			reference		front()
			{
				return (*(_begin));
			}

			const_reference	front() const
			{
				return (*(_begin));
			}

			// ************************************ Modifiers ************************************

			template<class InputIterator>
			void 	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				clear();
				size_type		n = 0;
				InputIterator	tmp = first;
				while (tmp++ != last)
					++n;
				if (n > _capacity)
					reserve(n);
				_size = n;
				InputIterator it2 = first;
				for(iterator it1 = begin(); it2 != last; it1++)
					_alloc.construct(&(*it1), *(it2++));
			}

			void	assign(size_type n, const value_type& val)
			{
				clear();
				if (n > _capacity)
					reserve(n);
				_size = n;
				for(iterator it = begin(); it != end(); ++it)
					_alloc.construct(&(*it), val);
			}

			void	pop_back()
			{
				resize(_size - 1);
			}

			void	push_back(const value_type& val)
			{
				resize(_size + 1, val);
			}

			iterator insert (iterator position, const value_type& val)
			{
				if (_capacity == 0)
					_capacity = 1;
				else if (_capacity < _size + 1 && _capacity * 2 > _size + 1)
					_capacity *= 2;
				else if (_capacity * 2 < _size + 1)
					_capacity = _size + 1;

				pointer tmp = _alloc.allocate(_capacity);
				difference_type diff = position - begin();

				std::uninitialized_copy(begin(), position, tmp); // tmp에다가 begin() ~ position까지 복사
				 // position 앞 까지 복사
				_alloc.construct(tmp + diff, val);
				std::uninitialized_copy(position, end(), tmp + diff + 1);

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, _size);
				_size++;
				_begin = tmp;

				return iterator(tmp + diff);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				if (_capacity == 0)
					_capacity = n;
				else if (_capacity < _size + n && _capacity * 2 > _size + n)
					_capacity *= 2;
				else if (_capacity * 2 < _size + n)
					_capacity = _size + n;

				pointer tmp = _alloc.allocate(_capacity);
				difference_type diff = position - begin();

				std::uninitialized_copy(begin(), position, tmp);
				std::uninitialized_fill(tmp + diff, tmp + diff + n, val); // tmp + diff ~ tmp + diff + n까지 val로 채우기
				std::uninitialized_copy(position, end(), tmp + diff + n);

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, _size);
				_size += n;
				_begin = tmp;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				if (_capacity * 2 > _size + std::distance(first, last))
					_capacity *= 2;
				else if (_size + std::distance(first, last) > _capacity)
					_capacity = _size + std::distance(first, last);

				pointer tmp = _alloc.allocate(_capacity);
				difference_type diff = position - begin();

				std::uninitialized_copy(begin(), position, tmp);
				size_type new_size = std::distance(first, last);
				size_type using_index = new_size;
				size_type i = 0;
				for (; using_index > 0; using_index--)
					_alloc.construct(tmp + diff + (i++), *(first++));
				std::uninitialized_copy(position, end(), tmp + diff + new_size);

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, _size);
				_size += new_size;
				_begin = tmp;
			}

			iterator erase(iterator position)
			{
				_alloc.destroy(&*position);
				for (iterator it = position; it != end(); it++)
				{
					_alloc.construct(&*it, *(it + 1));
					_alloc.destroy(&*it);
				}
				_size -= 1;
				return position;
			}

			iterator erase(iterator first, iterator last)
			{
				for (iterator it = first; it != last; it++)
					_alloc.destroy(&*it);
				for (iterator it = last; it != end(); it++)
				{
					_alloc.construct(&*(first + std::distance(last, it)), *it);
					_alloc.destroy(&*it);
				}
				_size -= std::distance(first, last);
				return first;
			}

			void	swap(vector& x)
			{
				allocator_type	tmp_alloc = _alloc;
				pointer			tmp_begin = _begin;
				size_type		tmp_size = _size;
				size_type		tmp_capacity = _capacity;

				_alloc = x._alloc;
				_begin = x._begin;
				_size = x._size;
				_capacity = x._capacity;

				x._alloc = tmp_alloc;
				x._begin = tmp_begin;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}

			void	clear()
			{
				resize(0);
			}

			// ************************************ Allocator ************************************

			allocator_type	get_allocator() const
			{
				return (_alloc);
			}

			// ************************************ Iterators ************************************

			iterator 				begin()
			{
				return (iterator(_begin));
			}

			const_iterator			begin() const
			{
				return (const_iterator(_begin));
			}

			iterator 				end()
			{
				return (iterator(_begin + _size));
			}

			const_iterator			end() const
			{
				return (const_iterator(_begin + _size));
			}

			reverse_iterator		rbegin()
			{
				return (reverse_iterator(_begin + _size));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(_begin + _size));
			}

			reverse_iterator		rend()
			{
				return (reverse_iterator(_begin));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(_begin));
			}

		private:
			allocator_type	_alloc;
			pointer			_begin;
			size_type		_size;
			size_type		_capacity;
	};

	template <typename T, class Alloc>
	bool  operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		else
			return false;
	};

	template <typename T, class Alloc>
	bool  operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	};

	template <typename T, class Alloc>
	void swap (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{
		lhs.swap(rhs);
	};

	template <typename T, class Alloc>
	bool  operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <typename T, class Alloc>
	bool  operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	};

	template <typename T, class Alloc>
	bool  operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	};

	template <typename T, class Alloc>
	bool  operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	};
}

#endif