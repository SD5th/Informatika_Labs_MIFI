#pragma once

#include <stdexcept>

#include "ShrdPtr.hpp"

template <class T>
class LinkedList
{
private:
  struct Node
  {
    T value;
    ShrdPtr<Node> next;
    Node(T const &);
    Node();

    // Iterative node cleaner
    void clearAfter();
  };

  ShrdPtr<Node> head;
  ShrdPtr<Node> tail;

public:
/* Constructors */
  // Constructor of zero-list
  LinkedList();

  // Constructor of empty list of given size
  LinkedList(size_t const &);

  // Constructor of list with given objects of given size
  LinkedList(T* const &, size_t const &);

  // Copy-constructor
  LinkedList(LinkedList<T> const &);

  // Move-constructor
  LinkedList(LinkedList<T> &&);

/* Destructor */
  ~LinkedList();

/* Getters */
  size_t getSize() const;

  // Get subsequence
  LinkedList<T> getSubsequence(size_t const &, size_t const &) const;  

/* Modifying Operations */
  // Resize
  void resize(size_t const &);

  // Insert 
  void insert(size_t const &, T const &);

  // Append
  void append(T const &);
  
  // Prepend
  void prepend(T const &);

  // Concatentaion
  void concat(LinkedList<T> const &);

/* Operators */
  // Dereferencing by index
  T & operator[](size_t const &);

  // Const version of dereferencing by index
  T const & operator[](size_t const &) const;
};



/* Node constructors */
  // Constructor of empty Node
  template <class T>
  LinkedList<T>::Node::Node():
    next(ShrdPtr<Node>())
  { }

  // Constructor of Node with given value
  template <class T>
  LinkedList<T>::Node::Node(T const & value):
    value(value),
    next(ShrdPtr<Node>())
  { }
  
  // Iterative node cleaner
  template <class T>
  void LinkedList<T>::Node::clearAfter()
    {
      if (next.get() != nullptr)
      {
        ShrdPtr<Node> current = next;
        next.set(nullptr);
        while (current.get() != nullptr) {
          ShrdPtr<Node> temp = current->next;
          current = temp;
        }
      }
    }


/* Constructors */
  // Constructor of zero-list
  template <class T>
  LinkedList<T>::LinkedList() : 
    head(ShrdPtr<Node>()),
    tail(ShrdPtr<Node>())
  { }

  // Constructor of empty list of given size
  template <class T>
  LinkedList<T>::LinkedList(size_t const & count) : 
    head(ShrdPtr<Node>()),
    tail(ShrdPtr<Node>())
  {
    if (count > 0)
    {
      head = ShrdPtr<Node>(new Node());
      ShrdPtr<Node> current = head;
      for (size_t i = 1; i < count; i++)
      {
        current->next = ShrdPtr<Node>(new Node());
        current = current->next;
      }
      tail = current;
    }
  }

  // Constructor of list with given objects of given size
  template <class T>
  LinkedList<T>::LinkedList(T* const & arr, size_t const & count) : 
    head(ShrdPtr<Node>()),
    tail(ShrdPtr<Node>())
  {
    if (count > 0)
    {
      head = ShrdPtr<Node>(new Node(arr[0]));
      ShrdPtr<Node> current = head;
      for (size_t i = 1; i < count; i++)
      {
        current->next = ShrdPtr<Node>(new Node(arr[i]));
        current = current->next;
      }
      tail = current;
    }
  }

  // Copy-constructor
  template <class T>
  LinkedList<T>::LinkedList(LinkedList<T> const & other) : 
    head(ShrdPtr<Node>()),
    tail(ShrdPtr<Node>())
  {
    if (other.head.get() != nullptr)
    {
      head = ShrdPtr<Node>(new Node(other.head->value));
      ShrdPtr<Node> current = head;
      ShrdPtr<Node> current_other = other.head;
      while(current_other.get() != other.tail.get())
      {
        current_other = current_other->next;
        current->next = ShrdPtr<Node>(new Node(current_other->value));
        current = current->next;
      }
      tail = current;
    }
  }
  // Move-constructor
  template <class T>
  LinkedList<T>::LinkedList(LinkedList<T> && other):
    head(other.head),
    tail(other.tail)
  {
    other.head.set(nullptr);
    other.tail.set(nullptr);
  }

/* Destructor */
  template <class T>
  LinkedList<T>::~LinkedList()
  {  
    if (head.get() != nullptr)
      head->clearAfter();
  }

/* Getters */
  // Get size
  template <class T>
  size_t LinkedList<T>::getSize() const {
    if (head.get() == nullptr)
      return 0;
    int size = 1;
    ShrdPtr<Node> current = head;
    while (current.get() != tail.get())
    {
      current = current->next;
      size++;
    }
    return size;
  }

  // Get subsequence
  template <class T>
  LinkedList<T> LinkedList<T>::getSubsequence(size_t const & startIndex, size_t const & endIndex) const
  {
    if (startIndex > endIndex)
      throw std::out_of_range("Function 'GetSubsequence': startIndex is greater than endIndex.");
    if (head.get() == nullptr)
      throw std::out_of_range("Function 'GetSubsequence': endIndex is equal or greater than size.");
    size_t index = 0;
    ShrdPtr<Node> current = head;
    for (; index < startIndex; index++)
    {
      if (current.get() == tail.get())
        throw std::out_of_range("Function 'GetSubsequence': endIndex is equal or greater than size.");
      current = current->next;
    }
    LinkedList<T> answer;
    answer.head = ShrdPtr<Node>(new Node(current->value));
    ShrdPtr<Node> answer_current = answer.head;
    for (; index < endIndex; index++)
    {
      if (current.get() == tail.get())
      {
        throw std::out_of_range("Function 'GetSubsequence': endIndex is equal or greater than size.");
      }
      answer_current->next = ShrdPtr<Node>(new Node(current->next->value));
      answer_current = answer_current->next;
      current = current->next;
    }
    answer.tail = answer_current;
    return std::move(answer);
  }


