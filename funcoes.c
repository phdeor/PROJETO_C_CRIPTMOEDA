#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Para usar a função exit()
#include "funcao.h"

typedef struct {
    char nome[50];
    char cpf[12];
    float reais;
    float bitcoin;
    float ethereum;
    float ripple;    
} USUARIO;

void inicializaUsuario(USUARIO *usuario, const char *nome, const char *cpf, float reais, float bitcoin, float ethereum, float ripple) {
    strcpy(usuario->nome, nome);
    strcpy(usuario->cpf, cpf);
    usuario->reais = reais;
    usuario->bitcoin = bitcoin;
    usuario->ethereum = ethereum;
    usuario->ripple = ripple;
}

void registrar_transacao(const char* tipo, float valor, const char* moeda, float cotacao) {
    printf("Transacao: %s de %.2f %s a uma cotacao de %.2f\n", tipo, valor, moeda, cotacao);
}

void main_menu(USUARIO *usuario) {

    printf("\nMenu Principal: ");
    printf("\nNome: Souza_henrique_delfino %s\n", usuario->nome);
    printf("CPF: 123456789 %s\n", usuario->cpf);

    int selecionar;

    while (1) {
        printf("\n");
        printf("Digite qual opcao deseja acessar:\n");
        printf("1. Consultar Saldo\n");
        printf("8. Sair\n");
        printf("\n");
        printf("opcao: ");
        

        scanf("%d", &selecionar);
        getchar();

        switch (selecionar) {
            case 1:
                consultar_saldo(usuario);
                break;
            case 8:
                printf("\nSaindo...\n");
                exit(0);  // Encerra o programa completamente
            default:
                printf("\nOpção inválida, tente novamente!\n");
        }
    }
}

void consultar_saldo(USUARIO *usuario) {
    printf("\nConsultar Saldo: ");

    printf("\nNome: Souza_henrique_delfino %s\n", usuario->nome);
    printf("CPF: 123456789 %s\n", usuario->cpf);
    printf("Reais: %.2f\n", usuario->reais);
    printf("Bitcoin: %.4f\n", usuario->bitcoin);
    printf("Ethereum: %.2f\n", usuario->ethereum);
    printf("Ripple: %.2f\n", usuario->ripple);

    int selecionar;
    while (1) {
        printf("\nDigite 0 para voltar ao menu principal: ");
        scanf("%d", &selecionar);
        getchar(); 

        if (selecionar == 0) {
            printf("\nVoltando....\n");
            break;
        } else {
            printf("\nTente novamente!\n");
        }
    }
}