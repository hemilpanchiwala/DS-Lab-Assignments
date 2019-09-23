// This is a line of text
// This is the first line
/** @file assign1.c
 */

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <cstring>
#include <stdbool.h>
#define bool _Bool

/** Queue of deleted roll no is declared */
int unusedRollNo[50];

/** rear stores the index of last element in Queue */
int rear = -1;

/** front stores the index of first element in Queue */
int front = -1;

/** @brief Insert element in Queue.
	*
	* This function inserts the deleted Roll No. from
	* linked list in a Queue.
	*
	* @param deleted_Roll_No.
	*
	* @return nothing
	*/
void insertInQueue(int roll){
	if(rear==49){
		printf("Queue is full\n");
	}else{
		if(front == -1){
			front = 0;
			rear=0;
			unusedRollNo[front] = roll;
		}else{
			rear++;
			unusedRollNo[rear] = roll;
		}
	}
}

/** @brief This function checks whether the queue is empty or not
	*
	* @param nothing
	*
	* @return boolean value
	*/
bool isQueueEmpty(){
	if(front == -1){
		return true;
	}
	return false;
}

/** @brief This function performs the pop function in queue
	*
	* @param nothing
	*
	* @return int value
	*/
int removeFromQueue()
{
	int removed_element = 0;
      if (front == rear){
      	removed_element = unusedRollNo[front];
      	front = -1;
      	rear = -1;
      }
      else
      {
	removed_element = unusedRollNo[front];
        front++;
      }
      return removed_element;
}

/** @brief This function prints the queue
	*
	* @param nothing
	*
	* @return nothing
	*/
void printQueue() {
	if(front == -1){
		printf("No elements present\n");
		return;
	}

	printf("Deleted Roll No.: ");
	for(int i=front;i<=rear;i++){
		printf("%d ", unusedRollNo[i]);
	}
	printf("\n");
}

/** @brief This struct defines a single node
	* of a student with its roll_no., name, dob, address and phone
	*/
struct node{
	int roll;
	char name[100];
	char dob[100];
	char address[500];
	long long int phone;

	struct node* prev;
	struct node* next;
};

struct node* head = NULL;
int roll1 = 100;

/** @brief This function inserts the node in doubly circular linked list
	*
	* @param name
	* @param dob
	* @param address
	* @param phone
	*
	* @return nothing
	*/
void insertInList(char name[100], char dob[100], char address[500], long long int phone){

	if(isQueueEmpty()){

		struct node *now = (struct node*) malloc(sizeof(struct node));
	roll1++;
	now->roll = roll1;
	strncpy(now->name, name, 100);
	strncpy(now->dob, dob, 100);
	strncpy(now->address, address, 500);
	now->phone = phone;

	if(head == NULL){
		head = now;
		head->next = head;
		head->prev = head;
	}else{
		struct node* current = head;

		while(current->next != head){
			current = current->next;
		}

		current->next = now;
		now->prev = current;
		now->next = head;
		head->prev = now;
		}
	}else{

		int deletedRoll = removeFromQueue();

		struct node *reusedNode = (struct node*) malloc(sizeof(struct node));

		reusedNode->roll = deletedRoll;
		strncpy(reusedNode->name, name, 100);
		strncpy(reusedNode->dob, dob, 100);
		strncpy(reusedNode->address, address, 500);
		reusedNode->phone = phone;

		if(head == NULL){
			head = reusedNode;
			head->next = head;
			head->prev = head;
		}else if(deletedRoll < head->roll){
			struct node* current = head;
			head = reusedNode;
			head->next = current;
			head->prev = current->prev;
			(current->prev)->next = head;
			(current->next)->prev = head;
		}else if((head->prev)->roll < deletedRoll){
			struct node* current = head->prev;
			current->next = reusedNode;
			reusedNode->prev = current;
			reusedNode->next = head;
			head->prev = reusedNode;
		}else{
			struct node* current = head;
			while(!((current->roll < deletedRoll) && ((current->next)->roll > deletedRoll))){
				current = current->next;
			}

			reusedNode->next = current->next;
			(current->next)->prev = reusedNode;
			current->next = reusedNode;
			reusedNode->prev = current;

		}

	}
}

