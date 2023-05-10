#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define N 5

sem_t forks[N]; // semáforos para os garfos

void* philosopher(void* arg) {
    int id = *(int*) arg;
    int left_fork = id;
    int right_fork = (id + 1) % N;

    while (1) {
        // filósofo pensando
        printf("Filósofo %d pensando...\n", id);
        sleep(rand() % 3);

        // pega o garfo esquerdo
        sem_wait(&forks[left_fork]);

        // tenta pegar o garfo direito
        if (sem_trywait(&forks[right_fork]) == 0) {
            // filósofo comendo
            printf("Filósofo %d comendo...\n", id);
            sleep(rand() % 3);

            // libera os garfos
            sem_post(&forks[right_fork]);
            sem_post(&forks[left_fork]);
        } else {
            // libera o garfo esquerdo
            sem_post(&forks[left_fork]);

            // filósofo pensando
            printf("Filósofo %d não conseguiu pegar o garfo da direita, pensando...\n", id);
            sleep(rand() % 3);
        }
    }

    pthread_exit(NULL);
}

int main() {
    // inicializa os semáforos para os garfos
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // cria as threads dos filósofos
    pthread_t philosophers[N];
    int philosopher_ids[N];
    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // aguarda as threads terminarem
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // destroi os semáforos dos garfos
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
