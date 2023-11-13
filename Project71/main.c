
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 200
#define INF 1000000

//(1)인접 행렬을 이용하여 구현
typedef struct GraphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];

}GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[]) 
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) { //아직 방문하지 못했고, min가 거리보다 적을때
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

// 현재 상태 출력 함수
void print_status(GraphType* g) { 
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF) //아직 방문하지 않았을때
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf("Found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");

}

// 최단 경로 찾기 함수
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) // 초기화
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; //시작 정점 방문 표시 

	distance[start] = 0;

	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}

	int sorted_vertices[MAX_VERTICES];

	for (i = 0; i < g->n; i++) {
		sorted_vertices[i] = i;
	}

	for (i = 0; i < g->n - 1; i++) {
		for (int j = 0; j < g->n - i - 1; j++) {
			if (distance[sorted_vertices[j]] > distance[sorted_vertices[j + 1]]) {
				int temp = sorted_vertices[j];
				sorted_vertices[j] = sorted_vertices[j + 1];
				sorted_vertices[j + 1] = temp;
			}
		}
	}
	// 정렬된 결과 출력
	for (i = 0; i < g->n; i++) {
		printf("%d ", sorted_vertices[i]+1);
	}

	
}


int main(void) {

	GraphType g = { 10,
	{{0 ,3 ,INF,INF,INF,11 ,12 ,INF,INF,INF},
	{3 ,0 ,5 ,4 ,1 ,7 ,8 ,INF,INF,INF},
	{INF,5 ,0 ,2 ,INF,INF,6 ,5 ,INF,INF},
	{INF,4 ,2 ,0 ,13 ,INF,INF,14 ,INF,16 },
	{INF,1 ,INF,13 ,0 ,9 ,INF,INF,18 ,17 },
	{11 ,7 ,INF,INF,9 ,0 ,INF,INF,INF,INF},
	{11 ,8 ,6 ,INF,INF,INF,0 ,13 ,INF,INF},
	{INF,INF,5 ,14 ,INF,INF,13 ,0 ,INF,15 },
	{INF,INF,INF,INF,18 ,INF,INF,INF,0 ,10},
	{INF,INF,INF,16 ,17,INF,INF,15 ,10,0 } }
	};
	printf("Dijkstra Algorithm (1)\n");
	shortest_path(&g, 0);
	return 0;
}

