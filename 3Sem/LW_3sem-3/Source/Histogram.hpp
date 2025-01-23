#pragma once

#include <stdexcept>
#include "Dictionary.hpp"
#include "../../LW_3sem-1/Source/DynamicArray.hpp"


struct Interval
{
  public:
  unsigned int lBorder;
  unsigned int rBorder;

  Interval()
  { }
  
  Interval(unsigned int const & lBorder, unsigned int const & rBorder):
    lBorder(lBorder),
    rBorder(rBorder)
  { }

  Interval(Interval const & other):
    lBorder(other.lBorder),
    rBorder(other.rBorder)
  { }

  Interval(Interval && other):
    lBorder(other.lBorder),
    rBorder(other.rBorder)
  { 
    other.lBorder = 0;
    other.rBorder = 0;
  }


  bool contains(unsigned int const & item) const
  {
    if (lBorder <= item && item <= rBorder)
      return true;
    return false;
  }

  Interval & operator=(Interval const& other) {
    if (this != &other) { 
        lBorder = other.lBorder;
        rBorder = other.rBorder;
    }
    return *this;
  }

  bool operator<(Interval const & other) const 
  {
    return lBorder < other.lBorder;
  }
  bool operator<=(Interval const & other) const
  {
    return lBorder <= other.lBorder;
  }
  bool operator==(Interval const & other) const
  {
    return lBorder == other.lBorder;
  }
  bool operator>=(Interval const & other) const
  {
    return lBorder >= other.lBorder;
  }
  bool operator>(Interval const & other) const
  {
    return lBorder > other.lBorder;
  }
};

class Histogram
{
private:
  Dictionary<Interval, unsigned int>* dict; 

public:
  class InOrderIterator
  {
    friend class Histogram;
  private:
    class Dictionary<Interval,unsigned int>::InOrderIterator* iterator;

    InOrderIterator(Dictionary<Interval,unsigned int>* dict):
      iterator(new typename Dictionary<Interval,unsigned int>::InOrderIterator(dict->createInOrderIterator()))
    { }

  public:
    // Destructor
    ~InOrderIterator();

    // Get const link to current amount
    unsigned int const & amount() const;

    // Get const link to current interval
    Interval const & interval() const;

    // Check if current node is last
    bool hasNext() const;

    // Go to the next key
    bool next() const;   
  };

/* Constructors */
  // Constructor of equally splitted histogram
  Histogram(DynamicArray<unsigned int> const & data, unsigned int numOfIntervals);

  // Constructor of unequally splitted histogram
  Histogram(DynamicArray<unsigned int> const & data, DynamicArray<unsigned int> const & partitions);

/* Destructor */
  ~Histogram();

/* Getters */
  // Get number of interval
  size_t getCount() const;

/* Iterators */
  /* Standart ascending InOrder iterator without permission to change values */
  const InOrderIterator createInOrderIterator() const;
};

/* Constructors */
  Histogram::Histogram(DynamicArray<unsigned int> const & data, unsigned int numOfIntervals):
    dict(new Dictionary<Interval, unsigned int>)
  {
    if (data.getSize() == 0)
      return;
    unsigned int minData = data[0];
    unsigned int maxData = data[0];
    for (size_t i = 1; i < data.getSize(); i++)
    {
      if (data[i] < minData)
        minData = data[i];
      if (data[i] > maxData)
        maxData = data[i];
    }
    unsigned int intervalWidth = (maxData - minData) / numOfIntervals;
    for (unsigned int lBorder = minData; lBorder <= maxData; lBorder += (intervalWidth + 1))
      (*dict)[Interval(lBorder, lBorder + intervalWidth)] = 0;
    Dictionary<Interval, unsigned int>::InOrderIterator it = dict->createInOrderIterator();
    do {
      for (size_t index = 0; index < data.getSize(); index++)
        if (it.key().contains(data[index]))
          it.value()++;
    } while (it.next());
  }

  Histogram::Histogram(DynamicArray<unsigned int> const & data, DynamicArray<unsigned int> const & partitions):
    dict(new Dictionary<Interval, unsigned int>)
  {
    if (data.getSize() == 0)
      return;
    
    unsigned int minVal = -1;
    unsigned int maxVal = 0;
    for (size_t i = 0; i < data.getSize(); i++)
    {
      if (data[i] > maxVal)
        maxVal = data[i];
      if (data[i] < minVal)
        minVal = data[i];
    }
    (*dict)[Interval(minVal, partitions[0])] = 0;

    size_t i = 0;
    for (; i < partitions.getSize() - 1; i++)
      (*dict)[Interval(partitions[i]+1, partitions[i+1])] = 0;
    
    (*dict)[Interval(partitions[i]+1, maxVal)] = 0;
    
    Dictionary<Interval, unsigned int>::InOrderIterator it = (*dict).createInOrderIterator();
    do {
      for (size_t i = 0; i < data.getSize(); i++)
        if (it.key().contains(data[i]))
          it.value()++;
    } while (it.next());
  }

/* Destructor */
  Histogram::~Histogram()
  {
    delete dict;
  }

/* Getters */
  // Get size
  size_t Histogram::getCount() const 
  {
    return dict->getCount();
  }

/* Iterators */
  /* Standart ascending InOrder iterator without permission to change values */
  const typename Histogram::InOrderIterator Histogram::createInOrderIterator() const
  {
    return typename Histogram::InOrderIterator::InOrderIterator(dict);
  }

/* InOrder Iterator */
  // Destructor
  Histogram::InOrderIterator::~InOrderIterator()
  {
    delete iterator;
  }

  // Get const link to current amount
  const unsigned int & Histogram::InOrderIterator::amount() const
  {
    return iterator->value();
  }

  // Get const link to current interval
  const Interval & Histogram::InOrderIterator::interval() const
  { 
    return iterator->key();
  }

  // Check if current interval is last
  bool Histogram::InOrderIterator::hasNext() const
  {
    return iterator->hasNext();
  }

  // Go to the next interval
  bool Histogram::InOrderIterator::next() const
  {
    return iterator->next();
  }