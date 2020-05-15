#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 } STRINGDATA;


/* Define globally accessible variables and a mutex */

#define VECLEN 100000
#define ARRAY_SIZE 2000000
#define MAXCHAR 1000
#define NUMTHRDS 4 //~OR: 8, 16, 32, 64... number of cores
#define FILENAME "~dan/625/wiki_dump.txt";
char str[ARRAY_SIZE][MAXCHAR];
double string_list[ARRAY_SIZE];
double differnece_list[ARRAY_SIZE];
   STRINGDATA sumstr; 
   pthread_t callThd[VECLEN];
   pthread_mutex_t mutexsum;
