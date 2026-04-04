#include "graph.h"

int main(){
    
    int option;
    int N, x, y, w;
    int res;
    /* 0 -> imprime o grafo ou o array de vizinhos de um vértice.
    1 -> imprime o que estiver em resp (para exist_edge e remove_edge, se não existir a aresta).
    2 -> imprime o vértice com mais vizinhos.
    3 -> imprime a matriz de adjacência. */
    int print_status = 0;
    
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

                // Não faz permanecer com um array e uma matriz que não corresponde ao novo grafo
                if(mat != NULL) remove_mat(&mat, tam_mat);
                if(ngr != NULL) free(ngr), ngr = NULL;

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
                print_status = 1;
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
                if(res == -1) print_status = 1;
                break;
            case 5:
                // pegando matriz de adjacência
                // Caso já tenha uma matriz de adjacência criado e queira criar outro, temos que apagar o anterior primeiro
                if(mat != NULL) remove_mat(&mat, tam_mat);
                mat = adjacency_matrix(G);
                tam_mat = N;
                print_status = 3;
                break;
            case 6:
                // buscando o com mais vizinhos
                res = max_neighbors(G);
                print_status = 2;
                break;
            default:
                printf("unrecognized option %d!\n", option);
        }
        scanf("%d", &option);
    }

    if(option == -1){
        if(print_status == 0)
            print_info(G, ngr, tam_ngr);
        else if(print_status == 1)
            printf("%d", res);
        else if(print_status == 2)
            printf("max vertex: %d", res);
        else if(print_status == 3){
            printf("Adjacency Matrix:\n");
            if(mat != NULL){
                for(int i = 0; i < tam_mat; i++){
                    for(int j = 0; j < tam_mat; j++){
                        if(mat[i][j] == -1) printf("%3d ", 0);
                        else printf("%3d ", mat[i][j]);
                    }
                    printf("\n");
                }
            }
            
        }
    }

    //Desalocando vetor de vizinhos
    if(ngr != NULL) free(ngr);
    //Desalocanco matriz de adjacência
    if(mat != NULL) remove_mat(&mat, tam_mat);

    //Desalocando o Grafo
    remove_graph(&G);
    return 0;
}
