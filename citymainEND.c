#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#define LINESIZE 50
#define MAX_VERTICES 100
#define MAX_EDGES 100
#define INF 100000000	//무한을 의미
#define NONE_ -1	//존재하지 않음을 의미

//초기 목숨
int heart = 3;

//MST알고리즘에서 쓰일 점의 개수, (존재하는)간선의 개수, (존재하지 않는 간선 포함)간선의 개수, 간선의 가중치 배열
typedef struct {
	int node;
	int lineSize;
	int fullLine;
	int line[LINESIZE];
} MST;

//여행자 알고리즘에서 쓰일 점이 개수, 간선의 개수, 간선의 가중치 배열
typedef struct Travel_struct {
	int node;
	int lineSize;
	int fullLine;
	int line[LINESIZE];
} Travel;

// 간선 구조체
typedef struct {
	int src, dest, weight;
} Edge;

typedef struct {
	int totalWeight;   // MST의 총 가중치
	Edge edges[MAX_EDGES]; // MST의 간선 배열
	int edgeCount;     // MST의 간선 개수
} MSTResult;

// Graph 구조체(vertices : 노드 개수, edges : 간선 개수)
typedef struct {
	int vertices, edges;
	Edge edge[MAX_EDGES];
} Graph;

// Subset 구조체
typedef struct {
	int parent;
	int rank;
} Subset;

// 간선 비교 함수
int compareEdges(const void* a, const void* b);

int find(Subset subsets[], int i);

void unionSets(Subset subsets[], int x, int y);

int kruskalMST(Graph* graph);

int findMST(MST* mst);

// 함수 선언
void initGraph(Graph* g, int v, int* n);
// MST를 기반으로 DFS를 수행하여 TSP 근사 경로를 찾는 함수
void dfs(int vertex, Edge* mstEdges, int mstEdgeCount, bool* visited, Edge* tspResult, int* resultIndex, int* totalWeight);
int tsp_main(MST* mst_tsp);

// MST를 사용한 TSP 근사 경로 생성 함수
int tspUsingMST(Graph* graph, Edge* tspResult);


//void randomEdge(Graph* graph);

//각종 함수 선언부, 함수의 메커니즘은 아래 구현부에서 확인
void storyPrint(const char* text);
void intro(void);
int randomMap(void);
void lineWeight(MST* mst);
void lineWeight2(MST* mst);
void randomline(MST* mst);

void printMapMST(int randNum);
void printMapTravel(int randNum);
void selectMST(MST* mst, int budget);
void selectTSP(MST* mst, int budget);
int numEquals(int num[], int budget, int num2[], MST* mst);
int numEquals2(int num[], int budget, int num2[], MST* mst);

int main(void) {
	//printMapMST(1);
	intro();	//인트로 스토리 출력 함수
	printMapTravel(1);
	printf("\n");
	if (heart == 3) {
		printf("축하합니다. 당신은 모든 도로 건설을 완벽하게 수행하여 이번 서울시장으로 당선되었습니다.\n<서울시장 엔딩>");
	}
	else if (heart == 2) {
		printf("축하합니다. 당신은 한국 도로공사의 임원으로 승진하였습니다.\n<도로공사 임원 엔딩>");
	}
	else if (heart == 1) {
		printf("당신은 도로 건설사의 만년 대리로 임명되었습니다.\n<만년 대리 엔딩>");
	}
	else {
		printf("당신은 주어진 예산을 적절히 사용하지 못하였습니다.\n<배드 엔딩>");
	}
	return 0;
}

