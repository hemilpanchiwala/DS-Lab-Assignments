/**
 * @file tree.cpp
 * @author Hemil Panchiwala
 * @brief This program creates binary search tree, AVL tree and Red-Black Tree.
 * @date 2019-08-20
 *
 * 
 */
#include <bits/stdc++.h>
#include <iostream>
#include <time.h>

using namespace std;

/**
 * @brief This is simple class defined for Binary Search Tree
 * 
 */
class BST {
public:
  int data;
  BST* left;
  BST* right;
  int height;
  int balance;
};

/**
 * @brief This is simple class defined for AVL Tree
 * 
 */
class AVL {
  public:
    int data;
    AVL* left;
    AVL* right;
    int height;
};

/**
 * @brief This is simple class defined for Red-Black Tree
 * 
 */
class RBTree {
  public:
    int data;
    RBTree *parent;
    char color;
    RBTree *left;
    RBTree *right;
    int height;
};

/**
 * @brief This method returns maximum of two numbers
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  
  
/**
 * @brief This method returns height of any node in AVL Tree
 * 
 * @param avlNode 
 * @return int 
 */
int height(AVL *avlNode)  
{  
    if (avlNode == NULL)  
        return 0;  
    return avlNode->height;  
} 

/**
 * @brief This method returns the balance factor of particular node
 * 
 * @param avlNode 
 * @return int 
 */
int getBalance(AVL *avlNode)  
{  
    if (avlNode == NULL)  
        return 0;  
    return height(avlNode->left) - height(avlNode->right);  
}  

/**
 * @brief This method performs the right rotation of nodes to make AVL Tree
 * 
 * @param avlNode 
 * @return AVL* 
 */
AVL *rightRotate(AVL *avlNode)  
{  
    AVL *avlNodeLeft = avlNode->left;  
    AVL *node = avlNodeLeft->right;  
  
    avlNodeLeft->right = avlNode;  
    avlNode->left = node;  
  
    avlNode->height = max(height(avlNode->left), 
                    height(avlNode->right)) + 1;  
    avlNodeLeft->height = max(height(avlNodeLeft->left), 
                    height(avlNodeLeft->right)) + 1;  
  
    return avlNodeLeft;  
}  

/**
 * @brief This method performs the left rotation of nodes to make AVL Tree
 * 
 * @param avlNode 
 * @return AVL* 
 */
AVL *leftRotate(AVL *avlNode)  
{  
    AVL *avlNodeRight = avlNode->right;  
    AVL *node = avlNodeRight->left;  

    avlNodeRight->left = avlNode;  
    avlNode->right = node;  

    avlNode->height = max(height(avlNode->left),     
                    height(avlNode->right)) + 1;  
    avlNodeRight->height = max(height(avlNodeRight->left),  
                    height(avlNodeRight->right)) + 1;  

    return avlNodeRight;  
}

/**
 * @brief This method inserts a node in AVL Tree
 * 
 * @param avlNode 
 * @param data 
 * @return AVL* 
 */
AVL* insert(AVL* avlNode, int data)  
{  
    if (avlNode == NULL) {
      AVL* node = new AVL(); 
	    node->data = data; 
	    node->left = NULL; 
	    node->right = NULL; 
	    node->height = 1;
      return node;
    }

	if (data < avlNode->data) 
		avlNode->left = insert(avlNode->left, data); 
	else if (data > avlNode->data) 
		avlNode->right = insert(avlNode->right, data); 
	else
		return avlNode; 

	avlNode->height = 1 + max(height(avlNode->left), 
						height(avlNode->right)); 

	int balance = getBalance(avlNode); 

	if (balance > 1 && data < avlNode->left->data) 
		return rightRotate(avlNode); 

	if (balance < -1 && data > avlNode->right->data) 
		return leftRotate(avlNode); 

	if (balance > 1 && data > avlNode->left->data) 
	{ 
		avlNode->left = leftRotate(avlNode->left); 
		return rightRotate(avlNode); 
	} 

	if (balance < -1 && data < avlNode->right->data) 
	{ 
		avlNode->right = rightRotate(avlNode->right); 
		return leftRotate(avlNode); 
	} 

	return avlNode;  
}

