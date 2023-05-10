#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Declaração das variáveis globais
sem_t semA, semB, semC;

void *threadA(void *arg) {
    while(1) {
        sem_wait(&semA); // Espera o semáforo semA ser liberado
        printf("A"); // Escreve "A" na tela
        sem_post(&semB); // Libera o semáforo semB
    }
    pthread_exit(NULL); // Termina a thread
}

void *threadB(void *arg) {
    while(1) {
        sem_wait(&semB); // Espera o semáforo semB ser liberado
        printf("B"); // Escreve "B" na tela
        sem_post(&semC); // Libera o semáforo semC
    }
    pthread_exit(NULL); // Termina a thread
}

void *threadC(void *arg) {
    while(1) {
        sem_wait(&semC); // Espera o semáforo semC ser liberado
        printf("C"); // Escreve "C" na tela
        sem_post(&semA); // Libera o semáforo semA
    }
    pthread_exit(NULL); // Termina a thread
}

int main() {
    // Inicialização dos semáforos
    sem_init(&semA, 0, 1);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);

    // Declaração das threads
    pthread_t tidA, tidB, tidC;

    // Criação das threads
    pthread_create(&tidA, NULL, threadA, NULL);
    pthread_create(&tidB, NULL, threadB, NULL);
    pthread_create(&tidC, NULL, threadC, NULL);

    // Espera pelas threads
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);
    pthread_join(tidC, NULL);

    // Destruir os semáforos
    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);

    return 0;
}
