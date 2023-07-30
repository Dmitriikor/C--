#include <iostream>
#include <vector>
#include <cassert>
#include "LinkedListIterator.hpp"

template <typename T>
struct Node
{
    T data;
    Node* next;
    int index;

    explicit Node(const T& value /*const int index*/) : data(value),
        next(nullptr)
        //index(index) 
    {}
};

template <typename T>
struct List
{
private:
    Node<T>* tail=nullptr;
    int index = 0;

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

    int size() const // This function returns the size of the object.
    {
        return index; // Return the value of the 'index' variable.
    }

    void push_back(const T& value) // Function to add a new element at the end of the linked list
    {
        if (head == nullptr) // If the linked list is empty
        {
            // Create a new node with the given value and make it the head
            head = new Node<T>(value);
            head->index = index;
            tail=head;
            ++index; // Increment the index
            return; // Exit the function
        }
        
        // Traverse to the last node
        Node<T>* temp = tail;
        // while (temp->next != nullptr)
        // {
        //     temp = temp->next;
        // } 

        // Create a new node with the given value
        temp->next = new Node<T>(value);
        temp = temp->next;
        temp->index = index;
        tail = temp;
        ++index; // Increment the index
    }
    void pop_back() // Function to remove the last element  
    {
        if (head->next == nullptr) // If there is only one element in the list
            return; // Return as there is nothing to remove
        /*
            if (head->next == nullptr) {
                delete head; 
                head = nullptr;// Если в списке только один элемент, удаляем его и делаем head nullptr
        */
        Node<T>* temp = head; // Create a temporary pointer and point it to the head of the list

        while ((index - 2) != temp->index) // Traverse the list until the second-to-last element
        {
            temp = temp->next; // Move to the next element
        }

        tail = temp; // Update the tail to point to the second-to-last element
        tail->next = nullptr; // Set the next pointer of the new tail to nullptr
        index--; // Decrement the index as the last element is being removed

        temp = temp->next; // Move the temporary pointer to the last element
        temp->data.~T(); // Destroy the data of the last element
        delete temp; // Delete the last element
    }

    void pop_front() // Function to remove the first element
    {
        if (head->next == nullptr) // If there is only one element in the list
            return; // Return as there is nothing to remove

        Node<T>* temp = head; // Create a temporary pointer and point it to the head of the list
        Node<T>* delited = head; // Create a pointer to store the deleted node
        head = temp->next; // Move the head pointer to the next element

        delited->data.~T(); // Destroy the data of the deleted node
        delete delited;

        index = 0;

        while (temp != nullptr)
        {
            temp->index = index;  // Set the index of the current node to the current index value
            ++index;  // Increment index by 1
            temp = temp->next;  // Move to the next node
        }
        ++index;
    }

    const Node<T>& get_head() const
    {
        return *head;
    }

    const Node<T>& get_tail() const
    {
        return *tail;
    }

    void push_front(const T& value)
    {

        if (head == nullptr) // If the linked list is empty, create a new node and make it the head
        {
            index = 0;
            head = new Node<T>(value);  // Create new node with value and index
            head->index = index;
            ++index;  // Increment index by 1
            return;  // Exit the function
        }

        Node<T>* temp = new Node<T>(value);  // Create new node with value and index
        temp->next = head;  // Set the next pointer of the new node to the current head
        head = temp;  // Set the head to the new node

        index = 0;  // Initialize index to 0
        while (temp != nullptr)
        {
            temp->index = index;  // Set the index of the current node to the current index value
            ++index;  // Increment index by 1
            temp = temp->next;  // Move to the next node
        }
    }

    void print() const
    {
        Node<T>* current = head;  // Create a pointer variable to keep track of the current node, starting from the head
        while (current != nullptr) // Loop through the linked list until we reach the end (nullptr)
        {
            std::cout << current->data << "/" << current->index << "; "; // Print the data stored in the current node
            current = current->next; // Move to the next node
        }
    }


