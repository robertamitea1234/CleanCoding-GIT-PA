#include <stdio.h>
#include <stdlib.h>

// Nume de noduri = restaurante (int-uri)
typedef struct Node
{
    int data;
    struct Node* next;
} NODE;

typedef struct Graph
{
    int vertices;
    int* visited;
    NODE** adjacency_list;
} GRAPH;

typedef struct Stack
{
    int top;
    int capacity;
    int* array;
} STACK;

NODE* create_node(int value)
{
    NODE* new_node = malloc(sizeof(NODE));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

GRAPH* create_graph(int vertices)
{
    GRAPH* graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;

    graph->visited = malloc(vertices * sizeof(int));
    graph->adjacency_list = malloc(vertices * sizeof(NODE*));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_list[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void add_edge(GRAPH* graph, int src, int dest)
{
    NODE* new_node = create_node(dest);
    new_node->next = graph->adjacency_list[src];
    graph->adjacency_list[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_list[dest];
    graph->adjacency_list[dest] = new_node;
}

STACK* create_stack(int capacity)
{
    STACK* stack = malloc(sizeof(STACK));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = malloc(capacity * sizeof(int));
    return stack;
}

void push(STACK* stack, int value)
{
    stack->top++;
    stack->array[stack->top] = value;
}

void dfs(GRAPH* graph, STACK* stack, int vertex)
{
    NODE* adj_list = graph->adjacency_list[vertex];
    NODE* temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);
    push(stack, vertex);

    while (temp != NULL)
    {
        int connected = temp->data;
        if (graph->visited[connected] == 0)
        {
            dfs(graph, stack, connected);
        }
        temp = temp->next;
    }
}

void reset_visited(GRAPH* graph, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void insert_edges(GRAPH* graph, int edge_count)
{
    int src, dest;
    printf("Adauga %d muchii (nodurile incep de la 0):\n", edge_count);

    for (int i = 0; i < edge_count; i++)
    {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int main()
{
    int vertices;
    int edge_count;
    int restaurant1, restaurant2;

    printf("Cate noduri (restaurante) are graful? ");
    scanf("%d", &vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &edge_count);

    GRAPH* graph = create_graph(vertices);
    STACK* stack = create_stack(2 * vertices);

    insert_edges(graph, edge_count);

    printf("Verificam daca exista drum intre doua restaurante.\n");
    printf("Introduceti cele doua noduri (ex: 0 3): ");
    scanf("%d %d", &restaurant1, &restaurant2);

    dfs(graph, stack, restaurant1);

    if (graph->visited[restaurant2])
    {
        printf("\nExista drum intre %d si %d.\n", restaurant1, restaurant2);
    }
    else
    {
        printf("\nNu exista drum intre %d si %d.\n", restaurant1, restaurant2);
    }

    return 0;
}
