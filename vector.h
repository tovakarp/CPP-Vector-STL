#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <iostream>
#include <cmath>


template <typename T>
class Vector{
public:
	typedef T* iterator;
	
	// CTOR
	Vector();
	Vector(size_t size, T val = T());
	Vector(const Vector &other);
	
	// DTOR
	~Vector();
	
	Vector& operator=(const Vector &other);
	
	// Capacity
	
	size_t size() const;
	
	size_t max_size() const;
	
	void resize (size_t size, T val = T());
	
	size_t capacity() const;
	
	bool empty() const;
	
	void reserve (size_t size);
	
	// Element Access
	
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
	
	// Modifiers​
	
	void assign (size_t size, const T& val);
	
	void push_back (const T& val);
	
	void pop_back();
	
	void insert(size_t index, const T &val);
	void insert(size_t index, size_t n, const T &val);
	
	void erase(size_t index);
	void erase (size_t firstIndex, size_t lastIndex);
	
	void swap (Vector& other);
	
	void clear();
	
	Vector& operator += (const Vector v);
	
	iterator begin();
	const iterator begin() const;
	
	iterator end();
	const iterator end() const;
	
	friend std::ostream& operator<<(std::ostream &os, const Vector &v){
		
		for(size_t i = 0; i < v.m_size; os << v.m_arrPtr[i] << " ", ++i);
			
		os << std::endl;
	
		return os;
	}
	
	
private:
	void validateIndex(size_t index) const;

	T *m_arrPtr;
	size_t m_capacity;
	size_t m_size;

};

template <typename T>
Vector<T> operator+(const Vector<T> v1, const Vector<T> v2);

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

	for(size_t i = 0; i < m_size; m_arrPtr[i] = other.m_arrPtr[i],  ++i);
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

		for(size_t i = 0; i < other.m_size; tmp[i] = other.m_arrPtr[i], ++i);
			
			
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
	
	for (size_t i = m_size; i < size; m_arrPtr[i] = val, ++i);

		
	m_size = size;
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
			T *tmp;
			if(!m_capacity)
				tmp = new T[2];
			else tmp = new T[2 * m_capacity];
			
			for(size_t i = 0; i < m_size; tmp[i] = m_arrPtr[i], ++i);
				
				
			delete[] m_arrPtr;
			
			m_arrPtr = tmp;
			m_capacity = !m_capacity? 2 : m_capacity * 2;
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

template <typename T>
inline void Vector<T>::assign (size_t size, const T& val){
	
	reserve(size);
	
	for(size_t i = 0; i < size; m_arrPtr[i] = val, ++i);
		
			
	m_size = size;
}

template <typename T>
inline void Vector<T>::push_back (const T& val){

	if(m_size + 1 > m_capacity)
		reserve(m_size + 1);
		
	++m_size;
	
	back() = val;
}

template <typename T>
inline void Vector<T>::pop_back (){
	--m_size;
}

template <typename T>
inline void Vector<T>::insert (size_t index, const T &val){
	insert(index, 1, val);
}

template <typename T>
inline void Vector<T>::insert (size_t index, size_t n, const T &val){

	if(index > m_size)
		throw std::out_of_range("Index does not exist...\n");

	reserve(m_size + n);
	
	for(size_t i = index; i < m_size; m_arrPtr[i + n] = m_arrPtr[i], ++i);
		
		
	for(size_t i = index; i < index + n; m_arrPtr[i] = val, ++i);
		
		
	m_size += n;
}

template <typename T>
inline void Vector<T>::erase(size_t index){
	erase(index, index + 1);
}

template <typename T>
inline void Vector<T>::erase(size_t firstIndex, size_t lastIndex){
	
	if(lastIndex < firstIndex or lastIndex > m_size)
		throw std::out_of_range("Index does not exist...\n");
		
	for(size_t i = firstIndex, j = lastIndex; i < m_size; m_arrPtr[i] = m_arrPtr[j], ++i, ++j);
				
	m_size -= lastIndex - firstIndex;
}
template <typename T>
inline void Vector<T>::swap (Vector& other){

	m_size > other.m_size? other.reserve(m_size) : reserve(other.m_size);
	
	//Swap arrays
	T* tmpPtr = m_arrPtr;
	m_arrPtr = other.m_arrPtr;
	other.m_arrPtr = tmpPtr;
	
	//Swap sizes
	size_t tmpSize = m_size;
	m_size = other.m_size;
	other.m_size = tmpSize;	
}

template <typename T>
inline void Vector<T>::clear (){
	delete[] m_arrPtr;
	
	m_arrPtr = NULL;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
inline Vector<T>& Vector<T>::operator +=(const Vector<T> v){
		
	*this = *this + v;
		
	return *this;
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::begin(){
	return m_arrPtr;
}

template <typename T>
inline const typename Vector<T>::iterator Vector<T>::begin() const {
	return m_arrPtr;
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::end(){
	return m_arrPtr + m_size;
}

template <typename T>
inline const typename Vector<T>::iterator Vector<T>::end() const {
	return m_arrPtr + m_size;
}

template <typename T>
inline Vector<T> operator+(const Vector<T> v1, const Vector<T> v2){
	
	Vector<T> res;
	
	for(size_t i = 0; i < v1.size(); res.push_back(v1.at(i)), ++i);
			
	for(size_t i = 0; i < v2.size(); res.push_back(v2.at(i)), ++i);
		
	return res;
}


#endif //__VECTOR_H__
