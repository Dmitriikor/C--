cmake_minimum_required(VERSION 3.0.0)
project(test_neon VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_BUILD_TYPE Debug)

# Поиск и добавление всех файлов cpp в директории src
file(GLOB SOURCES *.cpp)
# Поиск и добавление всех файлов hpp в директории include
file(GLOB HEADERS *.hpp)
# Добавление исполняемого файла
add_executable(MAIN.out ${SOURCES} ${HEADERS})

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

# Линковка с библиотекой Nana
target_link_libraries(MAIN.out PUBLIC ${CMAKE_SOURCE_DIR}/lib/libnana.a ${RUNNANA_LINK_LIBS} stdc++fs)

# Добавление пути к заголовочным файлам Nana
include_directories(${CMAKE_SOURCE_DIR}/include)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CPack)
