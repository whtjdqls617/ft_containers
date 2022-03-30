#include "utils.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>


void	checkErase(ft::vector<std::string>  &vct,
					ft::vector<std::string>::iterator  &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	
}

int		main(void)
{
	ft::vector<int> vct(10);

	// for (unsigned long int i = 0; i < vct.size(); ++i)
	// 	vct[i] = std::string((vct.size() - i), i + 65);
	

	// checkErase(vct, vct.erase(vct.begin() + 2));

	// checkErase(vct, vct.erase(vct.begin()));
	// checkErase(vct, vct.erase(vct.end() - 1));

	// checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	// checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	// vct.push_back("Hello");
	// vct.push_back("Hi there");
	
	// checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	// vct.push_back("ONE");
	// vct.push_back("TWO");
	// vct.push_back("THREE");
	// vct.push_back("FOUR");
	
	// checkErase(vct, vct.erase(vct.begin(), vct.end()));

	return (0);
}
