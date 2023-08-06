#include <iostream>
#include <vector>
#include <cassert>
#include "LinkedListIterator.hpp"

template <typename T>
struct Node
{
    T data;
    Node* next = nullptr;

    explicit Node(const T& value /*const int index*/) : data(value)
    {}
};

template <typename T>
struct List
{
private:
    Node<T>* tail=nullptr;

public:
    Node<T>* head = nullptr;
    
    List() = default;

    ~List()
    {
        while (head != nullptr)
        {
            Node<T>* temp = head;
            head = head->next;
            //std::cout<< "\n Destruct\n";
            temp->data.~T();

             delete temp;
        }
    }

    int size() const 
    {
        int size = 0;
        Node<T>* current = head;
        while (current != nullptr)
        {
            ++size;
            current=current->next;
        }
        return size;
    }

    void push_back(const T& value) 
    {
        if (head == nullptr) 
        {
            head = new Node<T>(value);
            tail = head;
            return;
        }

        tail->next = new Node<T>(value);
        tail = tail->next;
    }

    void pop_back() 
    {   
        if (head == nullptr) 
        {
            return;
        }

        if (head->next == nullptr) 
        {
            delete head;
            head = nullptr;
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

        delete deleted;
    }

    void pop_front() 
    {
        if (head == nullptr)
            return;

        if (head->next == nullptr) 
        {
            delete head;
            head = nullptr;
            return; 
        }

        Node<T>* deleted = head; 
        head = head->next;

        delete deleted;
    }

    const T& get_head_data() const
    {
        return head->data;
    }

    const T& get_tail_data() const
    {
        return tail->data;
    }

    void push_front(const T& value)
    {

        if (head == nullptr) 
        {
            head = new Node<T>(value);  
            return;  
        }

        auto* temp = new Node<T>(value); 
        temp->next = head;  
        head = temp;  
    }

    void print() const
    {
        Node<T>* current = head;  
        while (current != nullptr) 
        {
            std::cout << current->data <<"; "; 
            current = current->next; 
        }
    }

    T at(int id) const   
    {
        Node<T>* current = head;  

        for (int i = 0; current != nullptr; ++i)  
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

    void insert(int id, const T& value)
    {
        auto* inserted = new Node<T>(value);  

        if (head == nullptr || id == 0)  
        {
            inserted->next = head;  
            head = inserted;  
            return;  
        }

        auto* temp = head;

        int cntr = 0;       
        while (temp != nullptr && cntr != id-1)  
        {
            temp = temp->next;
            ++cntr;
        }

        if (temp == nullptr)  
        {
            delete inserted;  
            return;  
        }

        inserted->next = temp->next;  

        temp->next = inserted;  
    }


    class iterator 
    {
        public:
            explicit iterator(Node<T>* startNode) : current(startNode) {}

            bool operator!=(const iterator& other) const
            {
                return current != other.current;
            }
            
            bool operator==(const iterator& other) const
            {
                return current == other.current;
            }

            iterator& operator ++() 
            {
                current = current->next;
                return *this;
            }

            Node<T>* operator->() const
            {
                return current;
            }

            const T& operator *() const
            {
                return current->data;
            }

            const T& value() const 
            {
                return current->data;
            }


        private:
            Node<T>* current;
    };

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    void insert(iterator it, const T& value) const
    {
        auto* inserted = new Node<T>(value);

        inserted->next = it->next;
        it->next = inserted;
    }

    void insert(const T& value, iterator it)
    {
        auto* inserted = new Node<T>(value);

        if (it == begin()) 
        {
            inserted->next = head;
            head = inserted;
            return;
        }

        auto previous = head;

        for (auto current = begin(); current != it; ++current) 
            previous = current->next;
        
        inserted->next = it->next;
        previous->next = inserted;

    }

void erase(iterator &it)
{
    if(it == begin())
    {
        auto* temp = head;
        head = head->next;
        delete temp;
        return;
    }


    auto current = head;
    auto old = head;
    for (auto cntr = begin(); cntr != it; ++cntr) 
    {
        old=current;
        current = current->next;

    }
    //std::cout << old->data << "/" << ";\n";

    old->next = it->next;
    
    delete current;
}


    void reverse(Node<T>* current = nullptr)
    {
        if (current == nullptr)
        {
            current = head;  
        }

        if (current->next == nullptr)
        {
            std::cout << current->data << "/" << current->index << ";\n";
            return;
        }

        reverse(current->next);
        std::cout << current->data << "/" << current->index << ";\n";
    }

};

int main()
{
    List<int> myList;

    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    Node<int>* temp = myList.head;
    assert(temp->data == 10);
    temp = temp->next;
    assert(temp->data == 20);
    temp = temp->next;
    assert(temp->data == 30);
    assert(temp->next == nullptr);

    assert(myList.size() == 3);

    std::vector<int> expected = { 10, 20, 30 };
    std::vector<int> to_vector = myList.to_vector();
    for (size_t i = 0; i < to_vector.size(); i++)
    {
        assert(to_vector[i] == expected[i]);
    }

    //myList.print(); // Выведет: 10 20 30
    //std::cout << "\n\n\n";

    assert(myList.at(2) == 30);
 
    //myList.print();
    //std::cout << "\n" << myList.size() << "\n";

    myList.push_front(-10);
    std::vector<int> expected_front = { -10, 10, 20, 30 };
    std::vector<int> to_vector_front = myList.to_vector();
    for (size_t i = 0; i < to_vector_front.size(); i++)
        assert(to_vector_front[i] == expected_front[i]);
    
    //myList.print();
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
    myList.insert(2,-20);

    std::vector<int> to_vector_2 = myList.to_vector();

    for (size_t i = 0; i < to_vector_2.size(); i++)
         assert(to_vector_2[i] == expected_2[i]);


    int i = 0;
    for ( auto it = myList.begin(); it != myList.end(); ++it, ++i)
        assert(it.value() == expected_2[i]);

    myList.print();
    std::cout << std::endl;
    {
    auto it = myList.begin();
    myList.insert(100, it);
    myList.print();
    std::cout << std::endl;
    }

    {
    auto it = myList.begin();
    ++it;
    myList.insert(it, 99);
    myList.print();
    std::cout << std::endl;
    } 


    auto it_2 = myList.begin();
    ++it_2;
    myList.erase(it_2);

    myList.print();
    std::cout << std::endl;

    std::cout << "\nAll tests passed successfully!\n\n" << std::endl;
    return 0;
}
