#include "graph.h"

struct graph_{
    int **matrix;
    int n;
};

Graph *MyGraph(int n){
    Graph *G = (Graph*)malloc(sizeof(Graph));
    
    if(G != NULL){
        G->n = n;
        G->matrix = (int**)malloc(sizeof(int*)*n);
        
        for(int i = 0; i < n; i++){
            G->matrix[i] = (int*)malloc(sizeof(int)*n);
            
            for(int j = 0; j < n; j++){
                G->matrix[i][j] = -1;
                printf("%d ", G->matrix[i][j]);
            }

            printf("\n");
        }
    }

    return G;
}




/* João Neves*/

/*Função que mostra o conjunto V dos vértices do grafo, assim com o conjunto de tuplas E das arestas*/
void print_info(Graph* G){
    if (G != NULL){
        int n = G->n;
        printf("V = [");
        for (int i = 0; i < n - 1; i++){
            printf("%d, ", i+1);
        }
        printf("%d]\n", n);

        printf("E = [");
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (G->matrix[i][j] != -1){
                    printf("(%d, %d), ", i+1, j+1);
                }
            }
        }
        printf("\b\b]\n");

    }
    return;
}

/*Função que retorna o número do vértice que contém mais vizinhos*/
int max_neighbors(Graph *G){
    int vertice = -1;
    if (G != NULL){
        int n = G->n;
        
        int maisVizinhos = 0;
        
        for (int i = 0; i < n; i++){
            int maisPorLinha = 0;
            for (int j = 0; j < n; j++){
                if (G->matrix[i][j] != -1)
                    maisPorLinha++;
            }
            if (maisPorLinha > maisVizinhos){
                maisVizinhos = maisPorLinha;
                vertice = i + 1;
            }
        }
    }

    return vertice;
}