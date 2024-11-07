#include "UnqPtr.h"

/* UnqPtr to object */
/* Getters and setters */
  // Get ptr
  template <class T>
  T* UnqPtr<T>::get() const
  {
    return ptr;
  }
  // Set ptr
  template <class T>
  void UnqPtr<T>::set(T* const & newPtr)
  {
    if (ptr != nullptr)
        delete ptr;
    ptr = newPtr;
  }

/* Constructors */
  // UnqPtr with nullptr
	template <class T>
	UnqPtr<T>::UnqPtr():
		ptr(nullptr)
	{ }

	// UnqPtr with given ptr
	template <class T>
	UnqPtr<T>::UnqPtr(T* const & ptr):
		ptr(ptr)
	{ }

/* Destructor */
	template <class T>
	UnqPtr<T>::~UnqPtr()
	{
		delete ptr;
	}

/* Operators */
  // Operator * for dereferencing
	template <class T>
	T& UnqPtr<T>::operator*() {
	return *ptr;
	}

  // Const version of operator * for dereferencing
	template <class T>
	const T& UnqPtr<T>::operator*() const {
	return *ptr;
	}



/* UnqPtr to array */
/* Getters and setters */
  // Get ptr
  template <class T>
  T* UnqPtr<T[]>::get() const
  {
    return ptr;
  }

  // Set ptr
  template <class T>
  void UnqPtr<T[]>::set(T* const & newPtr)
  {
    if (ptr != nullptr)
        delete[] ptr;
    ptr = newPtr;
  }

/* Constructors */
  // UnqPtr with nullptr 
	template <class T>
	UnqPtr<T[]>::UnqPtr():
		ptr(nullptr)
	{ }

  // UnqPtr with given ptr
	template <class T>
	UnqPtr<T[]>::UnqPtr(T* const & ptr):
		ptr(ptr)
	{ }

/* Destructor */
	template <class T>
	UnqPtr<T[]>::~UnqPtr()
	{
		delete[] ptr;
	}
/* Operators */
  // Operator [] for dereferencing by index
	template <class T>
	T& UnqPtr<T[]>::operator[](size_t const & index) {
	return ptr[index];
	}

	// Const vetsion of operator [] for dereferencing by index
	template <class T>
	const T& UnqPtr<T[]>::operator[](size_t const & index) const {
		return ptr[index];
	}