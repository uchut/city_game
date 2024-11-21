#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

// 간선 비교 함수 
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

//  부모 노드 찾기
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

//  두 집합 합치기
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

void initGraph(Graph* g, int v)
{
    g->vertices = v;
    g->edges = 0;
    int maxedges = 0;
    for (int i = 0; i < v; i++)
    {
        for (int j = i + 1; j < v; j++)
        {
            g->edge[g->edges].src = i;
            g->edge[g->edges].dest = j;
            g->edges++;
        }
    }
}

void initNode(Graph* g, int* n)
{
    int eNode = 0;
    for (int i = 0; i < g->edges; i++)
    {
        g->edge[i].weight = n[i];
        if (n[i] == -1)
        {
            eNode++;
        }
        g->edges = g->edges - eNode;
    }
}

// Kruskal의 MST 알고리즘
Edge* kruskalMST(Graph* graph) {
    int vertices = graph->vertices;
    Edge result[MAX_EDGES];  
    int e = 0;
    int i = 0; 

    
    qsort(graph->edge, graph->edges, sizeof(graph->edge[0]), compareEdges);

    
    Subset* subsets = (Subset*)malloc(vertices * sizeof(Subset));
    for (int v = 0; v < vertices; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    
    while (e < vertices - 1 && i < graph->edges) {
        Edge nextEdge = graph->edge[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        
        if (x != y) {
            result[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    //printf("최소 신장 트리의 간선:\n");
    /*for (i = 0; i < e; ++i)
        printf("노드 %d - 노드 %d: 가중치 %d\n", result[i].src, result[i].dest, result[i].weight);*/
    return result;

    free(subsets);
}

//사용안함
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
