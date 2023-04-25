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
int flag[SIZE];
int top = -1;
int topn = -1;

void push(Node *addr, int k) {
	if(top == SIZE-1) {
		printf("\nStack is full");
		return;
	}
	arr[++top] = addr;
	flag[++topn] = k;
}

Node *pop() {
	if(top == -1) {
		printf("\nStack is empty");
		return NULL;
	}
	return arr[top--];
}

int popn(){
	if(topn == -1) {
		printf("\nStack is empty");
	}
	return flag[topn--];
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

void postorder(Node *r) {
	int f;
	while(1) {
		while(r) {
			push(r,-1);
			if(r->right)
				push(r->right, 1);
			r = r->left;
		}
		if(top!=-1) {
			r = pop();
			f = popn();
			while(f==-1) {
				printf("%d ", r->key);
				if(top==-1) {
					return;
				}
				r = pop();
				f = popn();
			}
		}
	}
}

int main() {
	int ch, n;
	do {
		printf("\n1. Insertion");
		printf("\n2. Postorder");
		printf("\n3. Exit");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);
		switch(ch) {
			case 1:
				printf("\nEnter the value to be inserted: ");
				scanf("%d", &n);
				insert(n);
				break;
			case 2:
				printf("\nPostorder Traversal\n");
				postorder(root);
				break;
			case 3:
				exit(1);
				break;
			default:
				printf("\nWrong Choice");
				break;
		}
	} while(ch != 0);
	return 0;
}
