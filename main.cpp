#include "vector.h"

int main(){

	Vector<int> v1(6, 16), v2;

	v2 = v1;
	
	v1.resize(6, 9);
	
	std::cout << v1;
	
	v2.back() = 569;
	
	std::cout << v2;
	

	return  0;
}
