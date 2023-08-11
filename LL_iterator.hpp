#pragma once

template <typename T>
class LL_List;
template <typename T>
struct Node;

template <typename T>
	class LL_Iterator
	{
        //friend class LL_List<T>;
	public:
		using iterator_category = std::forward_iterator_tag;  
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		explicit LL_Iterator(Node<T>* startNode) : current(startNode) {}

		bool operator!=(const LL_Iterator& other) const
		{
			return !(*this == other);
		}

		bool operator==(const LL_Iterator& other) const
		{
			return current == other.current;
		}

		LL_Iterator& operator++() 
		{
			current = current->next;
			return *this;
		}

		LL_Iterator operator++(int) 
		{
			LL_Iterator temp = *this;
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
