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

/* Destructor */
  ~UnqPtr(); 

/* Operators */
  // operator * for dereferencing
  T & operator*();

  // const version of operator * for dereferencing
  T const & operator*() const;

/* Deleted semantics */
  // No copy-constructor
 	UnqPtr(UnqPtr const &) = delete; 
	
  // No assignment
  UnqPtr operator=(UnqPtr const &) = delete;
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

/* Destructor */
  ~UnqPtr(); 

/* Operators */
  // Operator [] for dereferencing by index
  T & operator[](size_t const &);

  // Const version of operator [] for dereferencing by index
  T const & operator[](size_t const &) const;

/* Deleted semantics */
  // No copy-constructor
 	UnqPtr(UnqPtr const &) = delete;

  // No assignment
	UnqPtr operator=(UnqPtr const &) = delete;
};