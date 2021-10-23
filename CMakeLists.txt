cmake_minimum_required(VERSION 3.17)
project(fsorter)

set(CMAKE_CXX_STANDARD 20)

add_executable(fsorter main.cpp)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