/** @brief This function deletes the student with the particular roll no.
	*
	* @param roll_no
	*
	* @return nothing
	*/
void deleteElement(int roll){

	if(head==NULL){
		printf("Nothing to delete!!!\n");
		return;
	}

	struct node *current = head;
	struct node *current1 = current->next;

	if(current->next == head){
		head = NULL;
	}else if((head->prev)->roll == roll){
		current = (head->prev)->prev;
		current->next = head;
		head->prev = current;
	}else{
		if(current->roll == roll){
				head = current->next;
				head->prev = current->prev;
				(current->prev)->next = head;
		}else{
			while(current1->roll != roll){
					current = current->next;
					current1 = current1->next;
					if(current1 == head){
						printf("Roll No. not found\n");
						break;
					}
			}
			current1 = current1->next;
			current->next = current1;
			current1->prev = current;
		}
	}
	insertInQueue(roll);
	return;
}

/** @brief This function modifies all the information of
  * student with the particular roll no.
	*
	* @param roll_no
	* @param name
	* @param dob
	* @param address
	* @param phone
	*
	* @return nothing
	*/
void modify(int roll, char name[100], char dob[100], char address[500], long long int phone){

	if(head==NULL){
		printf("No data found!!!\n");
		return;
	}

	struct node *current = head;
	if(head->roll == roll){
		head->roll = roll;
		strncpy(head->name, name, 100);
		strncpy(head->dob, dob, 100);
		strncpy(head->address, address, 500);
		head->phone = phone;
	}
	while(current->roll != roll){
		if(current->next == head){
			return;
		}
		current = current->next;
	}


	current->roll = roll;
	strncpy(current->name, name, 100);
	strncpy(current->dob, dob, 100);
	strncpy(current->address, address, 500);
	current->phone = phone;

}

/** @brief This function sorts the student according to their names
	*
	* @param nothing
	*
	* @return nothing
	*/
void sort(){

	if(head == NULL) {
		printf("Nothing to sort!!!\n");
	}else {
		struct node *current = head;
		struct node *current1 = NULL;
		for(int i=100;i<roll1;i++){
			current1 = current->next;
			for(int j=i+1;j<roll1;j++){
				char temp[100];
				if(strcmp(current->name, current1->name) > 0){

					int tempRoll = 0;
					tempRoll = current->roll;
					current->roll = current1->roll;
					current1->roll = tempRoll;

					strcpy(temp, current->name);
					strcpy(current->name, current1->name);
					strcpy(current1->name, temp);

					strcpy(temp, current->dob);
					strcpy(current->dob, current1->dob);
					strcpy(current1->dob, temp);

					strcpy(temp, current->address);
					strcpy(current->address, current1->address);
					strcpy(current1->address, temp);

					long long int tempPhone = 0;
					tempPhone = current->phone;
					current->phone = current1->phone;
					current1->phone = tempPhone;
				}
				current1 = current1->next;
			}
			current = current->next;
		}
	}
}

/** @brief This function search the person in the doubly circular linked list
	*
	* @param name
	*
	* @return It prints the found person with all his/her information
	*/
void search(char name[100]){

	if(head == NULL){
		printf("List is Empty\n");
		return;
	}else if(head->next == head){
		if(strcmp(name, head->name) == 0){
			printf("%d\n", head->roll);
			printf("%s\n", head->name);
			printf("%s\n", head->dob);
			printf("%s\n", head->address);
			printf("%lld\n", head->phone);
			printf("\n");
			return;
		}else{
			printf("Person not present in list!!!\n");
			return;
		}
	}else{
		struct node *current = head;
		while(current->next != head){
			if(strcmp(name, current->name) == 0){
				printf("%d\n", current->roll);
				printf("%s\n", current->name);
				printf("%s\n", current->dob);
				printf("%s\n", current->address);
				printf("%lld\n", current->phone);
				printf("\n");
				return;
			}
			current = current->next;
		}
		printf("Person not present in list\n");
		return;
	}

}

