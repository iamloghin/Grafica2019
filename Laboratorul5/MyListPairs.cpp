#include "MyListPairs.h"

MyListPairs::MyListPairs()
{
	std::cout << "List of pairs created." << std::endl;
}

MyListPairs::~MyListPairs()
{
	std::cout << "List of pairs destroyed." << std::endl;
}

void MyListPairs::add_element(int index, element_type my_pair)
{
	this->container_.emplace_back(index, my_pair);
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

int MyListPairs::count() const
{
	return this->container_.size();
}

std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<int, std::pair<int, int>>>>> MyListPairs::
get_element(int next_position)
{
	return std::next(container_.begin(), next_position);
}
