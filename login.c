#include <stdio.h>
#include <string.h>
#include "funcao.h"

#define CPF "123456789"
#define SENHA "12345"
#define USUARIO "Souza_henrique_delfino"

void login() {
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

        printf("\n");

        if (strcmp(CPF, user) == 0 && strcmp(SENHA, password) == 0) {
            printf("\n");
            printf("Login efetuado com sucesso\n");
            break;
        } else {
            printf("\n");
            printf("Senha ou usuario incorreto\n");
        }
    }
}

int main() {
   
    login();
    main_menu();
    consultar_saldo();
    depositar();
    return 0;
}

#include <stdio.h>
#include <string.h>
#include "funcao.h"

#define CPF "123456789"
#define SENHA "12345"
#define USUARIO "Souza_henrique_delfino"

void login() {
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

        printf("\n");

        if (strcmp(CPF, user) == 0 && strcmp(SENHA, password) == 0) {
            printf("\n");
            printf("Login efetuado com sucesso\n");
            break;
        } else {
            printf("\n");
            printf("Senha ou usuario incorreto\n");
        }
    }
}

int main() {
   
    login();
    main_menu();
    consultar_saldo();
    depositar();
    return 0;
}

#include <stdio.h>
#include <string.h>
#include "funcao.h"

#define CPF "123456789"
#define SENHA "12345"
#define USUARIO "Souza_henrique_delfino"

void login() {
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

        printf("\n");

        if (strcmp(CPF, user) == 0 && strcmp(SENHA, password) == 0) {
            printf("\n");
            printf("Login efetuado com sucesso\n");
            break;
        } else {
            printf("\n");
            printf("Senha ou usuario incorreto\n");
        }
    }
}

int main() {
   
    login();
    main_menu();
    consultar_saldo();
    depositar();
    return 0;
}

