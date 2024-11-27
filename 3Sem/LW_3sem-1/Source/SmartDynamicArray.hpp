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
  // конструкторы

  DynamicArray();

  DynamicArray(size_t const &);

  DynamicArray(T *const &, size_t const &);

  DynamicArray(DynamicArray const &);

  // Move-constructor
  DynamicArray(DynamicArray &&);

  // декомпозиция
  DynamicArray<T> getSubsequence(size_t const &, size_t const &) const;

  int getSize() const;

  // операции
  void resize(size_t const &);

  void insert(size_t const &, T const &);

  void append(T const &);

  void prepend(T const &);

  DynamicArray<T> concat(DynamicArray<T> &);

  // перегрузка операторов
  T &operator[](size_t);

  T const &operator[](size_t) const;
};

template <class T>
DynamicArray<T>::DynamicArray() : size(0),
                                  capacity(0),
                                  data(UnqPtr())
{
}

template <class T>
DynamicArray<T>::DynamicArray(size_t const &size) : size(size),
                                                    capacity(size * 2),
                                                    data(UnqPtr(new T[capacity]))
{
}

template <class T>
DynamicArray<T>::DynamicArray(T *const &items, size_t const &size) : size(size),
                                                                     capacity(size * 2),
                                                                     data(UnqPtr(new T[capacity]))
{
  memcpy(data, items, size * sizeof(T));
}

template <class T>
DynamicArray<T>::DynamicArray(DynamicArray const &dynamicArray) : size(dynamicArray.size),
                                                                  capacity(dynamicArray.capacity),
                                                                  data(UnqPtr(new T[capacity]))
{
  memcpy(data, dynamicArray.data, size * sizeof(T));
}

  // Move-constructor	
  template <class T>
	DynamicArray<T>::DynamicArray(DynamicArray && other):
		data(std::move(other.data))
	{ }

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

template <class T>
int DynamicArray<T>::getSize() const // Получить size
{
  return size;
}

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

template <class T>
void DynamicArray<T>::insert(size_t const &index, T const &item)
{
  if (index < 0)
    throw IndexOutOfRange("Function 'InsertAt': Negative index.");
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

template <class T>
void DynamicArray<T>::append(T const &item)
{
  insert(size, item);
}

template <class T>
void DynamicArray<T>::prepend(T const &item)
{
  insert(0, item);
}

template <class T>
DynamicArray<T> DynamicArray<T>::concat(DynamicArray<T> &array)
{
  DynamicArray<T> *output = new DynamicArray<T>(*this);
  (*output).Resize(this->GetSize() + array.GetSize());
  for (int i = this->GetSize(); i < output->GetSize(); i++)
  {
    (*output).Set(i, array.Get(i - this->GetSize()));
  }
  return *output;
}

// перегрузка операторов
template <class T>
T &DynamicArray<T>::operator[](size_t index)
{
  if (index < 0)
    throw std::exception("Operator '[]': Negative index.");
  if (index >= size)
    throw std::exception("Operator '[]': Index is greater than size.");
  return data[index];
}

template <class T>
T const &DynamicArray<T>::operator[](size_t index) const
{
  if (index < 0)
    throw std::exception("Const operator '[]': Negative index.");
  if (index >= size)
    throw std::exception("Const operator '[]': Index is greater than size.");
  return data[index];
}