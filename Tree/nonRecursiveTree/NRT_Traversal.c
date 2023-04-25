#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct BTree {
	int key;
	struct BTree *left;
	struct BTree *right;
}Node;

Node *root = NULL;
Node *arr[SIZE];
int top = -1;

void push(Node *addr) {
	if(top == SIZE-1) {
		printf("\nStack is full");
		return;
	}
	arr[++top] = addr;
}

Node *pop() {
	if(top == -1) {
		printf("\nStack is empty");
		return NULL;
	}
	return arr[top--];
}

void insert(int n) {
	Node* x = (Node*)malloc(sizeof(Node));
	x->left = NULL;
	x->right = NULL;
	x->key = n;
	if(!root) {
		root = x;
		return;
	} else {
		Node *r1 = root;
		Node *r2;
		int c;
		while(r1) {
			r2 = r1;
			printf("\nEnter 0 to put %d to the left of %d",n,r1->key);
			printf("\nEnter 1 to put %d to the right of %d",n,r1->key);
			printf("\nEnter choice: ");
			scanf("%d", &c);
			if(c==0) {
				r1 = r1->left;
			} else {
				r1 = r1->right;
			}
		}
		if(c==0) {
			r2->left = x;
		} else {
			r2->right = x;
		}
	}
	return;
}

void preorder(Node *r) {
	while(1){ 
		while(r){
			printf("%d ",r->key); 
			if(r->right) 
				push(r->right);
			r=r->left; 
		} 
		if(top!=-1)
			r=pop();
		else
			return;
	} 
}

void inorder(Node *cur) {
	while(1) {
		if(cur){
			push(cur);
			cur = cur->left;
		} else {
			if(top != -1) {
				cur = pop();
				printf("%d ", cur->key);
				cur = cur->right;
			} else {
				return;
			}
		}
	}
}

int main() {
	int ch, n;
	do {
		printf("\n1. Insertion");
		printf("\n2. Preorder");
		printf("\n3. Inorder");
		printf("\n4. Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
				printf("\nEnter the value to be inserted: ");
				scanf("%d", &n);
				insert(n);
				break;
			case 2:
				printf("\nPreorder Traversal\n");
				preorder(root);
				break;
			case 3:
				printf("\nInorder Traversal\n");
				inorder(root);
				break;
			case 4:
				exit(1);
				break;
			default:
				printf("\nWrong Choice");
				break;
		}
	} while(ch != 0);
	return 0;
}
