#pragma once

#include <stdexcept>
#include "BalancedTree.hpp"

template <class K, class V>
class Dictionary
{
private:
  BalancedTree<K,V>* tree; 
public:
  class InOrderIterator
  {
    friend class Dictionary;
  private:
    typename BalancedTree<K, V>::InOrderIterator* iterator;


    InOrderIterator(BalancedTree<K,V>* tree):
      iterator(new typename BalancedTree<K, V>::InOrderIterator(tree->createInOrderIterator()))
    { }

  public:
    // Destructor
    ~InOrderIterator();

    // Get link to current value
    V & value();

    // Get const link to current value
    V const & value() const;
      
    // Get const link to current key
    K const & key() const;

    // Check if empty
    bool isEmpty() const;

    // Check if current node is last
    bool hasNext() const;

    // Go to the next key
    bool next() const;   
  };

/* Constructors */
  // Constructor of zero-array
  Dictionary();

  // Copy-constructors
  Dictionary(Dictionary const &);

/* Destructor */
  ~Dictionary();

/* Getters */
  // Get number of values
  size_t getCount() const;

  // Does dictionary contain key
  bool containsKey(K const &) const;

  // Secure way to read value of that key (similar to const [])
  V const & at(K const &) const;

  // Get minimal key
  K getMinKey() const;

  // Get maximal key
  K getMaxKey() const;

/* Modifying Operations */
  // Remove by key
  void remove(K const &);

  // Delete all tree
  void removeAllKeys();
  
  // Secure way to change value of that key
  V & at(K const &);

/* Operators */
  // Dereferencing by key
  V &operator[](K const &);

  // Const version of dereferencing by key
  V const & operator[](K const &) const;

  Dictionary& operator=(Dictionary const &);

/* Iterators */
  /* Standart ascending InOrder iterator */
  InOrderIterator createInOrderIterator();

  /* Standart ascending InOrder iterator without permission to change values */
  const InOrderIterator createInOrderIterator() const;
};

/* Constructors */
  // Constructor of zero-array
  template <class K, class V>
  Dictionary<K, V>::Dictionary():
    tree(new BalancedTree<K, V>)
  { }

  // Copy-constructor
  template <class K, class V>
  Dictionary<K, V>::Dictionary(Dictionary const & other):
    tree(new BalancedTree<K,V>(*(other.tree)))
  { }

/* Destructor */
  template <class K, class V>
  Dictionary<K, V>::~Dictionary()
  {
    delete tree;
  }

/* Getters */
  // Get size
  template <class K, class V>
  size_t Dictionary<K, V>::getCount() const 
  {
    return tree->getCount();
  }

  // Check if dictionary contains a key
  template <class K, class V>
  bool Dictionary<K, V>::containsKey(K const & key) const 
  {
    return tree->containsKey(key);
  }

  // Secure way to read value of that key (similar to const [])
  template<class K, class V> 
  const V & Dictionary<K, V>::at(const K & key) const
  {
    return tree->at(key);
  }

  // Get minimal key
  template<class K, class V> 
  K Dictionary<K, V>::getMinKey() const
  {
    return tree->getMinKey();
  }

  // Get maximal key
  template<class K, class V> 
  K Dictionary<K, V>::getMaxKey() const
  {
    return tree->getMaxKey();
  }

/* Modifying Operations */
  // Remove
  template <class K, class V>
  void Dictionary<K, V>::remove(K const & key)  
  {
    tree->remove(key);
  }
  
  // Delete all tree
  template <class K, class V>
  void Dictionary<K, V>::removeAllKeys()  
  {
    tree->removeAllKeys();
  }

  // Secure way to change value of that key
  template<class K, class V> 
  V & Dictionary<K, V>::at(const K & key)
  {
    return tree->at(key);
  }


/* Operators */
  // Dereferencing by index
  template <class K, class V>
  V & Dictionary<K, V>::operator[](K const & key)
  {
    return (*tree)[key];
  }

  // Const version of dereferencing by index
  template <class K, class V>
  V const & Dictionary<K, V>::operator[](K const & key) const
  {
    const BalancedTree<K,V>* temp = static_cast<const BalancedTree<K,V>*>(tree);
    return temp->operator[](key);
  }

  template<class K, class V> 
  Dictionary<K, V> & Dictionary<K, V>::operator=(Dictionary<K, V> const & other)
  {
    if (tree != nullptr)
      delete tree;
    if (this != &other) 
    {
      tree = new BalancedTree(*(other.tree));
    }
    return *this;
  }

/* Iterators */
  /* Standart ascending InOrder iterator */
  template <class K, class V> 
  typename Dictionary<K, V>::InOrderIterator Dictionary<K, V>::createInOrderIterator()
  {
    return typename Dictionary<K, V>::InOrderIterator::InOrderIterator(tree);
  }

  /* Standart ascending InOrder iterator without permission to change values */
  template <class K, class V> 
  const typename Dictionary<K, V>::InOrderIterator Dictionary<K, V>::createInOrderIterator() const
  {
    return typename Dictionary<K, V>::InOrderIterator::InOrderIterator(tree);
  }

/* InOrder Iterator */
  // Destructor
  template<class K, class V> 
  Dictionary<K, V>::InOrderIterator::~InOrderIterator()
  {
    delete iterator;
  }

  // Get link to current value
  template <class K, class V>  
  V& Dictionary<K, V>::InOrderIterator::value()
  {
    return iterator->value();
  }

  // Get const link to current value
  template <class K, class V>  
  const V &Dictionary<K, V>::InOrderIterator::value() const
  {
    return iterator->value();
  }

  // Get const link to current key
  template<class K, class V>  
  const K &Dictionary<K, V>::InOrderIterator::key() const
  { 
    return iterator->key();
  }

  // Check is empty
  template<class K, class V> 
  bool Dictionary<K, V>::InOrderIterator::isEmpty() const
  {
    return iterator->isEmpty();
  }

  // Check if current node is last
  template<class K, class V>  
  bool Dictionary<K, V>::InOrderIterator::hasNext() const
  {
    return iterator->hasNext();
  }

  // Go to the next key
  template<class K, class V>  
  bool Dictionary<K, V>::InOrderIterator::next() const
  {
    return iterator->next();
  }