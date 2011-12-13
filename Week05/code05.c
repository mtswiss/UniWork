
#include <stdio.h>
#include <stdlib.h>


char *read_text(char *);



int main(int argc, char **argv) {
	char *text;

	if (argc != 2) {
		printf("USAGE: %s filename\n", argv[0]);
		exit(1);
	}

	text=read_text(argv[1]);
	
	printf("PLAINTEXT:\n%s\n", text);
/*
	encode(text);	
	printf("CIPHERTEXT:\n%s\n", text);
	decode(text);
	printf("DECODED CIPHERTEXT:\n%s\n", text);
*/

	free(text);	
	return 0;
}



char *read_text(char *filename) {
	FILE 		*filedes;
	static char	*text;
	int			file_len, 
				i;

	if(!(filedes = fopen(filename, "r"))) {
		perror("fopen()");	
		exit(2);
	}

	/* One quick way to find out a file's size... */
	fseek(filedes, 0L, SEEK_END);
	file_len = ftell(filedes);
	rewind(filedes);

#ifdef DEBUG
	printf("File: %s; Length: %d\n", filename, file_len);
#endif

	if(!(text = (char *)malloc((size_t) (file_len + 1)))) {
		perror("malloc()");
		exit(3);
	}

	for(i = 0; i < file_len; i++) 
		text[i] = fgetc(filedes);		
	text[file_len] = (char)NULL;						/* NULL-terminate the character array */

#ifdef DEBUG
	for(i = 0; i <= file_len; i++)
		if (text[i] == (char)NULL)
			printf("NULL\n");
		else
			fputc(text[i], stdout);
	exit(0);
#endif

	fclose(filedes);
	return text;
}


