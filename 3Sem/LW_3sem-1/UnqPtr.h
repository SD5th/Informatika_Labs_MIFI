#pragma once

#include <cstring> // memcpy, size_t

template <class T>
class UnqPtr
{
private:
	T* ptr;
public:
  // UnqPtr with nullptr
	UnqPtr(); 
  
  // UnqPtr with given ptr
  UnqPtr(T* const &);

  // UnqPtr to copy of given object
	UnqPtr(T const &); 
	
  ~UnqPtr(); 

  // operator * for dereferencing
  T & operator*();

  // const version of operator * for dereferencing
  T const & operator*() const;
  
  T* operator=(UnqPtr const &);

  T* const operator=(UnqPtr const &) const;

 	UnqPtr(UnqPtr const &) = delete; 
	
  UnqPtr operator=(UnqPtr const &) = delete;
};


template <class T>
class UnqPtr<T[]>
{
private:
	T* ptr;
public:
  // UnqPtr with nullptr
	UnqPtr(); 

  // UnqPtr with given ptr
  UnqPtr(T* const &);

  // UnqPtr to copy of given array
  UnqPtr(T* const &, size_t const &); 
	
  ~UnqPtr(); 

  // operator [] for access to array element
  T & operator[](size_t const &);

  // const version of operator [] for access to array element
  T const & operator[](size_t const &) const;

 	UnqPtr(UnqPtr const &) = delete; 
	UnqPtr operator=(UnqPtr const &) = delete;
};