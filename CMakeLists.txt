cmake_minimum_required(VERSION 3.21)
project(ATM)

set(CMAKE_CXX_STANDARD 14)

add_executable(ATM main.cpp Application.cpp Application.h Base.h Base.cpp Console.h Identifier.h Issuancer.h Printer.h Reader.h Receiver.h signalsHandlers.cpp)
