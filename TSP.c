#include "kruskal.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// MST를 기반으로 DFS를 수행하여 TSP 근사 경로를 찾는 함수
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

// MST를 사용한 TSP 근사 경로 생성 함수
int tspUsingMST(Graph* graph, Edge* tspResult) {
    // MST 계산
    Edge* mstEdges = kruskalMST(graph);
    int mstEdgeCount = graph->vertices - 1;

    // 방문 여부를 추적하기 위한 배열과 기타 필요한 변수들
    bool visited[MAX_VERTICES] = { false };
    int totalWeight = 0;
    int resultIndex = 0;
    int currentVertex = 0; // 시작 정점은 0으로 설정

    // 시작 정점에서 DFS 시작
    dfs(currentVertex, mstEdges, mstEdgeCount, visited, tspResult, &resultIndex, &totalWeight);

    // 마지막에 시작 지점으로 돌아오는 간선 추가
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


// TSP 근사 알고리즘을 사용하는 함수 사용법 예시
int main() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    initGraph(g, 4);
    int weight[100];
    Edge tspResult[MAX_VERTICES];  // TSP 근사 경로를 저장할 배열

    // 가중치 초기화
    for (int i = 0; i < 100; i++) {
        weight[i] = i;
    }
    initNode(g, weight);

    // TSP 근사 경로 계산
    int totalWeight = tspUsingMST(g, tspResult);

    // 결과 출력
    printf("TSP 근사 경로의 총 가중치: %d\n", totalWeight);
    for (int i = 0; i < g->vertices; i++) {
        printf("시작노드 %d, 종료노드 %d, 가중치 %d\n", tspResult[i].src, tspResult[i].dest, tspResult[i].weight);
    }

    free(g);

    return 0;
}
