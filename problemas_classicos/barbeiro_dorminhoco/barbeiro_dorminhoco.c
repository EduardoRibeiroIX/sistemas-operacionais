#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define NUM_CADEIRAS 3

sem_t sem_cadeiras, sem_barbeiro, sem_cliente;

int clientes_esperando = 0;

void* barbeiro(void* arg) {
    while (1) {
        sem_wait(&sem_cliente); // espera um cliente chegar
        sem_wait(&sem_cadeiras); // bloqueia uma cadeira das cadeiras livres
        clientes_esperando--; // decrementa a quantidade de clientes esperando

        printf("Barbeiro atendendo um cliente. Clientes esperando: %d\n",       clientes_esperando);
        sleep(rand() % 3);

        sem_post(&sem_cadeiras); // libera a cadeira ocupada
        sem_post(&sem_barbeiro); // libera o barbeiro para dormir novamente
    }
}

void* cliente(void* arg) {
    int id = *(int*) arg;
    sleep(rand() % 5); // tempo para chegar na barbearia

    sem_wait(&sem_cadeiras); // tenta sentar em uma cadeira livre
    if (clientes_esperando < NUM_CADEIRAS) {
        clientes_esperando++; // incrementa a quantidade de clientes esperando
        printf("Cliente %d chegou e está esperando. Clientes esperando: %d\n", id, clientes_esperando);
        sem_post(&sem_cliente); // acorda o barbeiro
        sem_post(&sem_cadeiras); // libera a cadeira ocupada
        sem_wait(&sem_barbeiro); // espera ser atendido pelo barbeiro
    } else {
        printf("Cliente %d chegou, mas a barbearia está cheia. Saindo...\n", id);
        sem_post(&sem_cadeiras); // libera a cadeira ocupada
    }
}

int main() {
    sem_init(&sem_cadeiras, 0, NUM_CADEIRAS); // inicializa o semáforo para o número de cadeiras livres
    sem_init(&sem_barbeiro, 0, 0); // inicializa o semáforo para o barbeiro dormir
    sem_init(&sem_cliente, 0, 0); // inicializa o semáforo para acordar o barbeiro

    pthread_t tid_barbeiro;
    pthread_create(&tid_barbeiro, NULL, barbeiro, NULL); // cria a thread do barbeiro

    pthread_t tid_clientes[10];
    int ids[10];
    for (int i = 0; i < 10; i++) {
        ids[i] = i;
        pthread_create(&tid_clientes[i], NULL, cliente, &ids[i]); // cria as threads dos clientes
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(tid_clientes[i], NULL); // espera todas as threads dos clientes terminarem
    }
    pthread_cancel(tid_barbeiro); // cancela a thread do barbeiro

    sem_destroy(&sem_cadeiras); // destroi os semáforos
    sem_destroy(&sem_barbeiro);
    sem_destroy(&sem_cliente);

    return 0;
}
