#ifndef TREE_HPP
#define TREE_HPP
#include "utils.hpp"

namespace ft
{
	template <class T> // T => pair
	struct Node
	{
		public :
			typedef	T		value_type;
			Node			*_parent;
			Node 			*_left;
			Node	 		*_right;
			value_type		_value;

			Node() : _parent(NULL), _left(NULL), _right(NULL), _value() {}

			Node(Node *parent, Node *left, Node *right, const value_type &value) : _parent(parent), _left(left), _right(right), _value(value) {}

			Node(const Node &src) : _parent(src._parent), _left(src._left), _right(src._right), _value(src._value)
			{}

			~Node() {}

			Node &operator=(const Node &src)
			{
				_parent = src._parent;
				_left = src._left;
				_right = src._right;
				_value = src._value;
				return (*this);
			}
	};

	template <class T>
	class tree_iterator
	{
		public:
			typedef std::ptrdiff_t								difference_type;
			typedef T											value_type;
			typedef T*											pointer;
			typedef T&											reference;
			typedef typename std::bidirectional_iterator_tag 	iterator_category;


			tree_iterator() : _node() {}

			tree_iterator(Node<T> *node) : _node(node) {}

			tree_iterator(const tree_iterator &it) : _node(it.base()) {}

			tree_iterator &operator=(const tree_iterator &mit)
			{
				_node = mit.base();
				return (*this);
			}

			Node<T>* base() const
			{
				return _node;
			}

			reference operator*() const
			{
				return _node->_value;
			}

			// tree_iterator &operator++()
			// {
			// 	_node++;
			// 	return *this;
			// }

			// tree_iterator operator++(int)
			// {
			// 	tree_iterator tmp = *this;
			// 	_node++;
			// 	return tmp;
			// }

			// tree_iterator &operator--()
			// {
			// 	_node--;
			// 	return *this;
			// }

			// tree_iterator operator--(int)
			// {
			// 	tree_iterator tmp = *this;
			// 	_node--;
			// 	return tmp;
			// }

		protected:
			Node<T>		*_node;
	};

	template <class T>
	class const_tree_iterator
	{
	public:
		typedef std::ptrdiff_t 								difference_type;
		typedef T 											value_type;
		typedef const T* 									pointer;
		typedef const T& 									reference;
		typedef typename std::bidirectional_iterator_tag 	iterator_category;

		const_tree_iterator() : _node() {}

		const_tree_iterator(Node<T> *node) : _node(node) {}

		const_tree_iterator(const const_tree_iterator &it) : _node(it.base()) {}

		const_tree_iterator &operator=(const const_tree_iterator &mit)
		{
			_node = mit.base();
			return (*this);
		}

		Node<T> *base() const
		{
			return _node;
		}

		reference operator*() const
		{
			return _node->_value;
		}

		// const_tree_iterator &operator++()
		// {
		// 	_node++;
		// 	return *this;
		// }

		// const_tree_iterator operator++(int)
		// {
		// 	const_tree_iterator tmp = *this;
		// 	_node++;
		// 	return tmp;
		// }

		// const_tree_iterator &operator--()
		// {
		// 	_node--;
		// 	return *this;
		// }

		// const_tree_iterator operator--(int)
		// {
		// 	const_tree_iterator tmp = *this;
		// 	_node--;
		// 	return tmp;
		// }

	protected:
		Node<T> *_node;
	};

	template <class T, class Compare, class Alloc>
	struct Tree
	{
		public :
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef T													value_type;
			typedef std::ptrdiff_t										difference_type;
			typedef size_t												size_type;
			typedef typename allocator_type::template rebind < Node<T> >::other 	node_alloc_type; // 중첩 구조체 템플릿
			typedef typename allocator_type::reference	reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer	pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef typename ft::tree_iterator<value_type>	iterator;
			typedef typename ft::const_tree_iterator<value_type> const_iterator;
			// typedef typename ft::reverse_iterator<iterator>	reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

			Tree() : _super_root(NULL), _root(NULL), _key_compare(key_compare()), _pair_alloc(Alloc()), _node_alloc(node_alloc_type()), _size(0)
			{
				_super_root = _node_alloc.allocate(1);
				_node_alloc.construct(_super_root, Node<T>());
			}

			Tree(Node<T> *dummy, Node<T> *root, key_compare key_compare, allocator_type pair_alloc, node_alloc_type node_alloc, size_type size) : _super_root(dummy), _root(root), _key_compare(key_compare), _pair_alloc(pair_alloc), _node_alloc(node_alloc), _size(size)
			{
				if (!_root)
				{
					_super_root = _node_alloc.allocate(1);
					_node_alloc.construct(_super_root, Node<T>());
					_super_root->_left = _node_alloc.allocate(1);
					_node_alloc.construct(_root, Node<T>());
					_super_root->_left = _root;
					_root->_parent = _super_root;
					size++;
				}
				else
				{
					// insert
				}
			}

			Tree(const Tree& src)
			{
				*this = src;
			}

			Tree &operator=(const Tree &src)
			{
				_super_root = src._super_root;
				_root = src._root;
				_key_compare = src._key_compare;
				_pair_alloc = src._pair_alloc;
				_node_alloc = src._node_alloc;
				_size = src._size;
				return (*this);
			}

			~Tree() {}

			// Iterator

			iterator begin()
			{
				if (!_root)
					return (_super_root);
				Node<T> tmp = _root;
				while (tmp->_left)
					tmp = tmp->_left;
				return (tmp);
			}

			const_iterator begin() const
			{

			}

			iterator end();
			const_iterator end() const;

			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;

			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			// Capacity

			bool empty() const
			{
				if (_size)
					return (true);
				return (false);
			}

			size_type	size() const
			{
				return _size;
			}

			size_type max_size() const;

			Node<T> *search(Node<T> *_root, const value_type &val)
			{
				if (!_root)
					return _super_root;
				Node<T> *tmp = _root;
				while (tmp)
				{
					if (tmp->_value.first == val.first)
						return (tmp);
					if (tmp->_value.first < val.first)
					{
						if (!tmp->_right)
							return (tmp);
						tmp = tmp->_right;
					}
					else
					{
						if (!tmp->_left)
							return (tmp);
						tmp = tmp->_left;
					}
				}
				return (0);
			}

			pair<iterator, bool> insert(const value_type &val)
			{
				Node<T> *tmp = search(_root, val);
				Node<T> *new_node = _node_alloc.allocate(1);

				if (tmp == _super_root)
				{
					_node_alloc.construct(new_node, Node<T>(0, 0, 0, val));
					_root = new_node;
					_super_root->_left = _root;
					_root->_parent = _super_root;

					std::cout << _root << std::endl;

					return (ft::make_pair<iterator, bool>(_root, true));
				}
				if (tmp->_value.first == val.first) {

					return (ft::make_pair<iterator, bool>(tmp, false));
				}
				if (_key_compare(tmp->_value.first, val.first))
				{
					_node_alloc.construct(new_node, Node<T>(0, 0, 0, val));
					tmp->_left = new_node;
					new_node->_parent = tmp->_left;
				}
				else
				{
					_node_alloc.construct(new_node, Node<T>(0, 0, 0, val));
					tmp->_right = new_node;
					new_node->_parent = tmp->_right;
				}
				std::cout << new_node << std::endl;
				return (ft::make_pair<iterator, bool>(new_node, true));
			}

		private :
			Node<T>				*_super_root;
			Node<T>				*_root;
			key_compare			_key_compare;
			allocator_type		_pair_alloc;
			node_alloc_type		_node_alloc;
			size_type			_size;
		};
}


#endif