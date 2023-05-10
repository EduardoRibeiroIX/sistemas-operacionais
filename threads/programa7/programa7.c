#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 100000 // número máximo de threads a serem criadas

void *thread_func(void *arg){
    int id = *(int *)arg;
    printf("Thread %d criada\n", id);
    sleep(10); // aguarda 10 segundos antes de encerrar a thread
    printf("Thread %d encerrada\n", id);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[MAX_THREADS]; // vetor para armazenar as threads criadas
    int ids[MAX_THREADS]; // vetor para armazenar os IDs das threads
    int i, j, max_threads, max_processes;
    
    // Verificando o número máximo de threads permitido
    max_threads = pthread_getattr_np(pthread_self(), PTHREAD_ATTR_STACK_SIZE, NULL);
    printf("Número máximo de threads permitido: %d\n", max_threads);

    // Verificando o número máximo de processos permitido
    max_processes = sysconf(_SC_CHILD_MAX);
    printf("Número máximo de processos permitido: %d\n", max_processes);

    // Criando threads
    for(i = 0; i < max_threads; i++){
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }

    // Aguardando threads criadas encerrarem
    for(j = 0; j < max_threads; j++){
        pthread_join(threads[j], NULL);
    }

    return 0;
}
