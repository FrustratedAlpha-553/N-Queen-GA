#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 60
#define POP_SIZE 10000 
#define GENERATIONS 1000


typedef struct{
    int population[N];
    int fitness;
}GA;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void initial_population(int *population)
{
    int i ;
    for(i = 0 ; i < N ; ++i){
        population[i] = i;
    }
    int k ;
    for(k = 0 ; k < N ; ++k){
        int r = rand() % N;
        swap(&population[k],&population[r]);
    }
}

int fitness(int *population)
{
    int i ;
    int conflict = 0;
    for(i = 0 ; i < N ; ++i){
        for(int j = i+1 ; j < N ; ++j)
            if(abs(i-j)==abs(population[i]-population[j])){
                ++conflict;
            }
    }
    return conflict;
}

void mutation(int *population)
{
    int p1 = rand() % N ;
    int p2 = rand() % N ;
    swap(&population[p1],&population[p2]);
}

int select_parent(GA *population) {
    int best = rand() % POP_SIZE;
    for (int i = 0; i < (N*2); i++) {
        int candidate = rand() % POP_SIZE;
        if (population[candidate].fitness < population[best].fitness) {
            best = candidate;
        }
    }
    return best;
}

void single_point_crossover(int *parent1, int *parent2, int *child) {
    for (int i = 0; i < N; ++i){
        child[i] = -1;
    }
    int point = rand() % N;
    for (int i = 0 ; i <= point ; ++i){
        child[i] = parent1[i];
    }
    int Invalid = 0;
    for(int i = 0 ; i < N ; ++i){
        if(child[i] == -1){
            Invalid++;
        }
    }
    while(Invalid != 0){
        for(int i = 0 ; i < N ; ++i){
            if(child[i] != -1){
                continue;
            }
            int exists = 0;
            for (int j = 0; j < N; ++j) {
                if (child[j] == parent2[i]) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                child[i] = parent2[i];
                Invalid--;
            }
        }
    }
}

int valid_mapping_value(int *mapping,int value)
{
    while(mapping[value]!=-1)
        value = mapping[value];
    return value;
}

void PMX(int *parent1,int *parent2,int *child)
{
    int start,end; 
    start = rand() % N;
    end = rand() % N;
    if(start > end){
        int temp = start;
        start = end;
        end = temp;
    }
    int mapping[N];
    for(int i = 0 ; i < N ; ++i){
        child[i] = -1;
        mapping[i] = -1;
    }
    for(int i = start ; i <= end ; ++i){
        child[i] = parent1[i];
        mapping[parent2[i]] = parent1[i];
    }
    for(int i = 0 ; i < N ; ++i){
        if(i>=start && i<=end)
            continue;
        int value = parent1[i];
        int valid_value = valid_mapping_value(mapping,value);
        int exists = 0;
        for(int j = 0 ; j < N ; ++j){
            if(child[j] == valid_value){
                exists = 1;
                break;
            }
        }
        if(!exists)
            child[i] = valid_value;
        else{
            for(int k = 0 ; k < N ; ++k){
                int unique = 1;
                for(int m = 0 ; m < N ; ++m){
                    if(child[m] == k){
                        unique = 0;
                        break;
                    }
                } 
                if(unique){
                    child[i] = k;
                    break;
                }
            }
        }
    }
}


void copy(int from[N],int to[N])
{
    for(int i = 0 ; i < N ; ++i)
        to[i] = from[i];
}

void display(int *population)
{
    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < N ; ++j){
            if(population[i]==j){
                printf(" 1 ");
            }
            else{
                printf(" . ");
            }
        }
        printf("\n");
    }
}

void print(int *population)
{
    printf(" Points => {");
    for(int i = 0  ; i < N ; ++i)
        printf("{%d}" , population[i]);
    printf("};");
    printf("\n");
}

int main(void)
{   
    srand(time(NULL));
    GA generation1[POP_SIZE];
    GA generation2[POP_SIZE];
    for(int i = 0 ; i < POP_SIZE ; ++i){
        initial_population(generation1[i].population);
        generation1[i].fitness = fitness(generation1[i].population);
    }
    for(int gen = 1 ; gen <= GENERATIONS ; ++gen){
        int found = 0 ;
        for(int i = 0 ; i < POP_SIZE ; ++i){
            int parent1 = select_parent(generation1); 
            int parent2 = select_parent(generation1);
            PMX(generation1[parent1].population,generation1[parent2].population,generation2[i].population);          
            mutation(generation2[i].population);
            generation2[i].fitness = fitness(generation2[i].population);
            if(generation2[i].fitness == 0){
                printf("Solution found in Generation ( %d ) => Fitness  %d  : ",gen,generation2[i].fitness);
                print(generation2[i].population);
                printf("\n");
                display(generation2[i].population);
                found = 1;
                break;
            }
        }
        if(found) break;
        for(int i = 0 ; i < POP_SIZE ; ++i){
            copy(generation2[i].population,generation1[i].population);
            generation1[i].fitness = generation2[i].fitness;
        }
        if(gen % 100 == 0)
            printf(" %d Still searching ... \n",gen); 
    }
    
    return 0;
}
