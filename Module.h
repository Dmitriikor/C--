#pragma once
#include <iostream>


//export void MyFunc();
//
//void MyFunc()
//{
//	std::cout << "\nModule WW\n";
//}
template <typename T>
class MyClassModule {
public:
	void MyFunc()
	{
		std::cout << " MyClassModule" << std::endl;
	}
private:

};

