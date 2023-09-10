#include <iostream>
export module List;
import CarnifexModule;
//#pragma once

//TODO change

//import std;
import <cassert>;
import <stack>;
import <vector>;
template <typename T>
struct Node
{
	T data;
	//Node* next = nullptr;

	//TODO
	Carnifex<Node<T>> next = nullptr;

	explicit Node(const T& value) : data(value)
	{
		std::cout << "" << std::endl;
	}
	~Node() = default;
};




export template <typename T>
class LL_List
{
private:
	//Node<T>* head_ = nullptr;
	Carnifex<Node<T>> head_;
	//Node<T>* tail_ = nullptr;
	Carnifex<Node<T>> tail_;

	size_t size_ = 0;
	friend class iterator;

	Carnifex<Node<T>> create_node_(const T& value)
	{
		Carnifex<Node<T>> new_node_(new(std::nothrow) Node<T>(value));

		if (new_node_ == nullptr)
		{
			throw std::bad_alloc();
		}
		++size_;

		return new_node_;
	}

	//TODO ��������
	void copy_nodes_(const LL_List& other)
	{
		if (other.head_ == nullptr)
		{
			head_ = nullptr;
			tail_ = nullptr;
			return;
		}

		Carnifex<Node<T>> otherCurrent = other.head_;
		head_ = *create_node_(otherCurrent->data);

		otherCurrent = otherCurrent->next;
		Carnifex<Node<T>> thisCurrent = head_;

		while (otherCurrent != nullptr)
		{
			try
			{
				thisCurrent->next = *create_node_(otherCurrent->data);
				thisCurrent = thisCurrent->next;
			}
			catch (const std::exception& e)
			{
				clear_();
				std::cout << e.what() << '\n';
				throw;
			}

			otherCurrent = otherCurrent->next;
		}
		tail_ = thisCurrent;
	}

	size_t debugsize_() const
	{
		int size = 0;
		Carnifex<Node<T>> current = head_;
		while (current != nullptr)
		{
			++size;
			current = current->next;
		}
		//std::cout << "\n size = " << size << std::endl;
		return size;
	}
	void clear_()
	{
		head_ = nullptr;
		tail_ = nullptr;
	}

	void test_head_tail_(const LL_List& other_)
	{
		//assert(head_->data == other_.head_->data);
		//assert(tail_->data == other_.tail_->data);
		//assert(size_ == other_.size_);
	}

public:
	LL_List() = default;

	LL_List& operator=(const LL_List& other)
	{
		if (this == &other)
		{
			return *this;
		}
		clear_();
		copy_nodes_(other);

		test_head_tail_(other);

		return *this;
	}

	LL_List(const LL_List& other)
	{
		copy_nodes_(other);

		//std::cout << "\n other.tail_->data = " << other.tail_->data << std::endl;
		//std::cout << "\n tail_->data = " << tail_->data;
		test_head_tail_(other);
	}

	LL_List(LL_List&& other) noexcept
	{
		head_ = other.head_; 		// tacked other.head_ to us
		tail_ = other.tail_; 		// tacked other.tail_ to us
		size_ = other.size_; 		// tacked other.size_ to us

		other.head_ = nullptr;  	// block "empty" other.head_ LL_List
		other.tail_ = nullptr;		// block "empty" other.tail_ LL_List
		other.size_ = 0;			// set other.size_ to 0
	}

