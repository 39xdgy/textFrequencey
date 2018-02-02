#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/**
 * return a randomly generated character based on provided accumulated
 * distribution array.
 *
 * @param range pointer to accumulated distribution array. Determines
 * the likelihood of each character appearing in origin text.
 */

 char fin_word[50];
char randChar(int *range){

  char result;
  int randChar =  rand() % (range[25] + 1);

  for(int i = 0; i < 26; i++){
    if( i == 0){
      if(randChar >= 0 && randChar <= range[i]){
	result = 'a' + i;
      } // if
    } // if
    else {
      if(randChar > range[i-1] && randChar <= range[i]){
	result = 'a'+ i;
      } // if
    } // else
  } // for

  return result;
}

int ran_word_range(int wordcount){
  int fin;
  fin = rand() % (wordcount+1);
  //printf("%d\n",fin);
  return fin;
}

int ran_word_index(int *range, int wordcount){
  int ran_num = ran_word_range(wordcount);
  int i = 0;
  //printf("%d\n", i);
  while(range[i] != wordcount){
    if(i == 0 && ran_num >= 0 && ran_num <= range[i]) return i;
    if(ran_num > range[i-1] && ran_num <= range[i]) return i;
    i++;
  }
  return i;
}

char *ran_word(char words[][50], int *range, int wordcount){
  int index = ran_word_index(range, wordcount);
  //printf("%d\n", index);
  for(int i = 0; i < 50; i++){
    fin_word[i] = words[index][i];
  }
  return fin_word;
}



/**
 * generated a sequence of randomly generated characters.
 *
 * @param randomChars pointer to the destination of the chars.
 * @
 */
void generateRandChars(char *randomChars, int *letters_range, int size) {

  //randomly generate a letter
  for(int i = 0; i < size; i++){
      char a = randChar(letters_range);
      randomChars[i] = a;
  } // for

} // generateRandChars(int n);

void printChars(char *array) {
  printf("size: %ld\n", strlen(array));
//  printf("%s", array);
  for (int i = 0; i < strlen(array); i++) {
    if(i % 100 == 0 && i != 0){
      printf("\n");
    }
    printf("%c", array[i]);
  } // for
} // printChars(char *array)

void printChars_sized(char *array) {
  int length_of_word;
  printf("How long you want the words be: ");
  scanf("%d", &length_of_word);
  printf("size: %ld\n", strlen(array));
  //printf("%s", array);
    for (int i = 0; i < strlen(array) ; i++) {
      if(i % length_of_word == 0 && i != 0){
        printf(" ");
      }
      if(i % (length_of_word * 10) == 0 && i != 0){
        printf("\n");
      }
     printf("%c", array[i]);
    } // for
} // printChars(char *array)


void toTextFile(char *randomChars) {
  int fd = open("randomCharacters.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
  if (fd == -1) {
    perror("open");
  } // if

  int dprintfRet;
  for(int i = 0; i < strlen(randomChars);i++){
    if(i % 100 == 0 && i != 0){
      dprintfRet = dprintf(fd, "%c", '\n');
    }
      dprintfRet = dprintf(fd, "%c", randomChars[i]);
  }
  if (dprintfRet < 0) {
      perror("dprintf");
  } // if
  close(fd);
}
