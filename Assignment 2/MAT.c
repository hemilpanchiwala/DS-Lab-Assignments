
/** @file MAT.c
 *
 * @brief Performing Medial Axis Transformation
 *
 * @author Hemil Panchiwala
 */
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#define bool _Bool

/** @brief Declaring the global datatypes
*/
int **input;
int **output;
int initialSize = 0;
int treePointer = 0;

/** @brief Creating a node of quadTree
*/
struct quadTree {
  int level;
  int value;
  int indexValue;
};

struct quadTree treeNodes[100];

/**
 * @brief This function checks whether all elements are same or not 
 * 
 * @param row1 
 * @param row2 
 * @param col1 
 * @param col2 
 * @return true 
 * @return false 
 */
bool check(int row1, int row2, int col1, int col2){

  for(int i=row1; i<=row2; i++){
    for(int j=col1; j<=col2; j++){
      if(input[i][j] != input[row1][col1]){
        return false;
      }
    }
  }

  return true;
}

/**
 * @brief This function creates the maximal square array and the quadtree
 * 
 * @param row1 
 * @param row2 
 * @param col1 
 * @param col2 
 * @param level 
 * @param indexValue 
 * @return int 
 */
int makeArray(int row1, int row2, int col1, int col2, int level, int indexValue){

  if(check(row1, row2, col1, col2)){
    for(int i=row1; i<=row2; i++){
      for(int j=col1; j<=col2; j++){
        output[i][j] = indexValue;
      }
    }

    treeNodes[treePointer].level = level;
    treeNodes[treePointer].value = input[row1][col1];
    treeNodes[treePointer].indexValue = indexValue;
    treePointer++;

    indexValue = indexValue + 1;
    return indexValue;

  }

  int pp = (row1+row2)/2;
  int qq = (col1+col2)/2;

  indexValue = makeArray(row1, pp, col1, qq, level+1, indexValue);
  indexValue = makeArray(row1, pp, qq+1, col2, level+1, indexValue);
  indexValue = makeArray(pp+1, row2, col1, qq, level+1, indexValue);
  indexValue = makeArray(pp+1, row2, qq+1, col2, level+1, indexValue);


  return indexValue;

}

/**
 * @brief This function takes the input array from the txt file and 
 * then using the makeArray function creates and prints the maximal square array and 
 * the quadtree 
 * 
 * @return int 
 */
int main(){

  clock_t start, end;
  double cpu_time_used;

  start = clock();

  // Opening the input file
  FILE *inputfile = fopen("inputFile.txt", "r");

  if(inputfile == NULL){
    printf("No file found\n");
  }

  // Taking the size of input array
  char c;
  int x = 0;
  while( (c = fgetc(inputfile)) != EOF) {
      if(c == ' ' || c == '\n') continue;
      x++;
  }

  initialSize = sqrt(x);

  int size = 0;

  // changing the size if it is not divisible by 4
  if(initialSize%4 != 0){
    size = pow(2, ceil(log2(initialSize)));
  }else{
    size = initialSize;
  }

  // Taking the input array
  input = (int **) malloc((size+1)*sizeof(int *));
  for(int i=0;i<size+1;i++){
    input[i] = (int *)malloc((size+1)*sizeof(int));
  }

  inputfile = fopen("inputFile.txt", "r");

  // Here the array is mapped
  int max = size + 1;
  fseek(inputfile, 0, SEEK_SET);
  int i = max - initialSize;
  int j = max - initialSize;
  while(!feof(inputfile)){
    int t;
    char ch;
    fscanf(inputfile, "%d", &t);
    fscanf(inputfile, "%c", &ch);
    input[i][j] = t;
    if(j == max-1){
      j = max - initialSize;
      i++;
    }else{
      j++;
    }
    if(i == max){
      break;
    }
  }

  // Here output array is declared
  output = (int **) malloc((size+1)*sizeof(int *));
  for(int i=0;i<size+1;i++){
    output[i] = (int *)malloc((size+1)*sizeof(int));
  }

  int zz = makeArray(1, size, 1, size, 0, 1);

  // Printing the maximal square array
  printf("Maximal Square Array:\n");
  for(int i=1;i<=size;i++){
    for(int j=1;j<=size;j++){
      printf("%02d ", output[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  // Printing the quad tree
  printf("Quad Tree:\n");
  printf("(indexValue, value, level)\n");
  for(int i=0;i<treePointer;i++){
    printf("%02d %d %02d\n", treeNodes[i].indexValue, treeNodes[i].value, treeNodes[i].level);
  }

   end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f\n", cpu_time_used);

}
