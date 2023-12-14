#include <pthread.h>
#include <stdio.h>

pthread_cond_t cv;
pthread_mutex_t mutex;
int length;
int queue[200];

void * consumer( void* param)
{
  for( int i=0; i<200; i++ )
  {
    pthread_mutex_lock(&mutex);
    while (length==0)
    {
      pthread_cond_wait(&cv,&mutex);
    }
    int item = queue[ --length ];
    pthread_mutex_unlock(&mutex);   
    printf( "Received %i\n", item );
  }  
}
void * producer( void* param)
{
  for (int i=0; i<200; i++)
  {
    pthread_mutex_lock( &mutex );
    queue[length++]=i;
    pthread_cond_signal( &cv );
    pthread_mutex_unlock( &mutex );
  }
}

void main()
{
 pthread_t threads[2];
 pthread_cond_init( &cv, 0 );
 pthread_mutex_init( &mutex, 0 );
 length = 0;
 pthread_create( &threads[0], 0, producer, 0 );
 pthread_create( &threads[1], 0, consumer, 0 );
 pthread_join( threads[1], 0 );
 pthread_join( threads[0], 0 );
 pthread_mutex_destroy( &mutex );
 pthread_cond_destroy( &cv );
}


