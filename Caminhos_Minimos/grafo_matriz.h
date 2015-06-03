#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

typedef struct grafo_m GrafoM;
typedef int (*vertice_fn_m)(int, const int*, const int*, const int*, void *);
typedef int (*aresta_fn_m)(int, int, const int*, const int*, const int*, void *);

GrafoM *criar_grafo_m(int n, int digrafo);
void destruir_grafo_m(GrafoM *grafo);
GrafoM *transposto_m(const GrafoM *grafo);
int e_digrafo_m(const GrafoM *grafo);
int n_vertices_m(const GrafoM *grafo);
int existe_aresta_m(const GrafoM *grafo, int u, int v);
void adicionar_aresta_m(GrafoM *grafo, int u, int v, int peso);
void remover_aresta_m(GrafoM *grafo, int u, int v);
int peso_aresta_m(const GrafoM *grafo, int u, int v);
void imprimir_grafo_m(const GrafoM *grafo);
int cabeca_ordenacao_topologica_m(const GrafoM *grafo);
int cauda_ordenacao_topologica_m(const GrafoM *grafo);
void adjacentes_m(const GrafoM *grafo, int u, int *v, int max);
int algoritmo_prim_m(const GrafoM *grafo);
int algoritmo_dijkstra_m(const GrafoM *grafo, int origem, int destino);
void busca_em_profundidade_m(const GrafoM *grafo, int s, vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args);
void ordenacao_topologica_m(const GrafoM *grafo, int s, vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args);
void busca_em_largura_m(const GrafoM *grafo, int s, vertice_fn_m processa_vertice, aresta_fn_m processa_aresta, void *args);

#endif /* GRAFO_MATRIZ_H */
