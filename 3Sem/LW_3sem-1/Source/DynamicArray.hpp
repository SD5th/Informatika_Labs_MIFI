#pragma once

#include <stdexcept>

#include "UnqPtr.hpp"

template <class T>
class DynamicArray
{
private:
  size_t size;      // Amount of items that Array can contain
  size_t capacity;  // Maximum size without reallocating
  UnqPtr<T[]> data; // UnqPtr with items

public:
/* Constructors */
  // Constructor of zero-array
  DynamicArray();

  // Constructor of empty array of given size
  DynamicArray(size_t const &);

  // Constructor of array with given objects of given size
  DynamicArray(T* const &, size_t const &);

  // Copy-constructor
  DynamicArray(DynamicArray const &);

  // Move-constructor
  DynamicArray(DynamicArray &&);

/* Getters */
  // Get size
  size_t getSize() const;
  
  // Get subsequence
  DynamicArray<T> getSubsequence(size_t const &, size_t const &) const;

/* Modifying Operations */
  // Resize
  void resize(size_t const &);

  // Insert 
  void insert(size_t const &, T const &);

  // Append 
  void append(T const &);

  // Prepend 
  void prepend(T const &);

  // Remove
  void remove(size_t const &);

  // Concatenation  
  void concat(DynamicArray<T> const &);

/* Operators */
  // Dereferencing by index
  T &operator[](size_t const &);

  // Const version of dereferencing by index
  T const & operator[](size_t const &) const;
};

/* Constructors */
  // Constructor of zero-array
  template <class T>
  DynamicArray<T>::DynamicArray() : 
    size(0),
    capacity(0),
    data(UnqPtr<T[]>())
  { }

  // Constructor of empty array of given size
  template <class T>
  DynamicArray<T>::DynamicArray(size_t const &size) : 
    size(size),
    capacity(size * 2),
    data(UnqPtr<T[]>(new T[capacity]))
  { }

  // Constructor of array with given objects of given size
  template <class T>
  DynamicArray<T>::DynamicArray(T *const &items, size_t const &size) : 
    size(size),
    capacity(size * 2),
    data(UnqPtr<T[]>(new T[capacity]))
  {
    for (size_t index = 0; index < size; index++)
      data[index] = items[index];
  }

  // Copy-constructor
  template <class T>
  DynamicArray<T>::DynamicArray(DynamicArray const &dynamicArray) : 
    size(dynamicArray.size),
    capacity(dynamicArray.capacity),
    data(UnqPtr<T[]>(new T[capacity]))
  {
    for (size_t index = 0; index < size; index++)
      data[index] = dynamicArray[index];
  }

  // Move-constructor
  template <class T>
  DynamicArray<T>::DynamicArray(DynamicArray &&other) : 
    size(other.size),
    capacity(other.capacity),
    data(std::move(other.data))
  {
    other.size = 0;
    other.capacity = 0;
  }

/* Getters */
  // Get size
  template <class T>
  size_t DynamicArray<T>::getSize() const 
  {
    return size;
  }

  // Get subsequence
  template <class T>
  DynamicArray<T> DynamicArray<T>::getSubsequence(size_t const & startIndex, size_t const & endIndex) const
  {
    if (startIndex > endIndex)
      throw std::out_of_range("Function 'GetSubsequence': startIndex is greater than endIndex.");
    if (endIndex >= getSize())
      throw std::out_of_range("Function 'GetSubsequence': endIndex is equal or greater than size.");
    DynamicArray<T> result(data.get() + startIndex, endIndex - startIndex + 1);
    return std::move(result);
  }

/* Modifying Operations */
  // Resize
  template <class T>
  void DynamicArray<T>::resize(size_t const &newSize)
  {
    if (capacity >= newSize && newSize >= this->capacity / 4)
      this->size = newSize;
    else
    {
      size = newSize;
      capacity = newSize * 2;
      UnqPtr<T[]> buffer(new T[capacity]);
      for (size_t index = 0; index < size; index++)
        buffer[index] = data[index];      
      data = std::move(buffer);
    }
  }

  // Insert 
  template <class T>
  void DynamicArray<T>::insert(size_t const & ins_index, T const & item)
  {
    if (ins_index > size)
      throw std::out_of_range("Function 'InsertAt': Index is greater than size.");
    if (size == capacity)
    {
      capacity = (capacity == 0) ? 1 : 2 * capacity;
      UnqPtr<T[]> buffer(new T[capacity]);
      size_t index = 0;
      for (; index < ins_index; index++)
        buffer[index] = data[index];      
      buffer[index] = item;
      for (; index < size; index++)
        buffer[index+1] = data[index];
      data = std::move(buffer);
    }
    else
    {
      for (size_t index = size; index > ins_index; index--)
        data[index] = data[index - 1];
      data[ins_index] = item;
    }
    size++;
  }

  // Append 
  template <class T>
  void DynamicArray<T>::append(T const & item)
  {
    insert(size, item);
  }

  // Prepend 
  template <class T>
  void DynamicArray<T>::prepend(T const & item)
  {
    insert(0, item);
  }

  // Remove
  template <class T>
  void DynamicArray<T>::remove(size_t const & index)
  {
    if (index >= size)
      throw std::out_of_range("Remove: Index is greater than size.");
    for (size_t i = index; i < size - 1; i++)
      data[i] = std::move(data[i+1]);
    resize(size-1);
  }

  // Concatenation  
  template <class T>
  void DynamicArray<T>::concat(DynamicArray<T> const & other)
  {
    int prevSize = getSize();
    resize(getSize() + other.getSize());
    for (size_t i = prevSize; i < getSize(); i++)
    {
      (*this)[i] = other[i - prevSize];
    }
  }

/* Operators */
  // Dereferencing by index
  template <class T>
  T &DynamicArray<T>::operator[](size_t const & index)
  {
    if (index >= size)
      throw std::out_of_range("Operator '[]': Index is greater than size.");
    return data[index];
  }

  // Const version of dereferencing by index
  template <class T>
  T const &DynamicArray<T>::operator[](size_t const & index) const
  {
    if (index >= size)
      throw std::out_of_range("Const operator '[]': Index is greater than size.");
    return data[index];
  }