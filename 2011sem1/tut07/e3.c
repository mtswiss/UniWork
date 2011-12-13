#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct job {
  char name[21];         // job name
  struct job *next;      // next job
  void (*f)(void);       // fn pointer
  pthread_mutex_t *lock; // lock
};

struct job *list = NULL;

void *
thread_function(void *arg)
{
  char *name = (char *)arg;

  struct job *p;
  for (p = list; p != NULL; p=p->next) {
    if (!strcmp(p->name, name)) {
      pthread_mutex_lock(p->lock);
      (p->f)();
      pthread_mutex_unlock(p->lock);
    }
  }
}

void
add_job(char *name, void (*f)())
{
  struct job *p = (struct job *)malloc(sizeof(struct job));

  if (strlen(name) > 20) {
    fprintf(stderr, "name too long!\n");
    exit(1);
  }
  strcpy(p->name, name);

  p->next = list;
  list = p;

  p->f = f;

  p->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(p->lock, NULL); 
}

