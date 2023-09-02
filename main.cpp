#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <vector>
#include "TEST.hpp"
#include "LL_List.hpp"

import Module.test; //test module
import CarnifexModule; //carnifex module


int main()
{
	std::cout << "Testing" << std::endl;

	try
	{
		MyClassModule aModule;
		aModule.MyFuncModule();

		//MyFunc();
		{
			// Create an instance of the __TESTS__ class with the template type int
			__TESTS__<int> p(9);

			// Create an instance of the LL_List<int> class with the template type int
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
			std::vector<int> expected_2 = { -10, 10, 20 };

			// Insert an element at index 2 of the list
			//myList.insert(2, -20);

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
				myList.insert(it, 100);
			}

			{
				auto it = myList.begin();
				++it;
				myList.insert_after(it, 99);
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
				catch (const std::exception& e)
				{
					std::cout << e.what() << " | ";
				}

				try
				{
					myList2.pop_back();
					//myList2.pop_front();
				}
				catch (const std::exception& ee)
				{
					std::cout << ee.what() << " | ";
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
			{

				LL_List<int> list1;
				for (int i = 0; i < 5; ++i)
				{
					list1.push_back(i);
				}


				LL_List<int> list2;
				for (int i = 5; i < 10; ++i)
				{
					list2.push_back(i);
				}


				LL_List<int> list3 = list1;
				list3 = std::move(list2);


				assert(list2.size() == 0);
				assert(list2.empty());
				assert(list2.begin() == list2.end());


				assert(list3.size() == 5);
				assert(!list3.empty());
				for (size_t i = 0; i < list3.size(); ++i)
				{
					assert(list3.at(i) == (int)i + 5);
				}


				assert(list3.begin() != list3.end());
				assert(list3.size() == 5);


				assert(list1.size() == 5);
				assert(!list1.empty());
				std::cout << " \n";
				for (size_t i = 0; i < list1.size(); ++i)
				{
					assert(list1.at(i) == (int)i);
				}

			}

			assert(std::cout << "\nAll tests passed successfully!\n\n" << std::endl);

		}
		
		{
			Carnifex<int> test(new int(10));

			Carnifex<int> sharedPtr1(new int(42));
			assert(*sharedPtr1 == 42);
			assert(sharedPtr1.block_->counter_ == 1);

			Carnifex<int> sharedPtr2 = sharedPtr1;

			assert(*sharedPtr1 == 42);
			assert(sharedPtr1.block_->counter_ == 2);
			assert(*sharedPtr2 == 42);
			assert(sharedPtr2.block_->counter_ == 2);

			sharedPtr2 = new int(84);
			assert(*sharedPtr1 == 42);
			assert(sharedPtr1.block_->counter_ == 1);
			assert(*sharedPtr2 == 84);
			assert(sharedPtr2.block_->counter_ == 1);

			Carnifex<int> nullSharedPtr;
			assert(nullSharedPtr.block_->object_ == nullptr);
			assert(nullSharedPtr.block_->counter_ == 1);
		}

		int number = 0;
		{
			struct MyClass
			{
				int* flag;
				int value;
				MyClass(int v, int* const flag = nullptr) : flag(flag), value(v) {
					if (flag) *flag = +1;
				}
				~MyClass() {
					if (flag) *flag = -1;
				}
			};

			Carnifex<MyClass> classPtr(new MyClass(10, &number));
			assert(classPtr->value == 10);
			assert(number == 1);

			Carnifex<MyClass> sharedClassPtr1 = classPtr;
			Carnifex<MyClass> sharedClassPtr2 = sharedClassPtr1;
			sharedClassPtr1->value = 20;
			assert(sharedClassPtr2->value == 20);
			assert(number == 1);
		}

		assert(number == -1);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	printf("Press Enter to continue...\n");
	getchar(); // Wait for user to press Enter
	return 0;
}
