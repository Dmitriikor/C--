#include "H.hpp"
#include <iostream>
#include "hh.hpp"

int main(int argc, char const *argv[])
{
    // Call the test functions from the nnn namespace
    nnn::test();
    nnn::test_2();
    nnn::test_3();
    
    // Create an instance of the H class with parameters 1 and 1
    H parameter(1,1);
    
    // Output a newline character
    std::cout << "\n";
    
    // Output the summary of the parameter object
    std::cout << parameter.summary();
    
    // Output two newline characters
    std::cout << "\n\n";
    
    // Call the test_hh function
    test_hh();
    
    // Output two newline characters
    std::cout << "\n\n";
    
    // Create a character array of size 100
    char beta[100];
    
    // Set the value of the beta array to "test"
    std::cout << "Enter a string: ";

    // Read a line of input from the user and store it in the beta array
    std::cin.getline(beta, 100);

    // Iterate over the elements of the beta array and output each character
    for (size_t i = 0; i < 100; i++)
    {
        std::cout << beta[i];
    }

        // Output a newline character
    std::cout << "\n\n\n\n";

    //TODO add lambda expression here base of previous for loop
    auto test_lbd = [&]()
    {
    for (size_t i = 0; i < 100; i++)
    {
        std::cout << beta[i];
        if (beta[i] == '\0')
        {
            std::cout << "\n";
            break;
        }
    }
    };

    test_lbd();
    std::cout << "test_lbd";
    
    // Output a newline character
    std::cout << "\n";
    std::cout << "END_1\n";
    // Return 0 to indicate successful execution of the program
    return 0;
}
