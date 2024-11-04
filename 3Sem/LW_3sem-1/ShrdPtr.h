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
  T* get() const;
  
  void set(T* const &);

/* Constructors */
  // ShrdPtr with nullptr
	ShrdPtr(); 
  
  // ShrdPtr with given ptr
  ShrdPtr(T* const &); 
	
  // share ptr
  ShrdPtr(ShrdPtr const &); 

/* Destructor */
  ~ShrdPtr(); 

/* Operators */
  // operator * for dereferencing
  T & operator*();

  // const version of operator * for dereferencing
  T const & operator*() const;
  
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
  T* get() const;
  
  void set(T* const &);
  
/* Constructors */
  // ptr to empty object
	ShrdPtr(); 
  
  // ShrdPtr with given ptr
  ShrdPtr(T* const &);
	
  // share ptr
  ShrdPtr(ShrdPtr const &); 

/* Destructor */
  ~ShrdPtr(); 

/* Operators */  
  // operator [] for access to array element
  T & operator[](size_t const &);

  // const version of operator [] for access to array element
  T const & operator[](size_t const &) const;

	ShrdPtr<T> operator=(ShrdPtr const &);
};