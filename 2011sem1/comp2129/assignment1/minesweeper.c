#include <stdio.h>
#include <stdlib.h>

#define MAXMINES 10
#define MINSIZE 1
#define MAXSIZE 100
#define BORDER 1
#define CREATELIMIT 1
#define MINE '@'

/* value of width and height of the mine field */
int n=0,m=0;
/* temp vars to save the scan */
int x=0,y=0;
/* char for the next command */
char command;

/* 2D array containing the mines */
char mines[MAXSIZE][MAXSIZE];
/* 2D array storing values */
char values[MAXSIZE][MAXSIZE];
/* 2D array representing output of mine field */
char output[MAXSIZE][MAXSIZE];

int timesCreated = 0;
int minesCreated = 0;
int success = 0;

int 
main(void) {
	while(scanf("\n%c %i %i", &command, &x, &y)!= EOF){
		/* creating grid */
		if(command=='g'){
			if(timesCreated>=CREATELIMIT||!inBound(x)||!inBound(y)||x*y<=MAXMINES){
				printf("grid-error\n");
				return -1;
			}
			else{
				n=x; m=y;
				createGrid();
				printf("%c %i %i\n",command, n, m);
				timesCreated = timesCreated++;
				emptyGrid();
			}
		}

		/* place a mine */
		else if(command=='b'){
			if(mines[x+BORDER][y+BORDER] == MINE || !inGrid(x,y)){
				printf("mine-error\n");
				return -1;
			}
			if(minesCreated < MAXMINES){
				mines[x+BORDER][y+BORDER] = MINE;
				printf("%c %i %i\n",command, x, y);
				minesCreated=minesCreated++;
			}
			if(minesCreated==10){
				createValues();
				printOutput();
			}
		}

		/* uncover a tile */
		else if(command=='u'){
			if(minesCreated<MAXMINES){
				printf("mine-error\n");
				return -1;
			}
			if(!inGrid(x,y)){
				printf("uncover-error\n");
				return -1;
			}
			if(mines[x + BORDER][y + BORDER]==MINE){
				printf("%c %i %i\nlost\n",command, x, y);
				return -1;
			}
			if(success <= n*m && output[x + BORDER][y + BORDER]=='*'){
				output[x + BORDER][y + BORDER] = values[x + BORDER][y + BORDER];
				success++;
				printf("%c %i %i\n", command, x,y);
				printOutput();
			}
		}

		/* place a flag */
		else if(command=='f'){
			if(minesCreated<MAXMINES){
				printf("mine-error\n");
				return -1;
			}
			if(!inGrid(x,y)||mines[x+BORDER][y+BORDER]!=MINE){
				printf("uncover-error\n");
				return -1;
			}
			if(success <= n*m && output[x + BORDER][y + BORDER]=='*'){
				output[x + BORDER][y + BORDER] = 'f';
				success++;
				printf("%c %i %i\n", command, x,y);
				printOutput();
			}
		}
		if(success==n*m && success!=0){
			printf("won\n");
			return 0;
		}
		if(command!='g'&&command!='b'&&command!='u'&&command!='f'){
			printf("input error\n");
			return -1;
		}
	}
		if(success!=n*m){
			printf("missing-input\n");
			return -1;
		}
	return 0;
}

int createGrid(void){
	for(int i = 0; i <= n + BORDER; i++){
		if(i==0||i== n +BORDER) {
				output[i][0] = '+';
				output[i][m + BORDER] = '+';
		}
		else{
			output[i][0] = '-';
			output[i][m + BORDER] ='-';
	}

		}
	for(int i = 0; i <= n + BORDER; i++){ 
		for(int j = 1; j < m + BORDER; j++){
			if(i==0|| i== n + BORDER)	{output[i][j]='|';}
			else						{output[i][j]='*';}
		}
	}	
}

/* create array for mine */
int emptyGrid(void){
	for(int i = 1; i <= m + BORDER;i++){
		for(int j = 1; j <= n + BORDER; j++){
			mines[j][i]='*';
		}
	}
	return 0;
}


/* method to check if our vars are in bound or not */
int inBound(int i){
	if(i <=MAXSIZE && i>=MINSIZE)	{return 1;}
	else							{return 0;}
}

/* method to check if our vars are in grid or not */
int inGrid(int i, int j){
	if(i <n && j<m && 0<=i && 0<=j)	{return 1;}
	else							{return 0;}
}

/* print to screen */
int printOutput(void){
	for(int i = 0; i <= m + BORDER; i++){
		for(int j = 0; j <= n + BORDER; j++){
			putchar(output[j][i]);
		}
		printf("\n");
	}
	return 0;
}

/* print mines */
int printMine(void){
	for(int i = 1; i < m + BORDER; i++){
		for(int j = 1; j < n + BORDER; j++){
			putchar(mines[j][i]);
		}	
		printf("\n");
	}
	return 0;
}


/* method to create an array to store values */
int createValues(void){
	for(int i = 0; i < m + BORDER; i++){
		for(int j = 0; j < n + BORDER; j++){
			values[j][i]='0';
		}
	}
		for(int i = BORDER; i < m + BORDER; i++){
			for(int j = BORDER; j < n + BORDER; j++){
				if(mines[j][i]==MINE){
					/* squares above */
					values[j-1][i-1]++;
					values[j-1][i]++;
					values[j-1][i+1]++;
					/* squares on the side */
					values[j][i-1]++;
					values[j][i+1]++;
					/* squares under */
					values[j+1][i-1]++;
					values[j+1][i]++;
					values[j+1][i+1]++;
				}
			}
		}
		return 0;
}
