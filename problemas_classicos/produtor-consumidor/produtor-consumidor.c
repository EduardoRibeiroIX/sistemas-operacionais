#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 10  // tamanho do buffer
#define NUM_ITEMS 20    // número total de itens para produzir/consumir

int buffer[BUFFER_SIZE];  // buffer compartilhado
int in = 0;               // próxima posição de escrita no buffer
int out = 0;              // próxima posição de leitura no buffer
int num_items = 0;        // número de itens no buffer

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;   // mutex para garantir exclusão mútua
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER; // variável de condição para os produtores
pthread_cond_t cond_cons = PTHREAD_COND_INITIALIZER; // variável de condição para os consumidores

void *producer(void *arg) {
    int i, item;
    for (i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100;  // produz um item aleatório
        pthread_mutex_lock(&mutex);
        while (num_items == BUFFER_SIZE) {  // se buffer estiver cheio, espera
            pthread_cond_wait(&cond_prod, &mutex);
        }
        buffer[in] = item;  // adiciona o item ao buffer
        in = (in + 1) % BUFFER_SIZE;
        num_items++;
        printf("Produced item %d\n", item);
        pthread_cond_signal(&cond_cons);  // avisa aos consumidores que há um novo item no buffer
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i, item;
    for (i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);
        while (num_items == 0) {  // se buffer estiver vazio, espera
            pthread_cond_wait(&cond_cons, &mutex);
        }
        item = buffer[out];  // remove um item do buffer
        out = (out + 1) % BUFFER_SIZE;
        num_items--;
        printf("Consumed item %d\n", item);
        pthread_cond_signal(&cond_prod);  // avisa aos produtores que há espaço no buffer
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod_thread, cons_thread;

    // cria uma thread para o produtor e outra para o consumidor
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // espera as threads terminarem
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    return 0;
}