    T operator [](int id) const  // Get the element at the given index.
    {
        Node<T>* current = head; // Start at the head of the linked list.
        if (id < index)
        while (current->index <= index) // Traverse the linked list until the current node is nullptr or the desired index is found.
        {
            if (current->index == id) // Check if the current node's index matches the desired index.
            {
                return current->data; // Return the data of the current node.
            }
            current = current->next; // Move to the next node in the linked list.
        }
        
        return T();   // If the desired index is not found, return a default value of type T.
    }


    std::vector<T> to_vector() const // Returns a vector containing the data from the linked list
    {
        Node<T>* current = head;  // Start at the head of the linked list
        std::vector<T> data_accum; // Create an empty vector to store the data

        while (current != nullptr) // Traverse the linked list and append each element to the vector
        {
            data_accum.push_back(current->data);
            current = current->next;
        }

        return data_accum; // Return the vector containing the data from the linked list
    }

    void insert(int id, const T& value)
    {
        auto* inserted = new Node<T>(value); // Create a new Node with the provided value

        if (head == nullptr || id == 0) // If the list is empty or we want to insert at the beginning
        {
            inserted->next = head; // Set the next pointer of the new Node to the current head
            head = inserted; // Set the new Node as the new head
            return; // Exit the function
        }

        auto* temp = head; // Create a temporary Node pointer and set it to the head

        while (temp != nullptr && temp->index < id-1) // Find the Node before the insertion point
        {
            temp = temp->next; // Move to the next Node in the list
        }

        if (temp == nullptr) // If the insertion point is beyond the end of the list
        {
            inserted->data.~T(); // Destruct the data in the new Node
            delete inserted; // Delete the new Node
            return; // Exit the function
        }

        inserted->next = temp->next; // Set the next pointer of the new Node to the next Node after the insertion point

        temp->next = inserted; // Set the next pointer of the Node before the insertion point to the new Node

        index = 0; // Initialize an index counter to 0
        temp = head; // Reset the temporary Node pointer to the head

        while (temp != nullptr) // Update the index of each Node in the list
        {
            temp->index = index; // Set the index of the current Node
            ++index; // Increment the index counter
            temp = temp->next; // Move to the next Node in the list
        }
        ++index; // Increment the index counter for the newly inserted Node
    }

    class iterator 
    {
        public:
            explicit iterator(Node<T>* startNode) : current(startNode) {}

            bool operator!=(const iterator& other) const
            {
                return current != other.current;
            }

            iterator& operator ++() 
            {
                current = current->next;
                return *this;
            }


            bool End() const 
            {
                return current == nullptr;
            }

            Node<T>* getNode() const 
            {
                return current;
            }

            T& value() const 
            {
                return current->data;
            }
            int index() const 
            {
                return current->index;
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

    assert(myList[2] == 30);
    int tt = myList[100];
    //myList.print();
    //std::cout << "\n" << myList.size() << "\n";

    myList.push_front(-10);
    std::vector<int> expected_front = { -10, 10, 20, 30 };
    std::vector<int> to_vector_front = myList.to_vector();
    for (size_t i = 0; i < to_vector_front.size(); i++)
        assert(to_vector_front[i] == expected_front[i]);
    
    //myList.print();
    //std::cout << "\n" << myList.size() << "\n";

    assert(myList.get_head().data == -10);
    assert(myList.get_tail().data == 30);
    myList.pop_back();
    assert(myList.get_tail().data == 20);
    myList.push_back(30);
    assert(myList.get_tail().data == 30);
    myList.pop_back();
    assert(myList.get_tail().data == 20);
    assert(myList.get_head().data == -10);

    std::vector<int> expected_2 = { -10, 10,-20, 20 };
    myList.insert(2,-20);
    std::vector<int> to_vector_2 = myList.to_vector();

    for (size_t i = 0; i < to_vector_2.size(); i++)
         assert(to_vector_2[i] == expected_2[i]);

    for (auto it = myList.begin(); it != myList.end(); ++it)
         assert(it.value() == expected_2[it.index()]);

        
    

    myList.print();
    std::cout << "\nAll tests passed successfully!\n\n" << std::endl;
    return 0;
}
