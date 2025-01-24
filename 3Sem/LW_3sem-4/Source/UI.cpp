#include <QApplication>
#include <QImage>
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <thread> 
#include <chrono> 
#include <atomic>

#include <iostream>

#include "PixelMatrix.hpp"
#include "MatrixOperations.hpp"



class PixelWidget : public QWidget {
public:
  PixelWidget(QString const & imagePath, unsigned int pixelSize, QWidget* parent = nullptr)
    : QWidget(parent), pixelSize(pixelSize), counter(0) 
  {
    PixelMatrix matrix; 
    try {
      ImageIntoMatrix(matrix, imagePath);
    } catch (const std::exception &e) {
      qDebug() << e.what();
    }
    Graph<Pos, bool> globalGraph;
    MatrixIntoGraph(matrix, globalGraph);
    
    while (globalGraph.countVerticies() > 0)
    {
      DynamicArray<Pos>* letter(new DynamicArray<Pos>(globalGraph.longestPathInGraphAsArray()));
      for (size_t i = 0; i < letter->getSize(); i++)
        globalGraph.removeVertex(letter->operator[](i));
      lettersArray.append(letter);
    }
    
    setFixedSize(matrix.getWidth() * pixelSize, matrix.getHeight() * pixelSize);
    running = true;
    timerThread = std::thread(&PixelWidget::timerFunction, this);
  }

  ~PixelWidget() {
    running = false; 
    if (timerThread.joinable()) 
    {
      timerThread.join(); 
    }
  }
protected:
  void paintEvent(QPaintEvent* event) override {
    QPainter painter(this);
    unsigned int c = 0;
    for (size_t i = 0; i < lettersArray.getSize(); i++) {
      for (size_t j = 0; j < lettersArray[i]->getSize() && j < counter; j++) {
        if (c == counter)
          break;
        c++;
        Pos pos = lettersArray[i]->operator[](j);
        painter.fillRect(pos.x * pixelSize, pos.y * pixelSize, pixelSize, pixelSize, Qt::black);
      } 
    }
    counter++;
  }
    

private:
  void timerFunction() 
  {
    while (running) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      update(); 
    }
  }

  DynamicArray<DynamicArray<Pos>*> lettersArray;    
  unsigned int pixelSize;
  unsigned int counter;
  std::thread timerThread; 
  std::atomic<bool> running;
};