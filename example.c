#include "kruskal.h"
#include <stdlib.h>
#include <stdio.h>

//함수 사용법 예시 코드입니다.
int main() {
	Graph* g = (Graph*)malloc(sizeof(Graph)); // 그래프(게임의 맵 형태)는 구조체로 저장됩니다. 구조체 구성 요소에 대한 설명은 헤더파일에 적어놓았습니다.
	//initGraph(g, 4); // 그래프 구조체를 초기화하는 함수입니다. 매개변수는 그래프 구조체와 노드 개수입니다.
	int weight[100]; //그래프 구조체의 노드 가중치를 초기화 하기 위한 예시 배열입니다. 가중치 초기화 함수는 가중치 값을 배열로 입력받습니다.
	Edge result[MAX_EDGES]; //결과를 담기 위한 배열입니다. Edge 구조체의 배열로 결과를 출력합니다.
	
	//입력용 예시 가중치 배열 초기화. 작동여부 확인을 위해 임의로 생성한 배열입니다.
	for (int i = 0; i < 100; i++)
	{
		if (i == 2)
		{
			weight[i] = -1;
		}
		else
		{
			weight[i] = i;
		}
	}
	//initNode(g, weight); // 그래프의 노드 가중치를 초기화하는 함수입니다. 그래프 구조체 포인터와 가중치의 배열을 매개변수로 입력받습니다. 배열에 노드가 저장되는 순서는 헤더파일에 적어놓았습니다.
	initGraph(g, 4, weight);
	
	for (int i = 0; i < 100; i++)
	{
		result[i] = kruskalMST(g)[i]; // 크루스칼 알고리즘 함수입니다. 그래프 구조체의 포인터를 매개변수로 넣고 실행하면 Edge 자료형의 배열로 결과를 출력합니다.
	}
	for (int i = 0; i < g->edges; i++)
	{
		printf("시작노드%d, 종료노드%d, 가중치%d \n", result[i].src, result[i].dest, result[i].weight);
	}
	//run();
	return 0;
}

/*
예시
노드 갯수가 8개, 0-1, 0-2, 0-3, "0-4", 0-5, 0-6, 0-7, 1-2, 1-3, 1-4, 1-5, "1-6", 1-7, 2-3, 2-4, "2-5", 2-6, 2-7, 3-4, 3-5, 3-6, 3-7, 4-5, 4-6, 4-7, 5-6, 5-7, 6-7의 간선이 있고
따옴표 쳐진 간선은 이어지지 않은 간선이라고 할 때,
weight[3] = -1, weight[11] = -1, weight[15] = -1 이고 이것을 제외한 weight[0] ~ weight[27]의 값은 랜덤으로 저장.

그 이후 initGraph(exapmle, 8, weight); 하시면 example 그래프는 노드 갯수가 8개고 따옴표 쳐진 간선이 이어지지 않은 그래프로 초기화됩니다. 
*/
