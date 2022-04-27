#include "map.hpp"

int main()
{
	// ft::map<int, int> mymap;

	// // first insert function version (single parameter):
	// mymap.insert(ft::pair<int, int>(50, 200));
	// mymap.insert(ft::pair<int, int>(40, 200));
	// mymap.insert(ft::pair<int, int>(30, 200));
	// mymap.insert(ft::pair<int, int>(45, 200));

	// return 0;
	ft::map<int, int> test;
	srand(2);

	for (int i = 0; i < 1000; i++)
	{
		test.insert(ft::make_pair<int, int>(rand(), 1));
	}
	return (0);
}