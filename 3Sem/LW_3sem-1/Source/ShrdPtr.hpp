#pragma once

#include <cstring> // memcpy, size_t

template <class T>
class ShrdPtr
{
private:
	T* ptr;
	unsigned int * referenceCount;

public:
/* Getters and setters */
  // Get ptr
  T* get() const;

  // Set ptr
  void set(T* const &);

  // Get reference count
  unsigned int getReferenceCount() const;

/* Constructors */
  // ShrdPtr with nullptr
	ShrdPtr(); 
  
  // ShrdPtr with given ptr
  ShrdPtr(T* const &); 
	
  // ShrdPtr that shares ptr with another ShrdPtr
  ShrdPtr(ShrdPtr const &); 

/* Destructor */
  ~ShrdPtr(); 

/* Operators */
  // Operator * for dereferencing
  T & operator*();

  // Const version of operator * for dereferencing
  T const & operator*() const;

  // operator -> for access to class fields
  T* operator->();

  // const verison of operator -> for access to class fields
  const T* operator->() const;
  
  // Operator = for direct assignment
	ShrdPtr<T> & operator=(ShrdPtr const &);
};

template <class T>
class ShrdPtr<T[]>
{
private:
	T* ptr;
	unsigned int * referenceCount;
public:
/* Getters and setters */
  // Get ptr
  T* get() const;
  
  // Set ptr
  void set(T* const &);
  
  // Get reference count
  unsigned int getReferenceCount() const;

/* Constructors */
  // ShrdPtr with nullptr 
	ShrdPtr(); 
  
  // ShrdPtr with given ptr
  ShrdPtr(T* const &);
	
  // ShrdPtr that shares ptr with another ShrdPtr
  ShrdPtr(ShrdPtr const &); 

/* Destructor */
  ~ShrdPtr(); 

/* Operators */  
  // operator * for dereferencing
  T & operator*();

  // const version of operator * for dereferencing
  T const & operator*() const;

  // operator -> for access to class fields
  T* operator->();

  // const verison of operator -> for access to class fields
  const T* operator->() const;

  // Operator [] for dereferencing by index
  T & operator[](size_t const &);

  // Const vetsion of operator [] for dereferencing by index
  T const & operator[](size_t const &) const;

  // Operator = for direct assignment
	ShrdPtr<T[]> & operator=(ShrdPtr const &);
};

/* UnqPtr to object */
/* Getters and setters */
  // Get ptr
  template <class T>
  T* ShrdPtr<T>::get() const
  {
    return ptr;
  }
  
  // Set ptr
  template <class T>
  void ShrdPtr<T>::set(T* const & newPtr)
  {
    this->~ShrdPtr();
    ptr = newPtr;
    referenceCount = new unsigned int(1);
  }

  // Get reference count
  template <class T>
  unsigned int ShrdPtr<T>::getReferenceCount() const
  {
    return *referenceCount;
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

  // ShrdPtr that shares ptr with another ShrdPtr
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
    if (referenceCount != nullptr)
    {
      if (--(*referenceCount) == 0)
      {
        delete ptr;
        delete referenceCount;
      }
      ptr = nullptr;
      referenceCount = nullptr;
    }
  }

/* Operators */
  // Operator * for dereferencing
  template <class T>
  T& ShrdPtr<T>::operator*() {
    return *ptr;
  }

  // Const version of operator * for dereferencing
  template <class T>
  const T& ShrdPtr<T>::operator*() const {
    return *ptr;
  }

  // operator -> for access to class fields
  template <class T>
  T* ShrdPtr<T>::operator->() {
    return ptr;
  }

  // const verison of operator -> for access to class fields
  template <class T>
  const T* ShrdPtr<T>::operator->() const {
    return ptr;
  }

  // Operator = for direct assignment
  template <class T>
  ShrdPtr<T>& ShrdPtr<T>::operator=(ShrdPtr const & other)
  {
    if (this != &other) { 
      this->~ShrdPtr();
      ptr = other.ptr;
      referenceCount = other.referenceCount;
      (*referenceCount)++;
    }
    return *this;
  }



/* UnqPtr to array */
/* Getters and setters */
  // Get ptr
  template <class T>
  T* ShrdPtr<T[]>::get() const
  {
    return ptr;
  }
  
  // Set ptr
  template <class T>
  void ShrdPtr<T[]>::set(T* const & newPtr)
  {
    this->~ShrdPtr();
    ptr = newPtr;
    referenceCount = new unsigned int(1);
  }

  // Get reference count
  template <class T>
  unsigned int ShrdPtr<T[]>::getReferenceCount() const
  {
    return *referenceCount;
  }

/* Constructors */
  // ShrdPtr with nullptr 
  template <class T>
  ShrdPtr<T[]>::ShrdPtr():
    ptr(nullptr),
    referenceCount(nullptr)
  { }

  // ShrdPtr with given ptr
  template <class T>
  ShrdPtr<T[]>::ShrdPtr(T* const & ptr):
    ptr(ptr),
    referenceCount(new unsigned int(1))
  { }

  // ShrdPtr that shares ptr with another ShrdPtr
  template <class T>
  ShrdPtr<T[]>::ShrdPtr(ShrdPtr const & shrdPtr):
    ptr(shrdPtr.ptr),
    referenceCount(shrdPtr.referenceCount)
  {
    *referenceCount += 1;
  } 

/* Destructor */
  template <class T>
  ShrdPtr<T[]>::~ShrdPtr()
  {
    if (referenceCount != nullptr)
    {
      if (--(*referenceCount) == 0)
      {
        delete[] ptr;
        delete referenceCount;
      }
      ptr = nullptr;
      referenceCount = nullptr;
    }
  }

/* Operators */
  // Operator * for dereferencing
	template <class T>
	T& ShrdPtr<T[]>::operator*() {
	  return *ptr;
	}

  // Const version of operator * for dereferencing
	template <class T>
	const T& ShrdPtr<T[]>::operator*() const {
	  return *ptr;
	}

  // operator -> for access to class fields
  template <class T>
  T* ShrdPtr<T[]>::operator->() {
    return ptr;
  }

  // const verison of operator -> for access to class fields
  template <class T>
  const T* ShrdPtr<T[]>::operator->() const {
    return ptr;
  }

  // Operator [] for dereferencing by index
  template <class T>
  T& ShrdPtr<T[]>::operator[](size_t const & index) {
    return ptr[index];
  }

  // Const vetsion of operator [] for dereferencing by index
  template <class T>
  T const & ShrdPtr<T[]>::operator[](size_t const & index) const {
    return ptr[index];
  }

  // Operator = for direct assignment
  template <class T>
  ShrdPtr<T[]> & ShrdPtr<T[]>::operator=(ShrdPtr const & other)
  {
    if (this != &other) { 
      this->~ShrdPtr();
      ptr = other.ptr;
      referenceCount = other.referenceCount;
      (*referenceCount)++;
    }
    return *this;
  }