#include "game.h"
#include "kruskal.h"
#include <stdio.h>
#include <stdlib.h>
#define LIFE 5
void run()
{
	Quiz* quizmst1 = (Quiz*)malloc(sizeof(Quiz));
	Quiz* quiztsp1 = (Quiz*)malloc(sizeof(Quiz));
	initQuiz(quizmst1, 1, 10, 1); //마지막 매개변수가 1이면 mst 2면 tsp
	int n = 0;
	int life = LIFE;
	printf("인트로 내용 보여주는 함수 실행\n");
	do
	{	
		int sum = 0;
		int ressum = 10000;
		int ansnum;
		int s, d, n;
		Edge* ans = (Edge*)malloc(sizeof(Edge));
		Edge* result = (Edge*)malloc(sizeof(Edge));
		Quiz* selectquiz = (Quiz*)malloc(sizeof(Quiz));
		selectquiz = quizmst1; //게임에서 보여줄 맵 선택 랜덤으로 해주는 코드. 생략하고 일단 mst1을 고르는걸로 간소화.
		Graph* game = (Graph*)malloc(sizeof(Graph));
		/*if (selectquiz->type == 1)
			{*/
		result = kruskalMST(game);	
		/* }*/
		/*else
		{
			//result = tsp(game);
		}*/
		//tsp 함수가 있다면 주석해제. 타입에 따라서 정답을 도출하는 알고리즘을 다르게 선택하는 구간


		initGraph(game, selectquiz->node, selectquiz->weight);
		printf("문제입니다 \n");
		showmap(selectquiz->map);
		printf("정답을 입력해주세요. 입력이 끝났다면 -1, 0, 0 입력 \n");
		ansnum = 0;
		//정답 입력받는 구간
		do
		{
			printf("시작점: ");
			scanf_s("%d", &s);
			printf("도착점: ");
			scanf_s("%d", &d);
			if (s == d)
			{
				printf("시작점과 도착점이 같습니다. 다시 입력하세요 \n");
			}
			else
			{
				if (s < d)
				{
					ans[ansnum].src = s;
					ans[ansnum].dest = d;
				}
				else
				{
					ans[ansnum].src = d;
					ans[ansnum].dest = s;
				}
				//printf("시작노드: %d, 종료노드: %d, 가중치: %d", ans[ansnum].src, ans[ansnum].dest, ans[ansnum].weight);
				for (int i = 0; i < 100; i++)
				{

				}
				ansnum++;
			}
		} while (s != -1);
			//입력받은걸로 정답과 비교하는 구간
			for (int i = 0; i < 100; i++)
			{
				
					
					printf("정답 시작점: %d, 정답 도착점 %d, 정답 가중치 %d \n", result[i].src, result[i].dest, result[i].weight);
				
			}

			for (int i = 0; i < 100; i++)
			{
				if (ans[i].src >= 0)
				{
					printf("입력한 시작점: %d, 입력한 도착점 %d \n", ans[i].src, ans[i].dest);
				}
			}

			if (ressum > sum) //실패조건에 관한 계산은 일단 단순화. 이 부분은 아직 미완성
			{
				printf("실패입니다.목숨 1 감소, 다음문제\n");
				printf("현재 목숨: %d \n", life);
				life--;
			}
			else
			{
				printf("성공입니다.다음문제\n");
			}
		
	} while (life > 0);
	printf("목숨 0, 게임 종료");
}

void initQuiz(Quiz* q, int m, int n, int t)
{
	q->type = t;
	int strings;
	int connect[100];
	//연결될 간선의 번호를 입력하는 구역
	connect[0] = 0;
	connect[1] = 1;
	connect[2] = 2;
	connect[3] = 12;
	connect[4] = 16;
	connect[5] = 21;
	connect[6] = 23;
	connect[7] = 24;
	connect[8] = 26;
	connect[9] = 29;
	connect[10] = 32;
	q->map = m;
	q->node = n;
	strings = (n * (n - 3) * 0.5) + n;
	for (int i = 0; i < strings; i++)
	{
		q->weight[i] = -1;
	}
	for (int i = 0; i < 100; i++)
	{
		if (connect[i] >= 0)
		{
			q->weight[connect[i]] = 10; //랜덤대신 일단 10 적용
		}
	}
}

void showmap(int n)
{
	switch (n)
	{
	case 1:
		printf("1번맵\n");
		break;
	case 2:
		printf("2번맵\n");
	}
}