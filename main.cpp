#include "vector.h"

int main(){

	Vector<int> v1(6, 16), v2 = v1, v3(1,0);

	v2 = v1;
	
	v1.resize(6, 9);
	
	std::cout << v1;
	
	v2.back() = 569;
	
	std::cout << "***Swap***\nBefore:\nv1: " << v1;
	std::cout << "v2: " << v2;
	v2.swap(v1);
	std::cout << "After:\nv1: " << v1;
	std::cout << "v2: "<< v2 << "***End Swap***\n\n";
	
	
	v2.assign(1, 3);
	
	v2.push_back(15);
	v2.pop_back();
	v2.clear();
	
	v2.insert(0, 9);
	std::cout << "v2 insert: " << v2;
	
	v3.push_back(1);
	v3.push_back(2);
	v3.push_back(3);
	
	v3.insert(4, 4, 4);
	std::cout << "v3 insert: " << v3;
	
	v3.erase(0,3);
	v3.erase(4);
	std::cout << "v3 erase: " << v3;
	
	v1 += v3;
	
	std::cout << v1;
	
	for(Vector<int>::iterator it = v1.begin(); it < v1.end(); ++it)
		std::cout << *it << " ";
		
	std::cout << std::endl;
	
	//Vector<int>::iterator = v1.begin();
	

	return  0;
}
