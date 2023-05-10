#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_avo, pid_pai, pid_filho, pid_novo_pai;

    pid_avo = getpid();  // armazena o PID do processo avô

    pid_pai = fork();  // cria o processo pai

    if (pid_pai == -1) {
        fprintf(stderr, "Erro ao criar o processo pai\n");
        exit(EXIT_FAILURE);
    } else if (pid_pai == 0) {
        // código do processo filho
        pid_filho = getpid();  // armazena o PID do processo filho

        printf("Eu sou o processo filho (PID %d)\n", pid_filho);
        printf("Meu pai é o processo pai (PID %d)\n", getppid());
        sleep(10);  // espera 10 segundos para o processo pai ser eliminado

        printf("Processo pai eliminado\n");
        exit(EXIT_SUCCESS);
    } else {
        // código do processo pai
        pid_filho = fork();  // cria o processo filho

        if (pid_filho == -1) {
            fprintf(stderr, "Erro ao criar o processo filho\n");
            exit(EXIT_FAILURE);
        } else if (pid_filho == 0) {
            // código do processo filho
            printf("Eu sou o processo filho (PID %d)\n", getpid());
            printf("Meu pai é o processo pai (PID %d)\n", getppid());
            sleep(20);  // espera 20 segundos para o processo pai ser eliminado

            printf("Processo pai eliminado\n");
            exit(EXIT_SUCCESS);
        } else {
            // código do processo pai
            printf("Eu sou o processo pai (PID %d)\n", getpid());
            printf("Meu filho é o processo filho (PID %d)\n", pid_filho);
            sleep(5);  // espera 5 segundos para o processo pai ser eliminado

            pid_novo_pai = pid_avo;  // define o processo avô como o novo pai
            printf("Eliminando processo pai (PID %d)\n", pid_pai);
            kill(pid_pai, SIGKILL);  // elimina o processo pai

            printf("Meu novo pai é o processo avô (PID %d)\n", pid_novo_pai);
            printf("Meu pai atual é o processo %d\n", getppid());
            wait(NULL);  // espera pelo processo filho terminar
            exit(EXIT_SUCCESS);
        }
    }
return 0; // Retorna zero para indicar que o programa foi executado com sucesso
}

