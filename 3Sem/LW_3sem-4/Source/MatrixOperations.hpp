#include <QApplication>
#include <QImage>
#include <QColor>

#include "../../LW_3sem-3/Source/Dictionary.hpp"
#include "PixelMatrix.hpp"
#include "Graph.hpp"

void ImageIntoMatrix(PixelMatrix & matrix, QString const & imagePath)
{
  QImage image(imagePath);
  if (image.isNull()) {
    throw std::runtime_error("error with image");
  }
  size_t const width = image.width();
  size_t const height = image.height();
  matrix.resize(width, height);

  double borderColor = 128;
  
  /*
  for (size_t x = 0; x < width; x++)
    for (size_t y = 0; y < height; y++)
    {
      QColor const & color(image.pixel(x, y));
      borderColor += (color.red() + color.green() + color.blue()) / 3;
    }
  borderColor /= width * height;
  */
  
  for (size_t x = 0; x < width; x++)
  {
    for (size_t y = 0; y < height; y++)
    {
      QColor color(image.pixel(x, y));
      matrix.pixel(x, y) = ((color.red() + color.green() + color.blue()) / 3 < borderColor);
    }
  }
}

void MatrixIntoGraph(PixelMatrix const & matrix, Graph<Pos, bool> & graph)
{
  for (size_t x = 0; x < matrix.getWidth(); x++)
    for (size_t y = 0; y < matrix.getHeight(); y++)
      if (matrix.pixel(x, y))
        graph.addVertex(Pos(x, y));
    
  for (size_t x = 1; x < matrix.getWidth() - 1; x++)
    for (size_t y = 1; y < matrix.getHeight() - 1; y++)
    {
      if (!matrix.pixel(x, y))
        continue;
      Pos curr(x,y);
      if (matrix.pixel(x-1, y-1))
        graph.addEdge(curr, Pos(x-1, y-1), true);
      if (matrix.pixel(x-1, y))
        graph.addEdge(curr, Pos(x-1, y), true);
      if (matrix.pixel(x-1, y+1))
        graph.addEdge(curr, Pos(x-1, y+1), true);
      
      if (matrix.pixel(x, y-1))
        graph.addEdge(curr, Pos(x, y-1), true);
      if (matrix.pixel(x, y+1))
        graph.addEdge(curr, Pos(x, y+1), true);
      
      if (matrix.pixel(x+1, y-1))
        graph.addEdge(curr, Pos(x+1, y-1), true);
      if (matrix.pixel(x+1, y))
        graph.addEdge(curr, Pos(x+1, y), true);
      if (matrix.pixel(x+1, y+1))
        graph.addEdge(curr, Pos(x+1, y+1), true);
    }
}
