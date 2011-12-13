#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 4
#define MAX_ITER 5000000
pthread_t thr[MAX];
sem_t s;

long counter = 0;

void * tfunc(void *arg) {
  int i;
  for (i = 0; i < MAX_ITER; i++) {
    sem_wait(&s);
    counter++;
    sem_post(&s);
  }
}

int main() {
  int i;
  sem_init(&s, 0, 1);

  for (i = 0; i < MAX; i++)
    pthread_create(&thr[i], NULL, tfunc, NULL);

  for (i = 0; i < MAX; i++)
    pthread_join(thr[i], NULL);

  printf("counter = %ld\n", counter);
  return 0;
}
