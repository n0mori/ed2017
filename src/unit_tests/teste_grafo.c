#include <stdio.h>
#include <stdlib.h>
#include "../modules/Grafo/Grafo.h"

typedef struct basicVert {
    double x, y;
}* BData;

BData new_bdata(double x, double y) {
    BData data = malloc(sizeof(struct basicVert));

    data->x = x;
    data->y = y;

    return data;
}

int main() {
    Grafo g = new_grafo();
    BData data;
    Lista list = create_lista();

    grafo_insert_vertex(g, "A", new_bdata(0, 0));
    grafo_insert_vertex(g, "B", new_bdata(10, 0));
    grafo_insert_vertex(g, "C", new_bdata(20, 0));
    grafo_insert_vertex(g, "D", new_bdata(30, 0));

    data = grafo_get_vertex_data(g, "B");
    if (data != NULL) {
        printf("Data existente: %f %f\n", data->x, data->y);
    }

    data = grafo_get_vertex_data(g, "E");
    if (data != NULL) {
        printf("Data existente: %f %f\n", data->x, data->y);
    }

    grafo_insert_edge(g, "A", "B", new_bdata(2, 0));
    grafo_insert_edge(g, "A", "C", new_bdata(3, 2));
    grafo_insert_edge(g, "A", "D", new_bdata(4, 4));
    grafo_insert_edge(g, "A", "E", new_bdata(3, 2));

    if (grafo_adjacente(g, "A", "B")) {
        puts("Existe");
    }

    if (grafo_adjacente(g, "A", "E")) {
        puts("Existe");
    }

    grafo_remove_edge(g, "A", "B");

    if (grafo_adjacente(g, "A", "B")) {
        puts("Existe2");
    }

    grafo_adjacentes(g, "A", list);

    while (length_lista(list) > 0) {
        BData b = edge_get_data(remove_last(list));
        printf("%f %f\n", b->x, b->y);
        free(b);
    }
    free_lista(list);

    return 0;
}