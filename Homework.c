#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
#define true 1==1
#define false 1!=1
typedef int bool;

struct Stack {
    int head;
    struct Stack* pNext;
};
 
struct Stack* addNode(struct Stack* stack, int node) {
	struct Stack* newNode = malloc(sizeof(struct Stack));
    newNode->head = node;
	if(stack == NULL)
		newNode->pNext = NULL;
	else 
		newNode->pNext = stack;
	return newNode;
}

struct Stack* delNode(struct Stack *stack) {
	if(stack != NULL){
		struct Stack *temp = stack->pNext;
		free(stack);
		return temp;
	}
	return NULL;
}

struct Graf {
	int vertices;
	bool *visited;
	int **ms;
	struct Stack *stack;
};

struct Graf* initGraf(int ms[][SIZE], int v) {
	struct Graf *graf = malloc(sizeof(struct Graf));
    graf->vertices = v;
    graf->visited = malloc(v * sizeof(bool));
    graf->ms = malloc(v * sizeof(int*));
    for (int i = 0; i < v; ++i){
        graf->ms[i] = (int*)calloc(sizeof(int), v);
        graf->visited[i] = false;
    }
	for(int i = 0; i < v; ++i) {
		for(int j = 0; j < v; ++j) {
			*((*(graf->ms + i)) + j) = ms[i][j];
		}
	}
	graf->stack = NULL;
    return graf;
}

// task 1
void tgd(struct Graf *graf, int i) {
	if(graf->visited[i] != true){
		printf("%d ", i);
		graf->visited[i] = true;
		for(int r = 0; r < graf->vertices; ++r){
			if(graf->ms[i][r] == 1 && graf->visited[r] != true){
				graf->stack = addNode(graf->stack, r);
			}
		}
		i = graf->stack->head;
		graf->stack = delNode(graf->stack);
		tgd(graf, i);
	}
}

//task 2
void tgd1(struct Graf *graf, int v, int s) {
	if(s < graf->vertices){
		if(graf->ms[v][s] == 1 && graf->visited[s] != true){
			graf->visited[s] = true;
		}
		tgd1(graf, v, s+1);
	}
}

void printGraf(struct Graf *graf){
	for(int i = 0; i < graf->vertices; ++i){
		for(int j = 0; j < graf->vertices; ++j){
			graf->visited[j] = 0;
		}
		int k = 0;
		tgd1(graf, i, 0);
		for(int j = 0; j < graf->vertices; ++j){
			if(graf->visited[j])
				k++;
		}
		printf("%d -> %d \n", i, k);
	}
}


int main() {
   
   int  matrix[SIZE][SIZE] = {{0, 1, 1, 1, 0},
							  {1, 0, 1, 0, 0},
							  {1, 1, 0, 0, 1},
							  {1, 0, 0, 0, 0},
							  {0, 0, 1, 0, 0}};
	struct Graf *graf = initGraf(matrix, SIZE);
	
	// task 1
	tgd(graf, 0);
	
	printf("\n\n");
	//task 2
	printGraf(graf);
   
	
    return 0;
}
