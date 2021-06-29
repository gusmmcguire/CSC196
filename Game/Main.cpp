#include "Helper.h"
#include "Dynamic.h"
#include <iostream>

int main() {
	std::cout << gm::sqr(5) << std::endl;

	gm::point p1{ 10,10 };
	gm::point p2{ 10,10 };
	gm::point p3 = p1 + p2;
	
	std::cout << p3.x << " " << p3.y << std::endl;
}