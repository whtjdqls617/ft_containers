#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <memory> // allocator
#include "utils.hpp"
#include "tree.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	// std::less => 첫번째 매개변수가 두번째 매개변수보다 작으면 true 반환
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public :
			typedef Key							key_type;
			typedef T							mapped_type;
			typedef ft::pair<const Key, T>		value_type;
			typedef Compare 					key_compare;
			typedef Alloc						allocator_type;
			typedef ptrdiff_t					difference_type;
			typedef size_t						size_type;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool 				result_type;
					typedef value_type 			first_argument_type;
					typedef value_type 			second_argument_type;

					bool operator()(const value_type &x, const value_type &y) const
					{
						return comp(x.first, y.first);
					}
			};

			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::tree_iterator<value_type>					iterator;
			typedef ft::tree_const_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;


			// Constructor

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(Tree<value_type, key_compare, allocator_type>()), _key_compare(comp), _alloc(alloc)
			{}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(Tree<value_type, key_compare, allocator_type>()), _key_compare(comp), _alloc(alloc)
			{
				insert(first, last);
			}

			map(const map &x)
			{
				*this = x;
			}

			// Destructor

			~map() {}

			// Operation (Member func)

			map &operator=(const map &x)
			{
				_tree = x._tree;
				_key_compare = x._key_compare;
				_alloc = x._alloc;
				return (*this);
			}

			// Iterator

			iterator begin()
			{
				return (_tree.begin());
			}
			const_iterator begin() const
			{
				return (_tree.begin());
			}

			iterator end()
			{
				return (_tree.end());
			}
			const_iterator end() const
			{
				return (_tree.end());
			}

			reverse_iterator rbegin()
			{
				return (_tree.rbegin());
			}

			const_reverse_iterator rbegin() const
			{
				return (_tree.rbegin());
			}

			reverse_iterator rend()
			{
				return (_tree.rend());
			}

			const_reverse_iterator rend() const
			{
				return (_tree.rend());
			}

			// Capacity

			bool empty() const
			{
				if (_tree.countSize())
					return false;
				return true;
			}

			size_type size() const
			{
				return _tree.size();
			}

			size_type max_size() const
			{
				return _tree.max_size();
			}

			// Element access

			mapped_type &operator[](const key_type &k)
			{
				return ((*(_tree.insert(ft::make_pair(k, mapped_type()))).first).second);
			}

			// Modifiers

			pair<iterator, bool> insert(const value_type &val)
			{
				return (_tree.insert(val));
			}

			iterator insert(iterator position, const value_type &val)
			{
				return (_tree.insert(position, val));
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				return (_tree.insert(first, last));
			}

			void erase(iterator position)
			{
				return (_tree.erase(position));
			}

			size_type erase(const key_type &k)
			{
				return (_tree.erase(ft::make_pair(k, mapped_type())));
			}

			void erase(iterator first, iterator last)
			{
				return _tree.erase(first, last);
			}

			void swap(map &x)
			{
				return (_tree.swap(x._tree));
			}

			void clear()
			{
				return(_tree.clear());
			}

			// Observers

			key_compare key_comp() const
			{
				return (key_compare());
			}

			value_compare value_comp() const
			{
				return (value_compare(key_compare()));
			}

			// Operations

			iterator find(const key_type &k) // k = key
			{
				return _tree.find(ft::make_pair(k, mapped_type()));
			}

			const_iterator find(const key_type &k) const
			{
				return _tree.find(ft::make_pair(k, mapped_type()));
			}

			size_type count(const key_type &k) const
			{
				return (_tree.count(ft::make_pair(k, mapped_type())));
			}

			iterator lower_bound(const key_type &k) // 찾으려 하는 key값이 "없으면" key값보다 큰 것들 중에서 가장 작은 정수 값을 찾습니다.
			{
				iterator it = begin();
				for (; it != end(); it++)
				{
					if (_key_compare(it->first, k) == false)
						break;
				}
				return it;
			}

			const_iterator lower_bound(const key_type &k) const
			{
				const_iterator it = begin();
				for (; it != end(); it++)
				{
					if (_key_compare(it->first, k) == false)
						break;
				}
				return it;
			}

			iterator upper_bound(const key_type &k) // key값을 초과하는 가장 첫 번째 원소의 위치를 구하는 것
			{
				iterator it = begin();
				for (; it != end(); it++)
				{
					if (_key_compare(k, it->first) == true)
						break;
				}
				return it;
			}

			const_iterator upper_bound(const key_type &k) const
			{
				const_iterator it = begin();
				for (; it != end(); it++)
				{
					if (_key_compare(k, it->first) == true)
						break;
				}
				return it;
			}

			pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			pair<iterator, iterator> equal_range(const key_type &k) // 반환 값들이 갖는 범위는 [lower_bound, upper_bound)
			{
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			allocator_type get_allocator() const
			{
				return _alloc;
			}

		private:
			Tree<value_type, key_compare, allocator_type>	_tree;
			key_compare 									_key_compare;
			allocator_type 									_alloc;

	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		else
			return false;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif