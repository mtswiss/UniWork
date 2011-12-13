#include <pthread.h>
#include <stdio.h>

#define NUM 100
pthread_t my_threads[NUM];

struct my_arg {
  int a, b, result;
};

struct my_arg my_args[NUM];

void* foo(void* arg) {
  struct my_arg *ptr = (struct my_arg*)arg;
  ptr->result = ptr->a + ptr->b;
  return NULL;
}

int main(void) {

  int i;

  for (i = 0; i < NUM; ++i) {
    my_args[i].a = i;
    my_args[i].b = 2 * i;
    pthread_create(&my_threads[i], NULL, foo,
                   &my_args[i]);
  }

  for (i = 0; i < NUM; ++i) {
    pthread_join(my_threads[i], NULL);
  }

  for (i = 0; i < NUM; ++i) {
    printf("%i\n", my_args[i].result);
  }

  return 0;
}
