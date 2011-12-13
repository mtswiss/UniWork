#include "counter.h"

/* ============================================================================
 * File-global variables
 * ========================================================================== */
static int ncounters = 0;
static struct counter *counters = NULL; /* array of counters */

static int nthreads = 0; 
static int *ninstructions = NULL; /* array of  #threads per instruction */ 
static struct instruction ** instructions = NULL; /* array of array storing instructions per pthread */
int indicator = 0; 


/* ============================================================================
 * Operations
 * ========================================================================== */
static void
decrement(long long *n) {
	*n = *n-1;
}

static void
increment(long long *n) {
	*n = *n+1;
}

static void 
mult2(long long *n) {
	*n = *n*2;
}

/* ============================================================================
 * Helper functions
 * ========================================================================== */
static void free_memory(){
	free(counters);
	free(ninstructions);
	free(instructions);
}
 
 
 static void scan_instructions(int in_instructions, int thread_num){
	int scan_count;
	
	/* malloc space for instructions in thread */
	instructions[thread_num] = (struct instruction *)malloc(in_instructions * sizeof(instructions[in_instructions][thread_num]));
	
	for(int i=0; i<in_instructions;i++){
		
		int in_counter;
		char in_work;
		int in_repetition;
			
		/* scan each instruction */
		scan_count = scanf("%i %c %i\n", &in_counter, &in_work, &in_repetition);
		
		/* error */
		if(in_counter < 0 || in_counter >= ncounters || in_repetition<=0 || (in_work != 'I' && in_work !='D' && in_work != '2') || scan_count!=3){
			indicator = -1;
			return;
		}
		
		struct instruction n;
		
		/* point to counter in array*/
		n.counter = &counters[in_counter];
		
		/* store number of repetitions */
		n.repetitions = in_repetition;

		/* store work_fn */
		if(in_work == 'I'){
			n.work_fn = increment;
		}
		else if(in_work == 'D'){
			n.work_fn = decrement;
		}
		else if(in_work == '2'){
			n.work_fn = mult2;
		}

		/*store new instruction in array */
		instructions[thread_num][i] = n;
	}
}
 
 
/* ============================================================================
 * Thread function
 * ========================================================================== */
static void *
worker_thread(void *arg) {
	int position = arg;
	
	/* for every instruction in the array of array do something */ 
	for(int i = 0; i < ninstructions[position]; i++){
		pthread_mutex_lock(&instructions[position][i].counter->lock);
			for(long k = 0; k < instructions[position][i].repetitions;k++){
				instructions[position][i].work_fn(&(instructions[position][i].counter->counter));
			}
			pthread_mutex_unlock(&instructions[position][i].counter->lock);
			
		}
	return NULL;
}

/* ============================================================================
 * Main function
 * ========================================================================== */
int
main(void) {
	
	int scan_count;
	/* scan ncounters */
	scan_count = scanf("%i\n", &ncounters);
	if(ncounters<=0 || scan_count!=1){
		printf("error\n");
		return -1;
		
	}
	/* malloc array of counters */
	counters = (struct counter *)malloc(ncounters * sizeof(struct counter ));
	for(int i=0; i<ncounters;i++){
		struct counter c;
		c.counter = 0;
		pthread_mutex_init (&c.lock,NULL);
		counters[i] = c;
	}	
	
	/* scan nthreads */
	scan_count = scanf("%i\n", &nthreads);
	if(nthreads<=0 || scan_count!=1){
		printf("error\n");
		free(counters);
		return -1;
	}
		
	/* malloc array of instructions */
	ninstructions = (int *)malloc(nthreads * sizeof(int));
	
	/* malloc array of array */
	instructions = (struct instruction **)malloc(nthreads * sizeof(*instructions[nthreads])); 
	
	/* scan instructions */
	int instruct_input;
	for(int i=0; i<nthreads;i++){
		/* scan the number of instructions this thread contains */
		scan_count = scanf("%i\n", &instruct_input);
		
		/*constraint */
		if(instruct_input<=0 || scan_count!=1){
			printf("error\n");
			for(int j =0; j<=i;j++){
				free(instructions[j]);
			}
			free_memory();
			return -1;
		}
		
		/* store number of instructions per thread in separte array */
		ninstructions[i] = instruct_input;
		
		/* method scanning instructions */
		scan_instructions(ninstructions[i], i);
		if(indicator == -1){
			printf("error\n");
			for(int j =0; j<=i;j++){
				free(instructions[j]);
			}
			free_memory();
			return -1;
		}
	}
	
	/* not EOF */
	int buffer;
	if(scanf(" %i", &buffer)!=EOF){
		printf("error\n");
			for(int j =0; j<=nthreads;j++){
				free(instructions[j]);
			}
			free_memory();
			return -1;
	}
	
	
	/*creating threads */
	pthread_t threads[nthreads];
	
	/* executing the threads */
	for(int i = 0; i!= nthreads; i++)
		pthread_create(&threads[i], NULL, worker_thread, (void*)i);
	for(int i = 0; i!= nthreads; i++)
		pthread_join(threads[i], NULL);
	
	
	/* print each counter and destroy mutex*/
	for(int i = 0; i< ncounters;i++){
		printf("%lld\n", counters[i].counter);
		pthread_mutex_destroy(&counters[i].lock);
	}
	
	/* free all arrays */
	for(int i=0; i<nthreads;i++){
		free(instructions[i]);
	}
	free_memory();


	return 0;
}
