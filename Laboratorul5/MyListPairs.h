#pragma once

#include <list>
#include <iostream>
#include <string>
typedef std::pair<int, int> element_type;

class MyListPairs
{
private:
	std::list <std::pair<int, element_type>> container_;
public:
	MyListPairs();
	~MyListPairs();
	void add_element(int index, element_type my_pair);
	void display_elements();
	std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int, std::pair<int, int>>>>> get_element(int next_position);
	int count() const;
};

