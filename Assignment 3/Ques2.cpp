/**
 * @file Ques2.cpp
 * @author Hemil Panchiwala
 * @date 2019-08-20
 * 
 * 
 */
#include <iostream>
#include <time.h>

using namespace std;

/**
 * @brief This is class defined for Singly Linked List
 * 
 */
class List{
    public:
    int data;
    List* link;
};

/**
 * @brief Head of the list
 * 
 */
List* head = NULL;

/**
 * @brief End of the list
 * 
 */
List* last = NULL;

/**
 * @brief This method inserts a node in linked list
 * 
 * @param data 
 */
void insert(int data){
    List* node = new List();
    node->data = data;
    if(head == NULL){
        head = node;
        head->link = NULL;
        last = node;
    }else{
        last->link = node;
        last = node;
    }
    
}

/**
 * @brief This method prints the linked list
 * 
 */
void print(){
    List* node = head;
    while(node->link){
        cout<<node->data<<" ";
        node = node->link;
    }
    cout<<node->data<<endl;
}

/**
 * @brief Prints all the triplets from index a to b
 * 
 * @param a 
 * @param b 
 */
void allCases(int a, int b){
    for(int i=a+1;i<=b;i++){
        cout<<"("<<a<<","<<i<<","<<b<<")"<<endl;
    }
}

/**
 * @brief This method finds the triplets(i,j,k) 
 * such that 1 ≤ i < j ≤ k ≤ N and Ai⊕Ai+1⊕…⊕Aj−1 = Aj⊕Aj+1⊕…⊕Ak
 * 
 * @return int 
 */
int main() {

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    int preVal = a[0];
    insert(preVal);
    for(int i=1;i<n;i++){
        preVal = preVal ^ a[i];
        insert(preVal);
    }

    int ans = 0;

    List* zero = head;
    int count1 = 0;
    while(zero){
        if(zero->data == 0){
            ans = ans + count1;
            allCases(1, count1+1);
        }
        zero = zero->link;
        count1++;
    }

    List* first = head;
    int i = 0;
    while(first){
        List* second = first->link;
        int counter = 0;
        int prevAns = ans;
        while(second){
            if(second->data == first->data){
                List* temp = first->link;
                int count = 1;
                int count2 = 0;
                while(temp->data != second->data || counter != count2){
                    if(temp->data == second->data){
                        count2++;
                    }
                    count++;
                    temp = temp->link;
                }
                ans = ans + (count-1);
                allCases(i+2, count+i+1);
            }
            if(prevAns != ans){
                counter++;
                prevAns = ans;
            }
            second = second->link;
        }
        first = first->link;
        i++;
    }

    cout<<ans<<endl;

    end = clock();
  
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

    return 0;
}