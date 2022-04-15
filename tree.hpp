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

			tree_iterator(const tree_iterator &it) : _node(it._node) {}

			tree_iterator &operator=(const tree_iterator &it)
			{
				_node = it._node;
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

			tree_iterator &operator++()
			{
				if (_node->_right)
				{
					_node = _node->_right;
					if (!_node->_left)
						return *this;
					else
					{
						while (_node->_left)
							_node = _node->_left;
						return *this;
					}
				}
				else
				{
					// 부모가 왼쪽 자식일 때 까지 올라간 다음 그 부모 리턴
					while (_node && _node != _node->_parent->_left )
						_node = _node->_parent;
					_node = _node->_parent;
					return *this; // super node
				}
			}

			tree_iterator &operator--()
			{
				if (_node->_left)
				{
					_node = _node->_left;
					if (!_node->_right)
						return *this;
					else
					{
						_node = _node->_right;
						while (_node->_right)
							_node = _node->_right;
						return *this;
					}
				}
				else
				{
					// 부모가 오른쪽 자식일 때 까지 올라간 다음 그 부모 리턴
					while (_node != _node->_parent->_right )
						_node = _node->_parent;
					_node = _node->_parent;
					std::cout << _node->_value.first << std::endl;
					return *this; // super node
				}
			}

			tree_iterator operator++(int)
			{
				Node<T> *tmp = this->base();
				++(*this);
				return tmp;
			}

			tree_iterator operator--(int)
			{
				Node<T> *tmp = this->base();
				--(*this);
				return tmp;
			}

			bool operator==(const tree_iterator &lhs) { return (this->_node == lhs._node); }
			bool operator!=(const tree_iterator &lhs) { return (this->_node != lhs._node); }
			pointer operator->() const { return (&(_node->_value)); }

		protected:
			Node<T>		*_node;
	};

	template <class T>
	class tree_const_iterator
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef typename std::bidirectional_iterator_tag iterator_category;

		tree_const_iterator() : _node() {}

		tree_const_iterator(Node<T> *node) : _node(node) {}

		tree_const_iterator(const tree_const_iterator &cit) : _node(cit._node) {}

		tree_const_iterator &operator=(const tree_const_iterator &cit)
		{
			_node = cit._node;
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

		tree_const_iterator &operator++()
		{
			if (_node->_right)
			{
				_node = _node->_right;
				if (!_node->_left)
				{
					std::cout << _node->_value.first << std::endl;
					return *this;
				}
				else
				{
					_node = _node->_left;
					while (_node->_right)
						_node = _node->_right;
					std::cout << _node->_value.first << std::endl;
					return *this;
				}
			}
			else
			{
				// 부모가 왼쪽 자식일 때 까지 올라간 다음 그 부모 리턴
				while (_node != _node->_parent->_left)
					_node = _node->_parent;
				_node = _node->_parent;
				std::cout << _node->_value.first << std::endl;
				return *this; // super node
			}
		}

		tree_const_iterator &operator--()
		{
			if (_node->_left)
			{
				_node = _node->_left;
				if (!_node->_right)
				{
					std::cout << _node->_value.first << std::endl;
					return *this;
				}
				else
				{
					_node = _node->_right;
					while (_node->_right)
						_node = _node->_right;
					std::cout << _node->_value.first << std::endl;
					return *this;
				}
			}
			else
			{
				// 부모가 오른쪽 자식일 때 까지 올라간 다음 그 부모 리턴
				while (_node != _node->_parent->_right)
					_node = _node->_parent;
				_node = _node->_parent;
				std::cout << _node->_value.first << std::endl;
				return *this; // super node
			}
		}

		tree_const_iterator operator++(int)
		{
			Node<T> *tmp = this->base();
			++(*this);
			return tmp;
		}

		tree_const_iterator operator--(int)
		{
			Node<T> *tmp = this->base();
			--(*this);
			return tmp;
		}

		bool operator==(const tree_const_iterator &lhs) { return (this->_node == lhs._node); }
		bool operator!=(const tree_const_iterator &lhs) { return (this->_node != lhs._node); }
		pointer operator->() const { return (&(_node->_value)); }

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
			typedef typename ft::tree_const_iterator<value_type> const_iterator;
			// typedef typename ft::reverse_iterator<iterator>	reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

			Tree() : _super_root(NULL), _root(NULL), _key_compare(key_compare()), _pair_alloc(Alloc()), _node_alloc(node_alloc_type()), _size(0)
			{
				_super_root = _node_alloc.allocate(1);
				_node_alloc.construct(_super_root, Node<T>());
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

			~Tree()
			{
				_node_alloc.destroy(_super_root);
				_node_alloc.deallocate(_super_root, 1);
			}

			// Iterator

			iterator begin()
			{
				if (!_root)
					return (_super_root);
				Node<T> *tmp = _root;
				while (tmp->_left)
					tmp = tmp->_left;
				return (iterator(tmp));
			}

			const_iterator begin() const
			{
				return(const_iterator(begin()));
			}

			iterator end()
			{
				return (_super_root);
			}
			const_iterator end() const
			{
				return (const_iterator(_super_root));
			}

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

			Node<T> *getRoot()
			{
				return _root;
			}

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
					return (ft::make_pair<iterator, bool>(_root, true));
				}
				if (tmp->_value.first == val.first) {

					return (ft::make_pair<iterator, bool>(tmp, false));
				}
				if (_key_compare(tmp->_value.first, val.first))
				{
					_node_alloc.construct(new_node, Node<T>(0, 0, 0, val));
					tmp->_right = new_node;
					new_node->_parent = tmp;
				}
				else if (_key_compare(val.first, tmp->_value.first))
				{
					_node_alloc.construct(new_node, Node<T>(0, 0, 0, val));
					tmp->_left = new_node;
					new_node->_parent = tmp;
				}
				return (ft::make_pair<iterator, bool>(new_node, true));
			}

			iterator insert(iterator position, const value_type &val)
			{
				(void)position;
				return (insert(val).first);
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			}

			void erase(iterator position)
			{
				erase(*position);
			}

			size_type erase(const value_type &val)
			{
				// iterator it = find(val);
				// iterator tmp_it = it;

				// if (it == _super_root)
				// 	return countSize(); //getSize로 변경해야 할 듯
				// // 왼쪽 자식이 있을 떄
				// if (tmp_it.base()->_left)
				// 	--tmp_it; // 삭제할 키의 전 값
				// // 오른쪽 자식이 있을 떄
				// else if (tmp_it.base()->_right)
				// 	++tmp_it;
				// value_type tmp;
				// tmp = it.base()->_value;
				// it.base()->_value = tmp_it.base()->_value;
				// tmp_it.base()->_value = tmp;
				// // 최종 삭제
				// if (!tmp_it.base()->_right && !tmp_it.base()->_left)
				// {
				// 	// 삭제 될 것이 왼쪽 자식일 때
				// 	if (tmp_it.base() == tmp_it.base()->_parent->_left)
				// 		tmp_it.base()->_parent->_left = NULL;
				// 	// 삭제 될 것이 오른쪽 자식일 때
				// 	if (tmp_it.base() == tmp_it.base()->_parent->_right)
				// 		tmp_it.base()->_parent->_right = NULL;
				// 	tmp_it.base()->_parent = NULL;
				// 	_node_alloc.destroy(tmp_it.base());
				// 	_node_alloc.deallocate(tmp_it.base(), 1);
				// 	if (tmp_it.base() == _root)
				// 		_root = NULL;
				// 	return countSize();
				// }
				// return erase((*tmp_it));

				iterator it = find(val);
				iterator tmp_it = it;

				if (it == _super_root)
					return countSize();
				// 둘 다 없을 때
				if (!(it.base()->_left) && !(it.base()->_right))
				{
					if (it.base() == _root)
					{
						_node_alloc.destroy(it.base());
						_node_alloc.deallocate(it.base(), 1);
						_root = NULL;
						_super_root->_left = NULL;
						return 0;
					}
					if (it.base() == it.base()->_parent->_left)
						it.base()->_parent->_left = NULL;
					else if (it.base() == it.base()->_parent->_right)
						it.base()->_parent->_right = NULL;
				}
				// 왼쪽 자식만 있을 때
				else if (it.base()->_left && !(it.base()->_right))
				{
					// 삭제 노드가 왼쪽 자식일 때
					if (it.base()->_parent->_left == it.base())
					{
						if (it.base() == _root)
							_root = it.base()->_right;
						it.base()->_parent->_left = it.base()->_left;
						it.base()->_left->_parent = it.base()->_parent;
					}
					// 삭제 노드가 오른쪽 자식일 때
					else if (it.base()->_parent->_right == it.base())
					{
						it.base()->_parent->_right = it.base()->_left;
						it.base()->_left->_parent = it.base()->_parent;
					}
				}
				// 오른쪽 자식만 있을 때
				else if (!(it.base()->_left) && it.base()->_right)
				{
					// 삭제 노드가 왼쪽 자식일 때
					if (it.base()->_parent->_left == it.base())
					{
						if (it.base() == _root)
							_root = it.base()->_right;
						it.base()->_parent->_left = it.base()->_right;
						it.base()->_right->_parent = it.base()->_parent;
					}
					// 삭제 노드가 오른쪽 자식일 때
					else if (it.base()->_parent->_right == it.base())
					{
						it.base()->_parent->_right = it.base()->_right;
						it.base()->_right->_parent = it.base()->_parent;
					}
				}
				// 둘 다 있을 때
				else
				{
					// 삭제할 노드의 하나 전 값 이동
					--tmp_it;
					// swap
					value_type tmp;
					tmp = it.base()->_value;
					it.base()->_value = tmp_it.base()->_value;
					tmp_it.base()->_value = tmp;
					// 삭제 노드가 왼쪽 자식일 때
					// only left
					if (it.base()->_parent->_left == it.base())
					{
						if (it.base() == _root)
							_root = it.base()->_right;
						it.base()->_parent->_left = it.base()->_left;
						it.base()->_left->_parent = it.base()->_parent;
					}
					// 삭제 노드가 오른쪽 자식일 때
					else if (it.base()->_parent->_right == it.base())
					{
						it.base()->_parent->_right = it.base()->_left;
						it.base()->_left->_parent = it.base()->_parent;
					}
				}
				_node_alloc.destroy(it.base());
				_node_alloc.deallocate(it.base(), 1);
				return countSize();
			}

			void erase(iterator first, iterator last)
			{
				iterator tmp = first;
				while (first != last)
				{
					first++;
					erase(tmp);
					tmp = first;
				}
			}

			iterator find(const value_type &val)
			{
				iterator it = begin();
				for (; it != end(); it++)
				{
					if ((*it).first == val.first)
						return (it);
				}
				return it;
			}

			void	clear()
			{
				while (_root)
				{
					Node<T> *tmp = _root;
					while (tmp->_left || tmp->_right)
					{
						if (tmp->_left)
							tmp = tmp->_left;
						else if (tmp->_right)
							tmp = tmp->_right;
					}
					erase(tmp->_value);
				}
			}

			void swap(Tree &x)
			{
				Node<T>	*tmp_super_root = x._super_root;
				Node<T>	*tmp_root = x._root;
				key_compare	tmp_key_compare = x._key_compare;
				allocator_type	tmp_pair_alloc = x._pair_alloc;
				node_alloc_type	tmp_node_alloc = x._node_alloc;
				size_type	tmp_size = x._size;

				x._super_root = _super_root;
				x._root = _root;
				x._key_compare = _key_compare;
				x._pair_alloc = _pair_alloc;
				x._node_alloc = _node_alloc;
				x._size	= _size;

				_super_root = tmp_super_root;
				_root = tmp_root;
				_key_compare = tmp_key_compare;
				_pair_alloc = tmp_pair_alloc;
				_node_alloc = tmp_node_alloc;
				_size = tmp_size;
			}

			size_type countSize()
			{
				size_type count = 0;
				if (!_root)
					return count;
				for (iterator it = begin(); it != end(); it++)
					count++;
				return count;
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