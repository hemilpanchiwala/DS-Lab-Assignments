
/** @file compareFiles.c
 *
 * @brief Comparing decrypted string with original string
 *
 * @author Hemil Panchiwala
 */
#include <stdio.h>
#include <cstring>
#include <time.h>


/** @brief In this function, I have performed comparison between decrypted string and
  * original string
 */
int main(){

  clock_t start, end;
  double cpu_time_used;

  start = clock();

  char ch;
  char inputArr[5000];
  char decryptedOutputArr[5000];

  // Opening the input file
  FILE *inputfile = fopen("inputfile.txt", "r+");

  // Taking the string from the input file
  int i=0;
  while((ch = fgetc(inputfile)) != EOF) {
    inputArr[i] = ch;
    i++;
  }

  fclose(inputfile);

  // Opening the decryptedOutput file
  FILE *decryptedOutputfile = fopen("inputfile.txt", "r+");

  // Taking the decrypted string from the decryptedOutput file
  i=0;
  while((ch = fgetc(decryptedOutputfile)) != EOF) {
    decryptedOutputArr[i] = ch;
    i++;
  }

  fclose(decryptedOutputfile);

  // Comparing the original string and the decrypted string
  int size = (int)strlen(inputArr) - 1;

  int count = 0;
  for(int j=0;j<size;j++){
    if(inputArr[j] == decryptedOutputArr[j]){
      count++;
    }
  }
  if(count == size){
    printf("Your program shows correct output\n");
  }else{
    printf("Not same files\n");
  }

   end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f\n", cpu_time_used);

  return 0;
}
