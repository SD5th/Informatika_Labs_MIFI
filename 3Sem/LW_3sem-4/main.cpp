#include <QApplication>
#include <QImage>
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <vector>

#include "Source/PixelMatrix.hpp"
#include "Source/MatrixOperations.hpp"

/*
  int windowWidth = this->width();
  int windowHeight = this->height();
*/

class PixelWidget : public QWidget {
public:
    PixelWidget(PixelMatrix const & pixelMatrix, int pixelSize, QWidget* parent = nullptr)
        : QWidget(parent), matrix(pixelMatrix), pixelSize(pixelSize) {
        setFixedSize(matrix.getWidth() * pixelSize, matrix.getHeight() * pixelSize);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        for (size_t x = 0; x < matrix.getWidth(); x++) {
          for (size_t y = 0; y < matrix.getHeight(); y++) {
                if (matrix.pixel(x, y)) {
                    painter.fillRect(x * pixelSize, y * pixelSize, pixelSize, pixelSize, Qt::black);
                } else {
                    painter.fillRect(x * pixelSize, y * pixelSize, pixelSize, pixelSize, Qt::white);
                }
            }
        }
    }

private:
    PixelMatrix const & matrix;
    unsigned int pixelSize;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PixelMatrix matrix; 
    try {
      ImageIntoMatrix(matrix, "/home/whistling_daddy47/MyFolder/shkool_Labs/3Sem/LW_3sem-4/images/textKaifa.png");
    } catch (const std::exception &e) {
      qDebug() << e.what();
    }
    Graph<Pos, bool> globalGraph;
    MatrixIntoGraph(matrix, globalGraph);
    DynamicArray<Graph<Pos, bool>> allSubgraphs(globalGraph.splitIntoIndependentSubgraphs());
    unsigned int pixelSize = 1;
    PixelWidget widget(matrix, pixelSize);
    widget.setWindowTitle("Pixel Matrix");
    widget.show();

    return app.exec();
    }