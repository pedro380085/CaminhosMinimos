#include "grafo_matriz.h"

#include <stdlib.h>
#include <stdio.h>

#include "fila.h"

struct grafo_m
{
    int n;
    int digrafo;
    int **adj;
    int **peso;
};

GrafoM *criar_grafo_m(int n, int digrafo)
{
    if (n < 0)
        return NULL;

    GrafoM *grafo = (GrafoM *) malloc(sizeof(GrafoM));

    grafo->n = n;
    grafo->digrafo = digrafo;
    grafo->adj = (int **) malloc(n * sizeof(int *));
    grafo->peso = (int **) malloc(n * sizeof(int *));

    int i, j;
    for (i = 0; i < n; ++i)
    {
        grafo->adj[i] = (int *) malloc(n * sizeof(int));
        grafo->peso[i] = (int *) malloc(n * sizeof(int));

        for (j = 0; j < n; ++j)
        {
            grafo->adj[i][j] = 0;
            grafo->peso[i][j] = 0;
        }
    }

    return grafo;
}

void destruir_grafo_m(GrafoM *grafo)
{
    if (grafo == NULL)
        return;

    int i;
    for (i = 0; i < grafo->n; ++i)
    {
        free(grafo->adj[i]);
        free(grafo->peso[i]);
    }

    free(grafo->adj);
    free(grafo->peso);
    free(grafo);
}

GrafoM *transposto_m(const GrafoM *grafo)
{
    if (grafo == NULL || !grafo->digrafo)
        return NULL;

    GrafoM *resultado = criar_grafo_m(grafo->n, 1);

    int i, j;
    for (i = 0; i < grafo->n; ++i)
    {
        for (j = 0; j < grafo->n; ++j)
        {
            resultado->adj[i][j] = grafo->adj[j][i];
            resultado->peso[i][j] = grafo->peso[j][i];
        }
    }

    return resultado;
}

int e_digrafo_m(const GrafoM *grafo)
{
    if (grafo == NULL)
        return 0;

    return grafo->digrafo;
}

int n_vertices_m(const GrafoM *grafo)
{
    if (grafo == NULL)
        return 0;

    return grafo->n;
}

int existe_aresta_m(const GrafoM *grafo, int u, int v)
{
    if (grafo == NULL || u < 0 || v < 0 || u >= grafo->n || v >= grafo->n)
        return 0;

    return grafo->adj[u][v];
}

void adicionar_aresta_m(GrafoM *grafo, int u, int v, int peso)
{
    if (grafo == NULL || u < 0 || v < 0 || u >= grafo->n || v >= grafo->n)
        return;

    grafo->adj[u][v] = 1;
    grafo->peso[u][v] = peso;

    if (!grafo->digrafo)
    {
        grafo->adj[v][u] = 1;
        grafo->peso[v][u] = peso;
    }
}

void remover_aresta_m(GrafoM *grafo, int u, int v)
{
    if (grafo == NULL || u < 0 || v < 0 || u >= grafo->n || v >= grafo->n)
        return;

    grafo->adj[u][v] = 0;

    if (!grafo->digrafo)
        grafo->adj[v][u] = 0;
}

int peso_aresta_m(const GrafoM *grafo, int u, int v)
{
    if (grafo == NULL || u < 0 || v < 0 || u >= grafo->n || v >= grafo->n)
        return 0;

    return grafo->adj[u][v] ? grafo->peso[u][v] : 0;
}

void imprimir_grafo_m(const GrafoM *grafo)
{
    if (grafo == NULL)
        return;

    int i, j;
    for (i = 0; i < grafo->n; ++i)
    {
        for (j = 0; j < grafo->n; ++j)
            if (grafo->adj[i][j])
                printf("%d ", grafo->peso[i][j]);
            else
                printf(". ");
        printf("\n");
    }
}

int cabeca_ordenacao_topologica_m(const GrafoM *grafo) {
    
    // Primeiro precisamos achar a cabeça do grafo
    int i, j, f, inicial = -1;
    
    for (i = 0; i < grafo->n; ++i) {
        f = 0;
        for (j = 0; j < grafo->n; ++j) {
            if (grafo->adj[j][i]) {
                f = 1;
                break;
            }
        }
        
        // Encontramos nossa cabeça
        if (f == 0) {
            inicial = i;
            break;
        }
    }
    
    return inicial;
}

int cauda_ordenacao_topologica_m(const GrafoM *grafo) {
    
    // Primeiro precisamos achar a cabeça do grafo
    int i, j, f, final = -1;
    
    for (i = 0; i < grafo->n; ++i) {
        f = 0;
        for (j = 0; j < grafo->n; ++j) {
            if (grafo->adj[i][j]) {
                f = 1;
                break;
            }
        }
        
        // Encontramos nossa cabeça
        if (f == 0) {
            final = i;
            break;
        }
    }
    
    return final;
}