	LL_List& operator=(LL_List&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}
		clear_();
		head_ = other.head_;
		tail_ = other.tail_;
		size_ = other.size_;

		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.size_ = 0;
		return *this;
	}

	~LL_List()
	{
		//std::cout<< "\n Destruct LIST\n";
		//clear_();
	}

	size_t size() const
	{
		//std::cout << "\n size_ = " << size_ << std::endl;
		//assert(debugsize_() == size_);

		return size_;
	}

	bool empty() const
	{
		if (head_ == nullptr)
		{
			//assert(head_ == nullptr && tail_ == nullptr && size_ == 0);
			return true;
		}
		return false;
	}
	void clear()
	{
		clear_();
	}
	void push_front(const T& value)
	{
		if (head_ == nullptr) //TODO empty()
		{
			head_ = create_node_(value);

			tail_ = head_;
			return;
		}

		Node<T>* current = create_node_(value);

		current->next = head_;
		head_ = current;
	}
	void push_back(const T& value)
	{
		if (head_ == nullptr) //TODO empty()
		{
			head_ = create_node_(value); //

			tail_ = head_;
			return;
		}

		Node<T>* current = create_node_(value);

		tail_->next = current;
		tail_ = tail_->next;
	}
	void pop_front()
	{
		if (head_ == nullptr) //TODO empty()
		{
			throw std::out_of_range("head_ is nullptr");
		}

		if (head_->next == nullptr)
		{
			delete_node_(head_);
			head_ = nullptr;
			tail_ = nullptr;
			return;
		}

		Node<T>* deleted = head_;
		head_ = head_->next;

		delete_node_(deleted);
	}
	void pop_back()
	{
		if (head_ == nullptr) //TODO empty()
		{
			throw std::out_of_range("tail_ is nullptr");
		}

		if (head_->next == nullptr)
		{
			delete_node_(head_);//delete head_;
			head_ = nullptr;
			tail_ = nullptr;
			return;
		}

		//TODO search
		Node<T>* temp = head_;
		while (temp->next != tail_)
		{
			temp = temp->next;
		}

		Node<T>* deleted = tail_;
		tail_ = temp;
		tail_->next = nullptr;

		delete_node_(deleted);
	}

	const T& get_head_data() const
	{
		if (head_ == nullptr)
		{
			throw std::out_of_range("head_ is nullptr");
		}
		return head_->data;
	}

	const T& get_tail_data() const
	{
		if (tail_ == nullptr)
		{
			throw std::out_of_range("tail_ is nullptr");
		}
		return tail_->data;
	}
	void print() const
	{
		Node<T>* current = head_;
		while (current != nullptr)
		{
			std::cout << current->data << "; ";
			current = current->next;
		}
	}

	T& at(size_t id) const
	{
		Node<T>* current = head_;

		size_t i = 0;

		while (current != nullptr)
		{
			if (i == id)
			{
				return current->data;
			}
			current = current->next;
			++i;
		}

		throw std::out_of_range("Index out of range");
	}
	std::vector<T> to_vector() const
	{
		std::vector<T> data_accum;
		data_accum.reserve(size_);

		Node<T>* current = head_;
		while (current != nullptr)
		{
			data_accum.push_back(current->data);
			current = current->next;
		}

		return data_accum;
	}
private:
	class iterator
	{
		friend class LL_List<T>;
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

		friend class LL_List<T>;
		Node<T>* current;
	};

public:
	//using iterator = iterator<T>;

	iterator begin() {
		return iterator(head_);
	}
	iterator end() {
		return iterator(nullptr);
	}

	void insert_after(iterator it, const T& value)
	{
		if (it.current == nullptr)
			throw std::out_of_range("it.current == nullptr");

		Node<T>* inserted = create_node_(value);

		inserted->next = it.current->next;
		it.current->next = inserted;

		if (it.current == tail_)
			tail_ = inserted;

	}

	void insert(iterator it, const T& value)
	{
		if (it.current == nullptr)
			throw std::out_of_range("it.current == nullptr");

		Node<T>* inserted = create_node_(value);


		if (it.current == head_)
		{
			inserted->next = head_;
			head_ = inserted;

			if (it.current == nullptr)
				tail_ = head_;

			return;
		}

		auto old = head_;
		auto current = head_->next;
		while (current != it.current)
		{
			old = current;
			current = current->next;
		}

		inserted->next = it.current;
		old->next = inserted;

		if (old == tail_)
			tail_ = inserted;

	}

	void erase(const iterator& it)
	{
		if (it.current == nullptr) //TODO empty()
			throw std::out_of_range("it.current == nullptr");

		if (it == begin())
		{
			Node<T>* temp = head_;
			head_ = head_->next;
			delete_node_(temp);

			if (head_ == nullptr)
				tail_ = nullptr;

			return;
		}

		auto old = head_;
		auto current = head_->next;
		while (current != it.current)
		{
			old = current;
			current = current->next;
		}
		//std::cout << old->data << "/" << ";\n";

		if (current == tail_)
			tail_ = current->next;

		old->next = current->next;

		delete_node_(current);
	}

private:
	void reverse()
	{
		//reverse_(head_);
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

		Node<T>* current = head_;
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

	//TODO remove this insert ?
	void insert(int id, const T& value)
	{
		Node<T>* inserted = create_node_(value);


		if (head_ == nullptr) //TODO empty()
		{
			if (id == 0)
			{
				inserted->next = head_;
				head_ = inserted;
				tail_ = head_;
				return;
			}
			else
				throw std::out_of_range("Index out of range");
		}

		Node<T>* temp = head_;

		int counter = 0;
		while (temp != nullptr && counter != id - 1)
		{
			temp = temp->next;
			++counter;
		}

		if (temp == nullptr)
		{
			delete_node_(inserted);
			//delete inserted;
			throw std::out_of_range("Index out of range");
		}

		inserted->next = temp->next;

		temp->next = inserted;

		if (temp == tail_)
			tail_ = inserted;
	}
};

//export namespace test_template
//{
//	template <typename T>
//	
//}