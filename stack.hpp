#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

			explicit stack(const container_type &ctnr = container_type()) : c(ctnr)
			{}

			bool empty() const
			{
				return (c.empty());
			}

			size_type size() const
			{
				return (c.size());
			}

			value_type &top()
			{
				return (c.back());
			}

			const value_type &top() const
			{
				return (c.back());
			}

			void push(const value_type &val)
			{
				return (c.push_back(val));
			}

			void pop()
			{
				return (c.pop_back());
			}

		protected:
			container_type c;

		// friend는 외부함수나 클래스가 private 변수에 접근할 수 있도록 해줌.
		template <class U, class C>
		friend bool operator==(const stack<U, C> &lhs, const stack<U, C> &rhs);

		template <class U, class C>
		friend bool operator<(const stack<U, C> &lhs, const stack<U, C> &rhs);
	};
	// c에 접근할 수 있도록 하기 위해 위에 friend를 붙이고 밑에 오버로드는 벡터에 있는 것을 사용한다.
	template <class U, class C>
	bool operator==(const stack<U, C> &lhs, const stack<U, C> &rhs)
	{
		return (lhs.c == rhs.c);
	};

	template <class U, class C>
	bool operator!=(const stack<U, C> &lhs, const stack<U, C> &rhs)
	{
		return !(lhs == rhs);
	};

	template <class U, class C>
	bool operator<(const stack<U, C> &lhs, const stack<U, C> &rhs)
	{
		return (lhs.c < rhs.c);
	};

	template <class U, class C>
	bool operator<=(const stack<U, C> &lhs, const stack<U, C> &rhs)
	{
		return !(rhs < lhs);
	};

	template <class U, class C>
	bool operator>(const stack<U, C> &lhs, const stack<U, C> &rhs)
	{
		return (rhs < lhs);
	};

	template <class U, class C>
	bool operator>=(const stack<U, C> &lhs, const stack<U, C> &rhs)
	{
		return !(lhs < rhs);
	};
}

#endif