#include "map.hpp"

int main()
{
	ft::map<int, int> mymap;

	// first insert function version (single parameter):
	mymap.insert(ft::pair<int, int>(12, 200));
	mymap.insert(ft::pair<int, int>(2, 200));
	mymap.insert(ft::pair<int, int>(20, 200));
	mymap.insert(ft::pair<int, int>(10, 200));
	mymap.insert(ft::pair<int, int>(18, 200));
	mymap.insert(ft::pair<int, int>(37, 200));
	mymap.insert(ft::pair<int, int>(13, 200));
	mymap.insert(ft::pair<int, int>(25, 200));
	mymap.insert(ft::pair<int, int>(39, 200));
	mymap.insert(ft::pair<int, int>(38, 200));
	// for (int i=0; i < 1000000; i++)
	// 	mymap.insert(ft::pair<int, int>(i, 200));

	// ft::map<int, int>::iterator it = mymap.begin();
	// for (; it != mymap.end(); it++)
	// 	std::cout << (*it).first << "  ";
	return 0;
	// ft::map<int, int> test;
	// srand(time(NULL));

	// for (int i = 0; i < 50000000; i++)
	// {
	// 	test.insert(ft::make_pair<int, int>(rand(), 1));
	// }
	// return (0);
}