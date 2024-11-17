#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

// 간선 비교 함수 (가중치 오름차순 정렬용)
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Union-Find: 부모 노드 찾기
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union-Find: 두 집합 합치기
void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    }
    else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    }
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Kruskal의 MST 알고리즘
void kruskalMST(Graph* graph) {
    int vertices = graph->vertices;
    Edge result[MAX_EDGES];  // 최종 MST에 포함될 간선 배열
    int e = 0;  // result 배열의 인덱스
    int i = 0;  // 정렬된 간선 배열의 인덱스

    // 간선을 가중치 순으로 정렬
    qsort(graph->edge, graph->edges, sizeof(graph->edge[0]), compareEdges);

    // Union-Find용 Subset 초기화
    Subset* subsets = (Subset*)malloc(vertices * sizeof(Subset));
    for (int v = 0; v < vertices; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // 간선을 하나씩 확인하며 MST에 포함
    while (e < vertices - 1 && i < graph->edges) {
        Edge nextEdge = graph->edge[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        // 사이클이 생기지 않으면 MST에 추가
        if (x != y) {
            result[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    // 결과 출력
    printf("최소 신장 트리의 간선:\n");
    for (i = 0; i < e; ++i)
        printf("노드 %d - 노드 %d: 가중치 %d\n", result[i].src, result[i].dest, result[i].weight);

    free(subsets);
}

// 실행 함수
void run() {
    int vertices, edges = 0;

    printf("노드 개수를 입력하세요: ");
    scanf_s("%d", &vertices);

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->edges = 0;

    printf("각 노드 쌍의 가중치를 입력하세요 (연결되지 않은 경우 -1 입력):\n");
    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {
            int weight;
            printf("노드 %d - 노드 %d: ", i, j);
            scanf_s("%d", &weight);
            if (weight != -1) {
                graph->edge[edges].src = i;
                graph->edge[edges].dest = j;
                graph->edge[edges].weight = weight;
                edges++;
            }
        }
    }

    graph->edges = edges;

    kruskalMST(graph);

    free(graph);
}
