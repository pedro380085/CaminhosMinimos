#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

typedef struct grafo_l GrafoL;
typedef int (*vertice_fn_l)(int, const int*, const int*, const int*, void *);
typedef int (*aresta_fn_l)(int, int, const int*, const int*, const int*, void *);

GrafoL *criar_grafo_l(int n, int digrafo);
void destruir_grafo_l(GrafoL *grafo);
GrafoL *transposto_l(const GrafoL *grafo);
int e_digrafo_l(const GrafoL *grafo);
int n_vertices_l(const GrafoL *grafo);
int existe_aresta_l(const GrafoL *grafo, int u, int v);
void adicionar_aresta_l(GrafoL *grafo, int u, int v, int peso);
void remover_aresta_l(GrafoL *grafo, int u, int v);
int peso_aresta_l(const GrafoL *grafo, int u, int v);
void imprimir_grafo_l(const GrafoL *grafo);
void adjacentes_l(const GrafoL *grafo, int u, int *v, int max);
void busca_em_profundidade_l(const GrafoL *grafo, int s, vertice_fn_l processa_vertice, aresta_fn_l processa_aresta, void *args);
void busca_em_largura_l(const GrafoL *grafo, int s, vertice_fn_l processa_vertice, aresta_fn_l processa_aresta, void *args);

#endif /* GRAFO_LISTA_H */
