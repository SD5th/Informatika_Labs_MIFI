#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>

#include <iostream>

#include "Worker.hpp"
#include "Histogram.hpp"

struct Parameter
{
  enum ParameterType
  {
    age,
    experience,
    salary
  };
  
  ParameterType type;
  Parameter():
    type(age)
  { }

  QString asQString()
  {
    if (type == age)
      return QString("Age");
    if (type == experience)
      return QString("Experience");
    if (type == salary)
      return QString("Salary");
    return QString("?");
  }
};

class MainWindow : public QWidget {
public:
  MainWindow(DynamicArray<Worker> const & workers, QWidget *parent = nullptr);

  void SetType(Parameter::ParameterType const & newType);

private slots:
  void openSelectionWindow();

  void buildHistogram();

private:
  void initializeUI();
  
  void PrepareWorkers();
  
  Interval CountMinMax();
  
  DynamicArray<Worker> const & workers;
  Parameter selectedParameter;
  QLineEdit* inputField;
  DynamicArray<unsigned int> preparedWorkers;
};

class SelectionWindow : public QWidget {
public:
  SelectionWindow(MainWindow* mainWindow, QWidget *parent = nullptr);
private:
  void onAgeButtonClicked();

  void onExperienceButtonClicked();

  void onSalaryButtonClicked();

  MainWindow* mainWindow;
};

class HistogramWidget : public QWidget {
public:
  HistogramWidget(Histogram const & histogram, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    struct Column
    {
      Column();

      Column(Interval const & interval, unsigned int const & height);

      Column& operator=(const Column& other);

      unsigned int width();

      Interval interval;
      unsigned int height;
    };

    void turnHistogramIntoColumns(Histogram const & histogram);

    unsigned int globalWidth;
    unsigned int maxHeight;
    DynamicArray<Column> columns;
};


HistogramWidget::HistogramWidget(Histogram const & histogram, QWidget* parent)
  : QWidget(parent), globalWidth(0), maxHeight(0)
{
  Histogram::InOrderIterator it = histogram.createInOrderIterator();
  maxHeight = 0;
  globalWidth = 0;
  do {
    columns.append(Column(it.interval(), it.amount()));
    globalWidth += (it.interval().rBorder - it.interval().lBorder + 1);
    if (maxHeight < it.amount())
      maxHeight = it.amount(); 
  } while (it.next());
}

void HistogramWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  int windowWidth = this->width();
  int windowHeight = this->height();

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::black);
  painter.setBrush(QBrush(Qt::blue));

  unsigned int xshift = 0;
  for (size_t i = 0; i < columns.getSize(); i++){
    int columnHeight = (double)windowHeight * ((double)columns[i].height / (double)maxHeight);
    int columnWidth = (double)windowWidth * ((double)columns[i].width() / (double)globalWidth);
    
    painter.drawRect(xshift, 0.92 * (windowHeight - columnHeight), columnWidth - 1, 0.92 * columnHeight);
    
    QString valueLabel = QString::number(columns[i].height);
    painter.drawText(xshift + (columnWidth - 1) / 2, windowHeight*0.96, valueLabel); 
    
    QString intervalLabel = QString("%1-%2").arg(columns[i].interval.lBorder).arg(columns[i].interval.rBorder);
    painter.drawText(xshift + (columnWidth - 1) / 2, 0.99*windowHeight, intervalLabel); 
    xshift += columnWidth;
  }
}

HistogramWidget::Column::Column()
{ }

HistogramWidget::Column::Column(Interval const & interval, unsigned int const & height):
  interval(interval),
  height(height)
{ }

HistogramWidget::Column& HistogramWidget::Column::operator=(const Column& other) {
    if (this != &other) { 
      height = other.height;
      interval = other.interval;
    }
    return *this;
}

unsigned int HistogramWidget::Column::width()
{
  return (interval.rBorder - interval.lBorder + 1);
}

void HistogramWidget::turnHistogramIntoColumns(Histogram const & histogram)
{
  Histogram::InOrderIterator it = histogram.createInOrderIterator();
  do {
    columns.append(Column(it.interval(), it.amount()));
  } while (it.next());
}


MainWindow::MainWindow(DynamicArray<Worker> const & workers, QWidget *parent) : 
  QWidget(parent), workers(workers), selectedParameter(), inputField(nullptr), preparedWorkers() 
{
  initializeUI();
}

void MainWindow::SetType(Parameter::ParameterType const & newType)
{
  selectedParameter.type = newType;
  initializeUI();
}

