#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#define LINESIZE 50
#define MAX_VERTICES 100
#define MAX_EDGES 100
#define INF 100000000	//������ �ǹ�
#define NONE_ -1	//�������� ������ �ǹ�

//�ʱ� ���
int heart = 3;

//MST�˰��򿡼� ���� ���� ����, ������ ����, ������ ����ġ �迭
typedef struct {
	int node;
	int lineSize;
	int fullLine;
	int line[LINESIZE];
} MST;

//������ �˰��򿡼� ���� ���� ����, ������ ����, ������ ����ġ �迭
typedef struct Travel_struct {
	int node;
	int lineSize;
	int fullLine;
	int line[LINESIZE];
} Travel;

// ���� ����ü
typedef struct {
	int src, dest, weight;
} Edge;

// Graph ����ü(vertices : ��� ����, edges : ���� ����)
typedef struct {
	int vertices, edges;
	Edge edge[MAX_EDGES];
} Graph;

// Subset ����ü
typedef struct {
	int parent;
	int rank;
} Subset;

// ���� �� �Լ�
int compareEdges(const void* a, const void* b);

int find(Subset subsets[], int i);

void unionSets(Subset subsets[], int x, int y);

int kruskalMST(Graph* graph);

int findMST(MST* mst);

// �Լ� ����

// MST�� ������� DFS�� �����Ͽ� TSP �ٻ� ��θ� ã�� �Լ�
void dfs(int vertex, Edge* mstEdges, int mstEdgeCount, bool* visited, Edge* tspResult, int* resultIndex, int* totalWeight);

// MST�� ����� TSP �ٻ� ��� ���� �Լ�
int tspUsingMST(Graph* graph, Edge* tspResult);


void randomEdge(Graph* graph);

//���� �Լ� �����, �Լ��� ��Ŀ������ �Ʒ� �����ο��� Ȯ��
void storyPrint(const char* text);
void intro(void);
int randomMap(void);
void lineWeight(MST* mst);
void randomline(MST* mst);

void printMapMST(int randNum);
void printMapTravel(int randNum);
void selectMST(MST* mst, int budget);
int numEquals(int num[], int budget, int num2[], MST* mst);

int main(void) {
	//printMapMST(1);
	intro();	//��Ʈ�� ���丮 ��� �Լ�
	printMapTravel(1);
	
	return 0;
}

//��Ʈ�� ���丮
void intro(void) {
	printf("��");
	Sleep(30);
	printf("��");
	Sleep(30);
	printf("��");
	printf("��");
	printf(" 2"); Sleep(30); printf("0"); Sleep(30); printf("2"); Sleep(30); printf("4"); Sleep(30); printf("��");
	Sleep(2000);
	system("cls");

	const char* text1 = "���ѹα��� ���� ��������� ����� ���� �Ǿ���";
	const char* text2 = "�̿� ���� ���δ� ���ο� �ŵ��� ��ȹ�� �����ϴµ�...";
	const char* text3 = "����� ������ ���ð��� �����";
	const char* text4 = "���õ� �簳�� ��ǳ�� ������ �ŵ��� ���ڿ� ���� ���ο� ������ �����Ϸ��� �Ѵ�.";
	const char* text5 = "���ô� ���� �׸��� ���� ������ ������ �����̴�.";
	//const char* text6 = "�־��� ������ 20��";
	//const char* text7 = "���� ������ ���η� ���Ӱ� �����ؾ� �ϴµ�";
	
	const char* text8 = "����� ���ο� ���÷� �߷ɹ޾Ƽ� ���ο� ������ ���� �Ǽ��� ����ϰ� �Ǿ����ϴ�.";
	//���丮 ���
	for (int i = 0; text1[i] != '\0'; i++) {
		putchar(text1[i]);  // �� ���ھ� ���
		Sleep(30);  // 30 �и��� ���
	}
	Sleep(200);
	printf("."); Sleep(200); printf("."); Sleep(200); printf(".");
	Sleep(3000);
	system("cls");






	for (int i = 0; text2[i] != '\0'; i++) {
		putchar(text2[i]);  // �� ���ھ� ���
		Sleep(30);  // 30 �и��� ���
	}
	Sleep(3000);
	system("cls");
	Sleep(1500);

	for (int i = 0; text3[i] != '\0'; i++) {
		putchar(text3[i]);  // �� ���ھ� ���
		Sleep(30);  // 30 �и��� ���
	}
	Sleep(3000);
	system("cls");


	for (int i = 0; text4[i] != '\0'; i++) {
		putchar(text4[i]);  // �� ���ھ� ���
		Sleep(30);  // 30 �и��� ���
	}
	Sleep(3000);
	printf("\n");
	for (int i = 0; text5[i] != '\0'; i++) {
		putchar(text5[i]);  // �� ���ھ� ���
		Sleep(30);  // 30 �и��� ���
	}
	Sleep(2000);
	int temp = randomMap();
	printMapMST(temp);

	Sleep(1000);
	system("cls");
	
	for (int i = 0; text8[i] != '\0'; i++) {
		putchar(text8[i]);  // �� ���ھ� ���
		Sleep(30);  // 30 �и��� ���
	}
	Sleep(200);
	printf("."); Sleep(200); printf("."); Sleep(200); printf(".");
	Sleep(3000);
	

	//�� �ٸ� ������ �÷���
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
		putchar(text[i]);  // �� ���ھ� ���
		Sleep(30);  // 30 �и��� ���
	}
}


