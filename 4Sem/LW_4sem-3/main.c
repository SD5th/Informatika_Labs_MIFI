#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Source/virtual_memory.h"

#define MAX_WORKERS 50
#define WRITE_OPS 1000
#define PHYSICAL_MEMORY_SIZE 1000
#define MAX_VIRTUAL_PAGES_PER_WORKER 10000


typedef struct {
    int* expected_values;
    int* page_ids;
    char* written_flags;
    int  num_pages;
    int  capacity;
} WorkerTestMeta;

WorkerTestMeta workers[MAX_WORKERS];
int total_allocated = 0;

void fail(const char* message) {
    fprintf(stderr, "ERROR: %s\n", message);
    exit(1);
}

void alloc_page_for_worker(int worker_id, Virtual_Memory* vm) {
    if (total_allocated >= PHYSICAL_MEMORY_SIZE) return;

    int page = vm_alloc(vm, worker_id);
    if (page == -1) return;

    WorkerTestMeta* w = &workers[worker_id];

    if (w->num_pages == w->capacity) {
        w->capacity = w->capacity * 2 + 4;
        w->expected_values = realloc(w->expected_values, sizeof(int) * w->capacity);
        w->page_ids = realloc(w->page_ids, sizeof(int) * w->capacity);
        w->written_flags = realloc(w->written_flags, sizeof(char) * w->capacity);
    }

    w->expected_values[w->num_pages] = 0;
    w->page_ids[w->num_pages] = page;
    w->written_flags[w->num_pages] = 0;
    w->num_pages++;
    total_allocated++;
}

void free_random_pages(int count, Virtual_Memory* vm) {
    while (count > 0 && total_allocated > 0) {
        int worker_id = rand() % MAX_WORKERS;
        WorkerTestMeta* w = &workers[worker_id];
        if (w->num_pages == 0) continue;

        int idx = rand() % w->num_pages;
        int page = w->page_ids[idx];

        vm_free(vm, worker_id, page);
        total_allocated--;

        w->page_ids[idx] = w->page_ids[w->num_pages - 1];
        w->expected_values[idx] = w->expected_values[w->num_pages - 1];
        w->written_flags[idx] = w->written_flags[w->num_pages - 1];
        w->num_pages--;
        count--;
    }
}

void perform_writes(int count, Virtual_Memory* vm) {
    for (int i = 0; i < count; i++) {
        if (total_allocated >= PHYSICAL_MEMORY_SIZE) break;

        int worker_id = rand() % MAX_WORKERS;
        alloc_page_for_worker(worker_id, vm);

        WorkerTestMeta* w = &workers[worker_id];
        if (w->num_pages == 0) continue;

        int idx = rand() % w->num_pages;
        int page = w->page_ids[idx];
        int value = rand() % 100000;

        vm_write(vm, worker_id, page, value);
        w->expected_values[idx] = value;
        w->written_flags[idx] = 1;
    }
}

void perform_reads(Virtual_Memory* vm) {
    for (int worker_id = 0; worker_id < MAX_WORKERS; worker_id++) {
        WorkerTestMeta* w = &workers[worker_id];
        for (int i = 0; i < w->num_pages; i++) {
            int page = w->page_ids[i];

            if (w->written_flags[i]) {
                int expected = w->expected_values[i];
                int actual = vm_read(vm, worker_id, page);
                if (expected != actual) {
                    printf("[READ ] Worker %d Page %d -> %d (expected %d) [MISMATCH]\n",
                           worker_id, page, actual, expected);
                    char message[128];
                    snprintf(message, sizeof(message), 
                             "Test failed: Worker %d Page %d -> %d (expected %d)",
                             worker_id, page, actual, expected);
                    fail(message);
                }
                printf("[READ ] Worker %d Page %d -> %d (expected %d) [OK]\n",
                       worker_id, page, actual, expected);
            }
        }
    }
}

void free_all_workers() {
    for (int i = 0; i < MAX_WORKERS; i++) {
        free(workers[i].expected_values);
        free(workers[i].page_ids);
        free(workers[i].written_flags);
    }
}

void run_test(Virtual_Memory* vm) {
    perform_writes(WRITE_OPS, vm);
    perform_reads(vm);

    free_random_pages(300, vm);

    perform_writes(PHYSICAL_MEMORY_SIZE, vm);
    perform_reads(vm);

    free_all_workers();
}

int main() {
    Virtual_Memory* vm = vm_construct(PHYSICAL_MEMORY_SIZE, MAX_WORKERS, MAX_VIRTUAL_PAGES_PER_WORKER);
    srand(time(NULL));
    run_test(vm);
    vm_destruct(vm);
    return 0;
}
