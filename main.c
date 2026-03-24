#include "graph.h"

/*Recebe um ponteiro para um ponteiro de matriz de inteiros e sua quantidade de linhas n;
seta para o ponteiro da matriz o valor NULL;
retorna se a desalocação ocorreu de maneira correta (true, se ocorreu corretamente; false, senão)*/
bool free_matrix(int ***mat, int n){
    if(mat == NULL || *mat == NULL) return false;
    
    for(int i = 0; i < n; i++){
        if((*mat)[i] != NULL)
            free((*mat)[i]);
    }

    free(*mat);
    *mat = NULL;

    return true;
}

//Teste

int main(){
    int n; scanf("%d", &n);
    Graph* G = MyGraph(n);

    print_info(G);

    int m; scanf("%d", &m);
    int x, y, w;
    for(int i = 0; i < m; i++){
        scanf("%d %d %d", &x, &y, &w);
        add_edge(G, x, y, w);
    }

    int **mat = adjacency_matrix(G);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("%d\n", max_neighbors(G));

    free_matrix(&mat, n);

    delete_graph(&G);

    return 0;
}