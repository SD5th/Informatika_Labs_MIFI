#include "Source/UI.cpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  unsigned int pixelSize = 10;
  PixelWidget widget("/home/whistling_daddy47/MyFolder/shkool_Labs/3Sem/LW_3sem-4/images/text2.png", pixelSize);
  
  widget.setWindowTitle("Pixels");
  widget.show();
  return app.exec();
}