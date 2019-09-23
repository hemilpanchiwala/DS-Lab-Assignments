
/** @file assign1.c
 */


#include<stdio.h>
#include <cstdlib>

/** size1 is starting size of deque */
int size1 = 4;

/** Deque is initialized dynamically */
int *deque = (int *) malloc(sizeof(int)*size1);

/** Left gives index of leftmost position in deque */
int left = -1;

/** Right gives index of rightmost position in deque */
int right = -1;

/** size is current size of deque */
int size = 4;

/** @brief Insert element from right in the Deque
	*
	* @param number_to_insert
	*
	* @return nothing
	*/
void insertRight(int number){

	if(left == 0 && right == size-1){
		size = 2*size;
		deque = (int*) realloc(deque, size * sizeof(int));
	}

	if(left == -1){
		left = 0;
		right = 0;
	}else{
		right++;
	}
	deque[right] = number;

}

/** @brief Insert element from left in the Deque
	*
	* @param number_to_insert
	*
	* @return nothing
	*/
void insertLeft(int number){

	if((left == 0 && right == size-1)){
		size = 2*size;
		deque = (int*) realloc(deque, size * sizeof(int));
	}

	if(left == -1){
		left = 0;
		right = 0;
	}else{
		for(int i=right;i>=left;i--){
			deque[i+1]=deque[i];
		}
		right++;
	}
	deque[left] = number;

}

/// @brief Delete element from right in the Deque
void deleteRight(){

	if(right <= size/2){
		size = size/2;
		deque = (int*) realloc(deque, size * sizeof(int));
	}

	if(left == right){
		left = -1;
		right = -1;
	}else{
		right--;
	}
}

/// @brief Delete element from left in the Deque
void deleteLeft(){

	if(right <= size/2){
		size = size/2;
		deque = (int*) realloc(deque, size * sizeof(int));
	}

	if(left == right){
		left = -1;
		right = -1;
	}else{
		for(int i=left;i<right;i++){
			deque[i]=deque[i+1];
		}
		right--;
	}
}

/** @brief This function prints all the elements
	*	of the deque
	*/
void print(){
	if(left == -1){
		printf("Dequeue is Empty\n");
	}else{
		if(left<=right){
			for(int i=left;i<=right;i++){
				printf("%d ", deque[i]);
			}
			printf("\n");
		}
	}
}

/** @brief This is the main function of the program.
	* In this function, we are performing different actions like
	* inserting, deleting, printing etc. from the deque
	*/
int main(){

	while(1){
		int option = 0;
		printf("1. InsertLeft\n2. InsertRight\n3. DeleteLeft\n4. DeleteRight\n5. Print\n6. GetSize\n7. Exit\n");
		scanf("%d", &option);
		if(option == 1){
			int number;
			printf("Enter the number:");
			scanf("%d", &number);
			insertLeft(number);
		}else if(option == 2){
			int number;
			printf("Enter the number:");
			scanf("%d", &number);
			insertRight(number);
		}else if(option == 3){
			deleteLeft();
		}else if(option == 4){
			deleteRight();
		}else if(option == 5){
			print();
		}else if(option == 6){
			printf("%d\n", size);
		}else if(option == 7){
			break;
		}else{
			printf("Enter valid option!!!\n");
		}
	}
}