/**
 * @brief This method returns the height of any node in BST Tree
 * 
 * @param bstNode 
 * @return int 
 */
int height(BST *bstNode)  
{  
    if (bstNode == NULL)  
        return 0;  
    return bstNode->height;  
} 

/**
 * @brief This method returns the balance factor of any node in BST Tree
 * 
 * @param bstNode 
 * @return int 
 */
int getBalance(BST *bstNode)  
{  
    if (bstNode == NULL)  
        return 0;  
    return height(bstNode->left) - height(bstNode->right);  
}  

/**
 * @brief This method inserts a node in BST Tree
 * 
 * @param bstNode 
 * @param data 
 * @return BST* 
 */
BST* insert(BST* bstNode, int data){


  if(bstNode == NULL){
    BST* node = new BST();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1 + max(height(node->left), height(node->right));
    node->balance = getBalance(node);
    return node;
  }

  if(data < bstNode->data){
    bstNode->left = insert(bstNode->left, data);
  }else if(data > bstNode->data){
    bstNode->right = insert(bstNode->right, data);
  }

  bstNode->height = 1 + max(height(bstNode->left), height(bstNode->right));
  bstNode->balance = getBalance(bstNode);

  return bstNode;

}

/**
 * @brief This method prints the path from a node to all the leaves of BST Tree
 * 
 * @param bstNode 
 * @param arr 
 * @param length 
 */
void printPaths(BST* bstNode, int* arr, int length){

  if(bstNode == NULL){
    return;
  }

  arr[length] = bstNode->data;
  length++;

  if((bstNode->left == NULL) && (bstNode->right == NULL)){
    for(int i=0;i<length-1;i++){
      cout<<arr[i]<<"->";
    }
    cout<<arr[length-1];
    cout<<endl;
  }else{
    printPaths(bstNode->left, arr, length);
    printPaths(bstNode->right, arr, length);
  }

}

/**
 * @brief This method returns all the paths of the BST tree
 * 
 * @param bstNode 
 */
void getPaths(BST* bstNode)
{
  if(bstNode == NULL){
    return;
  }

	int arr[1000];
	printPaths(bstNode, arr, 0);
  getPaths(bstNode->left);
  getPaths(bstNode->right);
}

/**
 * @brief This method prints the path from a node to all the leaves of AVL Tree
 * 
 * @param avlNode 
 * @param arr 
 * @param length 
 */
void printPaths(AVL* avlNode, int* arr, int length){

  if(avlNode == NULL){
    return;
  }

  arr[length] = avlNode->data;
  length++;

  if((avlNode->left == NULL) && (avlNode->right == NULL)){
    for(int i=0;i<length-1;i++){
      cout<<arr[i]<<"->";
    }
    cout<<arr[length-1];
    cout<<endl;
  }else{
    printPaths(avlNode->left, arr, length);
    printPaths(avlNode->right, arr, length);
  }

}

/**
 * @brief This method returns all the paths of the AVL tree
 * 
 * @param avlNode 
 */
void getPaths(AVL* avlNode)
{
  if(avlNode == NULL){
    return;
  }

	int arr[1000];
	printPaths(avlNode, arr, 0);
  getPaths(avlNode->left);
  getPaths(avlNode->right);
}

/**
 * @brief Vector of BST Tree
 * 
 */
vector<int> arrBST;

/**
 * @brief This method stores the BST Tree in a vector
 * 
 * @param bstNode 
 * @return vector<int> 
 */
vector<int> getBST(BST* bstNode){
  if(bstNode != NULL){
    getBST(bstNode->left);
    arrBST.push_back(bstNode->data);
    getBST(bstNode->right);
  }
  return arrBST;
}

/**
 * @brief This method prints the inorder traversal of BST Tree
 * 
 * @param bstNode 
 */
void BSTinOrder(BST* bstNode){
  if(bstNode != NULL){
    BSTinOrder(bstNode->left);
    cout<<bstNode->data<<" ";
    BSTinOrder(bstNode->right);
  }
}

