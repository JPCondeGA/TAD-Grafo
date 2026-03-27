/*========================= Arquivo graph.c ===============================*/
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
    return (0 <= v && v < n);
}

bool remove_mat(int ***mat, int n){
    if(mat != NULL && *mat != NULL){

        for(int i = 0; i < n; i++){
            if((*mat)[i] != NULL){
                free((*mat)[i]);
                (*mat)[i] = NULL;
            }
        }
        
        free(*mat);
        *mat = NULL;
        return true;

    }
    return false;
}

/*==========================FUNÇÃO A=============================*/

Graph *MyGraph(int n){
    //Alocando struct
    Graph *G = (Graph*)malloc(sizeof(Graph));
    int i;
    bool flag;

    //Se deu certo a alocação da struct
    if(G != NULL){
        G->n = n;

        //Alocando matriz
        G->matrix = (int**)malloc(sizeof(int*)*n);

        //Se não conseguiu alocar
        if(G->matrix == NULL){
            free(G);
            G = NULL;
        }
        else{
            //Alocando linhas da matriz

            flag = true; //Verifica se todas as alocações ocorrerão corretamente
            for(i = 0; i < n; i++){
                G->matrix[i] = (int*)malloc(sizeof(int)*n);
                
                if(G->matrix[i] == NULL){
                    flag = false;
                    break;
                }
                
                //Inicializando matriz (-1, valor inválido para peso)
                for(int j = 0; j < n; j++){
                    G->matrix[i][j] = -1;
                }

            }

            //Se alguma alocação não deu certo, vamos desalocar tudo e retornar NULL
            if(!flag){
                //Desalocando linhas
                for(i = i - 1; i >= 0; i--) free(G->matrix[i]);

                //Desalocando matriz e grafo
                free(G->matrix);
                free(G);
                
                G = NULL;
            }
        }
    }

    return G;
}

/*==========================FUNÇÃO B=============================*/

/*Como na descrição do trabalho não diz nada sobre grafos direcionados ou não, levamos em conta o caso do grafo não direcionado.
Por isso, ocorre a adição do valor da aresta em matriz[v1][v2] e matriz[v2][v1]*/

bool add_edge(Graph *G, int v1, int v2, int w){
    //Conferindo se os vértices estão no conjunto de vértices do grafo e que o peso é válido
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

int *neighbors(Graph *G, int v, int *tam){

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
            
            *tam = 0;
            for(int i = 0; i < G->n; i++){
                if(G->matrix[v][i] != -1){
                    array[*tam] = i;
                    (*tam)++;
                }

            }
            return array;
        }
    }

    return NULL;
}

/*==========================FUNÇÃO E=============================*/

char remove_edge(Graph *G, int v1, int v2){    
    if (G != NULL && check_vertex(v1, G->n) && check_vertex(v2, G->n) && G->matrix[v1][v2] != -1){
        G->matrix[v1][v2] = -1; //Resseta o peso da aresta para -1
        G->matrix[v2][v1] = -1; //O grafo é não-direcionado
        return 1; //Remoção ocorreu corretamente
    }

    return -1; //Já não havia aresta
}

/*==========================FUNÇÃO F=============================*/

void print_info(Graph* G, int* neighbors, int neighbors_tam){
    if (neighbors == NULL){ //Se não há vizinhos para mostrar
        if (G != NULL){
            int n = G->n;
            bool have_edge = false; //Sinaliza se há ao menos uma aresta no grafo

            //Imprimindo índice dos vértices de 1 a n
            printf("V = [");
            for (int i = 0; i < n-1; i++){
                printf("%d, ", i+1);
            }
            printf("%d]\n", n);

            //Imprimindo arestas no formato (v1,  v2), em que v1 e v2 são os vértices ligados por essa aresta
            printf("E = [");
            for (int i = 0; i < n; i++){
                for (int j = 0; j < i; j++){

                    //Só há aresta se o peso não for negativo
                    if (G->matrix[j][i] != -1){
                        if(!have_edge){
                            printf("(%d, %d)", j+1, i+1);
                            have_edge = true;
                        }else{
                            printf(", (%d, %d)", j+1, i+1);
                        }
                        
                    }
                }
            }
            printf("]\n");
        }
    }
    else{  //Se há vizinhos para mostrar
        //Imprimindo array de vizinhos
        for (int i = 0; i < neighbors_tam-1; i++){
            printf("%d ", neighbors[i] + 1);
        }
        printf("%d\n", neighbors[neighbors_tam-1]+1);
    }
}

/*==========================FUNÇÃO G=============================*/

bool remove_graph(Graph **G){
    if(G == NULL || *G == NULL) return false;

    remove_mat(&((*G)->matrix), (*G)->n);
    
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
    bool flag; 
    int i;

    //Copiando matriz
    if(matrix_aux != NULL){

        flag = true; //Verificar se alocação deu certo
        for(i = 0; i < G->n; i++){
            matrix_aux[i] = (int*)malloc(sizeof(int)*(G->n));

            if(matrix_aux[i] == NULL){
                flag = false;
                break;
            }

            for(int j = 0; j < G->n; j++){
                matrix_aux[i][j] = G->matrix[i][j]; 
            }
        }

        //Se alguma alocação não funcionou, vamos desalocar tudo
        if(!flag){
            for(i = i - 1; i >= 0; i--) free(matrix_aux[i]);
            free(matrix_aux);

            matrix_aux = NULL;
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

        for (int i = n-1; i >= 0; i--){

            int mais_por_linha = 0; //conta quantos vizinhos tem o vértice i
            
            for (int j = n-1; j >= 0; j--){
                if (G->matrix[i][j] != -1)
                    mais_por_linha++;
            }
            if (mais_por_linha >= mais_vizinhos){ 
                mais_vizinhos = mais_por_linha;
                vertice = i;
            }

        }
    }

    return vertice;
}