/*
 * nqueens_ga_min.c
 * Estrutura geral de um Algoritmo Genético para N-Rainhas (N=4), versão enxuta.
 * - Saída apenas no terminal (stdout).
 * - Sem escrita de métricas/arquivos.
 * - Funções com TODOs para o aluno completar.
 *
 * Compilar: gcc -Wall -O2 nqueens_ga_min.c -o nqueens
 * Executar : ./nqueens            (seed baseada no tempo)
 *            ./nqueens 12345      (seed fixa p/ reprodutibilidade)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* ---------------- Parâmetros do problema e do GA ---------------- */
#define N               4           /* tamanho do tabuleiro */
#define POP_SIZE        10         /* tamanho da população */
#define MAX_GEN         100        /* máx. gerações */
#define CROSS_RATE      0.90f       /* taxa de crossover */
#define MUT_RATE        0.05f       /* taxa de mutação por gene */
#define ELITE_COUNT     2           /* nº de elites preservados */
#define TOURNAMENT_K    3           /* tamanho do torneio */

/* ---------------- Representação de indivíduo -------------------- */
typedef struct {
    int gene[N];     /* gene[i] = coluna da rainha na linha i */
    int fitness;     /* aptidão */
} Individual;

/* -------------------- Utilidades aleatórias --------------------- */
static inline int rand_int(int a, int b) {
    /* inteiro uniforme em [a,b] (assume a <= b) */
    return a + rand() % (b - a + 1);
}

static inline double rand_unit() {
    /* real uniforme em [0,1) */
    return (double)rand() / (double)(RAND_MAX);
}

/* -------------------- Protótipos das funções -------------------- */
void random_individual(Individual *ind);
int  compute_conflicts(const Individual *ind);
int  evaluate(Individual *ind);
int  cmp_desc_fitness(const void *a, const void *b);
void copy_individual(const Individual *src, Individual *dst);
int  tournament_select(Individual pop[], int pop_size);
void one_point_crossover(const Individual *p1, const Individual *p2,
                         Individual *c1, Individual *c2);
void mutate(Individual *ind);
void print_board_ascii(const Individual *ind);

/* -------------------- Implementações (STUBs) -------------------- */
void random_individual(Individual *ind) {
    /* para cada i em [0..N-1], sorteie ind->gene[i] em [0, N-1].
       Inicie ind->fitness = 0 (será definido em evaluate). */
       ind->fitness=0;
    for(int i =0;i<N;i++){
        ind->gene[i]=rand_int(0,N-1);
    }
    (void)ind;
}

int compute_conflicts(const Individual *ind) {
    /* contar pares (i<j) em conflito:*/
         //- mesma coluna:
         int i = 0, j=0;
         
         int conflics=0;
         
         for(i;i<N;i++)
         {
             for(j=i+1;j<N;j++)
             {
                if(i!=j){
                    
                    if((ind->gene[i] == ind->gene[j]) || (abs(i-j) == abs(ind->gene[i] - ind->gene[j])))
			{
				conflics++;

                    }
                }
             }
         }
         //- mesma diagonal: 

    return conflics; 
}


int evaluate(Individual *ind) {
    // :
       int total_pairs = N*(N-1)/2;
       int conflicts   = compute_conflicts(ind);
       ind->fitness = total_pairs - conflicts;
       return ind->fitness;
       
    (void)ind; /* provisório */
}

int cmp_desc_fitness(const void *a, const void *b) {
    /* ordenar decrescentemente por fitness */

    const Individual *ia = (const Individual*)a;
    const Individual *ib = (const Individual*)b;
    
    //(void)ia; (void)ib;
    return (ib->fitness-ia->fitness); 
}

void copy_individual(const Individual *src, Individual *dst) {
    /*  copiar todos os genes e o fitness */
    for(int i =0;i<N;i++)
    {
        dst->gene[i] = src->gene[i];
    }
    dst->fitness = src->fitness;
    (void)src; (void)dst;
}

int tournament_select(Individual pop[], int pop_size) {
    /* :
       - sorteie TOURNAMENT_K índices em [0, pop_size-1]
       - retorne o índice do indivíduo com maior fitness */
    int pos = rand_int(0,pop_size-1);
    int indice[TOURNAMENT_K];
    for(int i = 0; i < TOURNAMENT_K; i++)
    {
        indice[i] = rand_int(0, pop_size-1);
       
    }
    for(int j = 0; j < TOURNAMENT_K ; j++)
    {
        int indicesel = indice[j];
        if(pop[indicesel].fitness>pop[pos].fitness){
            pos = j;
        }
    }
    return pos;
    
    

}

