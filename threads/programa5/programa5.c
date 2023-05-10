#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int var = 1; // Declara e inicializa a variável

    printf("Valor da variável antes do fork(): %d\n", var);

    pid_t pid = fork(); // Cria um novo processo

    if (pid == 0) { // Processo filho
        var = 5; // Altera o valor da variável
        printf("Valor da variável no processo filho: %d\n", var);
        exit(0); // Encerra o processo filho
    } else if (pid > 0) { // Processo pai
        waitpid(pid, NULL, 0); // Espera o processo filho terminar
        printf("Valor da variável no processo pai após o filho ter alterado: %d\n", var);
    } else { // Erro ao criar o processo filho
        perror("fork");
        exit(1);
    }

    return 0;
}
