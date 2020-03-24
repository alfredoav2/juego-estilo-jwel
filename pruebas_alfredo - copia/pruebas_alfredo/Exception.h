#pragma once
#include<stdexcept>
class Exception : public std::runtime_error{
	Exception(const char* msg) : std::runtime_error(msg) {};
};