/**
 * @brief This method prints the BST Tree with proper indentation
 * 
 * @param bstNode 
 * @param space 
 */
void printBSTTree(BST* bstNode, int space){
  if(bstNode != NULL){
    for(int i=0;i<space;i++){
      cout<<"      ";
    }
    if(bstNode->left == 0 && bstNode->right == 0){
      cout<<bstNode->data<<endl;
    }else{
      cout<<bstNode->data<<"["<<abs(bstNode->balance)<<"]"<<endl;
    }
    printBSTTree(bstNode->left, space+1);
    printBSTTree(bstNode->right, space+1);
  }
}

/**
 * @brief This method prints the inorder traversal of AVL Tree
 * 
 * @param avlNode 
 */
void AVLinOrder(AVL* avlNode){
  if(avlNode != NULL){
    AVLinOrder(avlNode->left);
    cout<<avlNode->data<<" ";
    AVLinOrder(avlNode->right);
  }
}

/**
 * @brief This method prints the AVL Tree with proper indentation
 * 
 * @param avlNode 
 * @param space 
 */
void printAVLTree(AVL* avlNode, int space){
  if(avlNode != NULL){
    for(int i=0;i<space;i++){
      cout<<"      ";
    }
    int balance = getBalance(avlNode);
    if(avlNode->left == 0 && avlNode->right == 0){
      cout<<avlNode->data<<endl;
    }else{
      cout<<avlNode->data<<"["<<abs(balance)<<"]"<<endl;
    }
    printAVLTree(avlNode->left, space+1);
    printAVLTree(avlNode->right, space+1);
  }
}

RBTree *root = NULL;   
RBTree *q = NULL;

/**
 * @brief This method performs left rotation of any node in RBTree
 * 
 * @param rbNode 
 */
void leftrotate(RBTree *rbNode)
{
  if(rbNode->right==NULL){
    return;
  }else{
    RBTree *rbNodeRight=rbNode->right;

    if(rbNodeRight->left != NULL){
      rbNode->right=rbNodeRight->left;
        rbNodeRight->left->parent=rbNode;
    }else{
      rbNode->right=NULL;
    }

    if(rbNode->parent!=NULL){
      rbNodeRight->parent=rbNode->parent;
    }

    if(rbNode->parent==NULL){
      root = rbNodeRight;
    }else{
      if(rbNode==rbNode->parent->left)
              rbNode->parent->left=rbNodeRight;
          else
              rbNode->parent->right=rbNodeRight;
    }

    rbNodeRight->left=rbNode;
    rbNode->parent=rbNodeRight;
  }
}

/**
 * @brief This method performs right rotation of any node in RBTree
 * 
 * @param rbNode 
 */
void rightrotate(RBTree *rbNode){
  if (rbNode->left == NULL)
    return;
  else {
      RBTree* rbNodeLeft = rbNode->left;
      if (rbNodeLeft->right != NULL) {
          rbNode->left = rbNodeLeft->right;
          rbNodeLeft->right->parent = rbNode;
      }
      else
          rbNode->left = NULL;
      if (rbNode->parent != NULL)
          rbNodeLeft->parent = rbNode->parent;
      if (rbNode->parent == NULL)
          root = rbNodeLeft;
      else {
          if (rbNode == rbNode->parent->left)
              rbNode->parent->left = rbNodeLeft;
          else
              rbNode->parent->right = rbNodeLeft;
      }
      rbNodeLeft->right = rbNode;
      rbNode->parent = rbNodeLeft;
  }
}
  
/**
 * @brief This method performs the fixing of color and rotation after insertion of a node in RB Tree
 * 
 * @param rbNode 
 */
