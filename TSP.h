#ifndef TSP_H
#define TSP_H

#include "kruskal.h"

#define MAX_VERTICES 100

// 함수 선언

// MST를 기반으로 DFS를 수행하여 TSP 근사 경로를 찾는 함수
void dfs(int vertex, Edge* mstEdges, int mstEdgeCount, bool* visited, Edge* tspResult, int* resultIndex, int* totalWeight);

// MST를 사용한 TSP 근사 경로 생성 함수
int tspUsingMST(Graph* graph, Edge* tspResult);

#endif
