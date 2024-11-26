#include "kruskal.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// MST�� ������� DFS�� �����Ͽ� TSP �ٻ� ��θ� ã�� �Լ�
void dfs(int vertex, Edge* mstEdges, int mstEdgeCount, bool* visited, Edge* tspResult, int* resultIndex, int* totalWeight) {
    visited[vertex] = true;
    for (int i = 0; i < mstEdgeCount; i++) {
        Edge edge = mstEdges[i];
        if (edge.src == vertex && !visited[edge.dest]) {
            tspResult[(*resultIndex)++] = edge;
            *totalWeight += edge.weight;
            dfs(edge.dest, mstEdges, mstEdgeCount, visited, tspResult, resultIndex, totalWeight);
        }
        else if (edge.dest == vertex && !visited[edge.src]) {
            tspResult[(*resultIndex)++] = edge;
            *totalWeight += edge.weight;
            dfs(edge.src, mstEdges, mstEdgeCount, visited, tspResult, resultIndex, totalWeight);
        }
    }
}

// MST�� ����� TSP �ٻ� ��� ���� �Լ�
int tspUsingMST(Graph* graph, Edge* tspResult) {
    // MST ���
    Edge* mstEdges = kruskalMST(graph);
    int mstEdgeCount = graph->vertices - 1;

    // �湮 ���θ� �����ϱ� ���� �迭�� ��Ÿ �ʿ��� ������
    bool visited[MAX_VERTICES] = { false };
    int totalWeight = 0;
    int resultIndex = 0;
    int currentVertex = 0; // ���� ������ 0���� ����

    // ���� �������� DFS ����
    dfs(currentVertex, mstEdges, mstEdgeCount, visited, tspResult, &resultIndex, &totalWeight);

    // �������� ���� �������� ���ƿ��� ���� �߰�
    for (int i = 0; i < graph->edges; i++) {
        Edge edge = graph->edge[i];
        if ((edge.src == currentVertex && edge.dest == 0) ||
            (edge.dest == currentVertex && edge.src == 0)) {
            tspResult[resultIndex++] = edge;
            totalWeight += edge.weight;
            break;
        }
    }

    free(mstEdges);
    return totalWeight;
}


// TSP �ٻ� �˰����� ����ϴ� �Լ� ���� ����
int main() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    initGraph(g, 4);
    int weight[100];
    Edge tspResult[MAX_VERTICES];  // TSP �ٻ� ��θ� ������ �迭

    // ����ġ �ʱ�ȭ
    for (int i = 0; i < 100; i++) {
        weight[i] = i;
    }
    initNode(g, weight);

    // TSP �ٻ� ��� ���
    int totalWeight = tspUsingMST(g, tspResult);

    // ��� ���
    printf("TSP �ٻ� ����� �� ����ġ: %d\n", totalWeight);
    for (int i = 0; i < g->vertices; i++) {
        printf("���۳�� %d, ������ %d, ����ġ %d\n", tspResult[i].src, tspResult[i].dest, tspResult[i].weight);
    }

    free(g);

    return 0;
}
