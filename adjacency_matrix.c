#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define ERROR -9999999

int getIndex(int data, int vertices[SIZE], int n) {
	int i;
	for(i=0; i<n; i++) {
		if(data == vertices[i]) {
			return i;
		}
	}
}

void enqueue(int queue[SIZE], int *top, int data) {
	if(*top == SIZE - 1) {
		return;
	}
	queue[++(*top)] = data;
}

int dequeue(int queue[SIZE], int *top) {
	if(*top == -1) {
		return ERROR;
	}
	int data = queue[0];
	int i;
	for(i=1; i<=(*top); i++) {
		queue[i-1] = queue[i];
	}
	(*top)--;
	return data;
}

void printQueue(int queue[SIZE], int *top, int vertices[SIZE]) {
	if(*top == -1) {
		return;
	}
	int i;
	printf("\n");
	for(i=0; i<=(*top); i++) {
		printf("%d ", vertices[queue[i]]);
	}
}

void bfs(int a[SIZE][SIZE], int n, int vertices[SIZE]) {
	int top = -1;
	int queue[SIZE];
	int visited[SIZE] = {0};
	int u = 0, i;
	visited[u] = 1;
	printf("\nStarting vertex : %d\n", vertices[u]);
	printf("\nBFS Traversal: ");
	//BFS Implementation as per Horowitz and Sahni
	do {
		for(i=0; i<n; i++) {
			if(a[u][i] == 1 && visited[i] == 0) {
				enqueue(queue, &top, i);
				visited[i] = 1;
			}
		}
		printf("%d ", vertices[u]);
		if(top == -1)
			return;
		u = dequeue(queue, &top);
	} while(1);
}

void createAdjacencyMatrix(int a[SIZE][SIZE], int n, int vertices[SIZE]) {
	int i, j;
	printf("\nEnter the elements of vertices: ");
	for(i=0; i<n; i++) {
		scanf("%d", &vertices[i]);
	}
	int x, y;
	printf("\nEnter the edges: ");
	while(1) {
		scanf("%d", &x);
		scanf("%d", &y);
		if(x == -1 && y == -1) {
			break;
		}
		x = getIndex(x, vertices, n);
		y = getIndex(y, vertices, n);
		a[x][y] = 1;
	}
	printf("\n");
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int a[SIZE][SIZE], n;
	printf("\nCreating Adjacency Matrix of the Graph.\nEnter number of vertices: ");
	scanf("%d", &n);
	int v[SIZE];
	createAdjacencyMatrix(a, n, v);
	bfs(a, n, v);
	return 0;
}
