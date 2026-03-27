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

    if (ngr != NULL) free(ngr);

    remove_graph(&G);
    return 0;
}
