#include "graph.h"

/*==========================STRUCT=============================*/
struct graph_{
    int **matrix; //Ponteiro para matriz de adjacência
    int n; //Quantidade de vértices do grafo
};

/*======================FUNÇÃO AUXILIARES=========================*/

/*Recebe o índice de um vértice e o número de vértices e verifica se o índice é válido.
Retorna true, se o índice está entre 0 e n (inclusivo); false, caso contrário.*/
bool check_vertex(int v, int n){
    return (0 <= v && v <= n);
}


/*==========================FUNÇÃO A=============================*/

Graph *MyGraph(int n){
    //Alocando struct
    Graph *G = (Graph*)malloc(sizeof(Graph));

    //Se deu certo a alocação da struct
    if(G != NULL){
        G->n = n;

        //Alocando matriz
        G->matrix = (int**)malloc(sizeof(int*)*(n+1));

        //Alocando linhas da matriz
        for(int i = 0; i < n; i++){
            G->matrix[i] = (int*)malloc(sizeof(int)*(n+1));
            
            //Inicializando matriz (-1, valor inválido para peso)
            for(int j = 0; j < n; j++){
                G->matrix[i][j] = -1;
            }

        }
    }

    return G;
}

/*==========================FUNÇÃO B=============================*/

/*Como na descrição do trabalho não diz nada sobre grafos direcionados ou não, levamos em conta o caso do grafo não direcionado.
Por isso, ocorre a adição do valor da aresta em matriz[v1][v2] e matriz[v2][v1]*/

bool add_edge(Graph *G, int v1, int v2, int w){

    //Conferindo se os vértices estão no conjunto de vértices do grafo
    if(G != NULL && check_vertex(v1, G->n) && check_vertex(v2, G->n) && w >= 0){
        G->matrix[v1][v2] = w;
        G->matrix[v2][v1] = w;
        return true;
    }
    
    return false;
}

/*==========================FUNÇÃO C=============================*/

bool exist_edge(Graph *G, int v1, int v2){
    //Pesos negativos não são válidos para uma aresta, isto é, se há uma aresta, seu peso deve ser maior ou igual a 0
    if(G != NULL && check_vertex(v1, G->n) && check_vertex(v2, G->n) && G->matrix[v1][v2] > -1) return true;
  
    return false;
}

/*==========================FUNÇÃO D=============================*/

int *neighbors(Graph *G, int v){

    int grau = 0; 

    //Conferindo se o ponteiro para grafo e vértice são válidos
    if(G != NULL && check_vertex(v, G->n)){

        //Caminhando pela linha v na matriz de adjacência para contar os vizinhos
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
    }

    return NULL;
}

/*==========================FUNÇÃO E=============================*/

int remove_edge(Graph *G, int v1, int v2){
    int aux = -1;
    
    if (G != NULL && check_vertex(v1, G->n) && check_vertex(v2, G->n)){
        aux = G->matrix[v1][v2]; 
        G->matrix[v1][v2] = -1; //Resseta o peso da aresta para -1
    }

    return aux;
}

/*==========================FUNÇÃO F=============================*/

void print_info(Graph* G){
    if (G != NULL){
        int n = G->n;

        //Imprimindo índice dos vértices de 1 a n
        printf("V = [");
        for (int i = 0; i <= n - 1; i++){
            printf("%d, ", i);
        }
        printf("%d]\n", n);

        //Imprimindo arestas no formato (v1,  v2), em que v1 e v2 sao os vértices ligados por essa aresta
        printf("E = [");
        for (int i = 0; i < n; i++){
            for (int j = 0; j <= n; j++){

                //Só há aresta se o peso não for negativo
                if (G->matrix[i][j] != -1){
                    printf("(%d, %d), ", i, j);
                }
                
            }
        }
        printf("]\n");

    }
    return;
}

/*==========================FUNÇÃO G=============================*/

bool delete_graph(Graph **G){
    if(G == NULL || *G == NULL) return false;

    for(int i = 0; i < (*G)->n; i++){
    
        //Liberando a alocação de cada linha da matriz
        if((*G)->matrix[i] != NULL){
            free((*G)->matrix[i]);
            (*G)->matrix[i] = NULL;
        }
    
    }
    
    //Liberando a alocação da matriz
    free((*G)->matrix);
    
    //Liberando a alocação da struct do grafo
    free(*G);
    
    //Setando valor para impedir acesso indevido a memória
    *G = NULL;
    return true;
}

/*==========================FUNÇÃO H=============================*/

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

/*==========================FUNÇÃO I=============================*/

int max_neighbors(Graph *G){
    int vertice = -1; //Se G for um ponteiro inválido, retorna -1

    if (G != NULL){

        int mais_vizinhos = 0; //Guarda o maior grau de um vértice naquele grafo
        int n = G->n;

        for (int i = n; i >= 0; i--){

            int mais_por_linha = -1; //conta quantos vizinhos tem o vértice i
            //Começa em -1, para pelo menos entrar uma vez no if
            
            for (int j = n; j >= 0; j--){
                if (G->matrix[i][j] != -1)
                    mais_por_linha++;
            }

            if (mais_por_linha >= mais_vizinhos){ //somente >, para pegar o primeiro
                mais_vizinhos = mais_por_linha;
                vertice = i;
            }

        }
    }

    return vertice;
}
