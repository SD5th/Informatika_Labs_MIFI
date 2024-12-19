#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "Source/Person.hpp"
#include "Source/BubbleSorter.hpp"
#include "Source/QuickSorter.hpp"
#include "Source/SelectionSorter.hpp"
#include "Source/ShellSorter.hpp"

#include "../../../SimpleConsoleUI/SimpleConsoleUI.h"

using namespace std;

Shell* Head; 
Shell* CreateFile;
Shell* SelectFiles;
Shell* UnSelectFiles;
Shell* SelectSorters;
Shell* UnSelectSorters;
Shell* StartSorting;
Shell* Exit;

void Head_Function()
{
  cout << "Hello! This is User Interface for LW3-3\n";
  Head->Set_Function(nullptr);
}

void CreateFile_Function()
{
  std::string input;
  cout << "Input size of array to generate: ";
  getline(cin, input);
  size_t size;
  try {
    size = std::stoul(input);
  } catch (const std::invalid_argument& e) {
    std::cout << "Error: not a number!" << std::endl;
    return;
  } catch (const std::out_of_range& e) {
    std::cout << "Error: size is too long!" << std::endl;
    return;
  }
  
  cout << "Input name of new file: ";
  getline(cin, input);
  string fileName = "../Data/" + input + ".txt";
  ofstream fileTest(fileName);
  if (fileTest.is_open())
  {
    fileTest.close();
  }
  else
  {
    cout << "Failed to create file.\n";
    return;
  }
  
  ofstream file(fileName);
  DynamicArray<Person> array(size);
  fillArrayRandomly(array);
  for (size_t index = 0; index < array.getSize(); index++) {
    file << 
    array[index].gender << "\n" <<
    array[index].age << "\n" <<
    array[index].name << "\n" <<
    array[index].surname << "\n" <<
    array[index].height << "\n" <<
    array[index].isEmployed << "\n" <<
    array[index].salary << "\n" <<
    "\n";
  }
  file.close();
  cout << "Created " + input + ".txt\n";
}

DynamicArray<string> files;
void SelectFiles_Function()
{
  cout << "Currently selected files:\n";
  if (files.getSize() == 0)
    cout << "None!\n";
  else
    for (size_t i = 0; i < files.getSize(); i++)
      cout << i + 1 << ") " << files[i] << endl;
  
  std::string input;
  cout << "\nInput name of file to select: ";
  getline(cin, input);
  ifstream file("../Data/" + input);
  if (file.is_open())
  {
    file.close();
    files.append(input);
  }
  else
    cout << "This file doesn't exist.\n";
}

void UnSelectFiles_Function()
{
  cout << "Currently selected files:\n";
  if (files.getSize() == 0)
    cout << "None!\n";
  else
  {
    for (size_t i = 0; i < files.getSize(); i++)
      cout << i + 1 << ") " << files[i] << endl;
    
    std::string input;
    cout << "\nInput number of file to unselect: ";
    getline(cin, input);
    size_t number;
    try {
      number = std::stoul(input);
    } catch (const std::invalid_argument& e) {
      std::cout << "Error: not a number!" << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Error: number is too big!" << std::endl;
    }
    if (number - 1 >= files.getSize())
      cout << "File with that number doesn't exist.\n";
    else
      files.remove(number - 1);
  }
}

DynamicArray<ISorter*> sorters;
void SelectSorters_Function()
{
  cout << "Currently selected sorters:\n";
  if (sorters.getSize() == 0)
    cout << "None!\n";
  else
    for (size_t i = 0; i < sorters.getSize(); i++)
      cout << i + 1 << ") " << sorters[i]->GetType() << endl;
  
  std::string input;
  cout << "\nInput name of sorter (Shell, Selection, Quick, Bubble): ";
  getline(cin, input);
  if (input == "Shell")
    sorters.append(new ShellSorter);
  else if (input == "Selection")
    sorters.append(new SelectionSorter);
  else if (input == "Quick")
    sorters.append(new QuickSorter);
  else if (input == "Bubble")
    sorters.append(new BubbleSorter);
  else
    cout << "This sorter doesn't exist.\n";
}

void UnSelectSorters_Function()
{
  cout << "Currently selected sorters:\n";
  if (files.getSize() == 0)
    cout << "None!\n";
  else
  {
    for (size_t i = 0; i < sorters.getSize(); i++)
      cout << i + 1 << ") " << sorters[i]->GetType() << endl;
    
    std::string input;
    cout << "\nInput number of sorter to unselect: ";
    getline(cin, input);
    size_t number;
    try {
      number = std::stoul(input);
    } catch (const std::invalid_argument& e) {
      std::cout << "Error: not a number!" << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Error: number is too big!" << std::endl;
    }
    if (number - 1 >= sorters.getSize())
      cout << "Sorter with that number doesn't exist.\n";
    else
      sorters.remove(number - 1);
  }
}

