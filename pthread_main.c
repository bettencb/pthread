/*****************************************************************************
* FILE: pthread_compare.c (diff_of_sum mutex)
* DESCRIPTION:
*   This example program illustrates the use of mutex variables 
*   in a threads program. This version was obtained by modifying the
*   serial version of the program (dotprod_serial.c) which performs a 
*   dot product. The main data is made available to all threads through 
*   a globally accessible  structure. Each thread works on a different 
*   part of the data. The main thread waits for all the threads to complete 
*   their computations, and then it prints the resulting sum.
* SOURCE: Vijay Sonnad, IBM
* LAST REVISED: 05/14/20 Blaine Bettencourt
******************************************************************************/
#include "pthread_linpair.h"

/**
 *This is the difference part of the difference of sums. 
 Two strings should be getting compared in this method and
 the difference of sums between the two values should be getting
 set into differnece_list array in pthread_linpair.h 
 **/
void compare_strings()
{
  int i, j, randNum; 
  char randChar;

  for ( i = 0; i < ARRAY_SIZE; i++ ) {
	for ( j = 0; j < STRING_SIZE; j++ ) {
		 str[i][j] = parse_strings(); 
		 string_list[i] = pthread_char(str);
	}
  }

  for ( i = 1; i < ARRAY_SIZE; i++ ) { 
		differnece_list[i] = string_list[i-1] - string_list[i];	//compare temp counts for difference of each strings val
  }
}

/*
The function sum_of_strings is activated when the thread is created.
As before, all input to this routine is obtained from a structure 
of type DOTDATA and all output from this function is written into
this structure. The benefit of this approach is apparent for the 
multi-threaded program: when a thread is created we pass a single
argument to the activated function - typically this argument
is a thread number. All  the other information required by the 
function is accessed from the globally accessible structure. 
*/
void *sum_of_strings(void *arg)
{

/* Define and use local variables for convenience */
   int i, start, end, len ;
   long offset;
   double mysum, *x, *y;
   offset = (long)arg;
     
   len = sumstr.veclen;
   start = offset*len;
   end   = start + len;
   x = sumstr.a;
   y = sumstr.b;

/*
Perform the difference of sums and assign result
to the appropriate variable in the structure. 
*/
   mysum = 0;
   for (i=start; i<end ; i++) 
    {
      mysum += (x[i] + y[i]);
      string_list[i]=mysum;
    }

/*
Lock a mutex prior to updating the value in the shared
structure, and unlock it upon updating.
*/
   pthread_mutex_lock (&mutexsum);
   sumstr.sum += mysum;
   printf("Thread %ld did %d to %d:  mysum=%f global sum=%f\n",offset,start,end,mysum,sumstr.sum);
   pthread_mutex_unlock (&mutexsum);

   pthread_exit((void*) 0);
}


void *fileread() {
    FILE *fp = NULL;
    char line[STRING_SIZE][MAXCHAR];
    char* filename = FILENAME;
    int i = 0;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(line[i], MAXCHAR, fp) != NULL) 
    {
        printf("%s", line[i]);      // prints the string being stored into array
        str[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    fclose(fp);
}

/* 
The main program creates threads which do all the work and then 
print out result upon completion. Before creating the threads,
The input data is created. Since all threads update a shared structure, we
need a mutex for mutual exclusion. The main thread needs to wait for
all threads to complete, it waits for each one of the threads. We specify
a thread attribute value that allow the main thread to join with the
threads it creates. Note also that we free up handles  when they are
no longer needed.
*/
int main (int argc, char *argv[])
{
long i;
double *a, *b;
void *status;
pthread_attr_t attr;

/* Assign storage and initialize values */
a = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
b = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
  
for (i=0; i<VECLEN*NUMTHRDS; i++) {
  a[i]=1;
  b[i]=a[i];
  }

sumstr.veclen = VECLEN; 
sumstr.a = a; 
sumstr.b = b; 
sumstr.sum=0;

pthread_mutex_init(&mutexsum, NULL);
         
/* Create threads to perform the sum_of_stringsuct  */
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

for(i=0;i<NUMTHRDS;i++)
  {
  /* Each thread works on a different set of data.
   * The offset is specified by 'i'. The size of
   * the data for each thread is indicated by VECLEN.
   */
   pthread_create(&callThd[i], &attr, string_list, (void *)i); 
   }

pthread_attr_destroy(&attr);
/* Wait on the other threads */

for(i=0;i<NUMTHRDS;i++) {
  pthread_join(callThd[i], &status);
  }
/* After joining, print out the results and cleanup */

printf ("Difference =  %f \n", sumstr.sum);
free (a);
free (b);
pthread_mutex_destroy(&mutexsum);
pthread_exit(NULL);
}   


