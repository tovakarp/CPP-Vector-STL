#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H


#include <stdlib.h>
#include <iostream>
#include <math.h> // for pow

template<class T>
class Vector{
public:
    Vector();
    Vector(size_t n, T val = T());
    Vector(const Vector<T>& other);
    
    ~Vector();
    
    Vector& operator=(const Vector& other);

    size_t size() const;
    
    size_t max_size() const;
    
    void resize(size_t newSize, T val = T());
    
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
	
	void push_back (const T& val);
	
	void pop_back();
	
	void insert(size_t index, const T &val);
	void insert(size_t index, size_t n, const T &val);
	
	void erase(size_t index);
	void erase (size_t firstIndex, size_t lastIndex);
	
	void swap (Vector& other);
	
	void clear();
	
	friend std::ostream& operator<<(std::ostream &os, const Vector &v){
		
		for(size_t i = 0; i < v.m_size; ++i)
			os << v.m_vecArray[i] << " ";
			
		os << std::endl;
	
		return os;
	}

    T getVecArray() const;
    size_t getCapacity() const;

private:
	void validateIndex(size_t index) const;

    T* m_vecArray;
    size_t m_size;
    size_t m_capacity;
};


template<class T>
inline Vector<T>::Vector() : m_vecArray(NULL), m_size(0), m_capacity(0) {}

template<class T>
inline Vector<T>::Vector(size_t n, T val) : m_vecArray(NULL), m_size(n), m_capacity(0)
{
    m_vecArray = new T[n + 1];

    for(size_t i = 0; i < n; ++i)
        m_vecArray[i] = val;
    m_vecArray[n + 1] = '\0';
}

template<class T>
inline Vector<T>::Vector(const Vector<T>& other) : m_vecArray(other.getVecArray()), m_size(other.getm_size()), m_capacity(other.getCapacity())
{
    if(m_capacity < other.size())
    {
        m_vecArray = new T[other.size() + 1];
        m_vecArray = other.getVecArray();
    }
}

template<class T>
inline Vector<T>::~Vector()
{
    delete[] m_vecArray;
    m_vecArray = NULL;
}

template <typename T>
Vector<T>& Vector<T> :: operator =(const Vector<T> &other){

	try{

		T *tmp = new T[other.m_capacity];

		for(size_t i = 0; i < other.m_size; ++i)
			tmp[i] = other.m_vecArray[i];
			
		delete[] m_vecArray;
		
		m_vecArray = tmp;
		m_capacity = other.m_capacity;
		m_size = other.m_size;	
	}
	
	catch(std::bad_alloc &ba){
		std::cout << "Error accured in oprator=" << std::endl;
	}
	
	return *this;
}

template<class T>
inline size_t Vector<T>::size() const
{
    return m_size;
}

template<class T>
inline size_t Vector<T>::max_size() const
{
    return pow(2 ,64) / sizeof(T) - 1;
}

template <typename T>
inline void Vector<T>::resize (size_t size, T val){

	reserve (size);
	
	if(size < m_size){
		m_size = size;
		return;
	}
	
	for (size_t i = m_size; i < size; ++i)
        m_vecArray[i] = val;
		
	m_size = size;
}

template<class T>
inline T Vector<T>::getVecArray() const
{
    return m_vecArray;
}

template<class T>
inline size_t Vector<T>::getCapacity() const
{
    return m_capacity;
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
			
			for(size_t i = 0; i < m_size; ++i)
				tmp[i] = m_vecArray[i];
				
			delete[] m_vecArray;
			
			m_vecArray = tmp;
			m_capacity = !m_capacity? 2 : m_capacity * 2;
		}
		
		catch(std::bad_alloc &ba){
			std::cout << "Error accured in reserve()" << std::endl;
		}
	}
}

template <typename T>
inline const T& Vector<T>::operator[](size_t index) const{
	return m_vecArray[index];
}

template <typename T>
inline T& Vector<T>::operator[](size_t index){
	return m_vecArray[index];
}

template <typename T>
inline void Vector<T>::validateIndex(size_t index) const{
	if(index > m_size)
		throw std::out_of_range("This index does not exist...\n");
}

template <typename T>
inline const T& Vector<T>::at(size_t index) const{

	validateIndex(index);
	
	return m_vecArray[index];
}

template <typename T>
inline T& Vector<T>::at(size_t index){

	validateIndex(index);
	
	return m_vecArray[index];
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
	return m_vecArray;
}

template <typename T>
inline T* Vector<T>::data() {
	return m_vecArray;
}

template <typename T>
inline void Vector<T>::assign (size_t size, const T& val){
	
	reserve(size);
	
	for(size_t i = 0; i < size; ++i)
		m_vecArray[i] = val;
			
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
	
	for(size_t i = index; i < m_size; ++i)
		m_vecArray[i + n] = m_vecArray[i];
		
	for(size_t i = index; i < index + n; ++i)
		m_vecArray[i] = val;
		
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
		
	for(size_t i = firstIndex, j = lastIndex; i < m_size; ++i, ++j)
		m_vecArray[i] = m_vecArray[j];
		
	m_size -= lastIndex - firstIndex;
}

template <typename T>
inline void Vector<T>::swap (Vector& other){

	m_size > other.m_size? other.reserve(m_size) : reserve(other.m_size);
	
	//Swap arrays
	T* tmpPtr = m_vecArray;
	m_vecArray = other.m_vecArray;
	other.m_vecArray = tmpPtr;
	
	//Swap sizes
	size_t tmpSize = m_size;
	m_size = other.m_size;
	other.m_size = tmpSize;	
}

template <typename T>
inline void Vector<T>::clear (){
	delete[] m_vecArray;
	
	m_vecArray = NULL;
	m_size = 0;
	m_capacity = 0;
}




#endif //VECTOR_VECTOR_H