void StartSorting_Function()
{
  if (files.getSize() == 0)
  {
    cout << "No selected files!\n";
    return;
  }
  if (sorters.getSize() == 0)
  {
    cout << "No selected sorters!\n";
    return;
  }
  cout << "1. Sort by Age\n"
       << "2. Test by Salary\n"
       << "3. Test by Height\n";
  std::string input;
  size_t number;
  while (true)
  {
    cout << "Input 1-3: ";
    getline(cin, input);
    try {
      number = std::stoul(input);
      if (number < 1 || 3 < number) 
        cout << "WROONG!\n";
      else
        break;
    } catch (const std::invalid_argument& e) {
      std::cout << "Error: not a number!" << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Error: number is too big!" << std::endl;
    }
  }

  bool (*compare) (Person const &, Person const &);
  if (number == 1)
    compare = compareAge; 
  else if (number == 2)
    compare = compareSalary; 
  else if (number == 3)
    compare = compareHeight; 
  
  for (size_t file_index = 0; file_index < files.getSize(); file_index++)
  {
    string fileName = files[file_index];
    cout << "Currently sorting: " << fileName << endl;
    ifstream inFile("../Data/" + fileName);
    if (!inFile) {
      std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
      return;
    }

    DynamicArray<Person> unsorted;
    while (inFile) {
      Person buffer;
      inFile >> buffer.gender;
      inFile.ignore();
      inFile >> buffer.age;
      inFile.ignore();
      inFile >> buffer.name; 
      inFile.ignore();
      inFile >> buffer.surname;
      inFile.ignore();
      inFile >> buffer.height;
      inFile.ignore();
      inFile >> buffer.isEmployed;
      inFile.ignore();
      inFile >> buffer.salary;
      inFile.ignore();
      inFile.ignore();

      if (inFile) { // Проверяем, что чтение прошло успешно
        unsorted.append(buffer);
      }
    }
    inFile.close();

    auto start = std::chrono::high_resolution_clock::now();
    DynamicArray<Person> sorted(sorters[0]->Sort(unsorted, compare));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
  
    ofstream file("../Data/sorted_" + fileName);
    for (size_t index = 0; index < sorted.getSize(); index++) {
      file << 
      sorted[index].gender << "\n" <<
      sorted[index].age << "\n" <<
      sorted[index].name << "\n" <<
      sorted[index].surname << "\n" <<
      sorted[index].height << "\n" <<
      sorted[index].isEmployed << "\n" <<
      sorted[index].salary << "\n" <<
      "\n";
    }
    file.close();
    cout << "Created sorted_" + fileName + "\n";
    cout << "Duration:\n";
    cout << sorters[0]->GetType() << ": " << duration << "\n";
    for (size_t sorter_index = 1; sorter_index < sorters.getSize(); sorter_index++)
    {
      cout << endl;
      start = std::chrono::high_resolution_clock::now();
      sorters[0]->Sort(unsorted, compare);
      end = std::chrono::high_resolution_clock::now();
      duration = end - start;
      cout << sorters[sorter_index]->GetType() << ": " << duration << "\n";
    }
  }
}

void Exit_Function()
{
  cout << "Confirm exit from the program. Type EXIT\n";
  string UserText; 
  getline(cin, UserText);
  if (UserText == "EXIT")
  {
    cout << "So sad.. Bye!\n"; 
    exit(1);
  }
  else 
    cout << "Then let's stay together!\n";
}

int main() {
  Head =            new Shell("Head Window",         Head_Function, new Connector);
  CreateFile =      new Shell("Create File", CreateFile_Function, new Connector);
  SelectFiles =     new Shell("Select Files", SelectFiles_Function, new Connector); 
  UnSelectFiles =   new Shell("UnSelect Files", UnSelectFiles_Function, new Connector);
  SelectSorters =   new Shell("Select Sorters", SelectSorters_Function, new Connector);
  UnSelectSorters = new Shell("UnSelect Sorters", UnSelectSorters_Function, new Connector);
  StartSorting =    new Shell("Start Sorting", StartSorting_Function, new Connector);
  Exit =            new Shell("Exit",                Exit_Function, new Connector);

  Head->Get_Connector()->Append_Shell(CreateFile);
  Head->Get_Connector()->Append_Shell(SelectFiles);
  Head->Get_Connector()->Append_Shell(UnSelectFiles);
  Head->Get_Connector()->Append_Shell(SelectSorters);
  Head->Get_Connector()->Append_Shell(UnSelectSorters);
  Head->Get_Connector()->Append_Shell(StartSorting);
  Head->Get_Connector()->Append_Shell(Exit);

  CreateFile->Get_Connector()->Append_Shell(Head);

  SelectFiles->Get_Connector()->Append_Shell(Head);
  SelectFiles->Get_Connector()->Append_Shell(SelectFiles);
  SelectFiles->Get_Connector()->Append_Shell(UnSelectFiles);

  UnSelectFiles->Get_Connector()->Append_Shell(Head);
  UnSelectFiles->Get_Connector()->Append_Shell(SelectFiles);
  UnSelectFiles->Get_Connector()->Append_Shell(UnSelectFiles);
  
  SelectSorters->Get_Connector()->Append_Shell(Head);
  SelectSorters->Get_Connector()->Append_Shell(SelectSorters);
  SelectSorters->Get_Connector()->Append_Shell(UnSelectSorters);

  UnSelectSorters->Get_Connector()->Append_Shell(Head);
  UnSelectSorters->Get_Connector()->Append_Shell(SelectSorters);
  UnSelectSorters->Get_Connector()->Append_Shell(UnSelectSorters);
  
  StartSorting->Get_Connector()->Append_Shell(Head);

  Exit->Get_Connector()->Append_Shell(Head);

  ActiveShell Active(Head, ActiveShell::VScode);
  Active.StartUI();
}