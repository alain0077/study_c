#pragma once

#include <string>

class Print
{
public:
	static void print(int x, int y, std::string name, int t);
	static void print(int x, int y, std::string name, double t);
	static void print(int x, int y, std::string name, std::string t);
};