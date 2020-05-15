/*****************************************************************************
* FILE: pthread_main.c (diff_of_sum mutex)
* DESCRIPTION:
*   This example program illustrates the use of mutex variables 
*   in a threads program. This version was obtained by modifying the
*   serial version of the program (sum_of_strings_serial.c) which performs a 
*   dot product. The main data is made available to all threads through 
*   a globally accessible  structure. Each thread works on a different 
*   part of the data. The main thread waits for all the threads to complete 
*   their computations, and then it prints the resulting sum.
* SOURCE: Vijay Sonnad, IBM
* LAST REVISED: 05/14/20 Blaine Bettencourt
******************************************************************************/
#include "pthread_plib.h"

/**
 *This is the difference part of the difference of sums. 
 Two strings should be getting compared in this method and
 the difference of sums between the two values should be getting
 set into differnece_list array in pthread_linpair.h 
 **/
void diff_of_strings()
{
  int i;
  for (i = 1; i < ARRAY_SIZE; i++)
  {
    differnece_list[i] = string_list[i - 1] - string_list[i]; //compare temp counts for difference of each strings val
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

  int i, start, end, len;
  long offset;
  double mysum, *x, *y;
  offset = (long)arg;

  len = sumstr.veclen;
  start = offset * len;
  end = start + len;
  x = sumstr.a;
  y = sumstr.b;

  /*
    Perform the dot product and assign result
    to the appropriate variable in the structure. 
    */

  mysum = 0;
  for (i = start; i < end; i++)
  {
    mysum += (x[i] + y[i]);
  }

  /*
    Lock a mutex prior to updating the value in the shared
    structure, and unlock it upon updating.
    */
  pthread_mutex_lock(&mutexsum);
  sumstr.sum += mysum;
  pthread_mutex_unlock(&mutexsum);

  pthread_exit((void *)0);
}

/* 
 The main program creates threads which do all the work and then 
 print out result upon completion. Before creating the threads,
 the input data is created. Since all threads update a shared structure, 
 we need a mutex for mutual exclusion. The main thread needs to wait for
 all threads to complete, it waits for each one of the threads. We specify
 a thread attribute value that allow the main thread to join with the
 threads it creates. Note also that we free up handles when they are
 no longer needed.
 */
int main(int argc, char *argv[])
{
  /*
  * if file is hard coded, argv would be FILENAME and FILE fp =... would but used to
  * read in the file with ...fopen(filename, "r")
  */
  int j = 0;
  long i;
  double *a, *b;
  void *status;
  pthread_attr_t attr;

  while (fgets(str[j], MAXCHAR, argv))
  {
    str[j][strlen(str[j]) - 1] = '\0';
    j++;

    /* Assign storage and initialize values */
    a = (double *)malloc(NUMTHRDS * VECLEN * sizeof(double));
    b = (double *)malloc(NUMTHRDS * VECLEN * sizeof(double));

    for (i = 0; i < VECLEN * NUMTHRDS; i++)
    {
      a[i] = 1.0;
      b[i] = a[i];
    }

    sumstr.veclen = VECLEN;
    sumstr.a = a;
    sumstr.b = b;
    sumstr.sum = 0;

    pthread_mutex_init(&mutexsum, NULL);

    /* Create threads to perform the sum_of_stringsuct  */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < NUMTHRDS; i++)
    {
      /* 
    Each thread works on a different set of data. The offset is specified 
    by 'i'. The size of the data for each thread is indicated by VECLEN.
    */
      pthread_create(&callThd[i], &attr, sum_of_strings, (void *)i);
    }

    pthread_attr_destroy(&attr);

    /* Wait on the other threads */
    for (i = 0; i < NUMTHRDS; i++)
    {
      pthread_join(callThd[i], &status);
    }

    *string_list = sumstr.sum; //the list of double values, one for each line that was read in. Add also a count var here

    /* After joining, print out the results and cleanup */
    printf("Sum of string %d %f \n", j, sumstr.sum);
  
  /*
    //loop back to top, through string_SUM while SCANF() and
    //add an if statement (if loop is == 1 then start calling diff_of_strings.)
    //printf ("Diff of Sum of pair =  %f \n", sumstr.sum); but
  */
     if(j > 1)
     {
       diff_of_strings();
     }
  }
  free(a);
  free(b);
  pthread_mutex_destroy(&mutexsum);
  pthread_exit(NULL);
  argc = 0;
  return argc;
}