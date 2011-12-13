#include <assert.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const double D = 0.85;
static const double EPSILON = 0.005;

struct node *list = NULL; /* elements in the set */
static int N;
static int edges;
static int cores; 
int **in; /* list of pages it's being linked from */
int *in_magnitude;
int *out_magnitude;
double *current_scores;
double *old_scores; 


typedef struct node{
	char name[20];
	long hashvalue;
}node;

/* djb2 modified hash function from http://www.cse.yorku.ca/~oz/hash.html */
long
hash(char *str){
	long hash = 5381;
	int c;
	while (c = *str++){
		hash = ((hash << 5) + hash) + c; /*hash * 33 + c */
	}
	return hash;
}	


double vector_norm(){
	double normal = 0.0;
	for(int i = 0; i < N; i++){
		normal += (current_scores[i]-old_scores[i])*(current_scores[i]-old_scores[i]);
		old_scores[i] = current_scores[i];
	}
	return normal;
}

/* returns index if exists, otherwise returns -1*/
int check_existence(long h, char test[20], int position){
	for(int i =0; i<position;i++){
		if(list[i].hashvalue == h){
			if(strcmp(list[i].name, test) == 0)
				return i;
			else
				return -1;
		}		
	}
	return -1;
}


int
main(void) {
	int i, buffer = 0;
	char input[20];
	char str[20], str2[20], rand[20];
	if(scanf("\n%d",&cores)==1){
		if(cores>0){
			if(scanf("%d\n",&N)==1){
				buffer = 1;
			}
		}
	}
	if(buffer!= 1){
		printf("error\n");
		return -1;
	}
	list = (struct node*) malloc(N * sizeof(struct node));
	
	for(i = 0; i < N;i++){ 
		fgets(input,20, stdin);
			if(sscanf(input,"%s", str)!=1){
			break; /* when more than 1 arg */
		}
		if(strlen(str) < 20){
			long temp_hash = hash(str);
			if(check_existence(temp_hash, str,  i)== -1){
				struct node n;
				strcpy(n.name, str);
				n.hashvalue = temp_hash;
				list[i] = n;
			}
			else {
				/* when aleady exists */
				break;
			}
				
		}
		else{
			/* when longer than allowed */
			break;
		}
	}
	if(i!= N){
		printf("error\n");
		free(list);
		return -1;
	}	
	
	in = (int **)malloc(sizeof(int *)*N);
	for(i = 0; i<N; i++){
		in[i] = (int *) calloc(N,sizeof(int));
	}
	
	in_magnitude = (int*)calloc(N,sizeof(int));
	out_magnitude = (int*)calloc(N,sizeof(int));
	
	strcpy(rand, "");
	if(scanf("%d\n", &edges) ==1){
		if(edges >= 0){
			for(i = 0; i< edges; i++){
				fgets(input, 41, stdin);
				sscanf(input,"%s %s %s", str, str2, rand);
				long temp_hash = hash(str);
				long temp_hash2 = hash(str2);
				int pos = check_existence(temp_hash, str, N);
				int pos2 = check_existence(temp_hash2, str2, N);
				//printf("%s %d , %s %d\n", str, pos, str2, pos2);
				if(strcmp(rand, "")!=0)
					break;
				if(pos != -1 && pos2 != -1){
					out_magnitude[pos] +=1 ;
					in[pos2][in_magnitude[pos2]]= pos + 1;
					in_magnitude[pos2] +=1 ;
				}
				else {
				/* when not existing name */
					break;
				}
			}
		}
	}	
	
			
	if(scanf("\n%s", input) !=EOF || i!=edges){
		
		printf("error\n",input);
		free(in_magnitude);
		free(out_magnitude);
		for(int x =0; x<N;x++)
			free(in[x]);
		free(in);
		free(list);
		return -1;
	}
	
	old_scores = (double*)calloc(N,sizeof(double));
	current_scores = (double*) calloc(N,sizeof(double));
	
	for(i =0; i<N;i++){
		old_scores[i] = 1.0/N;
		current_scores[i] = 1.0/N;
	}
	buffer = -1;
	
	while(vector_norm() > EPSILON * EPSILON|| buffer == -1){
		for(int i = 0 ; i< N; i++){
			double total = 0.0;
			for(int j = 0; j < in_magnitude[i]; j++){
				total = total + (old_scores[in[i][j]-1]) / (out_magnitude[in[i][j]-1]);
			}
			current_scores[i] = (1.0-D) / N + D*total; 		
		}
		buffer++;
	}

	for(i =0; i<N;i++){
		printf("%s %.4lf\n", list[i].name, current_scores[i]);
	}	
	free(in_magnitude);
	free(out_magnitude);
	free(old_scores);
	free(current_scores);
	for(i =0;i<N;i++){
		free(in[i]);
	}
	free(in);
	free(list);
	
	return 0;
}

