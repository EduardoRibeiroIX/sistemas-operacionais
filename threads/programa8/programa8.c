#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_THREADS 1000 // número máximo de threads
#define MAX_PROCESS 1000 // número máximo de processos

int global_count = 0; // contador global que será compartilhado entre threads/processos

void *thread_func(void *arg){
    int i;
    for(i = 0; i < 100000; i++){ // realiza 100000 incrementos no contador global
        global_count++;
    }
    pthread_exit(NULL);
}

int main(){
    int i, j;
    struct timeval tstart, tend;
    double tthread, tprocess;

    // threads
    gettimeofday(&tstart, NULL);
    for(i = 0; i < 20; i++){ // realiza 20 simulações
        pthread_t threads[MAX_THREADS];
        for(j = 0; j < MAX_THREADS; j++){ // cria as threads
            pthread_create(&threads[j], NULL, thread_func, NULL);
        }
        for(j = 0; j < MAX_THREADS; j++){ // aguarda as threads encerrarem
            pthread_join(threads[j], NULL);
        }
    }
    gettimeofday(&tend, NULL);
    tthread = ((tend.tv_sec - tstart.tv_sec) * 1000000u + tend.tv_usec - tstart.tv_usec) / 1.e6;
    printf("Tempo com threads: %lf segundos\n", tthread);

    // processos
    gettimeofday(&tstart, NULL);
    for(i = 0; i < 20; i++){ // realiza 20 simulações
        int status;
        pid_t pid;
        for(j = 0; j < MAX_PROCESS; j++){ // cria os processos
            pid = fork();
            if(pid < 0){ // erro
                perror("Erro na criação do processo\n");
                exit(1);
            }
            else if(pid == 0){ // processo filho
                int k;
                for(k = 0; k < 100000; k++){ // realiza 100000 incrementos no contador global
                    global_count++;
                }
                exit(0);
            }
            else{ // processo pai
                waitpid(pid, &status, 0); // aguarda o processo filho encerrar
            }
        }
    }
    gettimeofday(&tend, NULL);
    tprocess = ((tend.tv_sec - tstart.tv_sec) * 1000000u + tend.tv_usec - tstart.tv_usec) / 1.e6;
    printf("Tempo com processos: %lf segundos\n", tprocess);

    printf("Contador global: %d\n", global_count);

    return 0;
}
