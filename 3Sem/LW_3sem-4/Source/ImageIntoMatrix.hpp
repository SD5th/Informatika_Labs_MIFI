#include "PixelMatrix.hpp"
#include <QApplication>
#include <QImage>
#include <QColor>

void ImageIntoMatrix(PixelMatrix & matrix, QString const & imagePath)
{
  QImage image(imagePath);
  if (image.isNull()) {
    throw std::runtime_error("Не удалось загрузить изображение");
  }
  size_t width = image.width();
  size_t height = image.height();
  matrix.resize(width, height);

  for (size_t x = 0; x < width; x++)
  {
    for (size_t y = 0; y < height; y++)
    {
      QColor color(image.pixel(x, y));
      matrix.pixel(x, y) = ((color.red() + color.green() + color.blue()) / 3 < 128);
    }
  }
}