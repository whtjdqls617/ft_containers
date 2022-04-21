#include "map.hpp"

#define T1 int
#define T2 std::string

template <typename T>
std::string printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

struct ft_more
{
	bool operator()(const T1 &first, const T1 &second) const
	{
		return (first > second);
	}
};

typedef ft::map<T1, T2, ft_more> ft_mp;
typedef ft::map<T1, T2, ft_more>::iterator ft_mp_it;

template <typename T_MAP>
void printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl
				  << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void func()
{

	ft_mp mp;
	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	printSize(mp);

	// ft::map<int, std::string>::iterator it = mp.begin();
	// for (; it != mp.end(); it++)
	// 	std::cout << (*it).first << std::endl;
}

int main()
{
	func();
	// while (1)
	// {

	// }

	return 0;
}