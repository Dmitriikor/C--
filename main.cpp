#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <vector>



template <typename T>
struct Node
{
	T data;
	Node* next = nullptr;

	explicit Node(const T& value) : data(value)
	{
	}
	~Node() = default;
	//{	
		//std::cout<< "\n NODE  Destruct\n";
	//}
};

template <typename T>
class List
{
private:
	Node<T>* tail = nullptr;
	Node<T>* head = nullptr;
	size_t _size = 0;
 	friend class iterator;
	Node<T>* create_node(const T& value) 
	{
		Node<T>* new_node_ = nullptr;

		new_node_ = new(std::nothrow) Node<T>(value);

		if (new_node_ == nullptr)
		{
			//throw std::bad_alloc();
			return nullptr;
		}
		++_size;
		return new_node_;
	}
	void delete_node(Node<T>*& current)
	{
		//std::cout << "\n delete statrt\n";
		delete current;
		//std::cout << "\n delete end\n";
		--_size;
	}
	void copy_node(const List& other) 
	{
        if (other.head == nullptr) 
		{
            return;
        }

        auto* otherCurrent = other.head;
        head = create_node(otherCurrent->data);
        otherCurrent = otherCurrent->next;
        auto* thisCurrent = head;

        while (otherCurrent != nullptr) {
            thisCurrent->next = create_node(otherCurrent->data);
            thisCurrent = thisCurrent->next;
            if (thisCurrent == nullptr) 
			{
                throw std::bad_alloc();
            }
            otherCurrent = otherCurrent->next;
        }
        tail = thisCurrent;
    }
	size_t debug_size() const
	{
		int size = 0;
		Node<T>* current = head;
		while (current != nullptr)
		{
			++size;
			current = current->next;
		}
		//std::cout << "\n size = " << size << std::endl;
		return size;
	}
	void clerar()
	{
		while (head != nullptr)
		{
			Node<T>* temp = head;
			head = head->next;
			delete_node(temp); //delete temp;
		}
	}

public:
	List() = default;

	List& operator=(const List& other)
	{
		if (this == &other)
		{
			return *this;
		}
		if (other.head == nullptr)
		{
			return *this;
		}
		clerar(); 
        copy_node(other);

		assert(head->data == other.head->data);
		assert(tail->data == other.tail->data);
		assert(_size == other._size);

        return *this;
	}

	List(const List& other)
	{
		if (this == &other)
		{
			return;
		}
		if (other.head == nullptr)
		{
			return;
		}
		 
		copy_node(other);

		//std::cout << "\n other.tail->data = " << other.tail->data << std::endl;
		//std::cout << "\n tail->data = " << tail->data;
		assert(head->data == other.head->data);
		assert(tail->data == other.tail->data);
		assert(_size == other._size);
	}

	List(List&& other) noexcept
	{
		head = other.head; 		// tacked other.head to us
		tail = other.tail; 		// tacked other.tail to us
		_size = other._size; 	// tacked other._size to us

		other.head = nullptr;  	// block "empty" other.head List
		other.tail = nullptr;	// block "empty" other.tail List
		other._size = 0;		// set other._size to 0
	}

	~List()
	{
		//std::cout<< "\n Destruct LIST\n";
		clerar();
	}

