#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM 100 // tamanho do vetor

int vetor[TAM]; // declaração do vetor global

void *ordenar(void *arg){ // função que será executada pela thread
    int *n = (int*)arg; // converte o argumento para um ponteiro inteiro
    for(int i = 0; i < TAM-1; i++){ // percorre o vetor
        for(int j = i+1; j < TAM; j++){
            if(vetor[i] > vetor[j]){ // se o elemento i for maior que o elemento j, troca a posição deles
                int aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
        }
    }
    pthread_exit(NULL); // encerra a thread
}

int main(){
    pthread_t thread; // declaração da thread

    // inicializa o vetor com números aleatórios
    for(int i = 0; i < TAM; i++){
        vetor[i] = rand() % 100;
    }

    printf("Vetor antes da ordenação:\n");
    for(int i = 0; i < TAM; i++){ // exibe o vetor antes da ordenação
        printf("%d ", vetor[i]);
    }
    printf("\n");

    if(pthread_create(&thread, NULL, ordenar, (void*) &TAM)){ // cria a thread e verifica se ocorreu algum erro
        printf("Erro ao criar thread!\n");
        exit(-1);
    }

    if(pthread_join(thread, NULL)){ // espera a thread terminar e verifica se ocorreu algum erro
        printf("Erro ao aguardar thread!\n");
        exit(-1);
    }

    printf("Vetor depois da ordenação:\n");
    for(int i = 0; i < TAM; i++){ // exibe o vetor após a ordenação
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
