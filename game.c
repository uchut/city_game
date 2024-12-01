#include "game.h"
#include "kruskal.h"
#include <stdio.h>
#include <stdlib.h>
#define LIFE 5
void run()
{
	Quiz* quizmst1 = (Quiz*)malloc(sizeof(Quiz));
	Quiz* quiztsp1 = (Quiz*)malloc(sizeof(Quiz));
	initQuiz(quizmst1, 1, 10, 1); //������ �Ű������� 1�̸� mst 2�� tsp
	int n = 0;
	int life = LIFE;
	printf("��Ʈ�� ���� �����ִ� �Լ� ����\n");
	do
	{	
		int sum = 0;
		int ressum = 10000;
		int ansnum;
		int s, d, n;
		Edge* ans = (Edge*)malloc(sizeof(Edge));
		Edge* result = (Edge*)malloc(sizeof(Edge));
		Quiz* selectquiz = (Quiz*)malloc(sizeof(Quiz));
		selectquiz = quizmst1; //���ӿ��� ������ �� ���� �������� ���ִ� �ڵ�. �����ϰ� �ϴ� mst1�� ���°ɷ� ����ȭ.
		Graph* game = (Graph*)malloc(sizeof(Graph));
		/*if (selectquiz->type == 1)
			{*/
		result = kruskalMST(game);	
		/* }*/
		/*else
		{
			//result = tsp(game);
		}*/
		//tsp �Լ��� �ִٸ� �ּ�����. Ÿ�Կ� ���� ������ �����ϴ� �˰����� �ٸ��� �����ϴ� ����


		initGraph(game, selectquiz->node, selectquiz->weight);
		printf("�����Դϴ� \n");
		showmap(selectquiz->map);
		printf("������ �Է����ּ���. �Է��� �����ٸ� -1, 0, 0 �Է� \n");
		ansnum = 0;
		//���� �Է¹޴� ����
		do
		{
			printf("������: ");
			scanf_s("%d", &s);
			printf("������: ");
			scanf_s("%d", &d);
			if (s == d)
			{
				printf("�������� �������� �����ϴ�. �ٽ� �Է��ϼ��� \n");
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
				//printf("���۳��: %d, ������: %d, ����ġ: %d", ans[ansnum].src, ans[ansnum].dest, ans[ansnum].weight);
				for (int i = 0; i < 100; i++)
				{

				}
				ansnum++;
			}
		} while (s != -1);
			//�Է¹����ɷ� ����� ���ϴ� ����
			for (int i = 0; i < 100; i++)
			{
				
					
					printf("���� ������: %d, ���� ������ %d, ���� ����ġ %d \n", result[i].src, result[i].dest, result[i].weight);
				
			}

			for (int i = 0; i < 100; i++)
			{
				if (ans[i].src >= 0)
				{
					printf("�Է��� ������: %d, �Է��� ������ %d \n", ans[i].src, ans[i].dest);
				}
			}

			if (ressum > sum) //�������ǿ� ���� ����� �ϴ� �ܼ�ȭ. �� �κ��� ���� �̿ϼ�
			{
				printf("�����Դϴ�.��� 1 ����, ��������\n");
				printf("���� ���: %d \n", life);
				life--;
			}
			else
			{
				printf("�����Դϴ�.��������\n");
			}
		
	} while (life > 0);
	printf("��� 0, ���� ����");
}

void initQuiz(Quiz* q, int m, int n, int t)
{
	q->type = t;
	int strings;
	int connect[100];
	//����� ������ ��ȣ�� �Է��ϴ� ����
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
			q->weight[connect[i]] = 10; //������� �ϴ� 10 ����
		}
	}
}

void showmap(int n)
{
	switch (n)
	{
	case 1:
		printf("1����\n");
		break;
	case 2:
		printf("2����\n");
	}
}