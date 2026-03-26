#ifndef GRAPH_H
    #define GRAPH_H

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
    int *neighbors(Graph *G, int v);

    /*Função E*/
    /*Recebe um ponteiro para Graph e os índices de dois vértices e remove a aresta entre esses dois vértices.
    Retorna o valor da aresta que havia entre os dois vértices (-1, em caso de não haver aresta).*/
    int remove_edge(Graph *G, int v1, int v2);

    /*Função F*/
    /*Recebe um ponteiro para Graph e imprime o conjunto de vértices e o conjunto de arestas no formato:
    V = [v1, v2, v3, v4,...]
    E = [(v1, v2), (v3, v4), ...]
    em que vi é o índice do vértice i e (vi, vj) é a aresta que liga os vértices vi e vj*/
    void print_info(Graph *G); 

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

#endif