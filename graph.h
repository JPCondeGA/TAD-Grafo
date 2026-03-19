#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct graph_ Graph;

Graph *MyGraph(int n);
//Luiz
bool add_edge(Graph *G, int v1, int v2, int w); //verificar se v1 <= N e v2 <= N; não pode adicionar aresta de valor negativo
//Edu
bool exist_edge(Graph *G, int v1, int v2);  
//Luiz
int *neighbors(Graph *G, int v);
//Edu
int remove_edge(Graph *G, int v1, int v2); //retornar -1, se não existir aresta
//Nevex
void print_info(Graph *G); //formato especificado no final do arquivo do trabalho
//Conde
bool delete_graph(Graph **G); //colocar nulo dentro da função
//Neves
int max_neighbors(Graph *G); //primeiro com mais vizinhos
//Conde
int **adjacency_matrix(Graph *G); //por enquanto faz retornando


//Dúvidas
//Parâmetros são indexados?
//Pode usar bool?
//Impressão da d como?
//e -> retornar -1?
//i -> printar ou retornar?