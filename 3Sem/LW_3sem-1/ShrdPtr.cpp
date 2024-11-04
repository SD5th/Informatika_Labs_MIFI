#include "ShrdPtr.h"

template <class T>
ShrdPtr<T>::ShrdPtr():
	ptr(nullptr),
  referenceCount(nullptr)
{ }

template <class T>
ShrdPtr<T>::ShrdPtr(T* const & ptr):
	ptr(ptr),
  referenceCount(new unsigned int(1))
{ }

template <class T>
ShrdPtr<T>::ShrdPtr(T const & object):
	ptr(new T(object)),
  referenceCount(new unsigned int(1))
{ }

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









template <class T>
ShrdPtr<T>::ShrdPtr():
	ptr(nullptr),
  referenceCount(new unsigned int(1))
{ }

template <class T>
ShrdPtr<T>::ShrdPtr(T* const & ptr):
	ptr(ptr),
  referenceCount(new unsigned int(1))
{ }

template <class T>
ShrdPtr<T>::ShrdPtr(T const & object):
	ptr(new T(object)),
  referenceCount(new unsigned int(1))
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