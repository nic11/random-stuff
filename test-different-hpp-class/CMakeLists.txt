cmake_minimum_required(VERSION 3.10)

PROJECT(kek)

ADD_EXECUTABLE(main main.cpp call1.cpp call2.cpp)

SET_PROPERTY(TARGET main PROPERTY CXX_STANDARD 17)