//인트로 스토리
void intro(void) {
	printf("바");
	Sleep(30);
	printf("야");
	Sleep(30);
	printf("흐");
	printf("로");
	printf(" 2"); Sleep(30); printf("0"); Sleep(30); printf("2"); Sleep(30); printf("4"); Sleep(30); printf("년");
	Sleep(2000);
	printf("\n");

	const char* text1 = "대한민국의 도시 인프라들은 상당히 낙후 되었고";
	const char* text2 = "이에 따라 정부는 새로운 신도시 계획을 수립하는데...";
	const char* text3 = "당신은 상명시의 도시개발 담당자";
	const char* text4 = "상명시도 재개발 열풍과 정부의 신도시 투자에 따라 새로운 인프라를 구축하려고 한다.";
	const char* text5 = "상명시는 다음 그림과 같이 도심이 형성될 예정이다.";
	//const char* text6 = "주어진 예산은 20조";
	//const char* text7 = "예산 내에서 도로롤 새롭게 구축해야 하는데";

	const char* text8 = "당신은 새로운 도시로 발령받아서 새로운 도시의 도로 건설을 담당하게 되었습니다.";
	//스토리 출력
	for (int i = 0; text1[i] != '\0'; i++) {
		putchar(text1[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
	Sleep(200);
	printf("."); Sleep(200); printf("."); Sleep(200); printf(". \n");
	Sleep(3000);
	
	system("cls");
	






	for (int i = 0; text2[i] != '\0'; i++) {
		putchar(text2[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
	Sleep(3000);
	printf("\n\n");
	system("cls");
	Sleep(1500);

	for (int i = 0; text3[i] != '\0'; i++) {
		putchar(text3[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
	Sleep(3000);
	printf("\n");
	system("cls");


	for (int i = 0; text4[i] != '\0'; i++) {
		putchar(text4[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
	Sleep(3000);
	printf("\n");
	for (int i = 0; text5[i] != '\0'; i++) {
		putchar(text5[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
	Sleep(2000);
	printf("\n");
	//1,2 중 랜덤 숫자
	int temp = randomMap();

	//MST맵 출력(맵1, 맵2 중 랜덤)
	printMapMST(temp);

	Sleep(1000);
	system("cls");
	printf("\n");
	for (int i = 0; text8[i] != '\0'; i++) {
		putchar(text8[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
	Sleep(200);
	printf("."); Sleep(200); printf("."); Sleep(200); printf(".");
	Sleep(3000);
	printf("\n");
	system("cls");
	//또 다른 맵으로 플레이
	if (temp == 1) {
		printMapMST(2);
	}
	else if (temp == 2) {
		printMapMST(1);
	}
	Sleep(3000);


	printf("\n");

}

void storyPrint(const char* text) {
	for (int i = 0; text[i] != '\0'; i++) {
		putchar(text[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
}


//어떤 맵을 사용할 지 결정하는 함수2
int randomMap(void) {
	srand(time(NULL));
	int randomNum = rand() % 2 + 1;
	return randomNum;
}

void printMapMST(int randNum) {
	//제 1 MST
	MST* mst1 = (MST*)malloc(sizeof(MST));
	mst1->node = 9;	mst1->lineSize = 11; mst1->fullLine = 36;
	//제 1 MST 간선 유무(0은 존재하며 초기화할 예정, -1은 존재하지 않음)
	mst1->line[0] = 0;	mst1->line[1] = 0; mst1->line[2] = 0;	mst1->line[3] = -1;	mst1->line[4] = -1; mst1->line[5] = -1; mst1->line[6] = -1; mst1->line[7] = -1;
	mst1->line[8] = -1; mst1->line[9] = -1; mst1->line[10] = -1; mst1->line[11] = -1; mst1->line[12] = 0; mst1->line[13] = -1; mst1->line[14] = -1;
	mst1->line[15] = -1; mst1->line[16] = 0; mst1->line[17] = -1;  mst1->line[18] = -1; mst1->line[19] = -1;  mst1->line[20] = -1;
	mst1->line[21] = 0; mst1->line[22] = -1; mst1->line[23] = 0;  mst1->line[24] = 0;  mst1->line[25] = -1;
	mst1->line[26] = 0; mst1->line[27] = -1; mst1->line[28] = -1;  mst1->line[29] = 0;
	mst1->line[30] = -1; mst1->line[31] = -1; mst1->line[32] = 0;
	mst1->line[33] = -1; mst1->line[34] = -1;
	mst1->line[35] = -1;





	//제 2 MST
	MST* mst2 = (MST*)malloc(sizeof(MST));
	mst2->node = 10; mst2->lineSize = 12; mst2->fullLine = 45;
	//제 2 MST 간선 유무(0은 존재하며 초기화할 예정, -1은 존재하지 않음)
	mst2->line[0] = 0; mst2->line[1] = 0; mst2->line[2] = -1; mst2->line[3] = -1; mst2->line[4] = -1; mst2->line[5] = -1; mst2->line[6] = -1; mst2->line[7] = -1; mst2->line[8] = -1;
	mst2->line[9] = -1; mst2->line[10] = 0; mst2->line[11] = -1; mst2->line[12] = -1; mst2->line[13] = -1; mst2->line[14] = -1; mst2->line[15] = -1; mst2->line[16] = -1;
	mst2->line[17] = 0; mst2->line[18] = -1; mst2->line[19] = 0; mst2->line[20] = -1; mst2->line[21] = -1; mst2->line[22] = -1; mst2->line[23] = -1;
	mst2->line[24] = 0; mst2->line[25] = -1; mst2->line[26] = 0; mst2->line[27] = -1; mst2->line[28] = -1; mst2->line[29] = -1;
	mst2->line[30] = -1; mst2->line[31] = -1; mst2->line[32] = -1; mst2->line[33] = -1; mst2->line[34] = -1;
	mst2->line[35] = 0; mst2->line[36] = -1; mst2->line[37] = -1; mst2->line[38] = -1;
	mst2->line[39] = 0; mst2->line[40] = 0; mst2->line[41] = -1;
	mst2->line[42] = -1; mst2->line[43] = 0;
	mst2->line[44] = 0;

	const char* type0 = "각 도로를 지을 경우 각각의 도로를 짓는데 들어가는 금액은 다음과 같다.";



	if (randNum == 1) {
		int budget = 0;
		printf("\n\n=================================================================================\n\n");
		printf("\t\t  ** A ***");
		printf("\n\t       ***   *    ****\n\t    ***\t     *        ****\n");
		printf("\tB **         *            *** C\n");
		printf("\t*	     *                *\n");
		printf("\t*            *               *\n");
		printf("\t*            *    \t    *\n");
		printf("\t*      ***** D ************ E ******** F");
		printf("\n\tG *****       *              *        *\n\t\t       *              *     *\n");
		printf("\t\t\tH\t       *  *\n");
		printf("\t\t\t\t\tI");
		printf("\n\n=================================================================================\n\n");
		Sleep(3000);
		for (int i = 0; type0[i] != '\0'; i++) {
			putchar(type0[i]);  // 한 글자씩 출력
			Sleep(30);  // 30 밀리초 대기
		}
		printf("\n");

		randomline(mst1);
		lineWeight(mst1);
		budget = findMST(mst1);
		printf("예산 : %d억원\n", budget);
		selectMST(mst1, budget);
		Sleep(800);



	}
	if (randNum == 2) {
		int budget = 0;
		printf("\n\n=================================================================================\n\n");
		printf("\t\t    A ***** B\n");
		printf("\t\t   *         *\n");
		printf("\t\t  *          *\n");
		printf("\t\t *            *      ***** E\n");
		printf("\t\tC *********** D *****\n");
		printf("\t\t *            *\n");
		printf("\t\t *            *\n");
		printf("\t\t  F ****      *\n");
		printf("\t\t        ***** G ********* H\n");
		printf("\t\t               *           *\n");
		printf("\t\t                *           *\n");
		printf("\t\t                 *           *\n");
		printf("\t\t                  *           *\n");
		printf("\t\t                   *        ** J\n");
		printf("\t\t                    *    ***\n");
		printf("\t\t                     I **\n");
		printf("\n\n=================================================================================\n\n");
		for (int i = 0; type0[i] != '\0'; i++) {
			putchar(type0[i]);  // 한 글자씩 출력
			Sleep(30);  // 30 밀리초 대기
		}
		printf("\n");

		randomline(mst2);
		lineWeight(mst2);
		budget = findMST(mst2);
		printf("예산 : %d억원\n", budget);
		selectMST(mst2, budget);
		Sleep(800);
	}





}

void printMapTravel(int randNum) {
	//// Graph 구조체(vertices : 노드 개수, edges : 간선 개수, edge[] : 간선 가중치)
	//// { int vertices, edges; int edge[]; }
	////제 1 Travel
	//Graph* graph1 = (Graph*)malloc(sizeof(Graph));
	//graph1->edges = 14;	graph1->vertices = 11;
	//Edge* edge1[14];
	//int i = 0;
	//for (i = 0; i < 14; i++) {
	//	edge1[i] = (Edge*)malloc(sizeof(Edge));
	//}



	MST* mst_TSP = (MST*)malloc(sizeof(MST));
	mst_TSP->node = 11; mst_TSP->lineSize = 20; mst_TSP->fullLine = 55;
	//MST_TSP 간선 유무(0은 존재하며 초기화할 예정, -1은 존재하지 않음)
	mst_TSP->line[0] = 0; mst_TSP->line[1] = 0; mst_TSP->line[2] = -1; mst_TSP->line[3] = -1; mst_TSP->line[4] = -1; mst_TSP->line[5] = -1; mst_TSP->line[6] = -1; mst_TSP->line[7] = -1; mst_TSP->line[8] = -1; mst_TSP->line[9] = -1;
	mst_TSP->line[10] = 0; mst_TSP->line[11] = 0; mst_TSP->line[12] = -1; mst_TSP->line[13] = -1; mst_TSP->line[14] = -1; mst_TSP->line[15] = -1; mst_TSP->line[16] = -1; mst_TSP->line[17] = -1; mst_TSP->line[18] = -1;
	mst_TSP->line[19] = 0; mst_TSP->line[20] = 0; mst_TSP->line[21] = 0; mst_TSP->line[22] = -1; mst_TSP->line[23] = -1; mst_TSP->line[24] = -1; mst_TSP->line[25] = -1; mst_TSP->line[26] = -1;
	mst_TSP->line[27] = 0; mst_TSP->line[28] = -1; mst_TSP->line[29] = 0; mst_TSP->line[30] = -1; mst_TSP->line[31] = -1; mst_TSP->line[32] = -1; mst_TSP->line[33] = 0;
	mst_TSP->line[34] = 0; mst_TSP->line[35] = -1; mst_TSP->line[36] = -1; mst_TSP->line[37] = -1; mst_TSP->line[38] = 0; mst_TSP->line[39] = 0;
	mst_TSP->line[40] = -1; mst_TSP->line[41] = 0; mst_TSP->line[42] = -1; mst_TSP->line[43] = 0; mst_TSP->line[44] = -1;
	mst_TSP->line[45] = -1; mst_TSP->line[46] = 0; mst_TSP->line[47] = -1; mst_TSP->line[48] = 0;
	mst_TSP->line[49] = -1; mst_TSP->line[50] = 0; mst_TSP->line[51] = -1;
	mst_TSP->line[52] = -1; mst_TSP->line[53] = 0;
	mst_TSP->line[54] = 0;
	const char* type1 = "당신은 도청에서 주관하는 순환 고속도로 건설의 계획자로 발령이 났습니다.";
	const char* type2 = "아래 나타난 그림에 있는 각 도로는 다음 도시들을 모두 거쳐야 하는 순환 고속도로의 후보 구간입니다.";
	const char* type3 = "각 도로를 지을 경우 각각의 도로를 짓는데 들어가는 금액은 다음과 같다.";

	const char* type0 = "각 도로를 지을 경우 각각의 도로를 짓는데 들어가는 금액은 다음과 같다.";
	const char* type4 = "각 도로를 지을 경우 각각의 도로를 짓는데 들어가는 금액은 다음과 같다.";
	const char* type5 = "각 도로를 지을 경우 각각의 도로를 짓는데 들어가는 금액은 다음과 같다.";
	for (int i = 0; type1[i] != '\0'; i++) {
		putchar(type1[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
	printf("\n");
	for (int i = 0; type2[i] != '\0'; i++) {
		putchar(type2[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}


	Sleep(3000);
	//system("cls");

	printf("\n\n=================================================================================\n\n");
	printf("\t\t          A    \n");
	printf("\t\t        *  *       \n");
	printf("\t\t      *     *        \n");
	printf("\t\t    B ***** C *\n");
	printf("\t\t    *     * *   *\n");
	printf("\t\t    *   *   *     *\n");
	printf("\t\t    * *     *       *\n");
	printf("\t\t    D ***** E ******* F\n");
	printf("\t\t   * *     * *       * *\n");
	printf("\t\t  *    * *    *     *   *\n");
	printf("\t\t G **** K      *   *     H\n");
	printf("\t\t  *  **   ***   * *   ***\n");
	printf("\t           I         *** J ***\n");
	printf("\n\n=================================================================================\n\n");
	for (int i = 0; type0[i] != '\0'; i++) {
		putchar(type0[i]);  // 한 글자씩 출력
		Sleep(30);  // 30 밀리초 대기
	}
	int budget = 0;
	printf("\n");

	randomline(mst_TSP);
	lineWeight2(mst_TSP);
	budget = tsp_main(mst_TSP);
	printf("예산 : %d00억원\n", budget);
	selectTSP(mst_TSP, budget);









	//randomEdge(graph1);
	//budget = findMST(mst2);
	//selectMST(mst2, budget);
	//Sleep(800);
	//tspUsingMST(graph1, edge1);




/*free(edge1);
free(graph1);*/
}



//MST간선들의 가중치를 랜덤으로 설정 하고 lineWeight()를 통해 그 값들을 출력
void randomline(MST* mst) {
	int i = 0;

	//printf는 테스트용
	//printf("%d %d", mst->node, mst->lineSize);

	//mst구조체에 있는 간선마다 가중치(예산을)값을 넣음
	srand(time(NULL));
	for (i = 0; i < mst->fullLine; i++) {
		if (mst->line[i] == 0) {

			mst->line[i] = rand() % 10 + 10;
			//printf("[%d] : %d\n",i, mst->line[i]);

		}
		else if (mst->line[i] == -1) {
			mst->line[i] = -1;
		}
	}

}

//간선별 가중치(예산) 출력
void lineWeight(MST* mst) {
	int i = 0;
	int j = 0, x = 0;
	for (i = 0; i < mst->node - 1; i++) {
		for (j = i + 1; j < mst->node; j++) {
			if (mst->line[x] != -1) {
				printf("[%2d] 도로 %c - %c 건설 시 예산 : %d억\n", x, i + 'A', j + 'A', mst->line[x]);
			}

			x++;
		}
	}
}

//@Overriding
void lineWeight2(MST* mst) {
	int i = 0;
	int j = 0, x = 0;
	for (i = 0; i < mst->node - 1; i++) {
		for (j = i + 1; j < mst->node; j++) {
			if (mst->line[x] != -1) {
				printf("[%2d] 도로 %c - %c 건설 시 예산 : %d00억\n", x, i + 'A', j + 'A', mst->line[x]);
			}

			x++;
		}
	}
}
//건설할 도로들의 후보중 최적의 도로들을 유저가 선택하도록 함.
void selectMST(MST* mst, int budget) {
	int i = 0;
	int j = 0, x = 0;
	int num[LINESIZE] = { 0 }, num2[LINESIZE] = { 0 };
	int pass_fail = 0;

	printf("\n어느 마을에서 다른 모든 마을로 갈 수 있도록 크러스컬 알고리즘을 사용하여 제한된 예산으로 도로를 건설하시오.\n");

	for (i = 0; i < mst->node - 1; i++) {
		for (j = i + 1; j < mst->node; j++) {
			if (mst->line[x] != -1) {
				printf("%c - %c : %d번 도로\n", i + 'A', j + 'A', x);
			}

			x++;
		}
	}

	//간선들의 후보를 num2[]에 담는 코드
	j = 0;
	for (i = 0; i < mst->fullLine; i++) {
		if (mst->line[i] != -1) {
			num2[j] = mst->line[i];
		}
	}

re:
	i = 0;
	while (1) {
		printf("건설할 도로의 번호를 입력(-1 입력시 도로를 건설) : ");
		scanf_s("%d", &num[i]);
		if (num[i] == -1) {
			break;
		}
		else if (mst->line[num[i]] == -1) {
			printf("잘못된 입력입니다.\n처음부터 다시 입력해주세요.\n");
			goto re;
		}
		i++;
	}

	pass_fail = numEquals(num, budget, num2, mst);
	if (pass_fail == -1) {
		heart--;
		printf("< 현재 목숨 : %d >\n", heart);
	}
}

//@Overriding
void selectTSP(MST* mst, int budget) {
	int i = 0;
	int j = 0, x = 0;
	int num[LINESIZE] = { 0 }, num2[LINESIZE] = { 0 };
	int pass_fail = 0;

	printf("\n모든 도시를 순환하는 순환 고속도로를 TSP 알고리즘을 이용하여 건설하시오.\n");

	for (i = 0; i < mst->node - 1; i++) {
		for (j = i + 1; j < mst->node; j++) {
			if (mst->line[x] != -1) {
				printf("%c - %c : %d번 도로\n", i + 'A', j + 'A', x);
			}

			x++;
		}
	}

	//간선들의 후보를 num2[]에 담는 코드
	j = 0;
	for (i = 0; i < mst->fullLine; i++) {
		if (mst->line[i] != -1) {
			num2[j] = mst->line[i];
		}
	}

re:
	i = 0;
	while (1) {
		printf("건설할 도로의 번호를 입력(-1 입력시 도로를 건설) : ");
		scanf_s("%d", &num[i]);
		if (num[i] == -1) {
			break;
		}
		else if (mst->line[num[i]] == -1) {
			printf("잘못된 입력입니다.\n처음부터 다시 입력해주세요.\n");
			goto re;
		}
		i++;
	}

	pass_fail = numEquals(num, budget, num2, mst);
	if (pass_fail == -1) {
		heart--;
		printf("< 현재 목숨 : %d >\n", heart);
	}
}
//주어진 예산으로 도로를 건설 할 수 있는지를 확인하여 예산 내로 도로를 건설하지 못하면 -1을, 건설 가능하면 0을 리턴
int numEquals(int num[], int budget, int num2[], MST* mst) {
	int i = 0, sum = 0;
	for (i = 0; i < mst->lineSize && num[i] != -1; i++) {
		if (num[i] == -1) {
			continue;
		}
		sum += mst->line[num[i]];
	}
	printf("%d억원 사용, 예산 : %d\n", sum, budget);
	if (budget == sum) {
		printf("주어진 예산으로 적절하게 도로를 건설하였습니다.\n");
		return 0;
	}
	else if (budget > sum) {
		printf("모든 마을을 잇는 도로를 건설하지 못하였습니다.\n");
		return -1;
	}
	else {
		printf("예산을 초과하여 도로를 건설하였습니다.\n");
		return -1;
	}
}

//@Overriding
int numEquals2(int num[], int budget, int num2[], MST* mst) {
	int i = 0, sum = 0;
	for (i = 0; i < mst->lineSize && num[i] != -1; i++) {
		if (num[i] == -1) {
			continue;
		}
		sum += mst->line[num[i]];
	}
	printf("%d00억원 사용, 예산 : %d00억원\n", sum, budget);
	if (budget == sum) {
		printf("주어진 예산으로 적절하게 도로를 건설하였습니다.\n");
		return 0;
	}
	else if (budget > sum) {
		printf("모든 마을을 잇는 도로를 건설하지 못하였습니다.\n");
		return -1;
	}
	else {
		printf("예산을 초과하여 도로를 건설하였습니다.\n");
		return -1;
	}
}

//간선들의 가중치(예산)을 받아 출력, 이후 최소 예산을 리턴
int findMST(MST* mst) {
	int vertices = 0, edges = 0;
	int budget = 0, i = 0;
	//printf("노드 개수를 입력하세요: ");
	//scanf_s("%d", &vertices);
	//node, vertices 점의 개수, lineSize edges 간선 개수
	//line, edges 각각의 간선(배열, 가중치가 입력될 예정)
	Graph* graph = (Graph*)malloc(sizeof(Graph));



	//mst구조체에 저장된 간선배열을 graph 구조체로 옮김
	for (i = 0; i < mst->fullLine; i++) {
		graph->edge[i].weight = mst->line[i];
	}
	graph->vertices = mst->node;	//점의 개수 옮김
	graph->edges = mst->fullLine;	//존재하지 않는 간선 + 존재하는 간선 개수 옮김



	//printf("각 노드 쌍의 가중치를 입력하세요 (연결되지 않은 경우 -1 입력):\n");



	for (int i = 0; i < mst->node; ++i) {
		for (int j = i + 1; j < mst->node; ++j) {
			int weight;
			//printf("노드 %d - 노드 %d: ", i, j);
			//scanf_s("%d", &weight);
			weight = mst->line[i - 1];
			if (weight != -1) {
				graph->edge[edges].src = i;
				graph->edge[edges].dest = j;
				graph->edge[edges].weight = weight;
				edges++;
			}
		}
	}

	graph->edges = edges;
	initGraph(graph, graph->vertices, mst->line);
	budget = kruskalMST(graph);

	free(graph);
	return budget;
}


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

int compareEdges(const void* a, const void* b) {
	Edge* edgeA = (Edge*)a;
	Edge* edgeB = (Edge*)b;
	return edgeA->weight - edgeB->weight;
}

int find(Subset subsets[], int i) {
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);
	return subsets[i].parent;
}

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

//크러스컬 알고리즘으로 구한 최소의 예산을 리턴
int kruskalMST(Graph* graph) {
	int vertices = graph->vertices;

	//정답을 임시로 저장할 Edge 구조체
	Edge result[MAX_EDGES];
	int e = 0;
	int i = 0;
	int v = 0;
	qsort(graph->edge, graph->edges, sizeof(graph->edge[0]), compareEdges);

	Subset* subsets = (Subset*)malloc(vertices * sizeof(Subset));

	//각 간선들마다 가중치에 의한 선별
	for (v = 0; v < vertices; ++v) {
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
	int sum = 0;


	printf("최소 신장 트리의 간선(정답 출력코드, 이후 주석 처리):\n");
	for (i = 0; i < e; ++i) {

		printf("마을 %c - 마을 %c: 가중치 %d억\n", result[i].src + 'A', result[i].dest + 'A', result[i].weight);
		sum += result[i].weight;
	}
	//printf("예산 : %d억원\n", sum);
	free(subsets);

	return sum;
}


int tsp_main(MST* mst_tsp) {
	int vertices = 0, edges = 0;
	int budget = 0, i = 0;
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	//mst구조체에 저장된 간선배열을 graph 구조체로 옮김
	for (i = 0; i < mst_tsp->fullLine; i++) {
		graph->edge[i].weight = mst_tsp->line[i];
	}
	graph->vertices = mst_tsp->node;	//점의 개수 옮김
	graph->edges = mst_tsp->fullLine;	//존재하지 않는 간선 + 존재하는 간선 개수 옮김



	//printf("각 노드 쌍의 가중치를 입력하세요 (연결되지 않은 경우 -1 입력):\n");



	for (int i = 0; i < mst_tsp->node; ++i) {
		for (int j = i + 1; j < mst_tsp->node; ++j) {
			int weight;
			//printf("노드 %d - 노드 %d: ", i, j);
			//scanf_s("%d", &weight);
			weight = mst_tsp->line[i - 1];
			if (weight != -1) {
				graph->edge[edges].src = i;
				graph->edge[edges].dest = j;
				graph->edge[edges].weight = weight;
				edges++;
			}
		}
	}

	graph->edges = edges;
	initGraph(graph, graph->vertices, mst_tsp->line);
	Edge tspResult[MAX_VERTICES];  // TSP 근사 경로를 저장할 배열

	// TSP 근사 경로 계산
	int totalWeight = tspUsingMST(graph, tspResult);

	// 결과 출력
	//최종 코드에서는 지울 예정, 정답확인용
	printf("TSP 근사 경로의 총 가중치: %d(정답확인용, 최종 코드에서는 제거)\n", totalWeight);
	for (int i = 0; i < graph->vertices - 1; i++) {
		printf("%c - %c : %d00억원\n", tspResult[i].src + 'A', tspResult[i].dest + 'A', tspResult[i].weight);
	}
	
	free(graph);
	return totalWeight;
}

MSTResult kruskalMST_edge(Graph* graph) {
	MSTResult result = { 0, {{0}}, 0 };
	int vertices = graph->vertices;
	int e = 0, i = 0;

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
			result.edges[e++] = nextEdge;
			result.totalWeight += nextEdge.weight;
			unionSets(subsets, x, y);
		}
	}

	result.edgeCount = e;
	free(subsets);
	return result;
}


//MST를 사용한 TSP 근사 경로 생성 함수
int tspUsingMST(Graph* graph, Edge* tspResult) {
	// MST 계산
	MSTResult mst = kruskalMST_edge(graph); // MST 간선 정보와 총 가중치 가져오기

	// 방문 여부를 추적하기 위한 배열과 기타 변수들
	bool visited[MAX_VERTICES] = { false };
	int totalWeight = 0;
	int resultIndex = 0;
	int currentVertex = 0; // 시작 정점은 0으로 설정

	// DFS를 통해 TSP 경로 계산
	dfs(currentVertex, mst.edges, mst.edgeCount, visited, tspResult, &resultIndex, &totalWeight);

	// 시작 지점으로 돌아오는 간선 추가
	for (int i = 0; i < graph->edges; i++) {
		Edge edge = graph->edge[i];
		if ((edge.src == currentVertex && edge.dest == 0) ||
			(edge.dest == currentVertex && edge.src == 0)) {
			tspResult[resultIndex++] = edge;
			totalWeight += edge.weight;
			break;
		}
	}

	return totalWeight;  // 총 가중치 반환
}



//Graph 구조체, 노드 개수, 간선의 가중치 배열
void initGraph(Graph* g, int v, int* n)
{
	g->vertices = v;
	g->edges = 0;
	int count = 0;
	int maxedges = 0;
	for (int i = 0; i < v; ++i)
	{
		for (int j = i + 1; j < v; ++j)
		{
			if (n[count] != -1)
			{
				g->edge[g->edges].src = i;
				g->edge[g->edges].dest = j;
				g->edge[g->edges].weight = n[count];
				g->edges++;
			}
			count++;
		}
	}
}