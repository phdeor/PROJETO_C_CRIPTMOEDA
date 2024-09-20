#include <stdio.h>
#include <string.h>
#include "funcao.h"

#define USUARIO "49878672816"
#define SENHA "070303"

// Função para efetuar login
int login() {
    char user[20];
    char password[20];

    while (1) {
        printf("\nLOGIN\n");
        printf("Digite o seu CPF: ");
        fgets(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = '\0';

        printf("Digite sua senha: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        if (strcmp(USUARIO, user) == 0 && strcmp(SENHA, password) == 0) {
            printf("Login efetuado com sucesso\n");
            return 1;
        } else {
            printf("Senha ou usuario incorreto. Tente novamente.\n");
        }
    }
}

// Função principal
int main() {
    int opcao;

    if (login()) { // Apenas chama o menu se o login for bem-sucedido
        while (1) {
            main_menu();
            printf("Escolha uma opcao: ");
            if (scanf("%d", &opcao) == 1) {
                getchar(); // Limpar o buffer do teclado

                switch(opcao) {
                    // Adicione os casos para outras opções aqui
                    case 8:
                        printf("Saindo...\n");
                        return 0;
                    default:
                        printf("Opcaoo invalida. Tente novamente.\n");
                }
            } else {
                printf("Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n'); // Limpar o buffer do teclado
            }
        }
    }
    return 0;
}
