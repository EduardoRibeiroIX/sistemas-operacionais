#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid_filho, pid_pai, pid_avo; // Variáveis para armazenar os PIDs dos processos

    // Cria processo filho
    pid_filho = fork(); // Cria um novo processo, que é uma cópia do processo pai

    if (pid_filho < 0) { // Testa se ocorreu um erro na criação do processo filho
        printf("Erro ao criar processo filho.\n"); // Imprime mensagem de erro
        exit(-1); // Termina o programa com código de erro
    }
    else if (pid_filho == 0) { // Testa se o PID do processo filho é igual a zero, o que significa que este é o processo filho
        printf("Filho (PID %d): sou o processo filho.\n", getpid()); // Imprime mensagem do processo filho
    }
    else { // Se o PID do processo filho for diferente de zero, este é o processo pai
        // Cria processo pai
        pid_pai = fork(); // Cria um novo processo, que é uma cópia do processo pai

        if (pid_pai < 0) { // Testa se ocorreu um erro na criação do processo pai
            printf("Erro ao criar processo pai.\n"); // Imprime mensagem de erro
            exit(-1); // Termina o programa com código de erro
        }
        else if (pid_pai == 0) { // Testa se o PID do processo pai é igual a zero, o que significa que este é o processo pai
            printf("Pai (PID %d): sou o processo pai.\n", getpid()); // Imprime mensagem do processo pai
        }
        else { // Se o PID do processo pai for diferente de zero, este é o processo avô
            // Cria processo avô
            pid_avo = fork(); // Cria um novo processo, que é uma cópia do processo pai

            if (pid_avo < 0) { // Testa se ocorreu um erro na criação do processo avô
                printf("Erro ao criar processo avô.\n"); // Imprime mensagem de erro
                exit(-1); // Termina o programa com código de erro
            }
            else if (pid_avo == 0) { // Testa se o PID do processo avô é igual a zero, o que significa que este é o processo avô
                printf("Avô (PID %d): sou o processo avô.\n", getpid()); // Imprime mensagem do processo avô
            }
            else { // Se o PID do processo avô for diferente de zero, este é o processo pai
                printf("Pai (PID %d): sou o processo pai.\n", getpid()); // Imprime mensagem do processo pai
            }
        }
    }

    return 0; // Retorna zero para indicar que o programa foi executado com sucesso
}
