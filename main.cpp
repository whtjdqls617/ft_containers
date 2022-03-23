#include "util.hpp"
#include "vector.hpp"
#include <iostream>

// int	main()
// {
// 	// ft::pair<int, double> p1(10, 1);
// 	// ft::vector<int> a;
// 	// ft::vector<int> b(10);

// 	// std::cout << p1.first << std::endl;
// 	// std::cout << p1.second << std::endl;

// 	// std::cout << a.max_size() << std::endl;
// 	// std::cout << b.max_size() << std::endl;

// 	// std::cout << a.capacity() << std::endl;
// 	// std::cout << b.capacity() << std::endl;

// 	// std::cout << b.empty() << std::endl;
// 	// std::cout << a.empty() << std::endl;
// 	ft::vector<int> myvector(10); // 10 zero-initialized ints

// 	// assign some values:
// 	for (unsigned i = 0; i < myvector.size(); i++)
// 		myvector.at(i) = i;

// 	std::cout << myvector.front() << std::endl;
// 	std::cout << myvector.back() << std::endl;

// 	return 0;
// }

int main()
{
	ft::vector<int> foo(3, 100); // three ints with a value of 100
	ft::vector<int> bar(5, 200); // five ints with a value of 200

	// foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i = 0; i < foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i = 0; i < bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';

	return 0;
}