/** @brief This function prints all the nodes of
	* doubly circular linked list
	*/
void print(){

	if(head == NULL){
		printf("Nothing to print\n");
	}else{
		struct node *current = head;
		if(head->next == head){
				printf("%d\n", head->roll);
				printf("%s\n", head->name);
				printf("%s\n", head->dob);
				printf("%s\n", head->address);
				printf("%lld\n", head->phone);
				printf("\n");
		}else{
			while(current->next != head){
				printf("%d\n", current->roll);
				printf("%s\n", current->name);
				printf("%s\n", current->dob);
				printf("%s\n", current->address);
				printf("%lld\n", current->phone);
				printf("\n");
				current = current->next;
			}
			if(current->next == head){
					printf("%d\n", current->roll);
					printf("%s\n", current->name);
					printf("%s\n", current->dob);
					printf("%s\n", current->address);
					printf("%lld\n", current->phone);
					printf("\n");
			}
		}
	}
}

/** @brief This is the main function of the program.
	* In this function, we are reading data from StudentData.csv file and
	* performing different operations on the data like insert, delete, modify etc.
	*/
int main(){
	char name[100][100];
	char dob[100][100];
	char address[500][500];
	long long int phone[13];

	char fileName[30] = "StudentData.csv";
	char buffer[1024];

	FILE *file = fopen(fileName, "r");
	fgets(buffer, sizeof(buffer), file);

	for(int i=0;i<13;i++){
		fgets(buffer, sizeof(buffer), file);

		char* getValue = strtok(buffer,",");
		getValue = strtok(NULL,",");
		strcpy(name[i], getValue);

		getValue = strtok(NULL,",");
		strcpy(dob[i], getValue);

		getValue = strtok(NULL,"\"");
		strcpy(address[i], getValue);

		getValue = strtok(NULL,",");
		phone[i] = strtol(getValue, NULL, 10);

	}

	while(1){
		printf("1. Insert\n2. Delete\n3. Search\n4. Modify\n5. Sort\n6. Print\n7. PrintDeletedQueue\n8. Exit\n");
		int option;
		scanf("%d", &option);
		if(option == 1){
			printf("Enter the index from file which you want to insert(starting from 1): \n");
			int i;
			scanf("%d", &i);
			insertInList(name[i-1], dob[i-1], address[i-1], phone[i-1]);
		}else if(option == 2){
			int getRoll;
			printf("Enter the roll no. to be deleted:\n");
			scanf("%d", &getRoll);
			deleteElement(getRoll);
		}else if(option == 3){
			char searchName[100];
			fgets (searchName, 100, stdin);
			fgets (searchName, 100, stdin);
			searchName[strlen(searchName) - 1] = '\0';
			search(searchName);
		}else if(option == 4){
			int modifyRoll;
			char modifyName[100];
			char modifyDob[100];
			char modifyAddress[100];
			long long int modifyPhone;
			printf("Enter the roll:");
			scanf("%d", &modifyRoll);
			printf("Enter the name:");
			fgets (modifyName, 100, stdin);
			fgets (modifyName, 100, stdin);
			modifyName[strlen(modifyName) - 1] = '\0';
			printf("Enter the dob:");
			fgets (modifyDob, 100, stdin);
			modifyDob[strlen(modifyDob) - 1] = '\0';
			printf("Enter the address:");
			fgets (modifyAddress, 500, stdin);
			modifyAddress[strlen(modifyAddress) - 1] = '\0';
			printf("Enter the phone:");
			scanf("%lld", &modifyPhone);
			modify(modifyRoll, modifyName, modifyDob, modifyAddress, modifyPhone);
		}else if(option == 5){
			sort();
		}else if(option == 6){
			print();
		}else if(option == 7){
			printQueue();
		}else if(option == 8){
			break;
		}else{
			printf("Enter valid option!!!\n");
		}
	}

	return 0;
}
