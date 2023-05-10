#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define MAX_READERS 5
#define MAX_WRITERS 2

sem_t mutex, rw_mutex; // Semáforos para garantir exclusão mútua

int read_count = 0; // Contador de leitores

// Função executada pelos leitores
void* reader(void* arg) {
    int id = *(int*) arg;
    while (1) {
        sem_wait(&mutex); // Adquire o mutex para atualizar o contador
        read_count++; // Incrementa o contador de leitores
        if (read_count == 1) {
            sem_wait(&rw_mutex); // Se for o primeiro leitor, bloqueia a escrita
        }
        sem_post(&mutex); // Libera o mutex

        // Simula a leitura de um recurso compartilhado
        printf("Leitor %d lendo...\n", id);
        sleep(rand() % 3);

        sem_wait(&mutex); // Adquire o mutex para atualizar o contador
        read_count--; // Decrementa o contador de leitores
        if (read_count == 0) {
            sem_post(&rw_mutex); // Se for o último leitor, libera a escrita
        }
        sem_post(&mutex); // Libera o mutex

        // Simula o tempo que o leitor fica sem acessar o recurso
        sleep(rand() % 3);
    }
}

// Função executada pelos escritores
void* writer(void* arg) {
    int id = *(int*) arg;
    while (1) {
        // Bloqueia a escrita enquanto houver leitores ou outros escritores
        sem_wait(&rw_mutex);

        // Simula a escrita em um recurso compartilhado
        printf("Escritor %d escrevendo...\n", id);
        sleep(rand() % 3);

        // Libera a escrita
        sem_post(&rw_mutex);

        // Simula o tempo que o escritor fica sem acessar o recurso
        sleep(rand() % 3);
    }
}

int main() {
    // Inicializa os semáforos
    sem_init(&mutex, 0, 1); // mutex inicia com 1 para garantir exclusão mútua
    sem_init(&rw_mutex, 0, 1); // rw_mutex inicia com 1 para permitir a escrita

    // Cria as threads dos leitores
    pthread_t readers[MAX_READERS];
    int reader_ids[MAX_READERS];
    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Cria as threads dos escritores
    pthread_t writers[MAX_WRITERS];
    int writer_ids[MAX_WRITERS];
    for (int i = 0; i < MAX_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Aguarda as threads terminarem
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroi os semáforos
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}

