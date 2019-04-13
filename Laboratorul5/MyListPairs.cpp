#include "MyListPairs.h"

MyListPairs::MyListPairs()
{
	pairs_ = 0;
	std::cout << "List of pairs created." << std::endl;
}

MyListPairs::~MyListPairs()
{
	std::cout << "List of pairs destroyed." << std::endl;
}

void MyListPairs::add_element(int index, element_type my_pair)
{
	this->container_.emplace_back(index, my_pair);
	pairs_++;
}

int MyListPairs::get_pairs()
{
	return pairs_;
}

void MyListPairs::display_elements()
{
	auto k = 0;
    for (auto& it : this->container_)
    {
        std::cout << "*it " << k << " = " << it.first << " - " << it.second.first << " : " << it.second.second << std::endl;
        ++k;
    }
    std::cout << "First element in container_ = " << this->container_.front().first << " - " << this->container_.front().second.first << " : " << this->container_.front().second.second << std::endl << std::endl;
}

std::list<std::pair<int,int>> MyListPairs::get_element_type_list()
{
	std::list<std::pair<int,int>> temp = {};
	auto k = 0;
    for (auto& it : this->container_)
    {
		temp.push_back((std::make_pair(it.second.first, it.second.second)));
        ++k;
    }
	return temp;
}

std::vector<float> MyListPairs::get_x_points()
{
    std::vector<float> temp_array(6);

	auto k = 0;
    for (auto& it : this->container_)
    {
        temp_array[k] = it.second.first;
        k++;
    }
   
   return temp_array;
}


std::vector<float> MyListPairs::get_y_points()
{
    std::vector<float> temp_array(6);

	auto k = 0;
    for (auto& it : this->container_)
    {
        temp_array[k] = it.second.second;
        k++;
    }
   
   return temp_array;
}

int MyListPairs::count() const
{
	return this->container_.size();
}

std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int, std::pair<int, int>>>>> MyListPairs::
get_element(int next_position)
{
	return std::next(container_.begin(), next_position);
}
