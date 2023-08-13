#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <vector>
#include "LL_iterator.hpp"

// template <typename T>
// class LL_Iterator;

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
class LL_List
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
	void copy_node(const LL_List& other) 
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
				clearerr();
                throw std::bad_alloc();
            }
            otherCurrent = otherCurrent->next;
        }
        tail = thisCurrent;
    }
	void check_node(Node<T>* current) const
	{
		if (temp == nullptr)
		{
			throw std::bad_alloc();
		}
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
	LL_List() = default;

	LL_List& operator=(const LL_List& other)
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

	LL_List(const LL_List& other)
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

	LL_List(LL_List&& other) noexcept
	{
		head = other.head; 		// tacked other.head to us
		tail = other.tail; 		// tacked other.tail to us
		_size = other._size; 	// tacked other._size to us

		other.head = nullptr;  	// block "empty" other.head LL_List
		other.tail = nullptr;	// block "empty" other.tail LL_List
		other._size = 0;		// set other._size to 0
	}

	~LL_List()
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
			check_node(head);
			tail = head;
			return;
		}

		auto* current = create_node(value); //new Node<T>(value);
		check_node(current);
		current->next = head;
		head = current;
	}
	void push_back(const T& value)
	{
		if (head == nullptr)
		{
			head = create_node(value);//new Node<T>(value);
			check_node(head);
			tail = head;
			return;
		}

		tail->next = create_node(value); //new Node<T>(value);
		check_node(current);
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

    using iterator = LL_Iterator<T>;

	iterator begin() {
		return iterator(head);
	}
	iterator end() {
		return iterator(nullptr);
	}

	void insert(iterator it, const T& value)
	{
		if (it.current == nullptr)
			throw std::out_of_range("it.current == nullptr");

		auto* inserted = create_node(value); //new Node<T>(value);
		check_node(inserted);
		inserted->next = it.current->next;
		it.current->next = inserted;

		if (it.current == tail)
			tail = inserted;
	}
	void insert(const T& value, iterator it)
	{
		if (it.current == nullptr)
			throw std::out_of_range("it.current == nullptr");

		auto* inserted = create_node(value); //new Node<T>(value);
		check_node(inserted);

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
		check_node(inserted);
		
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
