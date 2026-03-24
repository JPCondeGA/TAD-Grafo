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
            }

        }
    }

    return G;
}

/*Eduardo*/
bool exist_edge(Graph *G, int v1, int v2){
  if (G != NULL && G->matrix[v1][v2] > -1) return true;
  
  return false;
}

int remove_edge(Graph *G, int v1, int v2){
  if (G != NULL){
    int aux = G->matrix[v1][v2];
    G->matrix[v1][v2] = -1;
    return aux;
  }
  return -1;
}

/*João Conde*/
bool delete_graph(Graph **G){
    if(G == NULL || *G == NULL) return false;

    for(int i = 0; i < (*G)->n; i++){

        if((*G)->matrix[i] != NULL){
            free((*G)->matrix[i]);
            (*G)->matrix[i] = NULL;
        }
    }

    free(*G);
    *G = NULL;
    return true;
}


int **adjacency_matrix(Graph *G){
    if(G == NULL) return NULL; 

    /*Não podemos retornar a G->matrix em si, pois seria possível manipular os valores interiores do TAD
    sem ser por meio somente das funções, quebrando o conceito de TAD. Desse modo, vamos retorna a matrix_aux*/
    int **matrix_aux = (int**)malloc(sizeof(int*)*(G->n)); //A alocação deve ser dinâmica para que a matrix_aux não seja apagada ao fim da função

    //Copiando matriz
    for(int i = 0; i < G->n; i++){
        matrix_aux[i] = (int*)malloc(sizeof(int)*(G->n));
        for(int j = 0; j < G->n; j++){
            matrix_aux[i][j] = G->matrix[i][j]; 
        }
    }

    return matrix_aux;
}


/* João Neves*/

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
        printf("]\n");

    }
    return;
}

int max_neighbors(Graph *G){
    int vertice = -1;
    if (G != NULL){
        int maisVizinhos = 0;
        int n = G->n;
        for (int i = n-1; i >= 0; i--){
            int maisPorLinha = 0;
            for (int j = n-1; j >= 0; j--){
                if (G->matrix[i][j] != -1)
                    maisPorLinha++;
            }
            if (maisPorLinha >= maisVizinhos){
                maisVizinhos = maisPorLinha;
                vertice = i + 1;
            }
        }
    }

    return vertice;
}

/*Luiz Henrique*/

//como na descricao do trabalho nao diz nada sobre grafos direcionados ou nao, so levei em conta o caso do grafo nao direcionado
//por isso a adicao do valor da aresta em matriz[v1][v2] e matriz[v2][v1]
bool add_edge(Graph *G, int v1, int v2, int w){

    if(G != NULL && v1 >= 0 && v1 < G->n && v2 >= 0 && v2 < G->n && w >= 0){
        G->matrix[v1][v2] = w;
        G->matrix[v2][v1] = w;
        return true;
    }
    
    return false;
}

//essa funcao retorna um array de um elemento (-1) caso o vertice dado nao possui vertices adjacentes
int *neighbors(Graph *G, int v){

    int grau = 0;

    if(G != NULL && v < G->n){
        for(int i = 0; i < G->n; i++){
            if(G->matrix[v][i] != -1){
                grau++;
            }
        }
        
        if(grau != 0){

            int *array = (int*)malloc(sizeof(int)*grau);
            
            int n = 0;
            for(int i = 0; i < G->n; i++){
                if(G->matrix[v][i] != -1){
                    array[n] = i;
                    n++;
                }

            }
            return array;
        }
        else{
            int *array = (int*)malloc(sizeof(int));
            array[0] = -1;
            return array;
        }
    }

    return NULL;
}
