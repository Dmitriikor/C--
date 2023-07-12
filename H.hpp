#pragma once
#include <iostream>
namespace nnn
{
void test_2();


void test();

void test_3();

void test_4();

void test_5();

}
struct H
{
    private:
    int a;
    int b;

    public:
    H(int a, int b) : a(a), b(b)
    {
       
    }
    int getA() const
    {
    return a;
    }
    int getB() const
    {
    return b;
    }
    int summary()
    {
    return a + b;
    }
};

//void test_5(){};

