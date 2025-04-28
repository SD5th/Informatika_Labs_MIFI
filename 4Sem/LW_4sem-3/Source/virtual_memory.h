#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct 
{
  int*   physical_memory;
  bool*  physical_memory_isfree;
  size_t physical_memory_size;

  int**  virtual_pages;
  bool** virtual_pages_isused;
  size_t max_workers;
  size_t max_virtual_pages_per_worker;

} Virtual_Memory;

Virtual_Memory* vm_construct(size_t physical_memory_size, size_t max_workers, size_t max_virtual_pages_per_worker);

int vm_alloc(Virtual_Memory* vm, size_t worker_id);                 // Выделить виртуальную страницу, вернуть её номер или -1
void vm_free(Virtual_Memory* vm, size_t worker_id, size_t page);     // Освободить ранее выделенную виртуальную страницу

void vm_write(Virtual_Memory* vm, size_t worker_id, size_t page, int value);  // Записать значение в виртуальную страницу
int vm_read(Virtual_Memory* vm, size_t worker_id, size_t page);               // Прочитать значение из виртуальной страницы

void vm_destruct(Virtual_Memory* vm);

Virtual_Memory* vm_construct(size_t physical_memory_size, size_t max_workers, size_t max_virtual_pages_per_worker) {
  if (physical_memory_size == 0 || max_workers == 0 || max_virtual_pages_per_worker == 0) {
    return NULL;
  }  
  Virtual_Memory* vm = malloc(sizeof(Virtual_Memory));
  if (vm == NULL) {
    return NULL;
  }
  
  vm->physical_memory = malloc(sizeof(int) * physical_memory_size);
  if (vm->physical_memory == NULL) {
    free(vm);
    return NULL;
  }
  
  vm->physical_memory_isfree = malloc(sizeof(bool) * physical_memory_size);
  if (vm->physical_memory_isfree == NULL) {
    free(vm->physical_memory);
    free(vm);
    return NULL;
  }

  vm->virtual_pages = malloc(sizeof(int*) * max_workers);
  if (vm->virtual_pages == NULL) {
    free(vm->physical_memory_isfree);
    free(vm->physical_memory);
    free(vm);
    return NULL;
  }
  
  vm->virtual_pages_isused = malloc(sizeof(bool*) * max_workers);
  if (vm->virtual_pages_isused == NULL) {
    free(vm->virtual_pages);
    free(vm->physical_memory_isfree);
    free(vm->physical_memory);
    free(vm);
    return NULL;
  }
  
  
  for (size_t i = 0; i < max_workers; i++) {
    vm->virtual_pages[i] = malloc(sizeof(int) * max_virtual_pages_per_worker);  
    if (vm->virtual_pages[i] == NULL) {
      for (size_t j = 0; j < i; j++) {
        free(vm->virtual_pages[j]);
      }
      for (size_t j = 0; j < i; j++) {
        free(vm->virtual_pages_isused[j]);
      }
      free(vm->virtual_pages_isused);
      free(vm->virtual_pages);
      free(vm->physical_memory_isfree);
      free(vm->physical_memory);
      free(vm);
      return NULL;    
    }

    vm->virtual_pages_isused[i] = malloc(sizeof(bool) * max_virtual_pages_per_worker);  
    if (vm->virtual_pages_isused[i] == NULL) {
      for (size_t j = 0; j <= i; j++) {
        free(vm->virtual_pages_isused[j]);
      }
      free(vm->virtual_pages_isused);
      for (size_t j = 0; j < i; j++) {
        free(vm->virtual_pages[j]);
      }
      free(vm->virtual_pages);
      free(vm->physical_memory_isfree);
      free(vm->physical_memory);
      free(vm);
      return NULL;
    }
  }
  
  for (size_t i = 0; i < physical_memory_size; i++) {
    vm->physical_memory_isfree[i] = true;    
  }

  for (size_t i = 0; i < max_workers; i++) {
    for (size_t j = 0; j < max_virtual_pages_per_worker; j++) {  
      vm->virtual_pages_isused[i][j] = false;
    }
  }
  
  vm->physical_memory_size = physical_memory_size;
  vm->max_workers = max_workers;
  vm->max_virtual_pages_per_worker = max_virtual_pages_per_worker;
  
  return vm;
}

int vm_alloc(Virtual_Memory* vm, size_t worker_id) {
  if (vm == NULL || worker_id >= vm->max_workers) { 
    return -1; 
  } 

  int virtual_page = -1; 
  for (int i = 0; i < vm->max_virtual_pages_per_worker; i++) { 
    if (!vm->virtual_pages_isused[worker_id][i]) { 
      virtual_page = i; 
      break; 
    } 
  } 

  if (virtual_page == -1) { 
    return -1;    
  } 

  int physical_page = -1; 
  for (int i = 0; i < vm->physical_memory_size; i++) { 
    if (vm->physical_memory_isfree[i]) { 
      physical_page = i; 
      break; 
    } 
  } 

  if (physical_page == -1) { 
    return -1;    
  } 

  vm->virtual_pages[worker_id][virtual_page] = physical_page; 
  vm->virtual_pages_isused[worker_id][virtual_page] = true; 
  vm->physical_memory_isfree[physical_page] = false; 

  return virtual_page; 
}

void vm_free(Virtual_Memory* vm, size_t worker_id, size_t page) {
  if (vm == NULL || worker_id >= vm->max_workers || page >= vm->max_virtual_pages_per_worker) { 
    return; 
  } 
  if (vm->virtual_pages_isused[worker_id][page]) { 
    vm->physical_memory_isfree[vm->virtual_pages[worker_id][page]] = true; 
    vm->virtual_pages_isused[worker_id][page] = false; 
  }  
}

void vm_write(Virtual_Memory* vm, size_t worker_id, size_t page, int value) {
  if (vm == NULL || worker_id >= vm->max_workers || page >= vm->max_virtual_pages_per_worker) { 
    return; 
  } 
  if (vm->virtual_pages_isused[worker_id][page]) { 
    vm->physical_memory[vm->virtual_pages[worker_id][page]] = value; 
  } 
}

int vm_read(Virtual_Memory* vm, size_t worker_id, size_t page) {
  if (vm == NULL || worker_id >= vm->max_workers || page >= vm->max_virtual_pages_per_worker) { 
    return -1; 
  } 
  if (vm->virtual_pages_isused[worker_id][page]) { 
    return vm->physical_memory[vm->virtual_pages[worker_id][page]]; 
  }
  return -1;
}

void vm_destruct(Virtual_Memory* vm) {
  if (vm == NULL)
    return;
  for (size_t i = 0; i < vm->max_workers; i++) {
    free(vm->virtual_pages_isused[i]);
    free(vm->virtual_pages[i]);
  }
  free(vm->virtual_pages_isused);
  free(vm->virtual_pages);
  free(vm->physical_memory_isfree);
  free(vm->physical_memory);
  free(vm);
}


#endif