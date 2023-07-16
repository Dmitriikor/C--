#include "H.hpp"
#include <iostream>
#include "hh.hpp"
#include "nana/gui.hpp"
#include "nana/gui/widgets/label.hpp"
#include "2t.hpp"

int main(int argc, char const *argv[])
{
    // Call the test functions from the nnn namespace
    nnn::test();
    nnn::test_2();
    nnn::test_3();
    
    // Create an instance of the H class with parameters 1 and 1
    H parameter(1,1);
    
    // Output a newline character
    std::cout << '\n';
    
    // Output the summary of the parameter object
    std::cout << parameter.summary() << '\n';
    
    // Output two newline characters
    std::cout << '\n';
    
    // Call the test_hh function
    test_hh();
    
    // Output two newline characters
    std::cout << '\n';
    
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

    // Lambda expression to iterate over the elements of the beta array and output each character
    auto test_lbd = [&beta]()
    {
        for (size_t i = 0; i < 100 && beta[i] != '\0'; i++)
        {
            std::cout << beta[i];
        }
        std::cout << '\n';
    };

    test_lbd();
    std::cout << "test_lbd\n";
    
    // Output a newline character
    std::cout << '\n';
    std::cout << "END_2\n";
    _n::_t();
    nana::form fm;
   nana::label lb{ fm, nana::rectangle{ 10, 10, 100, 100 } };
    lb.caption("Hello World!");
    fm.show();
    nana::exec();

    _n::_t();
    // Return 0 to indicate successful execution of the program
    return 0;
}
