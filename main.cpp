#include "vector.h"

int main(){

	Vector<int> v1(6, 16), v2;

	v2 = v1;
	
	v2[3] = 569;
	
	std::cout << v2;
	

	return  0;
}