void adjacentes_m(const GrafoM *grafo, int u, int *v, int max)
{
    if (grafo == NULL || u < 0 || u >= grafo->n)
        return;

    int i, j = 0;
    for (i = 0; i < grafo->n && i < max-1; ++i)
        if (grafo->adj[u][i])
            v[j++] = i;
    v[j] = -1;
}

#define INFINITO 99999
#define MARCADO 1
#define MAXN 1000

#define RELEASE 1

int algoritmo_prim_m(const GrafoM *grafo) {
    
    int vertices[MAXN];
    int total = 0;
    
    for (int i = 0; i < grafo->n; i++) {
        vertices[i] = 0;
    }
    
    // Vamos primeiro contar o numero de arestas
    int numeroArestas = 0;
    for (int i = 0; i < grafo->n; i++) {
        for (int j = 0; j < grafo->n; j++) {
            if (grafo->adj[i][j]) numeroArestas++;
        }
    }
    
    int firstRun = 1;

    // Vamos passar por todas as arestas
    for (int h = 0; h < numeroArestas; h++) {

        // Vamos encontrar a aresta com menor peso
        int arestaComMenorPeso = INFINITO;
        int iMenor = 0;
        int jMenor = 0;
        
        for (int i = 0; i < grafo->n; i++) {
            for (int j = 0; j < grafo->n; j++) {
                if (grafo->adj[i][j] && grafo->peso[i][j] < arestaComMenorPeso && (firstRun || vertices[i] == MARCADO || vertices[j] == MARCADO) && !(vertices[i] == MARCADO && vertices[j] == MARCADO)) {
                    arestaComMenorPeso = grafo->peso[i][j];
                    iMenor = i;
                    jMenor = j;
                }
            }
        }
        
        // No início precisamos desmarcar a necessidade dos vértices já terem
        // sido visitados pois estamos procurando a primeira aresta
        firstRun = 0;
        
        // Se não encontrou mais nenhum caminho, acaba
        int temp = 0;
        for (int i = 0; i < grafo->n; i++) {
            temp += vertices[i];
        }
        if (temp == grafo->n) break;

#if RELEASE
#else
        // Debug information
        printf("\n");
        imprimir_grafo_m(grafo);
#endif
        
        // Marca arestas como marcadas
        vertices[iMenor] = MARCADO;
        vertices[jMenor] = MARCADO;
        grafo->adj[iMenor][jMenor] = 0;
        total += arestaComMenorPeso;
        
#if RELEASE
#else
        // Debug information
        printf("\n");
        printf("\n-------- %d %d %d\n", iMenor, jMenor, total);
        for (int i = 0; i < grafo->n; i++) {
            printf("%d", vertices[i]);
        }
        printf("\n\n");
#endif
        
    }
    
    return total;
}

int algoritmo_dijkstra_m(const GrafoM *grafo, int origem, int destino) {
    
    int **cost = (int **) malloc(n_vertices_m(grafo) * sizeof(int *));
    int *distance = (int *) malloc(n_vertices_m(grafo) * sizeof(int));
    int *pred = (int *) malloc(n_vertices_m(grafo) * sizeof(int));
    int *visited = (int *) malloc(n_vertices_m(grafo) * sizeof(int));
    
    int i,j;
    for (i = 0; i < n_vertices_m(grafo); i++) {
        cost[i] = (int *) malloc(n_vertices_m(grafo) * sizeof(int));
    }
    
    int count = 0;
    int mindistance = INFINITO;
    int nextnode = 0;
    
    // Create our matrix with costs
    for (i = 0; i < grafo->n; i++) {
        for (j = 0; j < grafo->n; j++) {
            if (grafo->adj[i][j] == 0) {
                cost[i][j] = INFINITO;
            } else {
                cost[i][j] = grafo->adj[i][j];
            }
        }
    }
    
    
    // Initialize variables
    for (i = 0; i < grafo->n; i++) {
        distance[i] = cost[origem][i];
        pred[i] = origem;
        visited[i] = 0;
    }
    distance[origem] = 0;
    visited[origem] = 1;
    count = 1;
    
    // Identify edges
    while (count < (grafo->n - 1)) {
        // Find minimum distance
        mindistance = INFINITO;
        for (i = 0; i < grafo->n; i++) {
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        }
        
        // Break if we found our destiny
        if (distance[nextnode] == INFINITO || nextnode == destino) {
            break;
        }

        // Find a better cost for a given path
        visited[nextnode] = 1;
        for (i = 0; i < grafo->n; i++) {
            if (!visited[i]) {
                if ((mindistance + cost[nextnode][i]) < distance[i]) {
                    distance[i] = (mindistance + cost[nextnode][i]);
                    pred[i] = nextnode;
                }
            }
        }
        count++;
    }
    
#if RELEASE
#else
    // Debug information
    for (int i = 0; i < grafo->n; i++) {
        printf("%d", pred[i]);
    }
    printf("\n");
#endif

    // Print our path
    if (origem != destino) {
        
        int size = 0;
        int inverse[MAXN];
        j = destino;
        
        do {
            j = pred[j];
            size++;
            inverse[size] = j;
        } while (j != origem);
        
        if (size > 1) {
            for (j = size; j > 0; j--) {
                printf("%d ", inverse[j]);
            }
            printf("%d", destino);
        }
        printf("\n");
    }
    
    return 1;
}