//� ���� ����� �� �����ϴ� �Լ�2
int randomMap(void) {
	srand(time(NULL));
	int randomNum = rand() % 2 + 1;
	return randomNum;
}

void printMapMST(int randNum) {
	//�� 1 MST
	MST* mst1 = (MST *)malloc(sizeof(MST));
	mst1->node = 9;	mst1->lineSize = 11; mst1->fullLine = 36;
	//�� 1 MST ���� ����(0�� �����ϸ� �ʱ�ȭ�� ����, -1�� �������� ����)
	mst1->line[0] = 0;	mst1->line[1] = 0; mst1->line[2] = 0;	mst1->line[3] = -1;	mst1->line[4] = -1; mst1->line[5] = -1; mst1->line[6] = -1; mst1->line[7] = -1;
	mst1->line[8] = -1; mst1->line[9] = -1; mst1->line[10] = -1; mst1->line[11] = -1; mst1->line[12] = 0; mst1->line[13] = -1; mst1->line[14] = -1;
	mst1->line[15] = -1; mst1->line[16] = 0; mst1->line[17] = -1;  mst1->line[18] = -1; mst1->line[19] = -1;  mst1->line[20] = -1;  mst1->line[21] = -1;
	mst1->line[22] = 0; mst1->line[23] = -1;  mst1->line[24] = 0;  mst1->line[25] = -1;  mst1->line[26] = -1;
	mst1->line[27] = 0; mst1->line[28] = -1;  mst1->line[29] = 0;  mst1->line[30] = 0;
	mst1->line[31] = -1; mst1->line[32] = -1;  mst1->line[33] = 0;
	mst1->line[34] = -1;  mst1->line[35] = -1;





	//�� 2 MST
	MST* mst2 = (MST *)malloc(sizeof(MST));
	mst2->node = 10; mst2->lineSize = 12; mst2->fullLine = 45;
	//�� 2 MST ���� ����(0�� �����ϸ� �ʱ�ȭ�� ����, -1�� �������� ����)
	mst2->line[0] = 0; mst2->line[1] = 0; mst2->line[2] = -1; mst2->line[3] = -1; mst2->line[4] = -1; mst2->line[5] = -1; mst2->line[6] = -1; mst2->line[7] = -1; mst2->line[8] = -1;
	mst2->line[9] = -1; mst2->line[10] = 0; mst2->line[11] = -1; mst2->line[12] = -1; mst2->line[13] = -1; mst2->line[14] = -1; mst2->line[15] = -1; mst2->line[16] = -1;
	mst2->line[17] = 0; mst2->line[18] = -1; mst2->line[19] = 0; mst2->line[20] = -1; mst2->line[21] = -1; mst2->line[22] = -1; mst2->line[23] = -1;
	mst2->line[24] = 0; mst2->line[25] = -1; mst2->line[26] = 0; mst2->line[27] = -1; mst2->line[28] = -1; mst2->line[29] = -1;
	mst2->line[30] = -1; mst2->line[31] = -1; mst2->line[32] = -1; mst2->line[33] = -1; mst2->line[34] = -1;
	mst2->line[35] = 0; mst2->line[36] = -1; mst2->line[37] = -1; mst2->line[38] = -1;
	mst2->line[39] = 0; mst2->line[40] = 0; mst2->line[41] = -1; 
	mst2->line[42] = -1; mst2->line[43] = 0;
	mst2->line[44] = 0;

	const char* type0 = "�� ���θ� ���� ��� ������ ���θ� ���µ� ���� �ݾ��� ������ ����.";
	

	
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
			putchar(type0[i]);  // �� ���ھ� ���
			Sleep(30);  // 30 �и��� ���
		}
		printf("\n");

		randomline(mst1);
		lineWeight(mst2);
		budget = findMST(mst2);
		selectMST(mst2, budget);
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
			putchar(type0[i]);  // �� ���ھ� ���
			Sleep(30);  // 30 �и��� ���
		}
		printf("\n");

		randomline(mst2);
		lineWeight(mst2);
		budget = findMST(mst2);
		selectMST(mst2, budget);
		Sleep(800);
	}





}

