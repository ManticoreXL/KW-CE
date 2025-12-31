cmake_minimum_required(VERSION 3.27.7)
project(Project1)
set(CMAKE_CXX_STANDARD)

add_executable(Project1 main.cpp
	MemberQueue.cpp
	TermsLIST.cpp
	TermsBST.cpp
	NameBST.cpp
	Manager.cpp)