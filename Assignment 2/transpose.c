
/** @file transpose.c
 *
 * @brief Encoding string to simple transposition cipher
 *
 * @author Hemil Panchiwala
 */
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>


/** @brief In this function, I have implemented the encryption of string taken from txt file
  * and have written the encrypted string to the output txt file
 */
int main(int argc, char** argv) {

  clock_t start, end;
  double cpu_time_used;

  start = clock();

  char input[5000];
  char ch;
  int n,a,b;

  // Here I have defined the variables needed to encrypt the string
  n = atoi(argv[1]);
  a = atoi(argv[2]);
  b = atoi(argv[3]);

  // Opening the input file
  FILE *inputfile = fopen(argv[4], "r");

  // Taking the string from the input file
  int i=0;
  while((ch = fgetc(inputfile)) != EOF) {
    input[i] = ch;
    i++;
  }

  fclose(inputfile);

  // Performing the encryption process
  int size = i;

  int tt=size;
  if(size%n!=0){
    size = (size/n + 1)*n;
  }

  // printf("%d\n", size);

  for(int i=tt;i<size;i++){
    input[i] = '*';
  }

  char enc[size];
  for(int i=0;i<(size/n);i++){
    for(int j=0;j<n;j++){
      int p = (a*j + b)%n;
      enc[j+n*i]=input[p+n*i];
    }
  }

  // Opening the output file
  FILE *outputfile = fopen("outputfile.txt", "w");

  //Writing encrypted string in the output file
  for(int i=0;i<size;i++){
    if(enc[i] != '\0'){
      fputc(enc[i], outputfile);
    }else{
      fputc('*', outputfile);
    }
  }
  
  fclose(outputfile);

  // Printing the encrypted string
  for(int i=0;i<size;i++){
    printf("%c", enc[i]);
  }
  printf("\n");

  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f\n", cpu_time_used);

  return 0;
}
