#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*Graph é o tipo abstrato que representa um grafo.*/
typedef struct graph_ Graph;

/*Função A*/
/*Recebe um inteiro n e aloca memória para um Graph de n vértices e nenhuma aresta.
Os vértices desse grafo é numerado de 0 a n. Retorna o endereço da posição da memória alocada.*/
Graph *MyGraph(int n);


/*Função B*/
/*Recebe um ponteiro de Graph, os índices de dois vértice e o peso das arestas e cria uma aresta entre
esses vértices com tal peso. Retorna true, se inserção da arestasa ocorreu corretamente; false, caso contrário.
Estamos considerando que o grafo é não direcionado. O peso deve ser um valor maior ou igual a 0.*/
bool add_edge(Graph *G, int v1, int v2, int w); 

/*Recebe um ponteiro de Graph e os índices de dois vértices e verifica se existe uma aresta entre esses dois vértices.
Retorna true, se existir; false, senão.*/
bool exist_edge(Graph *G, int v1, int v2); //0 ou 1????? 

/*Função D*/
/*Recebe um ponteiro para Graph e o índice de um vértice. Retorna um ponteiro para um array com índices 
dos vértices vizinhos ao passado por parâmetro. Em caso do vértice não ter vizinhos, retorna um ponteiro NULL*/
int *neighbors(Graph *G, int v, int *tam);

/*Função E*/
/*Recebe um ponteiro para Graph e os índices de dois vértices e remove a aresta entre esses dois vértices.
Retorna o valor da aresta que havia entre os dois vértices (-1, em caso de não haver aresta).*/
int remove_edge(Graph *G, int v1, int v2);

/*Função F*/
/*Recebe um ponteiro para Graph e imprime o conjunto de vértices e o conjunto de arestas no formato:
V = [v1, v2, v3, v4,...]
E = [(v1, v2), (v3, v4), ...]
em que vi é o índice do vértice i e (vi, vj) é a aresta que liga os vértices vi e vj*/
void print_info(Graph *G, int *neighbors, int neighbors_tam); 

/*Função G*/
/*Recebe um ponteiro de ponteiro de Graph e desaloca a memória de todo o grafo 
e seta para o ponteiro de Graph o valor nulo, evitando acesso indevido à memória. 
Retorna true, se o processo foi concluído com sucesso; false, senão*/
bool remove_graph(Graph **G); 

/*Função H*/
/*Recebe um ponteiro de Graph e encontra o vértice com maior grau (maior número de vizinhos).
Retorna o índice desse vértice.*/
int max_neighbors(Graph *G); 

/*Função I*/
/*Recebe um ponteiro de Graph e retorna um ponteiro para uma cópia da matriz de adjacência que representa o grafo;
em caso de parâmetro inválido, retorna NULL. Como é uma cópia, a mudança de seus valores não afetará a matriz original 
que representa o gráfico.*/
int **adjacency_matrix(Graph *G);


#include "graph.h"

int main(){

  int option;
  int N, x, y, w;
  int res;
  bool print_status = 1;
  
  Graph *G = NULL;
  int *ngr = NULL;
  int tam_ngr = 0;
  
  scanf("%d", &option);
  
  while (option != -1){
  
    switch (option){
      case 0:
          scanf("%d", &N);
          G = MyGraph(N);
          break;
      case 1:
          // adicionamos
          scanf("%d %d %d", &x, &y, &w);
          add_edge(G, x-1, y-1, w);
          break;
      case 2:
          // get
          scanf("%d %d", &x, &y);
          res = exist_edge(G, x-1, y-1);
          print_status = 0;
          break;
      case 3:
          // buscando vizinhos
          scanf("%d", &x);
          ngr = neighbors(G, x-1, &tam_ngr);
          break;
      case 4:
          // removendo
          scanf("%d %d", &x, &y);
          res = remove_edge(G, x-1, y-1);
          if(res == -1) print_status = 0;
          break;
      case 5:
          // buscando o com mais vizinhos
          res = max_neighbors(G);
          print_status = 0;
      default:
          printf("unrecognized option %d!\n", option);
    }
    scanf("%d", &option);
  }

  if (option == -1)
    if (print_status)
      print_info(G, ngr, tam_ngr);
    else
      printf("%d", res);

  remove_graph(&G);
  return 0;
}


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


/*==========================FUNÇÃO A=============================*/

Graph *MyGraph(int n){
    //Alocando struct
    Graph *G = (Graph*)malloc(sizeof(Graph));

    //Se deu certo a alocação da struct
    if(G != NULL){
        G->n = n;

        //Alocando matriz
        G->matrix = (int**)malloc(sizeof(int*)*n);

        //Alocando linhas da matriz
        for(int i = 0; i < n; i++){
            G->matrix[i] = (int*)malloc(sizeof(int)*n);
            
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

int remove_edge(Graph *G, int v1, int v2){    
    if (G != NULL && check_vertex(v1, G->n) && check_vertex(v2, G->n)){
        G->matrix[v1][v2] = -1; //Resseta o peso da aresta para -1
        return 1;
    }

    return -1;
}

/*==========================FUNÇÃO F=============================*/

/*Função que mostra o conjunto V dos vértices do grafo, assim com o conjunto de tuplas E das arestas*/
void print_info(Graph* G, int* neighbors, int neighbors_tam){
    if (neighbors == NULL){
        if (G != NULL){
            int n = G->n;
            bool have_edge = false;

            //Imprimindo índice dos vértices de 1 a n
            printf("V = [");
            for (int i = 0; i < n-1; i++){
                printf("%d, ", i+1);
            }
            printf("%d]\n", n);

            //Imprimindo arestas no formato (v1,  v2), em que v1 e v2 sao os vértices ligados por essa aresta
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
    else{   
        for (int i = 0; i < neighbors_tam-1; i++){
            printf("%d ", neighbors[i] + 1);
        }
        printf("%d\n", neighbors[neighbors_tam-1]+1);
    }
}

/*==========================FUNÇÃO G=============================*/

bool remove_graph(Graph **G){
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
            if (mais_por_linha >= mais_vizinhos){ 
                mais_vizinhos = mais_por_linha;
                vertice = i;
            }

        }
    }

    return vertice;
}

