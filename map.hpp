#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <memory> // allocator
#include "utils.hpp"
#include "tree.hpp"

namespace ft
{
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
					value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
				public:
					typedef bool 	result_type;
					typedef 		value_type first_argument_type;
					typedef 		value_type second_argument_type;

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
			typedef ft::const_tree_iterator<value_type>				const_iterator;
			// typedef ft::reverse_iterator<iterator>					reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;


			// Constructor

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) {}

			// template <class InputIterator>
			// map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());

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

			// iterator begin();
			// const_iterator begin() const;

			// iterator end();
			// const_iterator end() const;

			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;

			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			// Capacity

			bool empty() const;

			size_type size() const
			{
				return _tree.size();
			}

			size_type max_size() const;

			// Element access

			mapped_type &operator[](const key_type &k);

			// Modifiers

			pair<iterator, bool> insert(const value_type &val)
			{
				return (_tree.insert(val));
			}

			// iterator insert(iterator position, const value_type &val);

			// template <class InputIterator>
			// void insert(InputIterator first, InputIterator last);

			// void erase(iterator position);

			size_type erase(const key_type &k);

			// void erase(iterator first, iterator last);

			void swap(map &x);

			void clear();

			// Observers

			key_compare key_comp() const;

			value_compare value_comp() const;

			// Operations

			// iterator find(const key_type &k);
			// const_iterator find(const key_type &k) const;

			size_type count(const key_type &k) const;

			// iterator lower_bound(const key_type &k);
			// const_iterator lower_bound(const key_type &k) const;

			// iterator upper_bound(const key_type &k);
			// const_iterator upper_bound(const key_type &k) const;

			// pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
			// pair<iterator, iterator> equal_range(const key_type &k);

			allocator_type get_allocator() const;

		private:
			Tree<value_type, key_compare, allocator_type>	_tree;
			key_compare 									_key_compare;
			allocator_type 									_alloc;

	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y);
}

#endif