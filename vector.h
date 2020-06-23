#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <iostream>
#include <limits> // for 'std::numeric_limist'

template <typename T>
class Vector{
public:
	/*CTOR*/
	Vector();
	Vector(size_t size, T val = T());
	Vector(const Vector &other);
	
	/*DTOR*/
	~Vector();
	
	Vector& operator=(const Vector &other);
	
	size_t size() const;
	
	size_t max_size() const;
	
	size_t capacity() const;
	
	friend std::ostream& operator<<(std::ostream &os, const Vector &v){
		
		for(size_t i = 0; i < v.m_size; ++i)
			os << v.m_arrPtr[i] << " ";
			
		os << std::endl;
	
		return os;
	}
	
	
private:
	T *m_arrPtr;
	size_t m_capacity;
	size_t m_size;

};

// Vector Defs

template <typename T>
inline Vector<T> :: Vector() : m_arrPtr(NULL), m_capacity(0), m_size(0) {}

template <typename T>
inline Vector<T> :: Vector(size_t size, T val) : m_arrPtr(NULL), m_capacity(size), m_size(size){
	m_arrPtr = new T[size];
	
	for(size_t i = 0; i < size; ++i)
		m_arrPtr[i] = val;
}

template <typename T>
inline Vector<T> :: Vector(const Vector<T> &other) : m_arrPtr(NULL), m_capacity(other.capacity), m_size(other.m_size){
	m_arrPtr = new T[m_capacity];

	for(size_t i = 0; i < m_size; ++i){
		m_arrPtr[i] = other.m_arrPtr[i];
	}
}

template <typename T>
inline Vector<T> :: ~Vector() {
	delete[] m_arrPtr;
	m_arrPtr = NULL;
}

template <typename T>
Vector<T>& Vector<T> :: operator =(const Vector<T> &other){

	try{
		T *tmp = new T[other.m_capacity];
		delete[] m_arrPtr;
		m_arrPtr = tmp;
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		
		for(size_t i = 0; i < m_size; ++i)
			m_arrPtr[i] = other.m_arrPtr[i];
	}
	
	catch(std::bad_alloc &ba){
		std::cout << "Error accured in oprator=" << std::endl;
	}
	
	return *this;
}

template <typename T>
size_t Vector<T>::size() const {
	return m_size;
}

template <typename T>
size_t Vector<T>::max_size() const{
	//return std::numeric_limits<vector<T>>::max();
	return 0;
}

template <typename T>
size_t Vector<T>::capacity() const {
	return m_capacity;
}


#endif //__VECTOR_H__
