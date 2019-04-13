#pragma once

#include <list>
#include <iostream>
#include <string>
#include <vector>

typedef std::pair<int, int> element_type;

class MyListPairs
{
private:
	int pairs_;
	std::list <std::pair<int, element_type>> container_;
public:
	MyListPairs();
	~MyListPairs();
	void add_element(int index, element_type my_pair);
	void display_elements();
	std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int, std::pair<int, int>>>>> get_element(int next_position);
	std::list<std::pair<int,int>> get_element_type_list();
	std::vector<float> get_x_points();
	std::vector<float> get_y_points();
	int count() const;
	int get_pairs();
};

