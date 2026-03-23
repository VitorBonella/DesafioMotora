Desafio Motora
Implementação do desafio motora de busca de caminhos em um grid com movimentos do cavalo do xadrez, a solução foi feita em C, utilizando dois algoritmos:

 BFS (Breadth-First Search) e A (A-Star)*.

OBS: É possivel escolher o algoritmo baseado na sua estrategia. 


Como Rodar
O projeto utiliza um Makefile para gerenciar a compilação e execução.

1. Compilação
Para compilar o projeto e gerar o executável motora_challenge, execute:

```Bash
make
```
Isso criará o diretório build/ com os arquivos objetos e o binário final na raiz do projeto.

2. Execução Individual
Para rodar o programa manualmente em um arquivo de teste específico:

```Bash
make run FILE=testes/exemplo.txt ALGO=astar
```
FILE: Caminho para o arquivo de entrada.


ALGO: Escolha entre bfs ou astar.

3. Execução de Testes em Lote
Para rodar todos os arquivos dentro da pasta testes/ e salvar os resultados em test_output/:

```Bash
make test ALGO=bfs
```
Este comando exibirá o tempo de execução de cada teste e o tempo total acumulado.

4. Limpeza
Para remover os arquivos de build e o executável:

```Bash
make clean
```