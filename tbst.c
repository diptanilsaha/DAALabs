#include <stdio.h>
#include <stdlib.h>
 
 
typedef struct TBT{
	int data;
	struct TBT *lptr, *rptr;
	int lbit, rbit;
}Node;
 
Node *createNode(int data) {
	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->lptr = NULL;
	node->rptr = NULL;
	node->lbit = 1;
	node->rbit = 1;
	return node;
}
 
Node *createDNode() {
	Node *node = createNode(999999);
	node->lptr = node;
	node->rptr = node;
	node->lbit = 1; 
	node->rbit = 0;
	return node;
}
 
//for thread, bit value = 1
//for normal, bit value = 0
 
void insertNode(Node *root, Node *temp) {
	//root is dummynode, temp is the node which will be inserted
	//inserting root node in the tree
	if(root->lptr == root && root->rptr == root) {
		temp->lptr = root->lptr;
		temp->rptr = root->rptr;
		temp->lbit = root->lbit;
		temp->rbit = 1;
		root->lptr = temp;
		root->lbit = 0;
		printf("\nNode Inserted");
		return;
	}
	//inserting nodes in the tree
	//curr is the binary tree node
	Node *curr = root->lptr;
	while(1) {
		if(curr->data > temp->data) {
			if(curr->lbit == 1) {
				temp->lptr = curr->lptr;
				temp->rptr = curr;
				curr->lbit = 0;
				curr->lptr = temp;
				printf("\nNode Inserted");
				return;
			} else {
				curr = curr->lptr;
			}
		}
		if(curr->data < temp->data) {
			if(curr->rbit == 1) {
				temp->rptr = curr->rptr;
				temp->lptr = curr;
				curr->rbit = 0;
				curr->rptr = temp;
				printf("\nNode Inserted");
				return;
			} else {
				curr = curr->rptr;
			}
		}
	}
}
 
void print(Node *node) {
	printf("%d ",node->data);
	return;
}
 
Node *inorderSuccesor(Node *node) {
	if(node->rbit == 1)
		return node->rptr;
	if(node->rbit == 0) {
		node = node->rptr;
		while(!(node->lbit)){
			node = node->lptr;
		}
		return node;
	}
}
 
void traversal(Node *dummyNode) {
	printf("\nTREE: ");
	Node *ptr = dummyNode;
	Node *root = ptr->lptr;
	Node *temp = root;
	while(temp->lbit == 0) {
		temp = temp->lptr;
	}
	for(; temp != ptr; temp = inorderSuccesor(temp))
	print(temp);
}
 
int main() {
	Node *dummyNode = createDNode();
	int ch, data;
	while(1) {
		printf("\n1. Insert Node");
		printf("\n2. Tree Traversal");
		printf("\n3. Exit");
		printf("\nEnter choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
				printf("\nEnter data: ");
				scanf("%d", &data);
				insertNode(dummyNode, createNode(data));
				break;
			case 2:
				traversal(dummyNode);
				break;
			case 3:
				exit(1);
				break;
			default:
				printf("\nWrong choice!");
				break;
		}
	}
	return 0;
}
