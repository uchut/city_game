#include "kruskal.h"
#include <stdlib.h>
#include <stdio.h>

//함수 사용법 예시 코드입니다.
int main() {
	Graph* g = (Graph*)malloc(sizeof(Graph)); // 그래프(게임의 맵 형태)는 구조체로 저장됩니다. 구조체 구성 요소에 대한 설명은 헤더파일에 적어놓았습니다.
	initGraph(g, 4); // 그래프 구조체를 초기화하는 함수입니다. 매개변수는 그래프 구조체와 노드 개수입니다.
	int weight[100]; //그래프 구조체의 노드 가중치를 초기화 하기 위한 예시 배열입니다. 가중치 초기화 함수는 가중치 값을 배열로 입력받습니다.
	Edge result[MAX_EDGES]; //결과를 담기 위한 배열입니다. Edge 구조체의 배열로 결과를 출력합니다.
	
	//입력용 예시 가중치 배열 초기화. 작동여부 확인을 위해 임의로 생성한 배열입니다.
	for (int i = 0; i < 100; i++)
	{
		weight[i] = i;
	}
	initNode(g, weight); // 그래프의 노드 가중치를 초기화하는 함수입니다. 그래프 구조체 포인터와 가중치의 배열을 매개변수로 입력받습니다. 배열에 노드가 저장되는 순서는 헤더파일에 적어놓았습니다.
	
	
	for (int i = 0; i < 100; i++)
	{
		result[i] = kruskalMST(g)[i]; // 크루스칼 알고리즘 함수입니다. 그래프 구조체의 포인터를 매개변수로 넣고 실행하면 Edge 자료형의 배열로 결과를 출력합니다.
	}
	for (int i = 0; i < g->edges; i++)
	{
		printf("시작노드%d, 종료노드%d, 가중치%d \n", result[i].src, result[i].dest, result[i].weight);
	}
	return 0;
}
