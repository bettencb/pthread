/*****************************************************************************
* FILE: pthread_main.c (diff_of_sum mutex)
* DESCRIPTION:
*   Main File: responsible for reading in wiki data and uses pthread_compare.c
*  to compute the difference of sums, one line at a time.
* SOURCE: Blaine Bettencourt, KSU
* LAST REVISED: 05/14/20 Blaine Bettencourt
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "pthread_linpair.h"

/**
void compare_strings()
{
  int i, j, randNum; 
  char randChar;

  for ( i = 0; i < ARRAY_SIZE; i++ ) {
	for ( j = 0; j < STRING_SIZE; j++ ) {
		 char_array[i][j] = parse_strings(); 
		 sum_of_strings[i] = pthread_char(char_array);	// call pthread_char.c
	}
  }

  for ( i = 1; i < ARRAY_SIZE; i++ ) { 
		diff_of_sums[i] = sum_of_strings[i-1] - sum_of_strings[i];	//compare temp counts for difference of each strings val
  }
}
**/

/**
void count_array()
{
  char theChar;
  int i, j, charLoc;

  for ( i = 0; i < ARRAY_SIZE; i++) {
	for ( j = 0; j < STRING_SIZE; j++ ) {
	     theChar = char_array[i][j];
		 charLoc = ((int) theChar) - 97;
		 diff_of_sums[charLoc]++;
	}
  }
}
**/

void print_results()
{
  int i, total = 0;

  for ( i = 0; i < 26; i++ ) {
     printf(" %c %d\n", (char) (i + 97), diff_of_sums[i]);
  }
  printf("\nTotal characters:  %d\n", total);
}

main() {
	parse_strings();
	print_results();
}

