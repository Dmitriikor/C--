#include <iostream>
#include <vector>
#include <cassert>

template <typename T>
struct Node
{
    T data;
    Node *next;

    
    int index;

    explicit Node(const T &value, const int index) : data(value), next(nullptr), index(index) {}
};

template <typename T>
struct List
{
private:
int index = 0;

public:
    Node<T> *head = nullptr;

    List() = default;

    ~List()
    {
        while (head != nullptr)
        {
            Node<T> *temp = head;
            head = head->next;  
            //std::cout<< "\n Destruct\n";
            temp->data.~T();
            
            delete temp;
        }
    }

    // This function returns the size of the object.
    int size() const 
    {
        // Return the value of the 'index' variable.
        return index;
    }

    // Function to add a new element at the end of the linked list
    void push_back(const T &value)
    {
        // If the linked list is empty, create a new node and make it the head
        if (head == nullptr)
        {
            head = new Node<T>(value, index);
            ++index;
            return;
        }
        // Traverse to the last node
        Node<T> *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        // Create a new node and attach it to the last node
        temp->next = new Node<T>(value, index);

        ++index;
    }

void push_front(const T &value)
{
    index = 0;  // Initialize index to 0

    // If the linked list is empty, create a new node and make it the head
    if (head == nullptr)
    {
        head = new Node<T>(value, index);  // Create new node with value and index
        ++index;  // Increment index by 1
        return;  // Exit the function
    }

    // Create a new node and attach it to the first node
    Node<T> *temp = new Node<T>(value, index);  // Create new node with value and index
    temp->next = head;  // Set the next pointer of the new node to the current head
    head = temp;  // Set the head to the new node

    Node<T> *current = head;  // Create a pointer to traverse the linked list starting from the head
    while (current != nullptr)
    {
        current->index = index;  // Set the index of the current node to the current index value
        ++index;  // Increment index by 1
        current = current->next;  // Move to the next node
    }
}

    void print() const
    {
        // Create a pointer variable to keep track of the current node, starting from the head
        Node<T> *current = head;

        // Loop through the linked list until we reach the end (nullptr)
        while (current != nullptr)
        {
            // Print the data stored in the current node
            std::cout << current->data << " | " << current->index << "; ";

            // Move to the next node
            current = current->next;
        }
    }


// Get the element at the given index.
T operator [](int id) const
{
    // Start at the head of the linked list.
    Node<T> *current = head;

    // Traverse the linked list until the current node is nullptr or the desired index is found.
    while (current != nullptr)
    {
        // Check if the current node's index matches the desired index.
        if (current->index == id)
        {
            // Return the data of the current node.
            return current->data;
        }

        // Move to the next node in the linked list.
        current = current->next;
    }

    // If the desired index is not found, return a default value of type T.
    return T();
}

    // Function to convert linked list to vector
    // Returns a vector containing the data from the linked list
    std::vector<T> to_vector() const
    {
        // Start at the head of the linked list
        Node<T> *current = head;

        // Create an empty vector to store the data
        std::vector<T> data_accum;

        // Traverse the linked list and append each element to the vector
        while (current != nullptr)
        {
            data_accum.push_back(current->data);
            current = current->next;
        }

        // Return the vector containing the data from the linked list
        return data_accum;
    }
};

int main()
{
    List<int> myList;

    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    Node<int> *temp = myList.head;
    assert(temp->data == 10);
    temp = temp->next;
    assert(temp->data == 20);
    temp = temp->next;
    assert(temp->data == 30);
    assert(temp->next == nullptr);

    assert(myList.size() == 3);

    std::vector<int> expected = {10, 20, 30};
    std::vector<int> to_vector = myList.to_vector();
    for (size_t i = 0; i < to_vector.size(); i++)
    {
        assert(to_vector[i] == expected[i]);
    }

    //myList.print(); // Выведет: 10 20 30
    //std::cout << "\n\n\n";
    
    assert(myList[2]==30);
    
    myList.push_front(-10);
    std::vector<int> expected_front = {-10, 10, 20, 30};
    std::vector<int> to_vector_front = myList.to_vector();
    for (size_t i = 0; i < to_vector_front.size(); i++)
    {
        assert(to_vector_front[i] == expected_front[i]);
    }

    std::cout << "\nAll tests passed successfully!\n\n" << std::endl;
    return 0;
}
