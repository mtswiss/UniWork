#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 5

pthread_t threads[MAX];
pthread_mutex_t m[MAX];

void *
tfunc(void *arg)
{
  long i = (long)arg;
  for (;;) {
    pthread_mutex_lock(&m[i]);
    pthread_mutex_lock(&m[(i+1) % MAX]);
    printf("Philosopher %ld is eating...\n", i);
    pthread_mutex_unlock(&m[i]);
    pthread_mutex_unlock(&m[(i+1) % MAX]);
  }
}

int
main(void)
{
  pthread_t thread[MAX];
  int i;

  for (i = 0; i != MAX; i++)
    pthread_create(&thread[i], NULL, tfunc, (void *)i);

  for (i = 0; i != MAX; i++)
    pthread_join(thread[i], NULL);

  return 0;
}
