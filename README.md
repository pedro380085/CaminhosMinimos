Lab 05 - SCC0216 - ICMC-USP
==============

O conteúdo abaixo foi obtido diretamente do [run.codes](http://run.codes).

Esse trabalho é referente ao laboratório 5 de Modelagem de Grafos para a Turma SCC0216 do ICMC-USP. O mesmo descreve como encontrar o caminho mínimo de um grafo, informando o caminho mínimo para cada um dos pares de vértices fornecidos.


Especificação
==============
1 Especificação
O laboratório consiste na implementação de um algoritmo para encontrar menores caminhos
em dígrafos ponderados. Deverá ser utilizada a linguagem de programação C99. Os caminhos
mínimos entre dois vértices deverão ser encontrados utilizando o algoritmo de Dijkstra com fila
de prioridades. O programa terá um tempo limite de 3 segundos para execução e impressão
dos resultados.
O programa principal deverá ler da entrada padrão a lista de arestas do dígrafo e representá-
lo em memória – matriz ou lista de adjacência, conforme desejar. Em seguida, o programa
deverá ler uma sequência de vértices de origem e de destino. Para cada par de vértices, o
programa deverá imprimir o caminho mínimo entre eles na saída padrão.
Na primeira linha da entrada, haverá o descritor do dígrafo contendo 2 números separados
por espaço. Os números indicam, nesta ordem, o número de vértices e de arestas do dígrafo.
Nas linhas seguintes, as arestas do dígrafo serão representadas por três números indicando o
vértice de origem, o vértice de destino e o peso da aresta (valores de 1 à 9999 inteiros). Por fim,
nas demais linhas, pares de números indicarão os índices dos vértices de origem e de destino do
caminho a ser procurado.
Os caminhos deverão ser impressos com os índices dos vértices seguidos de espaço. Ao final,
insira uma quebra de linha. Quando não houver caminho, imprima apenas a quebra de linha.
Por exemplo, a entrada
7 11
5 2 105
5 6 86
2 0 713
3 0 603
0 5 362
0 1 479
1 0 671
4 2 10
0 4 979
6 2 536
2 5 217
2 3
1 4
1
resultará no dígrafo ponderado
105 86
713
603
362
479
671
10
979
536
217
0
1
2
3
4
5
6
Os vetores de predecessores com origem nos vértices 2 e 1, respectivamente, são
2 0 -1 -1 0 2 5
1 -1 5 -1 0 0 5
Deste modo, o programa terá como saída
1 0 4
2 Submissão
O exercício deverá ser entregue pelo sistema run.codes1
. Os alunos deverão submeter seus
códigos no exercício 5 - Caminhos Mínimos até o final da aula.
Somente a última submissão será considerada. Todas as demais submissões
serão desconsideradas, incluindo aquelas dentro do período normal de submissão.
Os exercícios deverão submetidos em um arquivo .zip contendo código-fonte do programa e
um Makefile para compilação e teste do trabalho. Se necessário, incluam no .zip um arquivo
chamado readme com informações extras.
Os códigos deverão ser compilados pelo compilador gcc com a flag -std=c99. A não conformidade
das implementações com a versão C estabelecida acarretará em nota zero.
1https://run.codes/
2
Atenção! Todos os códigos enviados passarão pelo sistema de veri-
ficação de plágio. Se forem identificados códigos duplicados, todos os
alunos envolvidos receberão nota zero.
3 Correção e Avaliação
As implementações serão avaliadas por meio de casos de testes, com peso 7, e pela legibilidade
e boas práticas de programação, com peso 3.
Os seguintes casos implicarão em nota zero:
• não conformidade com a versão C99;
• programas não estruturados como um TAD; e
• exercícios plagiados.
4 Dicas
• Implementem a fila de prioridades como um Heap binário.
• A cada atualização do vetor de distâncias, insiram novamente o vértice na fila de prioridades
ao invés de atualizar sua posição na fila. Deste modo, um mesmo vértice poderá
aparecer mais de uma vez na fila. Para resolver isto, utilizem um vetor auxiliar para
indicar quais vértices já foram removidos da fila de prioridade para não processá-lo duas
vezes.