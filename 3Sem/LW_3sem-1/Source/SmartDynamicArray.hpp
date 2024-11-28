#pragma once

#include <exception>

#include "UnqPtr.hpp"

template <class T>
class DynamicArray
{
private:
  UnqPtr<T[]> data; // Элементы (ссылка на первый)
  size_t size;      // Количество элементов
  size_t capacity;  // Количество зарезервированных ячеек памяти

public:

/* Constructors */
  // Constructor of zero-array
  DynamicArray();

  // Constructor of empty array of given size
  DynamicArray(size_t const &);

  // Constructor of array with given objects of given size
  DynamicArray(T *const &, size_t const &);

  // Copy-constructor
  DynamicArray(DynamicArray const &);

  // Move-constructor
  DynamicArray(DynamicArray &&);

/* Getters */
  // Get size
  int getSize() const;
  
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

  // Concatenation  
  void concat(DynamicArray<T> const &);

/* Operators */
  // Dereferencing by index
  T &operator[](size_t);

  // Const version of dereferencing by index
  T const & operator[](size_t) const;
};

/* Constructors */
  // Constructor of zero-array
  template <class T>
  DynamicArray<T>::DynamicArray() : 
    size(0),
    capacity(0),
    data(UnqPtr())
  { }

  // Constructor of empty array of given size
  template <class T>
  DynamicArray<T>::DynamicArray(size_t const &size) : 
    size(size),
    capacity(size * 2),
    data(UnqPtr(new T[capacity]))
  { }

  // Constructor of array with given objects of given size
  template <class T>
  DynamicArray<T>::DynamicArray(T *const &items, size_t const &size) : 
    size(size),
    capacity(size * 2),
    data(UnqPtr(new T[capacity]))
  {
    memcpy(data, items, size * sizeof(T));
  }

  // Copy-constructor
  template <class T>
  DynamicArray<T>::DynamicArray(DynamicArray const &dynamicArray) : 
    size(dynamicArray.size),
    capacity(dynamicArray.capacity),
    data(UnqPtr(new T[capacity]))
  {
    memcpy(data, dynamicArray.data, size * sizeof(T));
  }

  // Move-constructor
  template <class T>
  DynamicArray<T>::DynamicArray(DynamicArray &&other) : 
    data(std::move(other.data))
  { }

/* Getters */
  // Get size
  template <class T>
  int DynamicArray<T>::getSize() const 
  {
    return size;
  }
  
  // Get subsequence
  template <class T>
  DynamicArray<T> DynamicArray<T>::getSubsequence(size_t const &startIndex, size_t const &endIndex) const
  {
    if (startIndex < 0)
      throw std::exception("Function 'GetSubsequence': Negative startIndex.");
    if (startIndex > endIndex)
      throw std::exception("Function 'GetSubsequence': startIndex is greater than endIndex.");
    if (endIndex >= this->GetSize())
      throw std::exception("Function 'GetSubsequence': endIndex is equal or greater than size.");

    return DynamicArray<T>(data.ptr + startIndex, endIndex - startIndex + 1);
  }


/* Modifying Operations */
  // Resize
  template <class T>
  void DynamicArray<T>::resize(size_t const &newSize)
  {
    if (newSize < 0)
      throw std::exception("Function 'Resize': Negative size.");
    if (capacity >= newSize && newSize >= this->capacity / 4)
      this->size = newSize;
    else
    {
      size = newSize;
      capacity = newSize * 2;
      T *newPtr = new T[capacity];
      memcpy(newPtr, data.get(), size * sizeof(T));
      data = UnqPtr(newPtr);
    }
  }

  // Insert 
  template <class T>
  void DynamicArray<T>::insert(size_t const &index, T const &item)
  {
    if (index < 0)
      throw std::exception("Function 'InsertAt': Negative index.");
    if (index > size)
      throw std::exception("Function 'InsertAt': Index is greater than size.");
    if (size == capacity)
    {
      size += 1;
      capacity = 2 * size;
      T *ptr = new T[capacity];
      memcpy(ptr, data.get(), index * sizeof(T));
      ptr[index] = item;
      memcpy(ptr + index + 1, data.get() + index, (size - index - 1) * sizeof(T));
      data = UnqPtr(ptr);
    }
    else
    {
      size += 1;
      for (size_t i = size - 1; i > index; i -= 1)
        data[i] = data[i - 1];
      data[index] = item;
    }
  }

  // Append 
  template <class T>
  void DynamicArray<T>::append(T const &item)
  {
    insert(size, item);
  }

  // Prepend 
  template <class T>
  void DynamicArray<T>::prepend(T const &item)
  {
    insert(0, item);
  }

  // Concatenation  
  template <class T>
  void DynamicArray<T>::concat(DynamicArray<T> const & other)
  {
    int prevSize = getSize();
    Resize(getSize() + other.GetSize());
    for (int i = prevSize; i < getSize(); i++)
    {
      (*this)[i] = other[i - prevSize];
    }
  }

/* Operators */
  // Dereferencing by index
  template <class T>
  T &DynamicArray<T>::operator[](size_t index)
  {
    if (index < 0)
      throw std::exception("Operator '[]': Negative index.");
    if (index >= size)
      throw std::exception("Operator '[]': Index is greater than size.");
    return data[index];
  }

  // Const version of dereferencing by index
  template <class T>
  T const &DynamicArray<T>::operator[](size_t index) const
  {
    if (index < 0)
      throw std::exception("Const operator '[]': Negative index.");
    if (index >= size)
      throw std::exception("Const operator '[]': Index is greater than size.");
    return data[index];
  }