/* Modifying Operations */
  // Resize
  template <class T>
  void LinkedList<T>::resize(size_t const & newSize)
  {
    if (newSize == 0)
    {
      tail.set(nullptr);
      head->clearAfter();
      head.set(nullptr);
      return;
    }
    if (head.get() == nullptr)
    {
      head = ShrdPtr<Node>(new Node());
      ShrdPtr<Node> current = head;
      for (size_t index = 1; index < newSize; index++)
      {
        current->next = ShrdPtr<Node>(new Node());
        current = current->next;
      }
      tail = current;
      return;
    }
    size_t index = 1;
    ShrdPtr<Node> current = head;
    while ((index < newSize) && (current.get() != tail.get()))
    {
      current = current->next;    
      index++;
    }
    if (index == newSize && current.get() == tail.get())
      return;
    if (index == newSize)
    {
      tail = current;
      tail->clearAfter();
    }
    else
    {
      for (; index < newSize; index++)
      {
        current->next = ShrdPtr<Node>(new Node());
        current = current->next;
      }
      tail = current;
    }
  }

  // Insert
  template <class T>
  void LinkedList<T>::insert(size_t const & index, T const & value)
  {
    if (index == 0)
    {
      prepend(value);
      return;
    }
    if (head.get() == nullptr)
      throw std::out_of_range("Function 'insert': Index is greater than size.");
    ShrdPtr<Node> previous = head;
    ShrdPtr<Node> current = previous->next;
    for (size_t i = 1; i < index; i++)
    {
      if (current.get() == nullptr)
        throw std::out_of_range("Function 'insert': Index is greater than size.");
      previous = current;
      current = previous->next;
    }
    if (current.get() == nullptr)
    {
      append(value);
      return;
    }
    ShrdPtr<Node> insertion(new Node(value));
    insertion->next = current;
    previous->next = insertion;
  }

  // Append
  template <class T>
  void LinkedList<T>::append(T const & value)
  {
    ShrdPtr<Node> temp(new Node(value));
    if (head.get() == nullptr)
    {
      head = temp;
      tail = temp;
    }
    else
    {
      tail->next = temp;
      tail = temp;
    }
  }

  // Prepend
  template <class T>
  void LinkedList<T>::prepend(T const & value)
  {
    ShrdPtr<Node> temp(new Node(value));
    temp->next = head;
    head = temp; 
    if (head.get() == nullptr)
      tail = head;
  }

  // Concatenation
  template <class T>
  void LinkedList<T>::concat(LinkedList<T> const & other)
  {
    if (head.get() == nullptr)
    {
      if (other.head.get() != nullptr)
      {
        head = ShrdPtr<Node>(new Node(other.head->value));
        ShrdPtr<Node> current = head;
        ShrdPtr<Node> current_other = other.head;
        while(current_other.get() != other.tail.get())
        {
          current_other = current_other->next;
          current->next = ShrdPtr<Node>(new Node(current_other->value));
          current = current->next;
        }
        tail = current;
      }
    }
    else
    {
      if (other.head.get() != nullptr)
      {
        tail->next = ShrdPtr<Node>(new Node(other.head->value));
        ShrdPtr<Node> current = tail->next;
        ShrdPtr<Node> current_other = other.head;
        while(current_other.get() != other.tail.get())
        {
          current_other = current_other->next;
          current->next = ShrdPtr<Node>(new Node(current_other->value));
          current = current->next;
        }
        tail = current;
      }
    }
  }

/* Operators */
  // Dereferencing by index
  template <class T>
  T & LinkedList<T>::operator[](size_t const & index)
  {
    if (head.get() == nullptr)
      throw std::out_of_range("Operator '[]': Index is greater than or equal to size.");
    ShrdPtr<Node> current = head;
    for (size_t i = 0; i < index; i++)
    {
      if (current.get() == tail.get())
        throw std::out_of_range("Operator '[]': Index is greater than or equal to size.");
      current = current->next;
    }
    return current->value;
  }

  // Const version of dereferencing by index
  template <class T>
  T const & LinkedList<T>::operator[](size_t const & index) const
  {
    if (head.get() == nullptr)
      throw std::out_of_range("Const operator '[]': Index is greater than or equal to size.");
    ShrdPtr<Node> current = head;
    for (size_t i = 0; i < index; i++)
    {
      if (current.get() == tail.get())
        throw std::out_of_range("Const operator '[]': Index is greater than or equal to size.");
      current = current->next;
    }
    return current->value;
  }