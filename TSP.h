#ifndef TSP_H
#define TSP_H

#include "kruskal.h"

#define MAX_VERTICES 100

// �Լ� ����

// MST�� ������� DFS�� �����Ͽ� TSP �ٻ� ��θ� ã�� �Լ�
void dfs(int vertex, Edge* mstEdges, int mstEdgeCount, bool* visited, Edge* tspResult, int* resultIndex, int* totalWeight);

// MST�� ����� TSP �ٻ� ��� ���� �Լ�
int tspUsingMST(Graph* graph, Edge* tspResult);

#endif
