#include "SmartPointers.h"
#include <iostream>

using namespace std;

int main() {
  UnqPtr<int> empty_object;
  UnqPtr<int> object(5);

  int sample_arr[3] {1, 2, 3};
  int* ptr = nullptr;
  UnqPtr<int> empty_arr(ptr, 5);
  UnqPtr<int> arr(sample_arr, 3);
  
  *object = 2;
  cout << arr[2];
  arr[0] = -1;

  ShrdPtr<int> empty_object2;
}