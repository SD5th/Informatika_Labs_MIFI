#pragma once

#include <cstring> // memcpy, size_t

template <class T>
class ShrdPtr
{
private:
	T* ptr;
	unsigned int * const referenceCount;

public:
/* Getters and setters */
  // Get ptr
  T* get() const;

  // Set ptr
  void set(T* const &);

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
  
  // Operator = for direct assignment
	ShrdPtr<T> & operator=(ShrdPtr const &);
};

template <class T>
class ShrdPtr<T[]>
{
private:
	T* const ptr;
	int * const referenceCount;
public:
/* Getters and setters */
  // Get ptr
  T* get() const;
  
  // Set ptr
  void set(T* const &);
  
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
  // Operator [] for dereferencing by index
  T & operator[](size_t const &);

  // Const vetsion of operator [] for dereferencing by index
  T const & operator[](size_t const &) const;

  // Operator = for direct assignment
	ShrdPtr<T> & operator=(ShrdPtr const &);
};