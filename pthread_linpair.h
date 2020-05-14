
#include <pthread.h>

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
   DOTDATA sumstr; 
   pthread_t callThd[NUMTHRDS];
   pthread_mutex_t mutexsum;

#define ARRAY_SIZE 2000000
#define STRING_SIZE 16

char char_array[ARRAY_SIZE][STRING_SIZE];
int sum_of_strings[ARRAY_SIZE];
int diff_of_sums[ARRAY_SIZE];
