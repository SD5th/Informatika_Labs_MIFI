#include "UnqPtr.h"


template <class T>
UnqPtr<T>::UnqPtr():
	ptr(nullptr)
{ }

template <class T>
UnqPtr<T>::UnqPtr(T* const & ptr):
	ptr(ptr)
{ }

template <class T>
UnqPtr<T>::~UnqPtr()
{
	delete ptr;
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
UnqPtr<T[]>::UnqPtr():
	ptr(nullptr)
{ }

template <class T>
UnqPtr<T[]>::UnqPtr(T* const & ptr):
	ptr(ptr)
{ }


template <class T>
UnqPtr<T[]>::UnqPtr(T* const & array, size_t const & arrSize):
	ptr(new T[arrSize])
{
  if (array != nullptr)
    std::memcpy(ptr, array, arrSize * sizeof(T));
}

template <class T>
UnqPtr<T[]>::~UnqPtr()
{
	delete[] ptr;
}

template <class T>
T& UnqPtr<T[]>::operator[](size_t const & index) {
  return ptr[index];
}

template <class T>
const T& UnqPtr<T[]>::operator[](size_t const & index) const {
  return ptr[index];
}