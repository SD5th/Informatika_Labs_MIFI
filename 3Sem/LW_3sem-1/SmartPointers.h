#pragma once

#include <cstring> // Для memcpy

template <class T>
class UnqPtr
{
private:
	T* const ptr;
  bool const isArray;
public:
  // ptr to empty object
	UnqPtr(); 
  
  // ptr to object
	UnqPtr(T const &); 

  // ptr to array
  UnqPtr(T* const &, int const &); 
	
  ~UnqPtr(); 

  // operator * for dereferencing
  T & operator*();

  // const version of operator * for dereferencing
  T const & operator*() const;
  
  // operator [] for access to array element
  T & operator[](size_t const &);

  // const version of operator [] for access to array element
  T const & operator[](size_t const &) const;

 	UnqPtr(UnqPtr const &) = delete; 
	UnqPtr operator=(UnqPtr const &) = delete;
};

template <class T>
UnqPtr<T>::UnqPtr():
	ptr(new T),
	isArray(false)
{ }

template <class T>
UnqPtr<T>::UnqPtr(T const & object):
	ptr(new T(object)),
	isArray(false)
{ }


template <class T>
UnqPtr<T>::UnqPtr(T* const & array, int const & arrSize):
	ptr(new T[arrSize]),
  isArray(true)
{
  if (array != nullptr)
    std::memcpy(ptr, array, arrSize * sizeof(T));
}

template <class T>
UnqPtr<T>::~UnqPtr()
{
	if (isArray)
		delete ptr;
	else
		delete[] ptr;
}

template <class T>
T& UnqPtr<T>::operator*() {
  return *ptr;
}

template <class T>
const T& UnqPtr<T>::operator*() const {
  return *ptr;
}

template <class T>
T& UnqPtr<T>::operator[](size_t const & index) {
  return ptr[index];
}

template <class T>
const T& UnqPtr<T>::operator[](size_t const & index) const {
  return ptr[index];
}


template <class T>
class ShrdPtr
{
private:
	T* const ptr;
	int * const referenceCount;
	bool const isArray;
public:
  // ptr to empty object
	ShrdPtr(); 
  
  // ptr to given object
	ShrdPtr(T const &); 

  // ptr to static array
  ShrdPtr(T* const &, int const &); 
	
  // share ptr
 	ShrdPtr(ShrdPtr const &); 

  ~ShrdPtr(); 

  // operator * for dereferencing
  T & operator*();

  // const version of operator * for dereferencing
  T const & operator*() const;
  
  // operator [] for access to array element
  T & operator[](size_t const &);

  // const version of operator [] for access to array element
  T const & operator[](size_t const &) const;

	ShrdPtr<T> operator=(ShrdPtr const &);
};

template <class T>
ShrdPtr<T>::ShrdPtr():
	ptr(new T),
  referenceCount(new int(1)),
	isArray(false)
{ }

template <class T>
ShrdPtr<T>::ShrdPtr(T const & object):
	ptr(new T(object)),
  referenceCount(new int(1)),
	isArray(false)
{ }

template <class T>
ShrdPtr<T>::ShrdPtr(T* const & array, int const & arrSize):
	ptr(new T[arrSize]),
  referenceCount(new int(1)),
  isArray(true)
{
  if (array != nullptr)
    std::memcpy(ptr, array, arrSize * sizeof(T));
}

template <class T>
ShrdPtr<T>::ShrdPtr(ShrdPtr const & shrdPtr):
  ptr(shrdPtr.ptr),
  referenceCount(shrdPtr.referenceCount),
  isArray(shrdPtr.isArray) 
{
  *referenceCount += 1;
} 

template <class T>
ShrdPtr<T>::~ShrdPtr()
{
  *referenceCount -= 1;
	if (*referenceCount == 0)
  {
    if (isArray)
		  delete ptr;
	  else
  		delete[] ptr;
  }
}

template <class T>
T& ShrdPtr<T>::operator*() {
  return *ptr;
}

template <class T>
const T& ShrdPtr<T>::operator*() const {
  return *ptr;
}

template <class T>
T& ShrdPtr<T>::operator[](size_t const & index) {
  return ptr[index];
}

template <class T>
const T& ShrdPtr<T>::operator[](size_t const & index) const {
  return ptr[index];
}

template <class T>
ShrdPtr<T> ShrdPtr<T>::operator=(ShrdPtr const &)
{
  return ShrdPtr(this);
}