void printMapTravel(int randNum) {
	// Graph ����ü(vertices : ��� ����, edges : ���� ����, edge[] : ���� ����ġ)
	// { int vertices, edges; int edge[]; }
	//�� 1 Travel
	Graph* graph1 = (Graph*)malloc(sizeof(Graph));
	graph1->edges = 14;	graph1->vertices = 11;
	Edge* edge1[14];
	int i = 0;
	for (i = 0; i < 14; i++) {
		edge1[i] = (Edge*)malloc(sizeof(Edge));
	}
	

	const char* type0 = "�� ���θ� ���� ��� ������ ���θ� ���µ� ���� �ݾ��� ������ ����.";
	
	Sleep(3000);
	System("cls");
	if (randNum == 1) {
		printf("\n\n=================================================================================\n\n");
		printf("\t\t\t       A\n");
		printf("\t\t\t      *         \n");
		printf("\t\t\t     *            \n");
		printf("\t\t    B ***** C *\n");
		printf("\t\t    *       *   *\n");
		printf("\t\t    *       *     *\n");
		printf("\t\t    *       *       *\n");
		printf("\t\t    D ***** E ******* F\n");
		printf("\t\t   *         *         *\n");
		printf("\t\t  *           *         *\n");
		printf("\t\t G **** K      *         H\n");
		printf("\t\t  *       ***   *     ***\n");
		printf("\t           I         *** J ***\n");
		printf("\n\n=================================================================================\n\n");
		for (int i = 0; type0[i] != '\0'; i++) {
			putchar(type0[i]);  // �� ���ھ� ���
			Sleep(30);  // 30 �и��� ���
		}
		printf("\n");

		randomEdge(graph1);
		lineWeight2(graph1);
		//budget = findMST(mst2);
		//selectMST(mst2, budget);
		Sleep(800);
		tspUsingMST(graph1, edge1);
	}



	free(edge1);
	free(graph1);
}

//������ �˰����� ���� ���� ����ġ ���� �Լ�
void randomEdge(Graph* graph) {
	int i = 0;

	//printf�� �׽�Ʈ��
	//printf("%d %d", mst->node, mst->lineSize);

	//mst����ü�� �ִ� �������� ����ġ(������)���� ����
	srand(time(NULL));
	for (i = 0; i < graph->edges; i++) {
		graph->edge[i].weight = rand() % 10 + 10;
	}

}

//MST�������� ����ġ�� �������� ���� �ϰ� lineWeight()�� ���� �� ������ ���
void randomline(MST* mst) {
	int i = 0;
	
	//printf�� �׽�Ʈ��
	//printf("%d %d", mst->node, mst->lineSize);

	//mst����ü�� �ִ� �������� ����ġ(������)���� ����
	srand(time(NULL));
	for (i = 0; i < mst->fullLine; i++) {
		if (mst->line[i] == 0) {
			
			mst->line[i] = rand() % 10 + 10;
			//printf("[%d] : %d\n",i, mst->line[i]);

		}
		else if(mst->line[i] == -1){
			mst->line[i] = -1;
		}
	}
	
}

