#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS   (3)
#define ITERATIONS ((long long)1000000000)

static long long counter = 0;

static void *
thread_fn(void *arg) {
  long long i;
  (void) arg;
  for (i = 0; i != ITERATIONS; i++)
    counter = counter + 1; // critical section
  return NULL;
}


int
main(void) {
  pthread_t threads[NTHREADS];
  int i;

  for (i = 0; i != NTHREADS; i++)
    pthread_create(&threads[i], NULL, thread_fn, NULL);
  for (i = 0; i != NTHREADS; i++)
    pthread_join(threads[i], NULL);
  
  printf("expected=%lld actual=%lld\n", NTHREADS*ITERATIONS, counter);
  printf("experienced %lld race conditions\n", NTHREADS*ITERATIONS - counter);

  return 0;
}
