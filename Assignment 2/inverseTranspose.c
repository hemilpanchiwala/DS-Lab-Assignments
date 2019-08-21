
/** @file inverseTranspose.c
 *
 * @brief Decoding transposition cipher
 *
 * @author Hemil Panchiwala
 */
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>

/**
 * @brief this function calculates the modular inverse of a number
 * 
 * @param a 
 * @param m 
 * @return int 
 */
int modInverse(int a, int n){ 
    a = a%n; 
    for (int i=1; i<n; i++) 
       if ((a*i) % n == 1) 
          return i; 
    
    return 0;
} 

/** @brief In this function, I have implemented the decryption of string taken from txt file
  * and have written the decrypted string to the decryptedOutput txt file
 */
int main(int argc, char** argv) {

  clock_t start, end;
  double cpu_time_used;

  start = clock();

  char enc[5000];
  char ch;
  int n,a,b;

  // Here I have defined the variables needed to decrypt the string
  n = atoi(argv[1]);
  a = atoi(argv[2]);
  b = atoi(argv[3]);

  int a_dash = modInverse(a,n);
  int b_dash = (n - (a_dash*b)%n);

  // Opening the output file
  FILE *outputfile = fopen(argv[4], "r");

  // Taking the encrypted string from the output file
  int i=0;
  while((ch = fgetc(outputfile)) != EOF) {
    enc[i] = ch;
    i++;
  }

  fclose(outputfile);

  // Performing the encryption process
  int size = i;

  int tt=size;
  if(size%n!=0){
    size = (size/n + 1)*n;
  }

  for(int i=tt;i<size;i++){
    enc[i] = '*';
  }

  char dec[size];
  for(int i=0;i<(size/n);i++){
    for(int j=0;j<n;j++){
      int p = (a_dash*j + b_dash)%n;
      dec[j+n*i]=enc[p+n*i];
    }
  }

  // Opening the decryptedOutput file
  FILE *decryptedOutputfile = fopen("decryptedOutputfile.txt", "w");

  // Writing decrypted string in the decryptedOutput file
  for(int i=0;i<size;i++){
    if(dec[i] != '*'){
      fputc(dec[i], decryptedOutputfile);
    }
  }


  fclose(decryptedOutputfile);

  // Printing the encrypted string
  for(int i=0;i<size;i++){
    if(dec[i] != '*'){
      printf("%c", dec[i]);
    }
  }
  printf("\n");

  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f\n", cpu_time_used);

  return 0;
}
