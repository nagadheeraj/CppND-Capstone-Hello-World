# CPPND: Very simple HTTP server

This Capstone Project is a very simple HTTP server which serves the number of visits made by it's clients. The server supports 10 multiple, simultaneous connections from clients and it achives this by using C++ thread library. This server is very simplified since it serves only visitor count irrespective of the the client's HTTP request and closes the connection. Despite it's simplicity the implementation uses many C++ concepts which is the purpose of this capstone project. 

This project mainly contains two classes "Socket" and "SockAddr" which encapsulates the sockaddr generation and the unix socket fd usage. There is also an helper class "Counter" to implement visitor count functionality. The "Socket" class is implemented in the "socket.cpp" and it's interface is in "socket.h". The "SockAddr" class is implemented in the "socket_address.cpp" and it's interface is in "socket_address.h". The helper function is very small and it's interface and implementation is in "counter.h" file.

The server functionality is implemented in the "main.cpp" file. It first creates a TCP bind address using SockAddr object and passes it to the Socket object to create a server side endpoint. Then the server will wait in a loop until a client is connected. Once the client is connected the server loop will create a new thread to serve the client and waits for another client to be connected.

The server application must be started from a command line terminal. When a client is connected the application will print two lines on the terminal to indicate the client connection & dis-connection status along with client address. Example output from the server is shown below
	# ./server
	127.0.0.1: 42666 connected
	127.0.0.1: 42666 dis-connected

## Rubric points addressed in this project
* The project demonstrates an understanding of C++ functions and control structures
  * A variety of control structures are used in the project
    * In almost all files
  * The project code is clearly organized into functions
    * File: main.cpp, Line: 8, 26

* The project uses Object Oriented Programming techniques
  * The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks
    * File: counter.h, Line: 6
    * File: socket.h, Line: 9
    * File: socket_address.h, Line: 19
    
* Classes use appropriate access specifiers for class members
  * All class data members are explicitly specified as public, protected, or private
    * File: counter.h, Line: 7, 17
    * File: socket.h, Line: 10, 27
    * File: socket_address.h, Line: 20, 35
    
* Class constructors utilize member initialization lists
  * All class members that are set to argument values are initialized through member initialization lists
    * File: counter.h, Line: 9
    * File: socket.cpp, Line: 11

* Overloaded functions allow the same function to operate on different parameters
  * One function is overloaded with different signatures for the same function name
    * File: socket.h, Line: 13 & 28
    * File: socket_address.h, Line: 22 & 24

* The project makes use of references in function declarations
  * At least two variables are defined as references, or two functions use pass-by-reference in the project code
    * File: socket.h, Line: 13, 19

* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
  * The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
    * File: main.cpp, Line: 27, Class: SockAddr
    
* The project follows the Rule of 5
  * For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined
    * File: socket.h, Line: 22, 23, 24, 25, 26
    
* The project uses move semantics to move data, instead of copying it, where possible
  * For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object
    * File: main.cpp, Line: 35, Class: Socket
    
* The project uses smart pointers instead of raw pointers
  * The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
    * File: main.cpp, Line: 29

* The project uses multithreading
  * The project uses multiple threads in the execution
    * File: main.cpp, Line: 35
    
* A mutex or lock is used in the project
  * A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code
    * File: counter.h, Line: 11 & 19

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux)
  * Linux: make is installed by default on most Linux distros
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros

## Basic Build Instructions

1. Make a build directory in the top level directory: `mkdir build && cd build`
2. Compile: `cmake .. && make`
3. Start the server: `./server`.

## How to test the server
* The server will listen for the incoming connections on port "8080". To send http requests to the server use "cURL" linux command line application as shown below
  * # curl http://localhost:8080