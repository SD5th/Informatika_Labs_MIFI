#include <QApplication>
#include <QWidget>
#include <QPainter>

#include <iostream>

#include "Source/Worker.hpp"
#include "Source/Dictionary.hpp"

template <class T>
class Interval
{
  public:
  T lBorder;
  T rBorder;

  Interval(T const & lBorder, T const & rBorder):
    lBorder(lBorder),
    rBorder(rBorder)
  { }

  Interval(Interval const & other):
    lBorder(other.lBorder),
    rBorder(other.rBorder)
  { }

  Interval()
  { }

  bool contains(T const & item) const
  {
    if (lBorder <= item && item <= rBorder)
      return true;
    return false;
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


class HistogramWidget : public QWidget {
public:
    HistogramWidget(Dictionary<Interval<unsigned int>, unsigned int> const & distribution, QWidget* parent = nullptr)
        : QWidget(parent) {
          Dictionary<Interval<unsigned int>, unsigned int>::InOrderIterator it = distribution.createInOrderIterator();
          unsigned int globalWidth = 0;
          unsigned int maxValue = 0;
          do {
            columns.append(Column(it.value(), it.key()));
            if (it.value() > maxValue)
              maxValue = it.value();
            globalWidth += it.key().rBorder - it.key().lBorder + 1; 
          } while (it.next());
          for (size_t i = 0; i < columns.getSize(); i++)
          {
            columns[i].heightMultiplyer = static_cast<double>(columns[i].value)/static_cast<double>(maxValue);
            columns[i].widthMultiplyer = static_cast<double>((columns[i].interval.rBorder-columns[i].interval.lBorder))/static_cast<double>(globalWidth);
          }
        }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        int width = this->width();
        int height = this->height();

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::black);
        painter.setBrush(QBrush(Qt::blue));

        unsigned int xshift = 0;
        for (size_t i = 0; i < columns.getSize(); i++){
          int columnHeight = height * columns[i].heightMultiplyer;
          int columnWidth = width * columns[i].widthMultiplyer;
          painter.drawRect(xshift, 0.92 * (height - columnHeight), columnWidth - 1, 0.92 * columnHeight);
          
          QString valueLabel = QString::number(columns[i].value); // Преобразование числа в строку
          painter.drawText(xshift + (columnWidth - 1) / 2, height*0.96, valueLabel); 
          
          QString intervalLabel = QString("%1-%2").arg(columns[i].interval.lBorder).arg(columns[i].interval.rBorder);
          painter.drawText(xshift + (columnWidth - 1) / 2, 0.99*height, intervalLabel); 
          xshift += columnWidth;
        }
    }

private:
    struct Column
    {
      double widthMultiplyer;
      double heightMultiplyer;
      unsigned int value;
      Interval<unsigned int> interval;

      Column()
      { }

      Column(unsigned int const & value, Interval<unsigned int> const & interval):
        value(value),
        interval(interval)
      { }
    };
    DynamicArray<Column> columns;
};



void createDistribution(Dictionary<Interval<unsigned int>, unsigned int> & distribution, DynamicArray<Worker> & workers, unsigned int numOfColumns)
{
  distribution.removeAllKeys();
  Dictionary<unsigned int, bool> allValues;
  for (size_t index = 0; index < workers.getSize(); index++)
    allValues[workers[index].age] = true;
  unsigned int minVal = allValues.getMinKey();
  unsigned int maxVal = allValues.getMaxKey();
  unsigned int intervalWidth = (maxVal - minVal) / numOfColumns;
  for (unsigned int lBorder = minVal; lBorder <= maxVal; lBorder += (intervalWidth + 1))
    distribution[Interval<unsigned int>(lBorder, lBorder + intervalWidth)] = 0;
  Dictionary<Interval<unsigned int>, unsigned int>::InOrderIterator it = distribution.createInOrderIterator();
  do {
    for (size_t index = 0; index < workers.getSize(); index++)
      if (it.key().contains(workers[index].age))
        it.value()++;
  } while (it.next());
}

int main(int argc, char *argv[]) {
  DynamicArray<Worker> workers;
  readWorkersFromFile(workers, "/home/whistling_daddy47/MyFolder/shkool_Labs/3Sem/LW_3sem-3/Data/Data.txt");
  
  Dictionary<Interval<unsigned int>, unsigned int> distribution;
  createDistribution(distribution, workers, 5);

  QApplication app(argc, argv);
  HistogramWidget widget(distribution);
  widget.resize(800, 600);
  widget.setWindowTitle("Histogram");
  widget.show();
  return app.exec();
}
/*
*/