//������ ����ġ(����) ���
void lineWeight(MST* mst) {
	int i = 0;
	int j = 0, x = 0;
	for (i = 0; i < mst->node-1; i++) {
		for (j = i+1; j < mst->node; j++) {
			if (mst->line[x] != -1) {
				printf("[%2d] ���� %c - %c �Ǽ� �� ���� : %dõ��\n", x, i + 'A', j + 'A', mst->line[x]);
			}
			
			x++;
		}
	}
}
void lineWeight2(Graph* graph) {
	int i = 0;
	Edge* edge[MAX_EDGES];
	for (i = 0; i < graph->edges; i++) {
		edge[i] = (Edge*)malloc(sizeof(Edge)); // �� Edge ��ü�� ���� �޸� �Ҵ�
	}
	
	/*for (i = 0; i < graph->edges; ++i) {
		printf("���� %c - ���� %c: ����ġ %d\n", edge[i].src + 'A', edge[i].dest + 'A', edge[i].weight);
	}*/
}
//�Ǽ��� ���ε��� �ĺ��� ������ ���ε��� ������ �����ϵ��� ��.
void selectMST(MST* mst, int budget) {
	int i = 0;
	int j = 0, x = 0;
	int num[LINESIZE] = { 0 }, num2[LINESIZE] = { 0 };
	int pass_fail = 0;

	printf("\n��� �������� �ٸ� ��� ������ �� �� �ֵ��� ũ������ �˰����� ����Ͽ� ���ѵ� �������� ���θ� �Ǽ��Ͻÿ�.\n");
	
	for (i = 0; i < mst->node - 1; i++) {
		for (j = i + 1; j < mst->node; j++) {
			if (mst->line[x] != -1) {
				printf("%c - %c : %d�� ����\n", i + 'A', j + 'A', x);
			}

			x++;
		}
	}

	//�������� �ĺ��� num2[]�� ��� �ڵ�
	j = 0;
	for (i = 0; i < mst->fullLine; i++) {
		if (mst->line[i] != -1) {
			num2[j] = mst->line[i];
		}
	}

	re:
	i = 0;
	while (1) {
		printf("�Ǽ��� ������ ��ȣ�� �Է�(-1 �Է½� ���θ� �Ǽ�) : ");
		scanf_s("%d", &num[i]);
		if (num[i] == -1) {
			break;
		}
		else if (mst->line[num[i]] == -1) {
			printf("�߸��� �Է��Դϴ�.\nó������ �ٽ� �Է����ּ���.\n");
			goto re;
		}
		i++;
	}

	pass_fail = numEquals(num, budget, num2, mst);
	if (pass_fail == -1) {
		heart--;
		printf("< ���� ��� : %d >\n", heart);
	}
}

//�־��� �������� ���θ� �Ǽ� �� �� �ִ����� Ȯ���Ͽ� ���� ���� ���θ� �Ǽ����� ���ϸ� -1��, �Ǽ� �����ϸ� 0�� ����
int numEquals(int num[], int budget, int num2[], MST* mst) {
	int i = 0, sum = 0;
	for (i = 0; i < mst->lineSize && num[i] != -1; i++) {
		if (num[i] == -1) {
			continue;
		}
		sum += mst->line[num[i]];
	}
	printf("%dõ��� ���, ���� : %d\n", sum, budget);
	if (budget == sum) {
		printf("�־��� �������� �����ϰ� ���θ� �Ǽ��Ͽ����ϴ�.\n");
		return 0;
	}
	else if(budget > sum) {
		printf("��� ������ �մ� ���θ� �Ǽ����� ���Ͽ����ϴ�.\n");
		return -1;
	}
	else {
		printf("������ �ʰ��Ͽ� ���θ� �Ǽ��Ͽ����ϴ�.\n");
		return -1;
	}
}


//�������� ����ġ(����)�� �޾� ���, ���� �ּ� ������ ����
int findMST(MST* mst) {
	int vertices = 0, edges = 0;
	int budget = 0;
	//printf("��� ������ �Է��ϼ���: ");
	//scanf_s("%d", &vertices);
	//node, vertices ���� ����, lineSize edges ���� ����
	//line, edges ������ ����(�迭, ����ġ�� �Էµ� ����)
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->vertices = mst->node;
	graph->edges = mst->lineSize;

	//printf("�� ��� ���� ����ġ�� �Է��ϼ��� (������� ���� ��� -1 �Է�):\n");
	
	
	
	for (int i = 0; i < mst->node; ++i) {
		for (int j = i + 1; j < mst->node; ++j) {
			int weight;
			//printf("��� %d - ��� %d: ", i, j);
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

	budget = kruskalMST(graph);

	free(graph);
	return budget;
}


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

//ũ������ �˰������� ���� �ּ��� ������ ����
int kruskalMST(Graph* graph) {
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
	int sum = 0;
	printf("�ּ� ���� Ʈ���� ����(���� ����ڵ�, ���� �ּ� ó��):\n");
	for (i = 0; i < e; ++i) {
		
		printf("���� %c - ���� %c: ����ġ %d\n", result[i].src+'A', result[i].dest+'A', result[i].weight);
		sum += result[i].weight;
	}
	printf("���� : %dõ���\n", sum);
	free(subsets);
	return sum;
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

