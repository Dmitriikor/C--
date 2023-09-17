#include <iostream>;
export module Module.test;

//export void MyFunc();
//
//void MyFunc()
//{
//	std::cout << "\nModule WW\n";
//}
export template <typename T>
 class MyClassModule {
public:
	void MyFunc()
	{
	 std::cout << " MyClassModule" << std::endl;
	}
private:

};