void one_point_crossover(const Individual *p1, const Individual *p2,
                         Individual *c1, Individual *c2) {
    /* 
       - Com prob. CROSS_RATE: escolher um corte em [1, N-1),
         combinar prefixo de p1 com sufixo de p2 (c1) e o inverso (c2)
       - Caso contrário: apenas copiar p1->c1 e p2->c2 */
       if((double)rand()/(double)RAND_MAX<CROSS_RATE)
       {
            for(int i = 0;i<N/2;i++){
                
                c1->gene[i]=p1->gene[i];
                c1->gene[i+N/2]=p2->gene[i+N/2];
                c2->gene[i]=p1->gene[i+N/2];
                c2->gene[i+N/2]=p2->gene[i];
            }
       }
       else{
           for(int i = 0;i<N;i++){
               c1->gene[i]=p1->gene[i];
               c2->gene[i]=p2->gene[i];
           }
       }
    (void)p1; (void)p2; (void)c1; (void)c2;
}

void mutate(Individual *ind) {
    /* para cada gene i, com prob. MUT_RATE,
       sorteie nova coluna em [0, N-1] */
    if((double)rand()/(double)RAND_MAX<MUT_RATE){
        for(int i = 0;i<N;i++){
            ind->gene[i]=rand_int(0,N-1);
        }
    }
    (void)ind;
}

void print_board_ascii(const Individual *ind) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (ind->gene[i] == j) printf("Q ");
            else                   printf(". ");
        }
        printf("\n");
    }
}

/* --------------------------- main ------------------------------- */
int main(int argc, char *argv[]) {
    /* Seed: tempo ou valor fixo informado na linha de comando */
    if (argc >= 2) {
        unsigned int seed = (unsigned int)strtoul(argv[1], NULL, 10);
        srand(seed);
    } else {
        srand((unsigned int)time(NULL));
    }

    Individual pop[POP_SIZE], new_pop[POP_SIZE];

    /* 1) Inicialização e avaliação */
    for (int i = 0; i < POP_SIZE; ++i) {
        random_individual(&pop[i]);  
        evaluate(&pop[i]);           
    }

    /* 2) Ordenação inicial (facilita elitismo) */
    qsort(pop, POP_SIZE, sizeof(Individual), cmp_desc_fitness); 

    const int TOTAL_PAIRS = N * (N - 1) / 2;
    int best_gen_found = -1;

    /* 3) Loop evolutivo */
    for (int gen = 1; gen <= MAX_GEN; ++gen) {
        
        /* 3a) Elitismo */
        for (int e = 0; e < ELITE_COUNT; ++e) {
            copy_individual(&pop[e], &new_pop[e]); 
        }

        /* 3b) Reprodução: seleção, crossover, mutação */
        for (int i = ELITE_COUNT; i < POP_SIZE; i += 2) {
            int p1 = tournament_select(pop, POP_SIZE); 
            int p2 = tournament_select(pop, POP_SIZE); 

            Individual c1, c2;
            one_point_crossover(&pop[p1], &pop[p2], &c1, &c2);  
            mutate(&c1);                                        
            mutate(&c2);                                        
            evaluate(&c1);                                      
            evaluate(&c2);                                      

            new_pop[i] = c1;
            if (i + 1 < POP_SIZE) new_pop[i + 1] = c2;
        }

        /* 3c) Substituição e ordenação */
        for (int i = 0; i < POP_SIZE; ++i) pop[i] = new_pop[i];
        qsort(pop, POP_SIZE, sizeof(Individual), cmp_desc_fitness); 

        /* 3d) Parada por solução ótima (fitness = C(N,2)) */
        if (pop[0].fitness == TOTAL_PAIRS) {
            best_gen_found = gen;

        
            break;
        }

    }

    /* 4) Saída no terminal: melhor indivíduo e tabuleiro */
    Individual best = pop[0];
    printf("Melhor fitness: %d (ótimo = %d)\n", best.fitness, TOTAL_PAIRS);
    printf("Cromossomo (lin->col): ");
    for (int i = 0; i < N; ++i) printf("%d ", best.gene[i]);
    printf("\n\nTabuleiro:\n");
    print_board_ascii(&best);  /* TODO */

    if (best_gen_found >= 0)
        printf("\nSolução ótima alcançada na geração: %d\n", best_gen_found);
    else
        printf("\nSolução ótima NÃO alcançada (ajuste parâmetros/operadores).\n");

    return 0;
}