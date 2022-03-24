#include "utils.hpp"
#include "./vector/vector.hpp"
#include <iostream>
#include <iterator>
#include <vector>

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
  ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  typedef std::vector<int>::iterator iter_type;

  std::vector<int>::iterator it;
  for (it = myvector.begin(); it != myvector.end(); it++) {
	  std::cout << *it << std::endl;
  }


  return 0;
}