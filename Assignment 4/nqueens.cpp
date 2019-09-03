/**
 * @file nqueens.cpp
 * @author Hemil Panchiwala
 * @brief This code solves the n-queens problem with all its possible solutions
 * @date 2019-09-03
 * 
 * 
 */
#include <iostream>
#include <string.h>
#include <time.h>

using namespace std;

/**
 * @brief This variable keeps the data of number of combinations
 * 
 */
int count = 0;

/**
 * @brief This function prints the 2-D representation of solution of n-queens problem
 * 
 * @param arr 
 */
void print(int** arr, int n) {

    cout<<"Combination "<<count<<":"<<endl;

    for(int i=0;i<n;i++){
        cout<<"|";
        for(int j=0;j<n;j++){
            cout<<arr[i][j]<<"|";
        }
        cout<<endl;
    }
    cout<<endl;

}

/**
 * @brief This function checks whether the queen is in safe position or not
 * 
 * @param arr 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool isSafe(int** arr, int x, int y, int n) {

    for(int i=0;i<n;i++){
        if(arr[x][i] == 1) {
            return false;
        }
    }

    int i=x, j=y;
    while(i>=0 && j>=0) {
        if(arr[i][j] == 1) {
            return false;
        }
        i--;
        j--;
    }

    i=x;
    j=y;
    while(i<n && j>=0) {
        if(arr[i][j] == 1) {
            return false;
        }
        i++;
        j--;
    }

    return true;

}

/**
 * @brief This function makes the complete 2-D array of solved n-queen problem
 * 
 * @param arr 
 * @param col 
 * @return true 
 * @return false 
 */
bool solveNQueens(int** arr, int col, int n) {

    if(col == n){
        count++;
        print(arr, n);
        return true;
    }

    bool isThere = false;
    for(int i=0;i<n;i++) {
        if(isSafe(arr, i, col, n)) {
            arr[i][col] = 1;
            isThere = solveNQueens(arr, col + 1, n) || isThere;
            arr[i][col] = 0;
        }
    } 

    return isThere;
}

/**
 * @brief This function calls the function to solve the problem
 * 
 * @return int 
 */
int main(){

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int n;
    cout<<"Enter n:";
    cin>>n;

    int **arr;
    arr = new int *[n];
    for(int i=0;i<n;i++){
        arr[i] = new int[n];
    }

    for(int i=0;i<n;i++){
        memset(arr[i], 0, sizeof(int) * n);
    }

    solveNQueens(arr, 0, n);
    cout<<"Total number of combinations: "<<count<<endl;

    end = clock();
  
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

    return 0;                       
}