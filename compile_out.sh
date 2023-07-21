/home/dmitriy/Desktop/C++/main.cpp: In function ‘int main(int, const char**)’:
/home/dmitriy/Desktop/C++/main.cpp:41:10: error: redeclaration of ‘char beta [100]’
   41 |     char beta[100];
      |          ^~~~
/home/dmitriy/Desktop/C++/main.cpp:40:10: note: ‘char beta [100]’ previously declared here
   40 |     char beta[100];
      |          ^~~~
/home/dmitriy/Desktop/C++/main.cpp: In lambda function:
/home/dmitriy/Desktop/C++/main.cpp:65:33: warning: conversion from ‘size_t’ {aka ‘long unsigned int’} to ‘int’ may change value [-Wconversion]
   65 |             displayNumber(beta, i);
      |                                 ^
/home/dmitriy/Desktop/C++/main.cpp: In function ‘int main(int, const char**)’:
/home/dmitriy/Desktop/C++/main.cpp:14:14: warning: unused parameter ‘argc’ [-Wunused-parameter]
   14 | int main(int argc, char const *argv[])
      |          ~~~~^~~~
/home/dmitriy/Desktop/C++/main.cpp:14:32: warning: unused parameter ‘argv’ [-Wunused-parameter]
   14 | int main(int argc, char const *argv[])
      |                    ~~~~~~~~~~~~^~~~~~
make[2]: *** [CMakeFiles/MAIN.out.dir/build.make:118: CMakeFiles/MAIN.out.dir/main.cpp.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:839: CMakeFiles/MAIN.out.dir/all] Error 2
make: *** [Makefile:121: all] Error 2
