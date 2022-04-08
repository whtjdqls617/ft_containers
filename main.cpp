#include "utils.hpp"
#include "map.hpp"

int		main(void)
{
	int key = 1;
	std::string value = "42";
	ft::pair<int, std::string> pair1 = ft::make_pair<int, std::string>(key, value);
	ft::pair<int, std::string> pair2 = ft::make_pair<int, std::string>(2, value);
	ft::pair<int, std::string> pair3 = ft::make_pair<int, std::string>(3, value);

	ft::map<int, std::string> map1;
	std::cout << map1.size() << std::endl;
	ft::map<int, std::string>::iterator it;
	std::cout << it.base() << std::endl;

	map1.insert(pair1);
	// map1.insert(pair2);
	// map1.insert(pair3);

	return (0);
}
