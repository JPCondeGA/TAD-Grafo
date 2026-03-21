#ifndef GRAPH_H
    #define GRAPH_H

    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>

    typedef struct graph_ Graph;

    /*Recebe um inteiro n e aloca memória para um Graph de n vértices e nenhuma aresta;
    retorna o endereço da posição da memória alocada.*/
    Graph *MyGraph(int n);
    //Luiz
    bool add_edge(Graph *G, int v1, int v2, int w); //verificar se v1 <= N e v2 <= N; não pode adicionar aresta de valor negativo
    //Edu
    bool exist_edge(Graph *G, int v1, int v2);  
    //Luiz
    int *neighbors(Graph *G, int v);
    //Edu
    int remove_edge(Graph *G, int v1, int v2); //retornar -1, se não existir aresta
    //Neves
    void print_info(Graph *G); //formato especificado no final do arquivo do trabalho
    //Conde
    /*Recebe um ponteiro de ponteiro de Graph e desaloca a memória de todo o grafo 
    e seta para o ponteiro de Graph o valor nulo, evitando acesso indevido à memória. 
    Retorna true, se o processo foi concluído com sucesso; false, senão*/
    bool delete_graph(Graph **G); 
    //Neves
    int max_neighbors(Graph *G); //primeiro com mais vizinhos
    //Conde
    /*Recebe um ponteiro de Graph e retorna um ponteiro para matriz de adjacência que representa o grafo;
    em caso de parâmetro inválido, retorna NULL*/
    int **adjacency_matrix(Graph *G); //por enquanto faz retornando


    //Dúvidas
    //Parâmetros são indexados?
    //Pode usar bool?
    //Impressão da d como?
    //e -> retornar -1?
    //i -> printar ou retornar?

#endif