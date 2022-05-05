#ifndef TREE_HPP
#define TREE_HPP
#include "reverse_iterator.hpp"
#include <limits>

namespace ft
{
	template <typename T>
	class tree_const_iterator;

	template <class T> // T => pair
	struct Node
	{
	public:
		typedef T 	value_type;
		Node*		_parent;
		Node*		_left;
		Node*		_right;
		value_type 	_value;
		int 		_height;

		Node() : _parent(NULL), _left(NULL), _right(NULL), _value(), _height(1) {}

		Node(Node *parent, Node *left, Node *right, const value_type &value, int height) : _parent(parent), _left(left), _right(right), _value(value), _height(height) {}

		Node(const Node &src) : _parent(src._parent), _left(src._left), _right(src._right), _value(src._value), _height(src._height)
		{
		}

		~Node() {}

		Node &operator=(const Node &src)
		{
			_parent = src._parent;
			_left = src._left;
			_right = src._right;
			_value = src._value;
			_height = src._height;
			return (*this);
		}
	};

	template <class T>
	class tree_iterator
	{
	public:
		typedef std::ptrdiff_t 								difference_type;
		typedef T 											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::bidirectional_iterator_tag 	iterator_category;

		tree_iterator() : _node() {}

		tree_iterator(Node<T> *node) : _node(node) {}

		tree_iterator(const tree_iterator &it) : _node(it.base()) {}

		tree_iterator &operator=(const tree_iterator &it)
		{
			_node = it._node;
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
				while (_node != _node->_parent->_left)
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
				while (_node != _node->_parent->_right)
					_node = _node->_parent;
				_node = _node->_parent;
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
		bool operator==(const tree_const_iterator<T> &lhs) { return (this->base() == lhs.base()); }
		bool operator!=(const tree_const_iterator<T> &lhs) { return (this->base() != lhs.base()); }
		pointer operator->() const { return (&(_node->_value)); }

	protected:
		Node<T> *_node;
	};

	template <class T>
	class tree_const_iterator
	{
	public:
		typedef std::ptrdiff_t 								difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::bidirectional_iterator_tag 	iterator_category;

		tree_const_iterator() : _node() {}

		tree_const_iterator(Node<T> *node) : _node(node) {}

		tree_const_iterator(const tree_const_iterator &it) : _node(it._node) {}

		tree_const_iterator &operator=(const tree_const_iterator &it)
		{
			_node = it._node;
			return (*this);
		}

		tree_const_iterator(const tree_iterator<T> &it) : _node(it.base()) {} // const나 reverse를 인식하기 위해서 사용

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
				while (_node && _node != _node->_parent->_left)
					_node = _node->_parent;
				_node = _node->_parent;
				return *this; // super node
			}
		}

		tree_const_iterator &operator--()
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
				while (_node != _node->_parent->_right)
					_node = _node->_parent;
				_node = _node->_parent;
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
		bool operator==(const tree_iterator<T> &lhs) { return (this->base() == lhs.base()); }
		bool operator!=(const tree_iterator<T> &lhs) { return (this->base() != lhs.base()); }
		pointer operator->() const { return (&(_node->_value)); }

