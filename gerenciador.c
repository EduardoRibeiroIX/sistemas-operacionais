#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // Cria uma nova pasta chamada "teste"
    int status;
    status = mkdir("./nova_pasta", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(status != 0) {
        printf("Erro ao criar pasta.\n");
 
    }
    else{
        printf("Pasta criada com sucesso.\n");
    
    }


    // Cria um novo arquivo chamado "arquivo.txt" na pasta "teste"
    FILE *arquivo = fopen("./nova_pasta/arquivo.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }

    // Escreve uma mensagem no arquivo
    fprintf(arquivo, "Olá, mundo!\n");

    // Fecha o arquivo
    fclose(arquivo);

    // Abre o arquivo "arquivo.txt" para leitura
    arquivo = fopen("./nova_pasta/arquivo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    // Lê o conteúdo do arquivo e imprime na tela
    char buffer[100];
    fgets(buffer, 100, arquivo);
    printf("Conteúdo do arquivo: %s", buffer);

    // Fecha o arquivo novamente
    fclose(arquivo);

    // Remove o arquivo "arquivo.txt"
    //if (remove("./nova_pasta/arquivo.txt") != 0) {
    //   printf("Erro ao excluir o arquivo\n");
    //   exit(1);
    // }

    // Remove a pasta "./nova_pasta"
    //if (rmdir("./nova_pasta") != 0) {
    //    printf("Erro ao excluir a pasta\n");
    //    exit(1);
    //}

    return 0;
}
