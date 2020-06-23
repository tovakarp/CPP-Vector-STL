#include "vector.h"

int main(){

	Vector<int> v1(6, 1), v2;

	v2 = v1;
	
	std::cout << v2;
	

	return  0;
}
