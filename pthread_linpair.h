
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*   
The following structure contains the necessary information  
to allow the function "sum_of_string" to access its input data and 
place its output into the structure.  This structure is 
unchanged from the sequential version.
*/

typedef struct 
 {
   double      *a;
   double      *b;
   double     sum; 
   int     veclen; 
 } DOTDATA;

/* Define globally accessible variables and a mutex */

#define NUMTHRDS 4
#define VECLEN 100000
#define ARRAY_SIZE 2000000
#define STRING_SIZE 16
#define MAXCHAR 1000
#define FILENAME "c:\\temp\\test.txt";
   DOTDATA sumstr; 
   pthread_t callThd[NUMTHRDS];
   pthread_mutex_t mutexsum;

char str[ARRAY_SIZE][MAXCHAR];
double string_list[ARRAY_SIZE];
double differnece_list[ARRAY_SIZE];
// void *fileread();
