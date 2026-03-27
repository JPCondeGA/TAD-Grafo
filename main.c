/*========================= Arquivo main.c ===============================*/
#include "graph.h"

int main(){

    int option;
    int N, x, y, w;
    int res;
    bool print_status = 1;
    
    Graph *G = NULL;
    int *ngr = NULL;
    int **mat = NULL;
    int tam_ngr = 0;
    int tam_mat = 0;
    
    scanf("%d", &option);
    
    while (option != -1){
    
        switch (option){
            case 0:
                // criando grafo
                scanf("%d", &N);
                // Caso já tenha um grafo criado e queira criar outro, temos que apagar o anterior primeiro
                if(G != NULL) remove_graph(&G);
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
                // Caso já tenha um vetor de vizinhos criado e queira criar outro, temos que apagar o anterior primeiro
                if(ngr != NULL) free(ngr);
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
                break;
            case 6:
                // pegando matriz de adjacência
                // Caso já tenha uma matriz de adjacência criado e queira criar outro, temos que apagar o anterior primeiro
                if(mat != NULL) remove_mat(&mat, tam_mat);
                mat = adjacency_matrix(G);
                tam_mat = N;
                break;
            default:
                printf("unrecognized option %d!\n", option);
        }
        scanf("%d", &option);
    }

    if(option == -1)
        if(print_status)
            print_info(G, ngr, tam_ngr);
        else
            printf("%d", res);

    //Desalocando vetor de vizinhos
    if(ngr != NULL) free(ngr);
    //Desalocanco matriz de adjacência
    if(mat != NULL) remove_mat(&mat, tam_mat);

    //Desalocando o Grafo
    remove_graph(&G);
    return 0;
}