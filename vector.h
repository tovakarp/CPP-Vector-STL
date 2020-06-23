#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <iostream>
#include <cmath>


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
	
	void resize (size_t size, T val = T());
	
	size_t capacity() const;
	
	bool empty() const;
	
	void reserve (size_t size);
	
	const T& operator[] (size_t index) const;
	T& operator[] (size_t index);
	
	const T& at (size_t index) const;
	T& at (size_t index);
	
	const T& front () const;
	T& front ();
	
	const T& back () const;
	T& back ();
	
	T* data();
	const T* data() const;
	
	void assign (size_t size, const T& val);
	
	friend std::ostream& operator<<(std::ostream &os, const Vector &v){
		
		for(size_t i = 0; i < v.m_size; ++i)
			os << v.m_arrPtr[i] << " ";
			
		os << std::endl;
	
		return os;
	}
	
	
private:
	void validateIndex(size_t index) const;

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
inline Vector<T> :: Vector(const Vector<T> &other) : m_arrPtr(NULL), m_capacity(other.m_capacity), m_size(other.m_size){
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

		for(size_t i = 0; i < other.m_size; ++i)
			tmp[i] = other.m_arrPtr[i];
			
		delete[] m_arrPtr;
		
		m_arrPtr = tmp;
		m_capacity = other.m_capacity;
		m_size = other.m_size;	
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
size_t Vector<T>::max_size() const {
	return (pow(2, 64) / sizeof(T) ) - 1;
}

template <typename T>
inline void Vector<T>::resize (size_t size, T val){

	reserve (size);
	
	if(size < m_size){
		m_size = size;
		return;
	}
	
	for (size_t i = m_size; i < size; ++i)
        m_arrPtr[i] = val;
		
	m_size = size;
	
	/*T *tmp = new T[size];

    size_t min = size < m_size? size : m_size;

    for (size_t i = 0; i < min; ++i)
        tmp[i] = m_arrPtr[i];

    for (size_t i = min; i < size; ++i)
        tmp[i] = val;

    delete[] m_arrPtr;
    
    m_arrPtr = tmp;
    m_size = size;
    m_capacity = size;*/
}


template <typename T>
size_t Vector<T>::capacity() const {
	return m_capacity;
}

template <typename T>
bool Vector<T>::empty() const {
	return m_size > 0;
}

template <typename T>
void Vector<T>::reserve (size_t size){
	while (m_capacity < size){
		try{
			T *tmp = new T[2 * m_capacity];
			
			for(size_t i = 0; i < m_size; ++i)
				tmp[i] = m_arrPtr[i];
				
			delete[] m_arrPtr;
			
			m_arrPtr = tmp;
			m_capacity *= 2;
		}
		
		catch(std::bad_alloc &ba){
			std::cout << "Error accured in reserve()" << std::endl;
		}
	}
}

template <typename T>
inline void Vector<T>::validateIndex(size_t index) const{
	if(index > m_size)
		throw std::out_of_range("This index does not exist...\n");
}

template <typename T>
inline const T& Vector<T>::operator[](size_t index) const{
	return m_arrPtr[index];
}

template <typename T>
inline T& Vector<T>::operator[](size_t index){
	return m_arrPtr[index];
}

template <typename T>
inline const T& Vector<T>::at(size_t index) const{

	validateIndex(index);
	
	return m_arrPtr[index];
}

template <typename T>
inline T& Vector<T>::at(size_t index){

	validateIndex(index);
	
	return m_arrPtr[index];
}

template <typename T>
inline const T& Vector<T>::front() const{
	return at(0);
}

template <typename T>
inline T& Vector<T>::front(){
	return at(0);
}

template <typename T>
inline const T& Vector<T>::back() const{
	return at(m_size - 1);
}

template <typename T>
inline T& Vector<T>::back(){
	return at(m_size - 1);
}

template <typename T>
inline const T* Vector<T>::data() const {
	return m_arrPtr;
}

template <typename T>
inline T* Vector<T>::data() {
	return m_arrPtr;
}


#endif //__VECTOR_H__
