#include <string.h> /* memcpy */
#include <stdlib.h>
#include <stdio.h>

#include "grafo.h"

#define RELEASE 1

static void ler_arestas(Grafo *grafo, int m);
static void ler_comandos(Grafo *grafo);

/**
 * O programa principal receberá sempre um argumento.
 * Se este argumento for 'B', realiza a busca em largura,
 * caso contrário, a busca em profundidade.
 */
int main(int argc, char *argv[])
{
    Grafo *grafo;

    if (argc < 2) {
        return 1;
    }
    
#if RELEASE
    int n, m;
    scanf("%d %d\n", &n, &m);

    grafo = criar_grafo(n, 1, MATRIZ_DE_ADJACENCIA);
#else
    grafo = criar_grafo(5, 1, MATRIZ_DE_ADJACENCIA);
#endif

#if RELEASE
    ler_arestas(grafo, m);
#else
    ler_arestas(grafo, 10);
#endif
    
#if RELEASE
#else
    imprimir_grafo(grafo);
#endif
    
    ler_comandos(grafo);

    destruir_grafo(grafo);

    return 0;
}

void ler_arestas(Grafo *grafo, int m)
{
#if RELEASE
    int u, v, p;
#else
    int us[11] = {3, 1, 4, 2, 3, 4, 2, 1, 3, 2};
    int vs[11] = {1, 0, 1, 3, 0, 0, 1, 3, 4, 0};
    int ps[11] = {7056, 6702, 3998, 2283, 3543, 2029, 2190, 5429, 1212, 9648};
#endif
    
    int i;
    for (i = 0; i < m; ++i)
    {
#if RELEASE
        scanf("%d %d %d\n", &u, &v, &p);
        adicionar_aresta(grafo, u, v, p);
#else
        adicionar_aresta(grafo, us[i], vs[i], ps[i]);
#endif
    }
}

void ler_comandos(Grafo *grafo) {
    
#if RELEASE
    int origem;
    int destino;
    
    while (scanf("%d %d", &origem, &destino) != EOF) {
        algoritmo_dijkstra(grafo, origem, destino);
    }
#else
    algoritmo_dijkstra(grafo, 0, 1);
    algoritmo_dijkstra(grafo, 2, 4);
#endif

}
