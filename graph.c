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