void insertfix(RBTree *rbNode){
  RBTree* u;
  if (root == rbNode) {
      rbNode->color = 'b';
      return;
  }
  while (rbNode->parent != NULL && rbNode->parent->color == 'r') {
      RBTree* g = rbNode->parent->parent;
      if (g->left == rbNode->parent) {
          if (g->right != NULL) {
              u = g->right;
              if (u->color == 'r') {
                  rbNode->parent->color = 'b';
                  u->color = 'b';
                  g->color = 'r';
                  rbNode = g;
              }
          }
          else {
              if (rbNode->parent->right == rbNode) {
                  rbNode = rbNode->parent;
                  leftrotate(rbNode);
              }
              rbNode->parent->color = 'b';
              g->color = 'r';
              rightrotate(g);
          }
      }
      else {
          if (g->left != NULL) {
              u = g->left;
              if (u->color == 'r') {
                  rbNode->parent->color = 'b';
                  u->color = 'b';
                  g->color = 'r';
                  rbNode = g;
              }
          }
          else {
              if (rbNode->parent->left == rbNode) {
                  rbNode = rbNode->parent;
                  rightrotate(rbNode);
              }
              rbNode->parent->color = 'b';
              g->color = 'r';
              leftrotate(g);
          }
      }
      root->color = 'b';
  }     
}

/**
 * @brief This method inserts a node in RB Tree
 * 
 * @param z 
 */
void insert(int z)
{
    RBTree *p, *q;
    RBTree* t = new RBTree;
    t->data = z;
    t->left = NULL;
    t->right = NULL;
    t->color = 'r';
    p = root;
    q = NULL;

    if (root == NULL) {
        root = t;
        t->parent = NULL;
    }
    else {

        while (p != NULL) {
            q = p;
            if (p->data < t->data)
                p = p->right;
            else
                p = p->left;
        }

        t->parent = q;
        if (q->data < t->data)
            q->right = t;
        else
            q->left = t;
    }
    insertfix(t);
}

/**
 * @brief This method returns height of node in RB Tree
 * 
 * @param rbNode
 * @return int 
 */
int getHeight(RBTree* rbNode){

  if(rbNode == NULL){
    return 0;
  }

  if(rbNode->left == NULL && rbNode->right == NULL){
    return 1;
  }

  if(rbNode != NULL){
    int height1 = getHeight(rbNode->left);
    int height2 = getHeight(rbNode->right);        
    rbNode->height = 1 + max(height1, height2); 
  }
  return rbNode->height;
}

/**
 * @brief This method returns the balance factor of node in RB Tree
 * 
 * @param rbNode
 * @return int 
 */
int getBalance(RBTree *rbNode)  
{  
    if (rbNode == NULL)  
        return 0;  
    return getHeight(rbNode->left) - getHeight(rbNode->right);  
}  

/**
 * @brief This method prints the RB Tree with proper indentation
 * 
 * @param rbNode 
 * @param space 
 */
void printRBTree(RBTree *rbNode, int space)
{
     if(root==NULL)
     {
          cout<<"\nEmpty Tree.";
          return ;
     }
     if(rbNode!=NULL)
     {
       for(int i=0;i<space;i++){
      cout<<"      ";
    }
      int balance = getBalance(rbNode);
       if(rbNode->left == NULL && rbNode->right == NULL){
         if(rbNode->color == 'b'){
           cout<<rbNode->data<<"[BLACK]"<<endl;
         }else{
           cout<<rbNode->data<<"[RED]"<<endl;
         }
       }else{
        if(rbNode->color == 'b'){
          cout<<rbNode->data<<"["<<abs(balance)<<"]"<<"[BLACK]"<<endl;
        }else{
          cout<<rbNode->data<<"["<<abs(balance)<<"]"<<"[RED]"<<endl;
        }      
       } 
    if(rbNode->left)
    {
      printRBTree(rbNode->left, space+1);
    }
    
    if(rbNode->right)
    {
      printRBTree(rbNode->right, space+1);
    }
    
  }
}

/**
 * @brief This method prints the inorder traversal of RB Tree
 * 
 * @param rbNode 
 */
void RBTreeInOrder(RBTree* rbNode){

  if(rbNode != NULL){
    RBTreeInOrder(rbNode->left);
    cout<<rbNode->data<<" ";
    RBTreeInOrder(rbNode->right);
  }

}

