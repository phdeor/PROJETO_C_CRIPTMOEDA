#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

// #define CPF "123456789"
// #define SENHA "12345"

USUARIO usuario_logado; 
extern USUARIO usuarios_fixos[10];

void login(USUARIO usuarios_fixos[]) {
    char user[13];
    char password[20];

      while (1) {
        printf("\nLOGIN\n");

        printf("Digite o seu CPF: ");
        fgets(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = '\0'; // Remove a nova linha

        printf("Digite sua senha: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0'; // Remove a nova linha

        printf("\n");

        int login_sucesso = 0; // Flag para controle de sucesso no login

        for (int i = 0; i < NUM_USUARIOS; i++) {
            if (strcmp(usuarios_fixos[i].cpf, user) == 0 && strcmp(usuarios_fixos[i].senha, password) == 0) {
                printf("Login efetuado com sucesso, bem-vindo(a) %s!\n", usuarios_fixos[i].nome);
                usuario_logado = usuarios_fixos[i];
                login_sucesso = 1; // Define como verdadeiro
                menu(&usuario_logado);// Chama o menu se o login for bem-sucedido
                usuarios_fixos[i] = usuario_logado;
                break; // Sai do loop se o login foi bem-sucedido
            }
        }

        if (login_sucesso) {
            break; // Encerra o loop após o menu ser chamado
        } else {
            printf("Senha ou usuário incorreto\n"); // Exibe mensagem de erro apenas se o login falhar
        }
    }
}


