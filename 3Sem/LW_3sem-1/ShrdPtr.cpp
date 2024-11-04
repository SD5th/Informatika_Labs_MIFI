#include "ShrdPtr.h"

/* UnqPtr to object */
/* Getters and setters */
  template <class T>
  T* ShrdPtr<T>::get() const
  {
    return ptr;
  }
  
  template <class T>
  void ShrdPtr<T>::set(T* const & newPtr)
  {
    if (referenceCount != nullptr)
    {
      if (*referenceCount == 1)
      {
        delete ptr;
      }
      else
      {
        *referenceCount -= 1;
        referenceCount = new unsigned int(1);
      }
    }
    else
    {
      referenceCount = new unsigned int(1);
    }
    ptr = newPtr;
  }

/* Constructors */
  // ShrdPtr with nullptr
  template <class T>
  ShrdPtr<T>::ShrdPtr():
    ptr(nullptr),
    referenceCount(nullptr)
  { }

  // ShrdPtr with given ptr
  template <class T>
  ShrdPtr<T>::ShrdPtr(T* const & ptr):
    ptr(ptr),
    referenceCount(new unsigned int(1))
  { }

  // share ptr
  template <class T>
  ShrdPtr<T>::ShrdPtr(ShrdPtr const & shrdPtr):
    ptr(shrdPtr.ptr),
    referenceCount(shrdPtr.referenceCount)
  {
    *referenceCount += 1;
  }

/* Destructor */
  template <class T>
  ShrdPtr<T>::~ShrdPtr()
  {
    if (--(*referenceCount) == 0)
    {
      delete ptr;
      delete referenceCount;
    }
  }

/* Operators */
  template <class T>
  T& ShrdPtr<T>::operator*() {
    return *ptr;
  }

  template <class T>
  const T& ShrdPtr<T>::operator*() const {
    return *ptr;
  }

  template <class T>
  ShrdPtr<T>& ShrdPtr<T>::operator=(ShrdPtr const & other)
  {
    if (this != &other) { 
      if (--(*ref_count) == 0) {
        delete ptr;
        delete referenceCount; 
      }
      ptr = other.ptr;
      referenceCount = other.referenceCount;
      (*referenceCount)++;
    }
    return *this;
  }








/* UnqPtr to array */
/* Getters and setters */
  template <class T>
  T* ShrdPtr<T[]>::get() const
  {
    return ptr;
  }
  
  template <class T>
  void ShrdPtr<T[]>::set(T* const & newPtr)
  {
    if (referenceCount != nullptr)
    {
      if (*referenceCount == 1)
      {
        delete[] ptr;
      }
      else
      {
        *referenceCount -= 1;
        referenceCount = new unsigned int(1);
      }
    }
    else
    {
      referenceCount = new unsigned int(1);
    }
    ptr = newPtr;
  }

/* Constructors */
  // ShrdPtr with nullptr 
  template <class T>
  ShrdPtr<T[]>::ShrdPtr():
    ptr(nullptr),
    referenceCount(nullptr)
  { }

  template <class T>
  ShrdPtr<T[]>::ShrdPtr(T* const & ptr):
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

/* Destructor */
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

/* Operators */
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