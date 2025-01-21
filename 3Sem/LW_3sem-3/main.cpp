#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
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

void createEqualDistribution(Dictionary<Interval<unsigned int>, unsigned int> & distribution, DynamicArray<Worker> const & workers, unsigned int numOfColumns)
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

void createUnEqualDistribution(Dictionary<Interval<unsigned int>, unsigned int> & distribution, DynamicArray<Worker> const & workers, DynamicArray<unsigned int> const & partitions)
{
  distribution.removeAllKeys();
  Dictionary<unsigned int, bool> allValues;
  for (size_t index = 0; index < workers.getSize(); index++)
    allValues[workers[index].age] = true;
  unsigned int minVal = allValues.getMinKey();
  unsigned int maxVal = allValues.getMaxKey();
  distribution[Interval<unsigned int>(minVal, partitions[0])] = 0;
  size_t i = 0;
  for (; i < partitions.getSize() - 1; i++)
    distribution[Interval<unsigned int>(partitions[i]+1, partitions[i+1])] = 0;
  distribution[Interval<unsigned int>(partitions[i]+1, maxVal)] = 0;
  
  Dictionary<Interval<unsigned int>, unsigned int>::InOrderIterator it = distribution.createInOrderIterator();
  do {
    for (size_t index = 0; index < workers.getSize(); index++)
      if (it.key().contains(workers[index].age))
        it.value()++;
  } while (it.next());
}

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
          
          QString valueLabel = QString::number(columns[i].value);
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

class MainWindow : public QWidget {
public:
    MainWindow(DynamicArray<Worker> const & workers, QWidget *parent = nullptr) : workers(workers), QWidget(parent) {
        unsigned int minValue = 100; 
        unsigned int maxValue = 0;
        for (size_t i = 0; i < workers.getSize(); i++)
        {
          if (workers[i].age > maxValue)
            maxValue = workers[i].age;
          if (workers[i].age < minValue)
            minValue = workers[i].age;
          
        }
        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *infoLabel = new QLabel(QString("Range of values: %1-%2\nInput partition points separated by space.\nOr input amount of divisions with one number.").arg(minValue).arg(maxValue), this);
        layout->addWidget(infoLabel);
        inputField = new QLineEdit(this);
        inputField->setPlaceholderText(QString("Input parameters"));
        layout->addWidget(inputField);

        QPushButton *submitButton = new QPushButton("Build", this);
        layout->addWidget(submitButton);

        connect(submitButton, &QPushButton::clicked, this, &MainWindow::onSubmit);

        setLayout(layout);
    }

private slots:
    void onSubmit() {
        QString inputText = inputField->text();
        QStringList stringList = inputText.split(" ", QString::SkipEmptyParts);

        // Преобразование строк в числа

        Dictionary<Interval<unsigned int>, unsigned int> distribution;

        if (stringList.size() == 1)
          createEqualDistribution(distribution, workers, stringList[0].toUInt());
        else
        {
          DynamicArray<unsigned int> partitions;
          for (const QString &str : stringList) {
            bool ok;
            unsigned int number = str.toUInt(&ok);
            if (ok) {
              partitions.append(number);
            }
          }
          createUnEqualDistribution(distribution, workers, partitions);
        }

        // Создание и отображение гистограммы
        HistogramWidget *histogram = new HistogramWidget(distribution);
        histogram->setWindowTitle("Histogram");
        histogram->resize(800, 600);
        histogram->show();
    }
private:
    QLineEdit *inputField;
    DynamicArray<Worker> const & workers;
};


int main(int argc, char *argv[]) {
  DynamicArray<Worker> workers;
  readWorkersFromFile(workers, "/home/whistling_daddy47/MyFolder/shkool_Labs/3Sem/LW_3sem-3/Data/Data.txt");
  
  QApplication a(argc, argv);

  MainWindow w(workers);
  w.resize(400, 200);
  w.setWindowTitle("Input parameters");
  w.show();

  return a.exec();
}
/*
*/