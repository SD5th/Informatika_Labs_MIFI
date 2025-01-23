#include "Source/UI.cpp"

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


//main - пустой, вынести все отсюда