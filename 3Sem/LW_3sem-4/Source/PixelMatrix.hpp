#pragma once

#include "../../LW_3sem-1/Source/DynamicArray.hpp"
#include "../../LW_3sem-1/Source/UnqPtr.hpp"

class PixelMatrix
{
public:
  PixelMatrix();

  PixelMatrix(size_t const & width, size_t const & height);

  PixelMatrix(PixelMatrix const & other, size_t const & x1, size_t const & y1, size_t const & x2, size_t const & y2);

  ~PixelMatrix();

  size_t getWidth() const;
  
  size_t getHeight() const;

  void resize(size_t const & newWidth, size_t const & newHeight);

  bool & pixel(size_t x, size_t y);
  bool const & pixel(size_t x, size_t y) const;

private:
  size_t width;
  size_t height;
  UnqPtr<DynamicArray<UnqPtr<DynamicArray<bool>>>> data;
};

PixelMatrix::PixelMatrix():
  width(0),
  height(0),
  data(UnqPtr<DynamicArray<UnqPtr<DynamicArray<bool>>>>())
{ }

PixelMatrix::PixelMatrix(size_t const & width, size_t const & height):
  width(width),
  height(height),
  data(UnqPtr<DynamicArray<UnqPtr<DynamicArray<bool>>>>(new DynamicArray<UnqPtr<DynamicArray<bool>>>(width)))
{
  for (size_t i = 0; i < width; i++)
    data->operator[](i).set(new DynamicArray<bool>(height));
}

PixelMatrix::PixelMatrix(PixelMatrix const & other, size_t const & x1, size_t const & y1, size_t const & x2, size_t const & y2):
  width(x2-x1+1),
  height(y2-y1+1),
  data(UnqPtr<DynamicArray<UnqPtr<DynamicArray<bool>>>>(new DynamicArray<UnqPtr<DynamicArray<bool>>>(width)))
{
  for (size_t i = 0; i < width; i++)
    data->operator[](i).set(new DynamicArray<bool>(height));
  for (size_t x = x1; x <= x2; x++)
    for (size_t y = y1; y <= y2; y++)
      pixel(x-x1, y-y1) = other.pixel(x, y); 
}

PixelMatrix::~PixelMatrix()
{ }

size_t PixelMatrix::getWidth() const
{
  return width;
}

size_t PixelMatrix::getHeight() const
{
  return height;
}  

void PixelMatrix::resize(const size_t &newWidth, const size_t &newHeight)
{
  if (data.get() != nullptr)
    data->resize(newWidth);
  else
    data.set(new DynamicArray<UnqPtr<DynamicArray<bool>>>(newWidth));

  for (size_t i = 0; i < newWidth; i++)
  {
    if (data->operator[](i).get() != nullptr)
      data->operator[](i)->resize(newHeight);
    else
      data->operator[](i).set(new DynamicArray<bool>(newHeight));
  }
  width = newWidth;
  height = newHeight;
}

bool & PixelMatrix::pixel(size_t x, size_t y)
{
  return data->operator[](x)->operator[](y);
}

bool const & PixelMatrix::pixel(size_t x, size_t y) const
{
  return data->operator[](x)->operator[](y);
}