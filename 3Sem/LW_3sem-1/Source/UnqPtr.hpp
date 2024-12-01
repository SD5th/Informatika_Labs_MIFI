#pragma once

#include <cstring> // memcpy, size_t

template <class T>
class UnqPtr
{
private:
	T* ptr;
  
public:
/* Getters and setters */
  // Get ptr
  T* get() const;

  // Set ptr
  void set(T* const &);

/* Constructors */
  // UnqPtr with nullptr
	UnqPtr(); 
  
  // UnqPtr with given ptr
  UnqPtr(T* const &);

  // No copy-constructor
 	UnqPtr(UnqPtr const &) = delete; 

  // Move-constructor
  UnqPtr(UnqPtr &&);

/* Destructor */
  ~UnqPtr(); 

/* Operators */
  // operator * for dereferencing
  T & operator*();

  // const version of operator * for dereferencing
  T const & operator*() const;

  // No assignment with copying an object
	UnqPtr operator=(UnqPtr const &) = delete;

  // Assignment with moving an object
	void operator=(UnqPtr &&);
};


template <class T>
class UnqPtr<T[]>
{
private:
	T* ptr;
public:
/* Getters and setters */
  // Get ptr
  T* get() const;

  // Set ptr
  void set(T* const &);

/* Constructors */
  // UnqPtr with nullptr
	UnqPtr(); 

  // UnqPtr with given ptr
  UnqPtr(T* const &);

  // No copy-constructor
 	UnqPtr(UnqPtr const &) = delete; 

  // Move-constructor
  UnqPtr(UnqPtr &&);

/* Destructor */
  ~UnqPtr(); 

/* Operators */
  // Operator [] for dereferencing by index
  T & operator[](size_t const &);

  // Const version of operator [] for dereferencing by index
  T const & operator[](size_t const &) const;

  // No assignment with copying an object
	UnqPtr operator=(UnqPtr const &) = delete;

  // Assignment with moving an object
	void operator=(UnqPtr &&);
};


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
    this->~UnqPtr();
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
	
  // Move-constructor	
  template <class T>
	UnqPtr<T>::UnqPtr(UnqPtr && other):
		ptr(std::move(other.ptr))
	{ 
    other.ptr = nullptr;
  }

/* Destructor */
	template <class T>
	UnqPtr<T>::~UnqPtr()
	{
    if (ptr != nullptr)
    {
      delete ptr;
      ptr = nullptr;
    }
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

  // Assignment with moving an object
	template <class T>
	void UnqPtr<T>::operator=(UnqPtr && other)
  {
    if (this != &other) 
    {
      ptr = std::move(other.ptr);
      other.ptr = nullptr;
    }
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
    this->~UnqPtr();
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

  // Move-constructor	
  template <class T>
	UnqPtr<T[]>::UnqPtr(UnqPtr && other):
		ptr(std::move(other.ptr))
	{ 
    other.ptr = nullptr;
  }

/* Destructor */
	template <class T>
	UnqPtr<T[]>::~UnqPtr()
	{
    if (ptr != nullptr)
    {
      delete[] ptr;
      ptr = nullptr;
    }	
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

  // Assignment with moving an object
	template <class T>
	void UnqPtr<T[]>::operator=(UnqPtr && other)
  {
    if (this != &other) 
    {
      ptr = std::move(other.ptr);
      other.ptr = nullptr;
    }
  }