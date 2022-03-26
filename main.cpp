#include "utils.hpp"
#include "./vector/vector.hpp"
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
   // constructors used in the same order as described above:
  ft::vector<int> first;                                // empty vector of ints
  ft::vector<int> second (4,100);                       // four ints with value 100
  ft::vector<int> third (second.begin(),second.end());  // iterating through second
  ft::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

// int main()
// {
//   std::vector<int>::size_type sz;

//   std::vector<int> foo;
//   sz = foo.capacity();
//   std::cout << "making foo grow:\n";
//   for (int i=0; i<100; ++i) {
//     foo.push_back(i);
//     if (sz!=foo.capacity()) {
//       sz = foo.capacity();
//       std::cout << "capacity changed: " << sz << '\n';
//     }
//   }

//   std::vector<int> bar;
//   sz = bar.capacity();
//   bar.reserve(100);   // this is the only difference with foo above
//   std::cout << "making bar grow:\n";
//   for (int i=0; i<100; ++i) {
//     bar.push_back(i);
//     if (sz!=bar.capacity()) {
//       sz = bar.capacity();
//       std::cout << "capacity changed: " << sz << '\n';
//     }
//   }
//   return 0;
// }