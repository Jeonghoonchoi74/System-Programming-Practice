#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t semaphore;

void *func1(void *param)
{
    sem_wait(&semaphore); // 세마포어 대기
    printf("Thread 1\n");
    sem_post(&semaphore); // 세마포어 신호
    pthread_exit(NULL);
}

void *func2(void *param)
{
    sem_wait(&semaphore); // 세마포어 대기
    printf("Thread 2\n");
    sem_post(&semaphore); // 세마포어 신호
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[2];
    
    // 세마포어 초기화, 초기값은 1
    sem_init(&semaphore, 0, 1);

    pthread_create(&threads[0], NULL, func1, NULL);
    pthread_create(&threads[1], NULL, func2, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    sem_destroy(&semaphore); // 세마포어 제거

    return 0;
}



