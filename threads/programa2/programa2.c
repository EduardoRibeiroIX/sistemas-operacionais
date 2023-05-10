#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();  // cria o primeiro filho

    if (pid1 == -1) {
        fprintf(stderr, "Erro ao criar o processo filho 1\n");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // código do processo filho 1
        printf("Eu sou o processo filho 1 (PID %d)\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        // código do processo pai
        pid2 = fork();  // cria o segundo filho

        if (pid2 == -1) {
            fprintf(stderr, "Erro ao criar o processo filho 2\n");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // código do processo filho 2
            printf("Eu sou o processo filho 2 (PID %d)\n", getpid());
            exit(EXIT_SUCCESS);
        } else {
            // código do processo pai
            printf("Eu sou o processo pai (PID %d)\n", getpid());
            printf("Meus filhos são %d e %d\n", pid1, pid2);
            exit(EXIT_SUCCESS);
        }
    }
return 0; // Retorna zero para indicar que o programa foi executado com sucesso
}