	protected:
		Node<T> *_node;
	};

	template <class T, class Compare, class Alloc>
	struct Tree
	{
	public:
		typedef Compare 													key_compare;
		typedef Alloc 														allocator_type;
		typedef T 															value_type;
		typedef std::ptrdiff_t 												difference_type;
		typedef size_t 														size_type;
		typedef typename allocator_type::template rebind<Node<T> >::other	node_alloc_type; // 중첩 구조체 템플릿
		typedef typename allocator_type::reference 							reference;
		typedef typename allocator_type::const_reference 					const_reference;
		typedef typename allocator_type::pointer 							pointer;
		typedef typename allocator_type::const_pointer 						const_pointer;
		typedef typename ft::tree_iterator<value_type> 						iterator;
		typedef typename ft::tree_const_iterator<value_type> 				const_iterator;
		typedef typename ft::reverse_iterator<iterator> 					reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> 				const_reverse_iterator;

		Tree() : _super_root(NULL), _root(NULL), _key_compare(key_compare()), _node_alloc(node_alloc_type())
		{
			_super_root = _node_alloc.allocate(1);
			_node_alloc.construct(_super_root, Node<T>());
		}

		Tree(const Tree &src)
		{
			*this = src;
		}

		Tree &operator=(const Tree &src)
		{
			_key_compare = src._key_compare;
			_node_alloc = src._node_alloc;
			if (_root)
				clear();
			insert(src.begin(), src.end());
			return (*this);
		}

		~Tree()
		{
			clear();
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
			if (!_root)
				return (_super_root);
			Node<T> *tmp = _root;
			while (tmp->_left)
				tmp = tmp->_left;
			return (const_iterator(tmp));
		}

		iterator end()
		{
			return (iterator(_super_root));
		}
		const_iterator end() const
		{
			return (const_iterator(_super_root));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(_super_root));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(_super_root));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		// Capacity

		bool empty() const
		{
			if (size())
				return (true);
			return (false);
		}

		size_type countSize() const
		{
			size_type count = 0;
			if (!_root)
				return count;
			for (const_iterator it = begin(); it != end(); it++)
				count++;
			return count;
		}

		size_type size() const
		{
			return (countSize());
		}

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
				if (_key_compare(tmp->_value.first, val.first))
				{
					if (!tmp->_right)
						return (tmp);
					tmp = tmp->_right;
				}
				else if (_key_compare(val.first, tmp->_value.first))
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
				_node_alloc.construct(new_node, Node<T>(0, 0, 0, val, 1));
				_root = new_node;
				_super_root->_left = _root;
				_root->_parent = _super_root;
				return (ft::make_pair<iterator, bool>(_root, true));
			}
			if (tmp->_value.first == val.first)
			{
				_node_alloc.destroy(new_node);
				_node_alloc.deallocate(new_node, 1);
				return (ft::make_pair<iterator, bool>(tmp, false));
			}
			if (_key_compare(tmp->_value.first, val.first))
			{
				_node_alloc.construct(new_node, Node<T>(0, 0, 0, val, 1));
				tmp->_right = new_node;
				new_node->_parent = tmp;
			}
			else if (_key_compare(val.first, tmp->_value.first))
			{
				_node_alloc.construct(new_node, Node<T>(0, 0, 0, val, 1));
				tmp->_left = new_node;
				new_node->_parent = tmp;
			}
			new_node->_height = 1;
			tmp = new_node;
			// 삽입 노드 위로 height 갱신
			while (tmp->_parent != _super_root)
			{
				if (tmp->_height == tmp->_parent->_height)
					tmp->_parent->_height += 1;
				tmp = tmp->_parent;
			}

			// 새롭게 갱신
			rebalance_insert(new_node);
			_root = _super_root->_left;

			// 전위 순회로 height 갱신
			return (ft::make_pair<iterator, bool>(new_node, true));
		}

		void update_up(Node<T> *tmp)
		{
			while (tmp)
			{
				if (tmp == _super_root)
					return;
				// 내가 왼쪽 자식일 때 부모의 오른쪽자식이 있을 때 height를 비교해서 내가 더 작으면 return, 내가 더 크면 부모로 이동 후 ++
				if (tmp == tmp->_parent->_left)
				{
					if (tmp->_parent->_right)
					{
						if (tmp->_parent->_right->_height > tmp->_height)
							return;
						else
						{
							tmp->_parent->_height = tmp->_height + 1;
							tmp = tmp->_parent;
						}
					}
					// 내가 완쪽 자식일 때 부모의 오른쪽 자식이 없으면 부모로 이동 후 ++
					else
					{
						tmp = tmp->_parent;
						tmp->_height++;
					}
				}
				// 내가 오른쪽 자식일 때 부모의 왼쪽자식이 있을 때 height를 비교해서 내가 더 작으면 return, 내가 더 크면 부모로 이둥 후 ++
				else if (tmp == tmp->_parent->_right)
				{
					if (tmp->_parent->_left)
					{
						if (tmp->_parent->_left->_height > tmp->_height)
							return;
						else
						{
							tmp->_parent->_height = tmp->_height + 1;
							tmp = tmp->_parent;
						}
					}
					// 내가 오른쪽 자식일 때 부모의 왼쪽자식이 없으면 부모로 이동 후 ++
					else
					{
						tmp->_parent->_height = tmp->_height + 1;
						tmp = tmp->_parent;
					}
				}
			}
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
			iterator it = find(val);
			iterator tmp_it = it;

			if (it == (iterator)_super_root)
				return 0;
			// 자식이 없을 때
			if (!(tmp_it.base()->_left) && !(tmp_it.base()->_right))
			{
				if (tmp_it.base() == _root)
				{
					_super_root->_left = NULL;
					_node_alloc.destroy(tmp_it.base());
					_node_alloc.deallocate(tmp_it.base(), 1);
					_root = NULL;
					return 1;
				}
				if (tmp_it.base() == tmp_it.base()->_parent->_left)
					tmp_it.base()->_parent->_left = NULL;
				else if (tmp_it.base() == tmp_it.base()->_parent->_right)
					tmp_it.base()->_parent->_right = NULL;
			}
			// 왼쪽 자식만 있을 때
			else if (tmp_it.base()->_left && !(tmp_it.base()->_right))
			{
				// tmp_it가 왼쪽 자식일 때
				if (tmp_it.base() == tmp_it.base()->_parent->_left)
				{
					if (tmp_it.base() == _root)
						_root = tmp_it.base()->_left;
					tmp_it.base()->_parent->_left = tmp_it.base()->_left;
					tmp_it.base()->_left->_parent = tmp_it.base()->_parent;
				}
				// tmp_it가 오른쪽 자식일 때
				else if (tmp_it.base() == tmp_it.base()->_parent->_right)
				{
					tmp_it.base()->_parent->_right = tmp_it.base()->_left;
					tmp_it.base()->_left->_parent = tmp_it.base()->_parent;
				}
			}
			// 오른쪽 자식만 있을 때
			else if (tmp_it.base()->_right && !(tmp_it.base()->_left))
			{
				// tmp_it가 왼쪽 자식일 때
				if (tmp_it.base() == tmp_it.base()->_parent->_left)
				{
					if (tmp_it.base() == _root)
						_root = tmp_it.base()->_right;
					tmp_it.base()->_parent->_left = tmp_it.base()->_right;
					tmp_it.base()->_right->_parent = tmp_it.base()->_parent;
				}
				else if (tmp_it.base() == tmp_it.base()->_parent->_right)
				{
					tmp_it.base()->_parent->_right = tmp_it.base()->_right;
					tmp_it.base()->_right->_parent = tmp_it.base()->_parent;
				}
			}
			// 둘다 있을 때
			else if (tmp_it.base()->_left && tmp_it.base()->_right)
			{
				// 하나 작은 것과 data만 swap
				--tmp_it;
				it.base()->_value = tmp_it.base()->_value;

				// tmp_it가 왼쪽 자식을 가지고 있을 때
				if (tmp_it.base()->_left)
				{
					// tmp_it가 오른쪽 자식일 때
					if (tmp_it.base() == tmp_it.base()->_parent->_right)
					{
						// 부모와 자식 연결
						tmp_it.base()->_parent->_right = tmp_it.base()->_left;
						tmp_it.base()->_left->_parent = tmp_it.base()->_parent;
					}
					// tmp_it가 왼쪽 자식일 때
					else if (tmp_it.base() == tmp_it.base()->_parent->_left)
					{
						// 부모와 자식 연결
						tmp_it.base()->_parent->_left = tmp_it.base()->_left;
						tmp_it.base()->_left->_parent = tmp_it.base()->_parent;
					}
				}
				// tmp_it가 왼쪽 자식을 가지고 있지 않을 때 (자식이 없을 때)
				else
				{
					// tmp_it가 오른쪽 자식일 때
					if (tmp_it.base() == tmp_it.base()->_parent->_right)
						tmp_it.base()->_parent->_right = NULL;
					// tmp_it가 왼쪽 자식일 때
					else if (tmp_it.base() == tmp_it.base()->_parent->_left)
						tmp_it.base()->_parent->_left = NULL;
				}
			}
			Node<T> *start_node = tmp_it.base()->_parent;
			_node_alloc.destroy(tmp_it.base());
			_node_alloc.deallocate(tmp_it.base(), 1);
			while (start_node != _super_root)
			{
				rebalance_erase(start_node);
				if (start_node->_left && !start_node->_right)
					update_up(start_node->_left);
				else if (start_node->_right && !start_node->_left)
					update_up(start_node->_right);
				else if (!start_node->_left && !start_node->_right)
				{
					start_node->_height = 1;
					update_up(start_node);
				}
				else
					update_up(start_node->_left);
				start_node = start_node->_parent;
			}
			return 1;
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

		const_iterator find(const value_type &val) const
		{
			const_iterator it = begin();
			for (; it != end(); it++)
			{
				if ((*it).first == val.first)
					return (it);
			}
			return it;
		}

		void clear()
		{
			erase(begin(), end());
		}

		void swap(Tree &x)
		{
			Node<T> *tmp_super_root = x._super_root;
			Node<T> *tmp_root = x._root;
			key_compare tmp_key_compare = x._key_compare;
			node_alloc_type tmp_node_alloc = x._node_alloc;

			x._super_root = _super_root;
			x._root = _root;
			x._key_compare = _key_compare;
			x._node_alloc = _node_alloc;

			_super_root = tmp_super_root;
			_root = tmp_root;
			_key_compare = tmp_key_compare;
			_node_alloc = tmp_node_alloc;
		}

		size_type count(const value_type &val) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if ((*it).first == val.first)
					return (1);
			}
			return (0);
		}

		size_type max_size() const
		{
			return (_node_alloc.max_size());
		}

		int get_balance_factor(iterator it)
		{
			Node<T> *tmp = it.base();

			int l_depth = 0;
			int r_depth = 0;
			if (tmp->_left)
				l_depth = tmp->_left->_height;
			if (tmp->_right)
				r_depth = tmp->_right->_height;
			return (l_depth - r_depth);
		}

		void rebalance_insert(Node<T> *new_node)
		{
			Node<T> *tmp = new_node;
			int balance_factor;

			if (tmp == _super_root)
				return;
			while (tmp != _super_root)
			{
				balance_factor = get_balance_factor(iterator(tmp));
				if (balance_factor > 1 || balance_factor < -1)
					break;
				tmp = tmp->_parent;
			}
			if (balance_factor > 1)
			{
				// LL
				if (get_balance_factor(iterator(tmp->_left)) >= 0)
					tmp = RotateLL(tmp);
				// LR
				else
					tmp = RotateLR(tmp);
				update_up(tmp);
				_root = _super_root->_left;
			}
			else if (balance_factor < -1)
			{
				// RR
				if (get_balance_factor(iterator(tmp->_right)) <= 0)
					tmp = RotateRR(tmp);
				// RL
				else
					tmp = RotateRL(tmp);
				update_up(tmp);
				_root = _super_root->_left;
			}
		}

		void rebalance_erase(Node<T> *new_node)
		{
			Node<T> *tmp = new_node;
			int balance_factor = 0;

			if (tmp == _super_root)
				return;
			while (tmp != _super_root)
			{
				balance_factor = get_balance_factor(iterator(tmp));
				if (balance_factor > 1 || balance_factor < -1)
				{
					if (balance_factor < -1 && get_balance_factor(tmp->_right) == 0)
					{
						tmp->_height++;
						tmp->_right->_height++;
					}
					else if (balance_factor > 1 && get_balance_factor(tmp->_left) == 0)
					{
						tmp->_height++;
						tmp->_left->_height++;
					}
					break;
				}
				tmp = tmp->_parent;
			}
			if (balance_factor > 1)
			{
				// LL
				if (get_balance_factor(iterator(tmp->_left)) >= 0)
					tmp = RotateLL(tmp);
				// LR
				else
					tmp = RotateLR(tmp);
				_root = _super_root->_left;
			}
			else if (balance_factor < -1)
			{
				// RR
				if (get_balance_factor(iterator(tmp->_right)) <= 0)
					tmp = RotateRR(tmp);
				// RL
				else
					tmp = RotateRL(tmp);
				_root = _super_root->_left;
			}
		}

		Node<T> *RotateLL(Node<T> *current)
		{
			Node<T> *p_node;
			Node<T> *c_node;

			p_node = current;
			c_node = current->_left;
			p_node->_height -= 2;
			if (!c_node)
				return c_node;
			if (!c_node->_right)
				p_node->_left = NULL;
			else
			{
				c_node->_right->_parent = p_node;
				p_node->_left = c_node->_right;
			}
			c_node->_right = p_node;
			c_node->_parent = p_node->_parent;
			if (p_node == p_node->_parent->_left)
				p_node->_parent->_left = c_node;
			else
				p_node->_parent->_right = c_node;
			p_node->_parent = c_node;
			return c_node;
		}

		Node<T> *RotateRR(Node<T> *current)
		{
			Node<T> *p_node;
			Node<T> *c_node;

			p_node = current;
			c_node = current->_right;
			p_node->_height -= 2;
			if (!c_node)
				return c_node;
			if (!c_node->_left)
				p_node->_right = NULL;
			else
			{
				c_node->_left->_parent = p_node;
				p_node->_right = c_node->_left;
			}
			c_node->_left = p_node;
			c_node->_parent = p_node->_parent;
			if (p_node == p_node->_parent->_left)
				p_node->_parent->_left = c_node;
			else
				p_node->_parent->_right = c_node;
			p_node->_parent = c_node;

			return c_node;
		}

		Node<T> *RotateLR(Node<T> *current)
		{
			current->_left->_height += 1;
			current->_left->_right->_height += 1;
			current->_left = RotateRR(current->_left);

			return RotateLL(current);
		}

		Node<T> *RotateRL(Node<T> *current)
		{
			current->_right->_height += 1;
			current->_right->_left->_height += 1;
			current->_right = RotateLL(current->_right);

			return RotateRR(current);
		}

	private:
		Node<T>*		_super_root;
		Node<T>*		_root;
		key_compare 	_key_compare;
		node_alloc_type	_node_alloc;
	};
}

#endif
