#include <stdio.h>
#include <stdlib.h>
//#include <pthread_char.c>

#define ARRAY_SIZE 2000000
#define STRING_SIZE 16

char char_array[ARRAY_SIZE][STRING_SIZE];
int temp_count[ARRAY_SIZE];
int diff_of_sums[ARRAY_SIZE];

/*char parse_strings()
{
	int randNum = 0;
	char randChar = ' ';

	randNum = 26 * (rand() / (RAND_MAX + 1.0)); 	// pick number 0 < # < 25
	randNum = randNum + 97;				// scale to 'a'
	randChar = (char) randNum;

	// printf("%c", randChar);
	return randChar;
}
*/

void compare_strings()
{
  int i, j, randNum; 
  char randChar;

  for ( i = 0; i < ARRAY_SIZE; i++ ) {
	for ( j = 0; j < STRING_SIZE; j++ ) {
		 char_array[i][j] = parse_strings(); 
		 temp_count[i] = pthread_char(char_array);	// call pthread_char.c
	}
  }

  for ( i = 1; i < ARRAY_SIZE; i++ ) { 
		diff_of_sums[i] = temp_count[i-1] - temp_count[i];	//compare temp counts for difference of each strings val
  }
}

/*
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
*/

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