void MainWindow::openSelectionWindow() {
  SelectionWindow* selectionWindow = new SelectionWindow(this);
  selectionWindow->setWindowTitle("Selection Window");
  selectionWindow->resize(400, 200);
  selectionWindow->show();
}

void MainWindow::buildHistogram() {
  QString inputText = inputField->text();
  QStringList stringList = inputText.split(" ", Qt::SkipEmptyParts);

  Histogram* histogram;

  if (stringList.size() == 0)
    histogram = new Histogram(preparedWorkers, 1);
  else if (stringList.size() == 1)
    histogram = new Histogram(preparedWorkers, stringList[0].toUInt());
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
    histogram = new Histogram(preparedWorkers, partitions);
  }

  HistogramWidget* histogramWidget = new HistogramWidget(*histogram);
  histogramWidget->setWindowTitle("Histogram");
  histogramWidget->resize(800, 600);
  histogramWidget->show();
}

void MainWindow::initializeUI()
{
  QLayout* oldLayout = this->layout();
  
  if (oldLayout) {
    QLayoutItem *item;
    while ((item = oldLayout->takeAt(0)) != nullptr) {
      delete item->widget();
      delete item;
    } 
    delete oldLayout; 
  }

  QVBoxLayout* layout = new QVBoxLayout(this);

  PrepareWorkers();
  QLabel *infoLabel = new QLabel(QString("Currently selected parameter: %1\nRange of values: %2-%3\nInput partition points separated by space.\nOr input amount of divisions with one number.")
  .arg(selectedParameter.asQString()).arg(CountMinMax().lBorder).arg(CountMinMax().rBorder), this);
  layout->addWidget(infoLabel);
  
  inputField = new QLineEdit(this);
  inputField->setPlaceholderText(QString("Input partition settings"));
  layout->addWidget(inputField);

  QPushButton* buildButton = new QPushButton("Build Histogram", this);
  layout->addWidget(buildButton);
  connect(buildButton, &QPushButton::clicked, this, &MainWindow::buildHistogram);

  QPushButton *selectButton = new QPushButton("Change Parameter", this);
  layout->addWidget(selectButton);
  connect(selectButton, &QPushButton::clicked, this, &MainWindow::openSelectionWindow);

  setLayout(layout);
}

void MainWindow::PrepareWorkers()
{
  preparedWorkers.resize(0);
  if (selectedParameter.type == Parameter::age)
  {
    for (size_t i = 0; i < workers.getSize(); i++)
      preparedWorkers.append(workers[i].age);
  }
  else if (selectedParameter.type == Parameter::experience)
  {
    for (size_t i = 0; i < workers.getSize(); i++)
      preparedWorkers.append(workers[i].experience);
  }
  else
  {
    for (size_t i = 0; i < workers.getSize(); i++)
      preparedWorkers.append(workers[i].salary);
  }
}
  
Interval MainWindow::CountMinMax()
{
  unsigned int min = -1;
  unsigned int max = 0;
  for (size_t i = 0; i < preparedWorkers.getSize(); i++)
  {
    if (preparedWorkers[i] > max)
      max = preparedWorkers[i];
    if (preparedWorkers[i] < min)
      min = preparedWorkers[i];
  }
  return Interval(min, max);
}


SelectionWindow::SelectionWindow(MainWindow *mainWindow, QWidget* parent): 
  mainWindow(mainWindow), QWidget(parent) 
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  QPushButton *ageButton = new QPushButton("Age", this);
  QPushButton *experienceButton = new QPushButton("Experience", this);
  QPushButton *salaryButton = new QPushButton("Salary", this);
  QLabel *infoLabel = new QLabel(QString("Choose parameter for creating histogram."));

  layout->addWidget(infoLabel);
  layout->addWidget(ageButton);
  layout->addWidget(experienceButton);
  layout->addWidget(salaryButton);

  connect(ageButton, &QPushButton::clicked, this, &SelectionWindow::onAgeButtonClicked);
  connect(experienceButton, &QPushButton::clicked, this, &SelectionWindow::onExperienceButtonClicked);
  connect(salaryButton, &QPushButton::clicked, this, &SelectionWindow::onSalaryButtonClicked);

  setLayout(layout);
  setWindowTitle("Select Parameter");
}

void SelectionWindow::onAgeButtonClicked() {
  mainWindow->SetType(Parameter::age);
  this->close();
}

void SelectionWindow::onExperienceButtonClicked() {
  mainWindow->SetType(Parameter::experience);
  this->close();
}

void SelectionWindow::onSalaryButtonClicked() {
  mainWindow->SetType(Parameter::salary);
  this->close();
}