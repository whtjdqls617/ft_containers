#include <time.h>

#include <iostream>
#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"

/*
 **=========================================================================
 **     Vector Test
 **=========================================================================
 */

static void printVector(const ft::vector<std::string> &v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

void vector_test()
{
	clock_t g_start = clock();

	std::cout << "test : push_back" << std::endl;
	ft::vector<std::string> v1;
	v1.push_back("1");
	v1.push_back("2");
	v1.push_back("3");
	v1.push_back("4");
	v1.push_back("5");
	std::cout << "v1: ";
	printVector(v1);

	std::cout << "test : begin, end" << std::endl;
	ft::vector<std::string> v2(v1.begin(), v1.end());
	std::cout << "v2: ";
	printVector(v2);

	std::cout << "test : copy_constructor" << std::endl;
	ft::vector<std::string> v3(v2);
	std::cout << "v3: ";
	printVector(v3);

	std::cout << "test : at, operator '[]', front, back" << std::endl;
	std::cout << "v3[1]: " << v3.at(1) << std::endl;
	std::cout << "v3[2]: " << v3[2] << std::endl;
	std::cout << "v3 front: " << v3.front() << std::endl;
	std::cout << "v3 back: " << v3.back() << std::endl;

	std::cout << "test : operator '*'" << std::endl;
	ft::vector<std::string>::iterator it = v3.begin();
	for (; it < v3.end(); it++)
	{
		std::cout << "it: " << *it << " ";
	}
	std::cout << std::endl;

	std::cout << "test : rbegin, rend" << std::endl;
	ft::vector<std::string>::reverse_iterator r_it = v3.rbegin();
	for (; r_it < v3.rend(); r_it++)
	{
		std::cout << "r_it: " << *r_it << " ";
	}
	std::cout << std::endl;

	std::cout << "test : empty, size, max_size, capacity" << std::endl;
	std::cout << "v3 empty: " << (v3.empty() ? "true" : "false") << std::endl;
	std::cout << "v3 size: " << v3.size() << std::endl;
	std::cout << "v3 max_size: " << v3.max_size() << std::endl;
	std::cout << "v3 capacity: " << v3.capacity() << std::endl;

	std::cout << "v3 clear\n";
	v3.clear();
	std::cout << "v3 size: " << v3.size() << std::endl;
	std::cout << "v3 insert from v2\n";
	v3.insert(v3.begin(), v2.begin(), v2.end());
	std::cout << "v3 size: " << v3.size() << std::endl;
	std::cout << "v3: ";
	printVector(v3);

	std::cout << "erase 4번째\n";
	v3.erase(v3.begin() + 4);
	std::cout << "v3: ";
	printVector(v3);

	v3.push_back("5");
	v3.push_back("6");
	v3.push_back("7");
	std::cout << "v3: ";
	printVector(v3);

	std::cout << "test : pop_back" << std::endl;
	v3.pop_back();
	std::cout << "v3: ";
	printVector(v3);

	std::cout << "test : resize" << std::endl;
	v3.resize(4);
	std::cout << "v3: ";
	printVector(v3);

	std::cout << "test : assign" << std::endl;
	v3.assign(2, "42");
	std::cout << "v3: ";
	printVector(v3);

	v3.swap(v2);
	std::cout << "v3: ";
	printVector(v3);

	std::cout << "v3 == v2: " << (v3 == v2 ? "true" : "false") << std::endl;
	std::cout << "v3 < v2: " << (v3 < v2 ? "true" : "false") << std::endl;
	std::cout << "v3 >= v2: " << (v3 >= v2 ? "true" : "false") << std::endl;

	ft::vector<int> v4;
	for (int i = 0; i < 300000; i++)
	{
		v4.push_back(i);
	}

	clock_t g_end = clock();
	printf("걸린 시간: %.2fms\n",
		   (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000);
}

/*
 **=========================================================================
 **     Stack Test
 **=========================================================================
 */

void stack_test()
{
	clock_t g_start = clock();

	ft::stack<int> s1;
	for (int i = 0; i < 100000; i++)
	{
		s1.push(i * 3);
	}
	std::cout << "s top: " << s1.top() << std::endl;
	std::cout << "s size: " << (s1.empty() ? "true" : "false")
			  << std::endl;

	ft::stack<int> s2(s1);
	std::cout << "s2 top: " << s2.top() << std::endl;
	std::cout << "s2 size: " << (s2.empty() ? "true" : "false")
			  << std::endl;
	std::cout << "s2 empty: " << (s2.empty() ? "true" : "false")
			  << std::endl;

	s2.push(99);
	s2.push(42);
	std::cout << "s2 top: " << s2.top() << std::endl;
	std::cout << "s2 size: " << (s2.empty() ? "true" : "false")
			  << std::endl;

	ft::stack<int> s3 = s2;
	std::cout << "s2 == s3: " << (s2 == s3 ? "true" : "false") << std::endl;

	s3.pop();
	s3.pop();
	s3.pop();
	s3.pop();
	s3.pop();
	std::cout << "s3 top: " << s2.top() << std::endl;
	std::cout << "s2 == s3: " << (s2 == s3 ? "true" : "false") << std::endl;
	std::cout << "s2 != s3: " << (s2 != s3 ? "true" : "false") << std::endl;
	std::cout << "s2 < s3: " << (s2 < s3 ? "true" : "false") << std::endl;
	std::cout << "s2 >= s3: " << (s2 >= s3 ? "true" : "false") << std::endl;

	int count = 0;
	while (!s3.empty())
	{
		count++;
		s3.pop();
	}
	std::cout << "s3 pop count: " << count << std::endl;
	std::cout << "s3 empty: " << (s3.empty() ? "true" : "false")
			  << std::endl;

	clock_t g_end = clock();
	printf("시간: %.2fms\n",
		   (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000);
}

/*
 **=========================================================================
 **     Map Test
 **=========================================================================
 */

static void printMap(const ft::map<std::string, int> &m)
{
	std::cout << '{';
	ft::map<std::string, int>::const_iterator b = m.begin();
	ft::map<std::string, int>::const_iterator e = m.end();
	while (b != e)
	{
		std::cout << b->first << ':' << b->second << ' ';
		b++;
	}
	std::cout << "}\n";
}

void map_test()
{
	clock_t g_start = clock();

	ft::map<std::string, int> m1;
	m1["A"] = 20;
	m1["B"] = 70;
	m1["C"] = 100;
	m1["D"] = 500;
	std::cout << "m1: ";
	printMap(m1);

	ft::map<std::string, int> m2(m1.find("B"), m1.end());
	std::cout << "m2: ";
	printMap(m2);

	ft::map<std::string, int> m3(m1);
	std::cout << "m3: ";
	printMap(m3);

	std::cout << "m3[no key] with []: " << m3["no key"]
			  << std::endl;
	printMap(m3);

	ft::map<std::string, int>::reverse_iterator r_it = m3.rbegin();
	std::cout << '{';
	for (; r_it != m3.rend(); r_it++)
	{
		std::cout << r_it->first << ':' << r_it->second << ' ';
	}
	std::cout << "}\n";

	std::cout << "m3 empty: " << (m3.empty() ? "true" : "false") << std::endl;
	std::cout << "m3 size: " << m3.size() << std::endl;

	std::cout << "m3 clear\n";
	m3.clear();
	std::cout << "m3 size: " << m3.size() << std::endl;
	std::cout << "m3 insert (from m2)\n";
	m3.insert(m2.begin(), m2.end());
	std::cout << "m3 size: " << m3.size() << std::endl;
	std::cout << "m3: ";
	printMap(m3);

	std::cout << "erase 'C'\n";
	m3.erase(m3.find("C"));
	std::cout << "erase 'no key'\n";
	m3.erase("no key");
	std::cout << "m3: ";
	printMap(m3);

	m3.swap(m2);
	std::cout << "m3: ";
	printMap(m3);

	std::cout << "m3 == m2: " << (m3 == m2 ? "true" : "false") << std::endl;
	std::cout << "m3 < m2: " << (m3 < m2 ? "true" : "false") << std::endl;
	std::cout << "m3 >= m2: " << (m3 >= m2 ? "true" : "false") << std::endl;

	ft::map<int, int> mp4;
	for (int i = 0, j = 100; i < 300000; i++, j++)
	{
		mp4.insert(ft::make_pair(i * 2, j));
	}
	std::cout << "count 41: " << mp4.count(41) << std::endl;
	std::cout << "count 50: " << mp4.count(50) << std::endl;
	std::cout << "count 300005: " << mp4.count(300005) << std::endl;
	std::cout << "find 26: " << mp4.find(26)->first << std::endl;
	std::cout << "lower bound 127: " << mp4.lower_bound(127)->first << std::endl;
	std::cout << "upper bound 244: " << mp4.upper_bound(244)->first << std::endl;

	clock_t g_end = clock();
	printf("시간: %.2fms\n",
		   (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000);
}

/*
 **=========================================================================
 **     Launch Tests
 **=========================================================================
 */

int main()
{
	std::cout << "\n***** VECTOR TEST *****\n"
			  << std::endl;
	vector_test();
	std::cout << std::endl;

	std::cout << "\n***** STACK TEST *****\n"
			  << std::endl;
	stack_test();
	std::cout << std::endl;

	std::cout << "\n***** MAP TEST *****\n"
			  << std::endl;
	map_test();
	std::cout << std::endl;

	return 0;
}