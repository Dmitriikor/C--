#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <vector>
#include "TEST.hpp"
#include "LL_List.hpp"

int main()
{
    // Create an instance of the __TESTS__ class with the template type int
    __TESTS__<int> p(9);

    // Create an instance of the LL_List class with the template type int
    LL_List<int> myList;

    // Add elements to the list using the push_back function
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    // Check if the size of the list is equal to 3
    assert(myList.size() == 3);

    // Create a vector with the expected values
    std::vector<int> expected = { 10, 20, 30 };

    // Convert the list to a vector and compare it with the expected vector
    std::vector<int> to_vector = myList.to_vector();
    for (size_t i = 0; i < to_vector.size(); i++)
    {
        assert(to_vector[i] == expected[i]);
    }

    // Check if the element at index 2 of the list is equal to 30
    assert(myList.at(2) == 30);

    // Add an element to the front of the list
    myList.push_front(-10);

    // Create a vector with the expected values after adding an element to the front
    std::vector<int> expected_front = { -10, 10, 20, 30 };

    // Convert the list to a vector and compare it with the expected vector
    std::vector<int> to_vector_front = myList.to_vector();
    for (size_t i = 0; i < to_vector_front.size(); i++)
        assert(to_vector_front[i] == expected_front[i]);

    // Check if the head data of the list is equal to -10
    assert(myList.get_head_data() == -10);

    // Check if the tail data of the list is equal to 30
    assert(myList.get_tail_data() == 30);

    // Remove the last element from the list
    myList.pop_back();

    // Check if the tail data of the list is equal to 20
    assert(myList.get_tail_data() == 20);

    // Add an element to the end of the list
    myList.push_back(30);

    // Check if the tail data of the list is equal to 30
    assert(myList.get_tail_data() == 30);

    // Remove the last element from the list
    myList.pop_back();

    // Check if the tail data of the list is equal to 20
    assert(myList.get_tail_data() == 20);

    // Check if the head data of the list is equal to -10
    assert(myList.get_head_data() == -10);

    // Create a vector with the expected values after inserting an element at index 2
    std::vector<int> expected_2 = { -10, 10, -20, 20 };

    // Insert an element at index 2 of the list
    myList.insert(2, -20);

    // Convert the list to a vector and compare it with the expected vector
    std::vector<int> to_vector_2 = myList.to_vector();
    for (size_t i = 0; i < to_vector_2.size(); i++)
        assert(to_vector_2[i] == expected_2[i]);

    // Iterate over the list using an iterator and compare the values with the expected vector
    int i = 0;
    for (auto it = myList.begin(); it != myList.end(); ++it, ++i)
        assert(*it == expected_2[i]);

    // Insert an element with the value 100 at the position after the first element
    {
        auto it = myList.begin();
        ++it;
        myList.insert(100, it);
    }

	{
		auto it = myList.begin();
		++it;
		myList.insert(it, 99);
		std::cout << std::endl;
	}

	auto it_2 = myList.begin();
	++it_2;
	myList.erase(it_2);

	// myList.print();
	//std::cout << std::endl;
	//myList.reverse();
	//std::cout << std::endl;

	{
		LL_List<int> copiedList(myList);
		//std::cout << "\n" << myList.size() << "\n";
		//std::cout << "\n" << copiedList.size() << "\n";
		assert(copiedList.size() == myList.size());
    	for (size_t ii = 0; ii < copiedList.size(); ++ii) 
        assert(copiedList.at(ii) == myList.at(ii));
	}
	{
		LL_List<int> myList2;
		myList2.push_back(4);
		myList2.push_back(5);
		myList2.push_back(6);
		LL_List<int> movedList(std::move(myList2));
		assert(myList2.size() == 0);
		try
		{
			//myList2.pop_back();
			myList2.pop_front();
		}
		catch(const std::exception& e)
		{
			assert(std::cerr << e.what() << " | ");
		}
		try
		{
			myList2.pop_back();
			//myList2.pop_front();
		}
		catch(const std::exception& ee)
		{
			assert(std::cerr << ee.what() << "\n\n");
		}
		assert(movedList.size() == 3);
		assert(movedList.at(0) == 4);
		assert(movedList.at(1) == 5);
		assert(movedList.at(2) == 6);
	}
	{
		LL_List<int> list1;
		list1.push_back(1);
		list1.push_back(2);
		list1.push_back(3);

		LL_List<int> list2;
		list2.push_back(4);
		list2.push_back(5);

		list2 = list1;  

		assert(list1.size() == list2.size());

		auto iter1 = list1.begin();
		auto iter2 = list2.begin();

		while (iter1 != list1.end()) {
			assert(*iter1 == *iter2);
			++iter1;
			iter2++;
		}
	}

	assert(std::cout << "\nAll tests passed successfully!\n\n" << std::endl);
	return 0;
}
//test git2