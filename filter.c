
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "header.h"

#define ARRAY_LEN 50000

int letterSum = 0; // counter of letters read
int letters_range[26] = {0};
int letters[26] = {0};
int wordCount = 0;

void accumulatedDistribution(int *letters, int *letters_range, int arrlen) {
  letterSum = 0;
  for (int i = 0; i < arrlen; i++) {
    letterSum += letters[i];
    letters_range[i] = letterSum;
  }
} // accumulatedDistribution(int *letters, int *letters_range)

void accumulatedDistribution_word(int *words, int *words_range) {
  int wordsum = 0;
  int i = 0;
  while(words[i] != 0) {
    wordsum += words[i];
    words_range[i] = wordsum;
    i++;
  }
}



/**
 * Given a filename and a pointer to two array, this method will count the frequence of
 * occurences for each word in the file, and update the corresponding position in the
 * array.
 * void generateRandChars_nobreak(char*, int*, int);
 * @param filename the name of a text file to be read from.
 * @param double array of words of size 50000 by a string length of up to 50.
 * @param int array that contains the freqency of each word.
 *
 */
void frequencyOfWord(char *filename,char words[ARRAY_LEN][50],int frequency[ARRAY_LEN]){
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    wordCount = 0;
    int uniqueWordCount = 0;


    FILE *file = fopen (filename, "r");
    if (file == NULL) {
      perror("fopen");
    }

    int wordsIndex = 0;
    while( (read = getline(&line, &len, file)) != -1 ) {
      if (read > 0) {
	int offset = 0;

	while (line[offset] != '\0') {
	  //printf("line: %ld\n", strlen(line));
	  char word[100];
	  memset(word, 0, sizeof(word));
	  for (int i = 0; i < strlen(line); i++) {
	    char currChar = tolower(line[offset]);
	    //printf("%c\n", currChar);
	    if (('a' <= currChar && currChar <= 'z') || currChar == '\''
		|| '0' <= currChar && currChar <= '9') {
	      word[i] = currChar;
	      offset++;
	    }
	    else {
	      offset++;
	      break;
	    } // else
	  } // for
	  if (word[0] != '\0'){
	    //printf("%s\n", word);
	    wordCount++;


	    // store word and calculate frequency
	    for (int i = 0; i < ARRAY_LEN; i++) {
	      // did not find match so add new word
	      if (strcmp(words[i], "\0") == 0) {
		//printf("no match\n");
		strcpy(words[i], word);
		frequency[i]++;
		uniqueWordCount++;
		break;
	      }
	      // did we find match?
	      else if (strcmp(words[i], word) == 0) {
		//printf("match\n");
		frequency[i]++;
		break;
	      }
	      else {
		//printf("hi\n");
		continue;
	      }
	    } // for
	  } // if
	  //printf("offset: %d\n", offset);
	} // while
      } // if
    } // while
    printf("%d\n", wordCount);
    printf("%d\n", uniqueWordCount);

    fclose(file);
} // frequencyOfWord()


/**
 * Prints the array provided to the screen.
 * @param array pointer to the array to be printed.
 */
void printArray(int *array) {
  for (int i = 0; i < 26; i++) {
    printf("%c = %d\n", 'a' + i, array[i]);
  } // for
} // printArray(int *array)

/**
 * Create a histogram displaying the frequency of occurences for the values of a
 * character array.
 *
 * @param array integer array containing character counts.
 * @param maxLen the largest possible bar size.
 */
void drawHistogram(int *array, int maxLen) {
  int max = 0;
  for (int i = 0; i < 26; i++) {
    if (array[i] > max) {
      max = array[i];
    }
  } // for

  // standardize each value to be between 0 - 40, and print histogram
  printf("\n");
  for (int i = 0; i < 26; i++) {
    int numOfStars = (int) (((double) array[i] / (double) max) * maxLen);
    printf("%c: ", 'a' + i);

    for (int j = 0; j < numOfStars; j++) {
      printf("*");
    } // inner for
    printf("\n");
  } // outer for

} // drawHistogram (int *array, int maxLen)

/**
 * Given a filename and a pointer to an array, this method will count the frequence of
 * occurences for each character in the file, and update the corresponding position in the
 * array.
 *
 * For the array, position 0 corresponds to 'a' and position 25 corresponds to 'z'.
 *
 * @param filename the name of a text file to be read from.
 * @param letters pointer to an int array of size 26.
 *
 */
void frequencyOfCharacters(char *filename, int *letters) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  //printf( "Enter string below [ctrl-D to quit]\n" );

  // set the seed for rand()
  time_t t;
  srand((unsigned) time(&t));

  FILE * inputStream = fopen( filename, "r" );

  while( (read = getline(&line, &len, inputStream)) != -1 ) {

    if( read > 0 ) {

      for (int i = 0; i < strlen(line); i++) {
	       char c = tolower(line[i]);
	        if ('a' <= c && c <= 'z') {
	           letters[c-'a']++;
	           //printf ("%c", c);
	        } //if
      } //for

      //printf( "\n=> %s\n", line );
    } // if

    //printf( "Enter string below [ctrl-D to quit]\n" );
  } // while


  fclose( inputStream );
  free( line );
} // frequencyOfCharacters(char *filename, int *letters)

int main( int argc, char** argv ) {
  char filename;

  printf("What file do you want to find the frequency of?\n");
  scanf("%s",&filename);

  frequencyOfCharacters(&filename, letters);

  /* print the frequences for each letter */
  /* printf("Frequencies for letters in original\n"); */
  /* printArray(letters); */

  /* printf("\n\n\n\n\n"); */

  /* // print the accumulated values */

  accumulatedDistribution(letters, letters_range, 26);
  /* printf("Accumulated values for original file\n"); */
  /* printArray(letters_range); */

  printf("original file histogram\n");
  drawHistogram(letters, 100);

  char randomChars[letterSum];

  memset(randomChars, 0, sizeof(randomChars));
  generateRandChars(randomChars, letters_range, letterSum);
  //printChars_sized(randomChars); // it would print out the characters base on users input
  //printChars(randomChars);
  //toTextFile(randomChars);



  // compare the file created
  int compLetters[26] = {0};
  int compLetter_ranges[26] = {0};

  frequencyOfCharacters("randomCharacters.txt", compLetters);
  /* printf("Frequencies for letters in random generation\n"); */
  /* printArray(compLetters); */

  /* letterSum = 0; */
  /* printf("Accumulated values for random generation\n"); */
  /* accumulatedDistribution(compLetters, compLetter_ranges); */
  /* printArray(compLetter_ranges); */


  printf("random generated letters histogram\n");
  drawHistogram(compLetters, 100);

  // creates and then create an array of words and an array of frequency
  char words[ARRAY_LEN][50];
  int frequency[ARRAY_LEN];
  int frequency_range[ARRAY_LEN];
  printf("What file would you like to find the words to?\n");
  scanf("%s", &filename);
  frequencyOfWord(&filename, words,frequency);
  accumulatedDistribution_word(frequency, frequency_range);
  int i = 0;
  while(frequency_range[i] != 0){
    //printf("%d\n", frequency_range[i]);
    i++;
  }
  //printf("\n%d\n", wordCount);

  //we have the range of the word working, frequency_range is the one;
  int size = 5000;
  for(int num = 0; num < size; num++){
  char *test = ran_word(words, frequency_range, wordCount);
  for(int i = 0; i < sizeof(test); i++){
    printf("%c", test[i]);
  }
  printf(" ");
  if(num % 10 == 0 && num != 0) printf("\n");
}
  //printf("\n");















  return 0;

} // main( int, char** )
