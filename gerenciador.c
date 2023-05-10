#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Função para criar uma pasta
int criarPasta(const char* nomePasta) {
    int status = mkdir(nomePasta, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(status != 0) {
        printf("Erro ao criar pasta.\n");
        return 1;
    }
    else{
        printf("Pasta criada com sucesso.\n");
        return 0;
    }
}

// Função para criar um arquivo em uma pasta existente
int criarArquivo(const char* nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo\n");
        return 1;
    }

    fclose(arquivo);
    return 0;
}

// Função para escrever uma mensagem em um arquivo existente
int escreverArquivo(const char* nomeArquivo, const char* mensagem) {
    FILE *arquivo = fopen(nomeArquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    fprintf(arquivo, "%s\n", mensagem);

    fclose(arquivo);
    return 0;
}

// Função para ler o conteúdo de um arquivo
int lerArquivo(const char* nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    char buffer[100];
    fgets(buffer, 100, arquivo);
    printf("Conteúdo do arquivo: %s", buffer);

    fclose(arquivo);
    return 0;
}

// Função para excluir um arquivo
int excluirArquivo(const char* nomeArquivo) {
    if (remove(nomeArquivo) != 0) {
       printf("Erro ao excluir o arquivo\n");
       return 1;
    }
    else {
        return 0;
    }
}

// Função para excluir uma pasta
int excluirPasta(const char* nomePasta) {
    if (rmdir(nomePasta) != 0) {
        printf("Erro ao excluir a pasta\n");
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    const char* nomePasta = "./nova_pasta";
    const char* nomeArquivo = "./nova_pasta/arquivo.txt";
    const char* mensagem = "Olá, mundo!";

    // Cria uma nova pasta chamada "nova_pasta"
    if (criarPasta(nomePasta) != 0) {
        exit(1);
    }

    // Cria um novo arquivo chamado "arquivo.txt" na pasta "nova_pasta"
    if (criarArquivo(nomeArquivo) != 0) {
        exit(1);
    }

    // Escreve uma mensagem no arquivo
    if (escreverArquivo(nomeArquivo, mensagem) != 0) {
        exit(1);
   }
    // Le o conteudo do arquivo
    if (lerArquivo(nomeArquivo) != 0) {
        exit(1);
   }
    
    // Exclui o arquivo
    if (excluirArquivo(nomeArquivo) != 0) {
        exit(1);
   }
    
    // Exclui a pasta
    if (excluirPasta(nomePasta) != 0) {
        exit(1);
   }



    return 0;
}
