#include "graph.h"

int main(){
    int n; scanf("%d", &n);
    Graph* G = MyGraph(n);

    print_info(G);
    printf("%d\n", max_neighbors(G));

    return 0;
}