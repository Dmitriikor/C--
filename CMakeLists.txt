cmake_minimum_required(VERSION 3.5.0)
project(test_neon VERSION 0.1.0 LANGUAGES C CXX)

#denail create temp file in root floader
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_BUILD_TYPE Debug)

include(CPack)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
# Конфигурации для Linux

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wpedantic -Wconversion -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-align -fstack-protector -O -march=native")
#-Wshadow
# Поиск и добавление всех файлов cpp в директории src
file(GLOB SOURCES *.cpp)
# Поиск и добавление всех файлов hpp в директории include
file(GLOB HEADERS *.hpp)



# Поиск директорий lib и include в вашем проекте
find_package (Threads REQUIRED)
find_package(Freetype REQUIRED)
find_package(X11 REQUIRED)

set (NANA_INCLUDE include/)
set (NANA_LINK build/)

set (RUNNANA_LINK_LIBS
stdc++fs
${X11_LIBRARIES}
${CMAKE_THREAD_LIBS_INIT}
rt
Xft
fontconfig
${FREETYPE_LIBRARIES}
)

# Добавление пути к заголовочным файлам Nana
include_directories(${CMAKE_SOURCE_DIR}/include)

include(CTest)
enable_testing()

# Добавление исполняемого файла
add_executable(MAIN.out ${SOURCES} ${HEADERS})

# Линковка с библиотекой Nana
target_link_libraries(MAIN.out PUBLIC ${CMAKE_SOURCE_DIR}/lib/libnana.a ${RUNNANA_LINK_LIBS} stdc++fs)




elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Конфигурации для Windows
    # Конфигурации для Windows
# Use Clang as the compiler
set(CMAKE_CXX_COMPILER "clang")

# Add compiler flags for warnings and errors
add_compile_options(
  -Wall # Включить все предупреждения
  -Werror # Считать все предупреждения ошибками
  -Wextra # Включить дополнительные предупреждения
  -Wshadow # Предупреждать о теневом замещении переменных
  -Wunused # Предупреждать о неиспользуемых переменных, параметрах и функциях
  -pedantic # Предупреждать о нарушении стандарта ISO C++
  -pedantic-errors # Считать нарушение стандарта ISO C++ ошибкой
  -std=c++20 # Указать стандарт языка C++20
  -Og # Включить уровень оптимизации для отладки
  -g # Включить генерацию отладочной информации
  -fsanitize=address # Включить инструмент AddressSanitizer
  -Wconversion # Включить предупреждения о неявных преобразованиях типов
)

# Add compiler flags for modules
add_compile_options(-fmodules-ts --precompile-module -Xclang -fmodules-embed-all-files)

# Add linker flags for modules
add_link_options(-fmodules-ts -Xclang -fmodules-embed-all-files)

# Add an extra flag to handle ixx files as modules
add_compile_options(-Xclang -fmodules-embed-all-files)

# Find all source files in the current directory and store them in a variable
file(GLOB_RECURSE SOURCES_ "*.ixx" "*.hpp" "*.cpp")

# Add the executable target with the source files
add_executable(my_project ${SOURCES_})


# # Установка флагов компилятора
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


# # Поиск и добавление всех файлов cpp в директории src
# file(GLOB SOURCES *.cpp)
# # Поиск и добавление всех файлов hpp в директории include
# file(GLOB HEADERS *.hpp)
# file(GLOB HEADERS *.ixx)
# set (NANA_INCLUDE include/)
# set (NANA_LINK build/)
# # Добавление пути к заголовочным файлам Nana
# include_directories(${CMAKE_SOURCE_DIR}/include)

# include(CTest)
# enable_testing()

# add_definitions(-D__STDC_WANT_SECURE_LIB__)

# # Добавление исполняемого файла
# add_executable(MAIN.exe ${SOURCES} ${HEADERS})

# set (RUNNANA_LINK_LIBS
 
# )

# # Линковка с библиотекой Nana
# target_link_libraries(MAIN.exe PUBLIC ${CMAKE_SOURCE_DIR}/lib/nana_v143_Debug_x64.lib ${RUNNANA_LINK_LIBS})


    endif()