	size_t size() const
	{
		//std::cout << "\n _size = " << _size << std::endl;
		assert(debug_size() == _size);

		return _size;
	}
	void push_front(const T& value)
	{
		if (head == nullptr)
		{
			head = create_node(value); //new Node<T>(value);
			tail = head;
			return;
		}

		auto* temp = create_node(value); //new Node<T>(value);
		temp->next = head;
		head = temp;
	}
	void push_back(const T& value)
	{
		if (head == nullptr)
		{
			head = create_node(value);//new Node<T>(value);
			tail = head;
			return;
		}

		tail->next = create_node(value); //new Node<T>(value);
		tail = tail->next;
	}
	void pop_front()
	{
		if (head == nullptr)
		{
			throw std::out_of_range("Head is nullptr");
			return; //!!! throw
		}

		if (head->next == nullptr)
		{
			delete_node(head);//delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}

		Node<T>* deleted = head;
		head = head->next;

		delete_node(deleted);
		//delete deleted;
		//--_size;
	}
	void pop_back()
	{
		if (tail == nullptr)
		{
			throw std::out_of_range("Tail is nullptr");
			return;  //!!! throw
		}

		if (head == nullptr)
		{
			return; 
		}

		if (head->next == nullptr)
		{
			delete_node(head);//delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}

		Node<T>* temp = head;
		while (temp->next != tail)
		{
			temp = temp->next;
		}

		Node<T>* deleted = tail;
		tail = temp;
		tail->next = nullptr;

		delete_node(deleted);
		//delete deleted;
		//--_size;
	}

	const T& get_head_data() const
	{
		if (head == nullptr)
		{
			throw std::out_of_range("Head is nullptr");
		}
		return head->data;
	}

	const T& get_tail_data() const
	{
		if (tail == nullptr)
		{
			throw std::out_of_range("Tail is nullptr");
		}
		return tail->data;
	}
	void print() const
	{
		Node<T>* current = head;
		while (current != nullptr)
		{
			std::cout << current->data << "; ";
			current = current->next;
		}
	}

	T& at(size_t id) const
	{
		Node<T>* current = head;

		for (size_t i = 0; current != nullptr; ++i)
		{
			if (i == id)
			{
				return current->data;
			}
			current = current->next;
		}

		throw std::out_of_range("Index out of range");
	}
	std::vector<T> to_vector() const
	{
		Node<T>* current = head;
		std::vector<T> data_accum;

		while (current != nullptr)
		{
			data_accum.push_back(current->data);
			current = current->next;
		}

		return data_accum;
	}


	class iterator
	{

	public:
		using iterator_category = std::forward_iterator_tag;  
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		explicit iterator(Node<T>* startNode) : current(startNode) {}

		bool operator!=(const iterator& other) const
		{
			return !(*this == other);
		}

		bool operator==(const iterator& other) const
		{
			return current == other.current;
		}

		iterator& operator++() 
		{
			current = current->next;
			return *this;
		}

		iterator operator++(int) 
		{
			iterator temp = *this;
			current = current->next;
			return temp;
		}

		T* operator->()
		{
			return &current->data;
		}

		T& operator*()
		{
			return current->data;
		}

	private:
		
		friend class List<T>; 
		Node<T>* current;
	};

	iterator begin() {
		return iterator(head);
	}
	iterator end() {
		return iterator(nullptr);
	}
	void insert(iterator it, const T& value)
	{
		//if (it.current == nullptr)
		//throw;

		auto* inserted = create_node(value); //new Node<T>(value);

		inserted->next = it.current->next;
		it.current->next = inserted;

		if (it.current == tail)
			tail = inserted;
	}
	void insert(const T& value, iterator it)
	{
		auto* inserted = create_node(value); //new Node<T>(value);

		if (it.current == head)
		{
			inserted->next = head;
			head = inserted;

			if (it.current == nullptr)
				tail = head;

			return;
		}

		auto old = head;
		auto current = head->next;
		while (current != it.current)
		{
			old = current;
			current = current->next;
		}

		inserted->next = it.current; // not it.current->next; !!!!
		old->next = inserted;

		if (old == tail)
			tail = inserted;

	}
	void insert(int id, const T& value)
	{
		auto* inserted = create_node(value); //new Node<T>(value);

		if (head == nullptr)
		{
			if (id == 0)
			{
				inserted->next = head;
				head = inserted;
				tail = head;
				return;
			}
			else
				throw std::out_of_range("Index out of range");
		}

		auto* temp = head;

		int counter = 0;
		while (temp != nullptr && counter != id - 1)
		{
			temp = temp->next;
			++counter;
		}

		if (temp == nullptr)
		{
			delete_node(inserted);
			//delete inserted;
			throw std::out_of_range("Index out of range");
		}

		inserted->next = temp->next;

		temp->next = inserted;

		if (temp == tail)
			tail = inserted;
	}
	void erase(const iterator& it)
	{
		if (it.current == nullptr)
			throw std::out_of_range("it.current == nullptr");

		if (it == begin())
		{
			auto* temp = head;
			head = head->next;
			delete_node(temp);//delete temp;

			if (head == nullptr)
				tail = nullptr;

			return;
		}

		auto old = head;
		auto current = head->next;
		while (current != it.current)
		{
			old = current;
			current = current->next;
		}
		//std::cout << old->data << "/" << ";\n";

		if (current == tail)
			tail = current->next;

		old->next = current->next;

		delete_node(current);
	}

private:
	void reverse()
	{
		//reverse_(head);
		reverse_();
		std::cout << "\n";
	}

	static void reverse_(Node<T>* current)
	{
		if (current == nullptr)
		{
			return;
		}

		reverse_(current->next);
		std::cout << current->data << "; ";
	}

	void reverse_()
	{
		std::stack<T> st;

		auto* current = head;
		while (current != nullptr)
		{
			st.push(current->data);
			current = current->next;
		}

		while (!st.empty())
		{
			std::cout << st.top() << "; ";

			st.pop();
		}
	}

};


 


int main()
{
	List<int> myList;

	myList.push_back(10);
	myList.push_back(20);
	myList.push_back(30);

	assert(myList.size() == 3);
	std::vector<int> expected = { 10, 20, 30 };
	std::vector<int> to_vector = myList.to_vector();
	for (size_t i = 0; i < to_vector.size(); i++)
	{
		assert(to_vector[i] == expected[i]);
	}

	//// myList.print(); // Выведет: 10 20 30
	//std::cout << "\n\n\n";

	assert(myList.at(2) == 30);

	//// myList.print();
	//std::cout << "\n" << myList.size() << "\n";

	myList.push_front(-10);
	std::vector<int> expected_front = { -10, 10, 20, 30 };
	std::vector<int> to_vector_front = myList.to_vector();
	for (size_t i = 0; i < to_vector_front.size(); i++)
		assert(to_vector_front[i] == expected_front[i]);

	//// myList.print();
	//std::cout << "\n" << myList.size() << "\n";

	assert(myList.get_head_data() == -10);
	assert(myList.get_tail_data() == 30);
	myList.pop_back();
	assert(myList.get_tail_data() == 20);
	myList.push_back(30);
	assert(myList.get_tail_data() == 30);
	myList.pop_back();
	assert(myList.get_tail_data() == 20);
	assert(myList.get_head_data() == -10);

	std::vector<int> expected_2 = { -10, 10,-20, 20 };
	myList.insert(2, -20);

	std::vector<int> to_vector_2 = myList.to_vector();

	for (size_t i = 0; i < to_vector_2.size(); i++)
		assert(to_vector_2[i] == expected_2[i]);


	int i = 0;
	for (auto it = myList.begin(); it != myList.end(); ++it, ++i)
		//assert(it.value() == expected_2[i]);
		assert(*it == expected_2[i]);

	//std::cout << "\n 1 - " << myList.size() << "\n";
	// myList.print();
	// std::cout << std::endl;
	{
		auto it = myList.begin();
		++it;

		myList.insert(100, it);
		// myList.print();
		// std::cout << std::endl;
	}
	// myList.print();
	// std::cout << std::endl;
	//std::cout << "\n 2 - " << myList.size() << "\n";
	/*{
		List<int> myList2;

		myList2.push_back(1);

		auto it = myList2.begin();

		myList.insert(100, it);

		// myList.print();
		myList2.print();
		std::cout << std::endl;
	}*/

	{
		auto it = myList.begin();
		++it;
		myList.insert(it, 99);
		// myList.print();
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
		List<int> copiedList(myList);
		//std::cout << "\n" << myList.size() << "\n";
		//std::cout << "\n" << copiedList.size() << "\n";
		assert(copiedList.size() == myList.size());
    	for (size_t ii = 0; ii < copiedList.size(); ++ii) 
        assert(copiedList.at(ii) == myList.at(ii));
	}
	{
		List<int> myList2;
		myList2.push_back(4);
		myList2.push_back(5);
		myList2.push_back(6);
		List<int> movedList(std::move(myList2));
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
		List<int> list1;
		list1.push_back(1);
		list1.push_back(2);
		list1.push_back(3);

		List<int> list2;
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
