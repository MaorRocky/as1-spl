cmake_minimum_required(VERSION 3.12)
project(this_is_not_AS1)

set(CMAKE_CXX_STANDARD 14)

add_executable(this_is_not_AS1 main.cpp Customer.h Customer.cpp Action.h Dish.h Dish.cpp Restaurant.cpp Restaurant.h Table.cpp Table.h Action.cpp)