#define BRANCO 0
#define CINZA  1
#define PRETO 2

#define INF -1
#define NIL -1

#define PARAR 0
#define CONTINUAR 1

static int visitar_profundidade(const GrafoM *grafo, int u,
        vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args,
        int *cor, int *d, int *p, int *f)
{
    cor[u] = CINZA;

    if (processa_vertice && processa_vertice(u, cor, d, p, args) == PARAR) {
        return PARAR;
    }

    int v;
    for (v = 0; v < grafo->n; ++v)
    {
        
        if (grafo->adj[u][v] == 0) {
            continue;
        }

        if (processa_aresta && processa_aresta(u, v, cor, d, p, args) == PARAR) {
            return PARAR;
        }

        if (cor[v] == BRANCO) {
            p[v] = u;
            d[v] = d[u] + 1;
            visitar_profundidade(grafo, v, processa_vertice, processa_aresta, args, cor, d, p, f);
        }
    }

    cor[u] = PRETO;
    int i;
    for (i = 0; i < grafo->n; i++) {
        if (f[i] == -1) {
            f[i] = u;
            break;
        }
    }

    return CONTINUAR;
}

void busca_em_profundidade_m(const GrafoM *grafo, int s,
        vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args)
{
    if (grafo == NULL || s < 0 || s >= grafo->n)
        return;

    int *cor = (int *) malloc(grafo->n * sizeof(int));
    int *d = (int *) malloc(grafo->n * sizeof(int));
    int *p = (int *) malloc(grafo->n * sizeof(int));
    int *f = (int *) malloc(grafo->n * sizeof(int));

    int i;
    for (i = 0; i < grafo->n; ++i)
    {
        cor[i] = BRANCO;
        p[i] = NIL;
        d[i] = INF;
        f[i] = NIL;
    }

    d[s] = 0;
    visitar_profundidade(grafo, s, processa_vertice, processa_aresta, args, cor, d, p, f);
    
    free(cor);
    free(d);
    free(p);
}

void ordenacao_topologica_m(const GrafoM *grafo, int s,
                            vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args) {
    if (grafo == NULL || s < 0 || s >= grafo->n)
        return;
    
    int *cor = (int *) malloc(grafo->n * sizeof(int));
    int *d = (int *) malloc(grafo->n * sizeof(int));
    int *p = (int *) malloc(grafo->n * sizeof(int));
    int *f = (int *) malloc(grafo->n * sizeof(int));
    
    int i;
    for (i = 0; i < grafo->n; ++i)
    {
        cor[i] = BRANCO;
        p[i] = NIL;
        d[i] = INF;
        f[i] = NIL;
    }
    
    d[s] = 0;
    visitar_profundidade(grafo, s, processa_vertice, processa_aresta, args, cor, d, p, f);
    
//    printf("f:");
    for (i = grafo->n - 1; i >= 0; i--) {
        if (f[i] != -1) {
            if (i == 0) {
                printf("%d", f[i]);
            } else {
                printf("%d ", f[i]);
            }
        }
    }
    printf("\n");
    
    free(f);
    free(cor);
    free(d);
    free(p);
}

void busca_em_largura_m(const GrafoM *grafo, int s,
        vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args)
{
    if (grafo == NULL || s < 0 || s >= grafo->n)
        return;

    int *cor = (int *) malloc(grafo->n * sizeof(int));
    int *d = (int *) malloc(grafo->n * sizeof(int));
    int *p = (int *) malloc(grafo->n * sizeof(int));

    int i;
    for (i = 0; i < grafo->n; ++i)
    {
        cor[i] = BRANCO;
        d[i] = INF;
        p[i] = NIL;
    }

    cor[s] = CINZA;
    d[s] = 0;
    p[s] = NIL;

    Fila *fila = criar_fila(int);
    entrar_fila(fila, s);

    while (!esta_vazia_fila(fila))
    {
        int u, v;
        sair_fila(fila, u);
        if (processa_vertice && processa_vertice(u, cor, d, p, args) == PARAR)
            break;

        for (v = 0; v < grafo->n; ++v)
        {
            if (grafo->adj[u][v] == 0)
                continue;

            if (processa_aresta && processa_aresta(u, v, cor, d, p, args) == PARAR)
            {
                esvaziar_fila(fila);
                break;
            }

            if (cor[v] == BRANCO)
            {
                cor[v] = CINZA;
                d[v] = d[u] + 1;
                p[v] = u;
                entrar_fila(fila, v);
            }
        }

        cor[u] = PRETO;
    }

    destruir_fila(fila);
    free(cor);
    free(d);
    free(p);
}
