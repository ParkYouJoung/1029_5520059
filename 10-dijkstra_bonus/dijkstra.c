#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000000

// ����
typedef struct EdgeNode {
    int vertex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

// ����
typedef struct VertexNode {
    EdgeNode* head;
} VertexNode;

// �׷���
typedef struct GraphType {
    int n;
    VertexNode adj[MAX_VERTICES + 1]; // ���� ��ȣ�� 1���� �����ؾ��ؼ� +1
} GraphType;

//�׷��� �ʱ�ȭ
void graph_init(GraphType* g, int n) {
    g->n = n;
    for (int i = 1; i <= n; i++) {
        g->adj[i].head = NULL;
    }
}

//���� �߰�
void insert_edge(GraphType* g, int u, int v, int weight) {
    EdgeNode* node = (EdgeNode*)malloc(sizeof(EdgeNode));
    node->vertex = v;
    node->weight = weight;
    node->next = g->adj[u].head;
    g->adj[u].head = node;
}

//�������� ������ �׷��� ��Ÿ����
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 10, 9, 10);
    insert_edge(g, 9, 5, 18);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 6, 1, 11);
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 6, 2, 7);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 4, 8, 4);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 5, 10, 17);
}

//�湮���� ���� ���� �� ���� ���� ���� ���� ���� �����ϱ�
int choose(int distance[], int n, int found[]) {
    int minpos = -1;
    int min = INT_MAX;
    for (int i = 1; i <= n; i++) {
        if (distance[i] < min && !found[i]) { //�湮x && �ּڰ����� ������
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

//found ����Լ�
void print_status(GraphType* g, int distance[], int found[]) {  
    printf("Distance: ");
    for (int i = 1; i <= g->n; i++) {
        if (distance[i] == INF)
            printf("* ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nFound:    ");
    for (int i = 1; i <= g->n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

//���������� �� �������� ���� ª����� ã��
void FindShortestPath(GraphType* g, int start, int distance[], int found[], int found_order[], int* order_index) {
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[start] = 0;

    for (int i = 1; i <= g->n; i++) {
        print_status(g, distance, found);
        int u = choose(distance, g->n, found);
        if (u == -1) break;
        found[u] = TRUE;
        found_order[(*order_index)++] = u;

        for (EdgeNode* node = g->adj[u].head; node != NULL; node = node->next) {
            int w = node->vertex;
            if (!found[w] && distance[u] + node->weight < distance[w]) {
                distance[w] = distance[u] + node->weight;
            }
        }
    }
}

//�湮�� ���� ���� ����ϱ�
void print_found_order(int found_order[], int order_index) {
    printf("Found Order: ");
    for (int i = 0; i < order_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g, MAX_VERTICES);
    GenerateGraph(g);

    int distance[MAX_VERTICES + 1];
    int found[MAX_VERTICES + 1];
    int found_order[MAX_VERTICES + 1];
    int order_index = 0;

    FindShortestPath(g, 1, distance, found, found_order, &order_index);

    print_found_order(found_order, order_index);

    free(g);
    return 0;
}
