#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

/*
Few assumptions,
1. Graph will not contain any negative values.
2. Visited Array will be global.
3. Max vertice of Graph can be of 100.
4. Adjacent List is also a linked list as for array, we need to return the size of the array too.
*/

int visited[SIZE]; //visited array

typedef struct adjList { //adjacent list
	int data;
	struct adjList *next;
}adjListNode;

typedef struct List { //main list
	int key;
	struct List *next; // next node
	struct adjList *list; // adjacent list
}listNode;

adjListNode *createAdjListNode(int key) {
	adjListNode *temp = (adjListNode*)malloc(sizeof(adjListNode));
	temp->data = key;
	temp->next = NULL;
	return temp;
}

listNode *createListNode(int key) {
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->next = NULL;
	node->list = NULL;
	int data;
	printf("\nEnter adjacent vertices for %d (Enter -1 to exit): ", node->key);
	scanf("%d", &data);
	if(data == -1) {
		return node;
	}
	node->list = createAdjListNode(data);
	adjListNode *tmp = node->list;
	while(1) {
		scanf("%d", &data);
		if(data == -1) {
			return node;
		}
		tmp->next = createAdjListNode(data);
		tmp = tmp->next;
	}
	return node;
}

listNode *createList() {
	listNode *head = NULL;
	int data;
	printf("\nEnter vertice(-1 to exit): ");
	scanf("%d", &data);
	if(data == -1) {
		return head;
	}
	head = createListNode(data);
	listNode *tmp = head;
	while(1) {
		printf("\nEnter vertice(-1 to exit): ");
		scanf("%d", &data);
		if(data == -1) {
			return head;
		}
		tmp->next = createListNode(data);
		tmp = tmp->next;
	}
	return head;
}

void printAdjList(adjListNode *head) {
	if(!head) {
		return;
	}
	printf("%d ", head->data);
	printAdjList(head->next);
}

void printlist(listNode *head) {
	if(!head) {
		return;
	}
	printf("\n%d -> ", head->key);
	printAdjList(head->list);
	printlist(head->next);
}

adjListNode* getadjlist(int key, listNode *head) {
	listNode *tmp = head;
	while(tmp) {
		if (key == tmp->key) {
			return tmp->list;
		}
		tmp = tmp->next;
	}
	return tmp->list;
}

void DFS(int key, listNode *head) {
	printf("%d ", key);
	visited[key] = 1;
	adjListNode *list = getadjlist(key, head);
	while(list) {
		if(visited[list->data] == 0) {
			DFS(list->data, head);
		}
		if(list->next == NULL) {
			return;
		}
		list = list->next;
	}
}

int main() {
	listNode *head = NULL;
	head = createList();
	//printlist(head);
	printf("\nDFS Traversal: ");
	DFS(head->key, head);
	return 0;
}
