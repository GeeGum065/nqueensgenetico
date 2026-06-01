# Problema das N-Rainhas com Algoritmo

# Genético

## Descrição

Este projeto implementa uma solução para o clássico Problema das N-Rainhas utilizando um Algoritmo
Genético (GA) em linguagem C.

O objetivo é posicionar N rainhas em um tabuleiro NxN de forma que nenhuma rainha ataque outra.
Para este projeto foi utilizado um tabuleiro 4x4 (N = 4).

O algoritmo utiliza conceitos de computação evolutiva, como seleção por torneio, crossover, mutação e
elitismo para evoluir uma população de soluções candidatas até encontrar uma configuração válida.

## Funcionalidades

```
Geração aleatória da população inicial.
Avaliação de indivíduos baseada no número de conflitos entre rainhas.
Seleção por torneio.
Crossover de um ponto.
Mutação aleatória.
Elitismo para preservação dos melhores indivíduos.
Critério de parada ao encontrar uma solução ótima.
Exibição da melhor solução encontrada.
Impressão do tabuleiro em formato ASCII.
```
## Representação da Solução

Cada indivíduo é representado por um vetor onde:

```
gene[i] = coluna da rainha na linha i
```
Exemplo:

#### [1, 3, 0, 2]

Representa o tabuleiro:

#### . Q..

#### ... Q

#### • • • • • • • • •


#### Q...

#### .. Q.

Cada linha possui exatamente uma rainha.

## Como Funciona

### Inicialização

O algoritmo gera uma população inicial de indivíduos aleatórios.

### Avaliação

A aptidão (fitness) de cada indivíduo é calculada através da quantidade de conflitos entre rainhas.

A solução ideal possui:

```
Fitness = C(N,2)
```
Para N = 4:

```
Fitness ótimo = 6
```
Quanto menos conflitos existirem, maior será o fitness.

### Seleção

Os pais são escolhidos utilizando o método de torneio.

### Crossover

Com probabilidade de 90%, dois indivíduos trocam parte de seus genes para gerar novos
descendentes.

### Mutação

Com probabilidade de 5%, um indivíduo sofre alterações aleatórias em seus genes.

### Elitismo

Os melhores indivíduos da geração atual são preservados para a próxima geração.


## Parâmetros Utilizados

```
Parâmetro Valor
```
```
N 4
```
```
POP_SIZE 10
```
```
MAX_GEN 100
```
```
CROSS_RATE 0.
```
```
MUT_RATE 0.
```
```
ELITE_COUNT 2
```
```
TOURNAMENT_K 3
```
## Estrutura do Código

### random_individual()

Gera um indivíduo aleatório.

```
voidrandom_individual(Individual*ind);
```
### compute_conflicts()

Conta quantos pares de rainhas estão em conflito.

```
intcompute_conflicts(constIndividual*ind);
```
### evaluate()

Calcula o fitness do indivíduo.

```
intevaluate(Individual*ind);
```
### tournament_select()

Seleciona indivíduos utilizando torneio.

```
inttournament_select(Individualpop[], intpop_size);
```

### one_point_crossover()

Realiza o crossover entre dois pais.

```
voidone_point_crossover(
const Individual*p1,
const Individual*p2,
Individual *c1,
Individual *c
);
```
### mutate()

Aplica mutação em um indivíduo.

```
voidmutate(Individual*ind);
```
### print_board_ascii()

Exibe o tabuleiro no terminal.

```
voidprint_board_ascii(constIndividual *ind);
```
## Compilação

Utilizando GCC:

```
gcc-Wall -O2nqueens_ga_min.c -onqueens
```
## Execução

### Seed aleatória

```
./nqueens
```
### Seed fixa (reprodutibilidade)

```
./nqueens 12345
```

## Exemplo de Saída

```
Melhor fitness: 6 (ótimo = 6)
Cromossomo (lin->col): 1 3 0 2
```
```
Tabuleiro:
```
. Q..
... Q
Q...
.. Q.

```
Solução ótima alcançada na geração: 12
```
## Conceitos Aplicados

```
Algoritmos Genéticos
Computação Evolutiva
Seleção por Torneio
Crossover
Mutação
Elitismo
Otimização Combinatória
Problema das N-Rainhas
```
## Possíveis Melhorias

```
Permitir valores arbitrários de N.
Implementar crossover com ponto de corte variável.
Utilizar representação por permutação para evitar conflitos de coluna.
Ajustar dinamicamente a taxa de mutação.
Coletar métricas de convergência.
Exibir estatísticas por geração.
Exportar resultados para arquivos CSV.
Comparar diferentes estratégias de seleção.
```
## Autor

Projeto desenvolvido para fins acadêmicos e estudo de Algoritmos Genéticos aplicados ao Problema
das N-Rainhas.

#### • • • • • • • • • • • • • • • •


