
#include        "pracquiz.h"
 
#define N       10


char *
Get_line(void)
{
        char            *line;  /* pointer to the complete line */
        char            *cp;    /* pointer to last character put into the string */
        size_t		size;   /* current size of string buffer */
        size_t		count;  /* count of characters read so far */
        int		c;

        size = N;
        line = (char*) malloc(N); /* allocate N bytes initially for line */
        cp = line;

        for (count = 0; (c = getchar()) != '\n'; count++)
        {
                if (c == EOF)
                        return NULL;

                if (count >= (size - 1))
                {
                        line = (char*)srealloc(line, size += N); /* allow N more
 chars */
                        cp = line + count; /* restore cp */
                }
                *cp++ = c;
        }
        *cp = '\0';
        count++;
        return (char*)srealloc(line, count); /* return the correct sized string
*/
}



void *
salloc(size_t size)
{
        void    *result;

        if ((result = malloc(size)) == NULL)
        {
                fprintf(stderr,"cannot malloc %d bytes\n", size);
                exit(1);
        }
        return result;
}

void *
srealloc(void *ptr, size_t size)
{
        void    *result;

        if ((result = realloc(ptr, size)) == NULL)
        {
                fprintf(stderr,"cannot malloc %d bytes\n", size);
                exit(1);
        }
        return result;
}

