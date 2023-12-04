#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

void* child_thread_function(void* thread_id) {
    int id = *((int*)thread_id);
    printf("Child thread %d started.\n", id);
    printf("Child thread %d finished.\n", id);
    pthread_exit(thread_id);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, child_thread_function, (void*)&thread_ids[i]);
        if (result) {
            fprintf(stderr, "Error creating thread %d: %d\n", i, result);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        void* status;
        int result = pthread_join(threads[i], &status);
        if (result) {
            fprintf(stderr, "Error joining thread %d: %d\n", i, result);
            return 1;
        }
        printf("Child thread %lu joined and finished.\n", (unsigned long)threads[i]);
    }

    printf("Parent thread finished.\n");

    return 0;
}

