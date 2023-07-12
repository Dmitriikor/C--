#include "H.hpp"
#include <iostream>
#include "hh.hpp"

int main(int argc, char const *argv[])
{
    nnn::test();
    nnn::test_2();
    nnn::test_3();
    H parameter(1,1);
    std::cout << "\n";
    std::cout << parameter.summary();
    std::cout << "\n";
    test_hh();
    std::cout << "\n";
    char beta[100];
    std::cin.getline(beta, 100);
    for (size_t i = 0; i < 100; i++)
    {
        std::cout << beta[i];
    }
    
    std::cout << "\n";
    return 0;
}