/**
 * @brief This method prints the path from a node to all the leaves of AVL Tree
 * 
 * @param rbNode 
 * @param arr 
 * @param size 
 */
void printPaths(RBTree* rbNode, int* arr, int size){

  if(rbNode == NULL){
    return;
  }

  arr[size] = rbNode->data;
  size++;

  if((rbNode->left == NULL) && (rbNode->right == NULL)){
    for(int i=0;i<size-1;i++){
      cout<<arr[i]<<"->";
    }
    cout<<arr[size-1];
    cout<<endl;
  }else{
    printPaths(rbNode->left, arr, size);
    printPaths(rbNode->right, arr, size);
  }

}

/**
 * @brief This method returns all the paths of the RB tree
 * 
 * @param rbNode 
 */
void getPaths(RBTree* rbNode)
{
  if(rbNode == NULL){
    return;
  }

	int arr[1000];
	printPaths(rbNode, arr, 0);
  getPaths(rbNode->left);
  getPaths(rbNode->right);
}

/**
 * @brief This method creates a menu for insertion in Binary Search Tree and RB Tree and 
 * creates a AVL Tree from Binary Search Tree. This method prints inorder of all trees and even displays all the paths in tree 
 * and prints the nodes of tree with proper indentation.
 * 
 * @return int 
 */
int main(){
  clock_t start, end;
  double cpu_time_used;

  start = clock();

  BST* rootBST = NULL;

  vector<int> BSTTree;
  AVL* rootAVL = NULL;
  
  while(1){
    cout<<"1. To insert a node in the BST and in the red-black tree "<<endl;
    cout<<"2. To create AVL tree from the inorder traversal of the BST "<<endl;
    cout<<"3. To print the inorder traversal of the BST/AVL/red-black tree "<<endl;
    cout<<"4. To display all the paths in the BST/AVL tree/red-black tree  "<<endl;
    cout<<"5. To print the BST/AVL tree/red-black Tree in the terminal using level-wise indentation (print color for red-black tree) "<<endl;
    cout<<"6. Exit "<<endl;

    int option;
    cin>>option;
      int option3;
      int option4;
    switch(option){
      case 1:
        int p;
        cout<<"Enter the value of the node to be inserted: "<<endl;
        cin>>p;
        rootBST = insert(rootBST, p);
        insert(p);
        break;

      case 2:
        BSTTree = getBST(rootBST);

        for(int i=0;i<BSTTree.size();i++){
          rootAVL = insert(rootAVL, BSTTree[i]);
        }
        cout<<"AVL Tree created successfully"<<endl;
        break;

      case 3:
        cout<<"1. BST Tree"<<endl;
        cout<<"2. AVL Tree"<<endl;
        cout<<"3. Red-Black Tree"<<endl;
        cin>>option3;
        switch(option3){
          case 1:
            BSTinOrder(rootBST);
            cout<<endl;
            break;

          case 2:
            AVLinOrder(rootAVL);
            cout<<endl;
            break;

          case 3:
            RBTreeInOrder(root);
            cout<<endl;
            break;
        }
        break;

      case 4:
        cout<<"1. BST Tree"<<endl;
        cout<<"2. AVL Tree"<<endl;
        cout<<"3. Red-Black Tree"<<endl;
        int option3;
        cin>>option3;
        switch(option3){
          case 1:
            getPaths(rootBST);
            break;

          case 2:
            getPaths(rootAVL);
            break;

          case 3:
            getPaths(root);
            break;
        }
        break;

      case 5:
        cout<<"1. BST Tree"<<endl;
        cout<<"2. AVL Tree"<<endl;
        cout<<"3. Red-Black Tree"<<endl;
        
        cin>>option4;
        switch(option4){
          case 1:
            printBSTTree(rootBST, 0);
            break;

          case 2:
            printAVLTree(rootAVL, 0);
            break;

          case 3:
            printRBTree(root, 0);
            break;
        }
        break;

      case 6:
        goto help;
        break;

      default:
        cout<<"Enter valid choice"<<endl;
    }
    
  }

  help:

  end = clock();
  
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%f\n", cpu_time_used);

  return 0;
}
