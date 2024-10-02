#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcao.h"

USUARIO usuario_logado;

USUARIO usuarios_fixos[NUM_USUARIOS] = {
    {"Alice Silva", "11111111111", "senha1", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Bruno Santos", "22222222222", "senha2", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Carla Oliveira", "33333333333", "senha3", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Diego Souza", "44444444444", "senha4", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Elisa Costa", "55555555555", "senha5", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Felipe Lima", "66666666666", "senha6", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Gabriela Alves", "77777777777", "senha7", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Henrique Pereira", "88888888888", "senha8", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Isabela Rocha", "99999999999", "senha9", 0.0, 0.0, 0.0, 0.0, {{0}}, 0},
    {"Gustavo Mendes", "10101010101", "senha10", 0.0, 0.0, 0.0, 0.0, {{0}}, 0}};

int verifica_senha(USUARIO *usuario)
{
    char senha[20];
    printf("Digite sua senha para confirmar a transacao: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0'; // Remove a nova linha

    return strcmp(usuario->senha, senha) == 0;
}

int flush_input()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return 1;
}

void menu(USUARIO *usuario)
{
    int opcao;
    do
    {
        printf("\n--- MENU ---\n");
        printf("1. Consultar Saldo\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Comprar Criptomoedas\n");
        printf("6. Vender Criptomoedas\n");
        printf("7. Atualizar Cotacoes\n");
        printf("8. Sair\n");
        printf("Digite sua opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada invalida! Tente novamente.\n");
            flush_input();
            continue;
        }
        flush_input();

        switch (opcao)
        {
        case 1:
            consultar_saldo(usuario);
            break;
        case 3:
            depositar(usuario);
            break;
        case 4:
            sacar(usuario);
            break;
        case 5:
            comprar_criptomoedas(usuario);
            break;
        case 6:
            vender_criptomoedas(usuario);
            break;
        case 7:
            atualizar_cotacao();
            break;
        case 8:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (opcao != 8);
}

void inicializaUsuario(USUARIO *usuario, const char *nome, const char *cpf, float reais, float bitcoin, float ethereum, float ripple)
{
    strcpy(usuario->nome, nome);
    strcpy(usuario->cpf, cpf);
    usuario->reais = reais;
    usuario->bitcoin = bitcoin;
    usuario->ethereum = ethereum;
    usuario->ripple = ripple;
    usuario->num_transacoes = 0;
}

void obter_data_hora_atual(char *buffer)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%04d %02d:%02d:%02d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}
void consultar_saldo(USUARIO *usuario)
{
    printf("\nConsultar Saldo:");
    printf("\nNome: %s\n", usuario->nome);
    printf("CPF: %s\n", usuario->cpf);
    printf("Reais: %.2f\n", usuario->reais);
    printf("Bitcoin: %.4f\n", usuario->bitcoin);
    printf("Ethereum: %.2f\n", usuario->ethereum);
    printf("Ripple: %.2f\n", usuario->ripple);
}

void depositar(USUARIO *usuario)
{
    float deposito;
    printf("\nDigite o valor que voce deseja depositar: ");
    scanf("%f", &deposito);
    flush_input();

    if (deposito > 0)
    {
        usuario->reais += deposito;
        printf("Deposito realizado com sucesso!\n");
    }
    else
    {
        printf("Valor invalido para deposito.\n");
    }
}

void sacar(USUARIO *usuario)
{
    if (!verifica_senha(usuario))
    {
        printf("Senha incorreta. Transacao cancelada.\n");
        return;
    }
    float valor;
    printf("\nDigite o valor que voce deseja sacar: ");
    scanf("%f", &valor);
    flush_input();

    if (valor > 0 && valor <= usuario->reais)
    {
        usuario->reais -= valor;
        printf("Saque realizado com sucesso!\n");
    }
    else
    {
        printf("Valor invalido ou saldo insuficiente.\n");
    }
}

float gerar_variacao()
{
    return ((float)rand() / RAND_MAX * 2 - 1) * 0.05;
}

void atualizar_cotacao()
{
    for (int i = 0; i < 3; i++)
    {
        float variacao = gerar_variacao();
        CT[i].cotacao *= (1 + variacao);
        printf("Nova cotacao de %s: %.2f (variacao: %.2f%%)\n", CT[i].nome, CT[i].cotacao, variacao * 100);
    }
}

void comprar_criptomoedas(USUARIO *usuario)
{
    if (!verifica_senha(usuario))
    {
        printf("Senha incorreta. Transacao cancelada.\n");
        return;
    }
    int opcao;
    printf("\nDigite o codigo da criptomoeda (1-Bitcoin, 2-Ethereum, 3-Ripple): ");
    scanf("%d", &opcao);
    flush_input();

    if (opcao < 1 || opcao > 3)
    {
        printf("Opcao invalida.\n");
        return;
    }

    float valor;
    printf("Digite a quantidade que voce deseja comprar: ");
    scanf("%f", &valor);
    flush_input();

    if (valor <= 0)
    {
        printf("Valor invalido.\n");
        return;
    }

    float taxa, total;
    Criptomoeda *cripto = &CT[opcao - 1];
    taxa = valor * cripto->cotacao * 0.01;
    total = valor * cripto->cotacao + taxa;

    printf("\n--- Detalhes da Compra ---\n");
    printf("Criptomoeda: %s\n", cripto->nome);
    printf("Quantidade: %.2f\n", valor);
    printf("Cotacao: %.2f\n", cripto->cotacao);
    printf("Taxa: %.2f\n", taxa);
    printf("Total a pagar: %.2f\n", total);

    char confirmacao;
    printf("Deseja confirmar a compra? (s/n): ");
    scanf(" %c", &confirmacao);
    flush_input();

    if (confirmacao == 's' || confirmacao == 'S')
    {
        if (usuario->reais >= total)
        {
            usuario->reais -= total;
            if (opcao == 1)
                usuario->bitcoin += valor;
            if (opcao == 2)
                usuario->ethereum += valor;
            if (opcao == 3)
                usuario->ripple += valor;
        }
    }
}
void vender_criptomoedas(USUARIO *usuario)
{
    if (!verifica_senha(usuario))
    {
        printf("Senha incorreta. Transacao cancelada.\n");
        return;
    }
    int opcao;
    printf("\nDigite o codigo da criptomoeda (1-Bitcoin, 2-Ethereum, 3-Ripple): ");
    scanf("%d", &opcao);
    flush_input();

    if (opcao < 1 || opcao > 3)
    {
        printf("Opcao invalida.\n");
        return;
    }

    float valor;
    printf("Digite a quantidade que voce deseja vender: ");
    scanf("%f", &valor);
    flush_input();

    if (valor <= 0)
    {
        printf("Valor invalido.\n");
        return;
    }
    Criptomoeda *cripto = &CT[opcao - 1];
    float taxa = valor * cripto->cotacao * 0.01;
    float total = valor * cripto->cotacao - taxa;

    printf("\n--- Detalhes da Compra ---\n");
    printf("Criptomoeda: %s\n", cripto->nome);
    printf("Quantidade: %.2f\n", valor);
    printf("Cotacao: %.2f\n", cripto->cotacao);
    printf("Taxa: %.2f\n", taxa);
    printf("Total a receber: %.2f\n", total);

    char confirmacao;
    printf("Deseja confirmar a venda? (s/n): ");
    scanf(" %c", &confirmacao);
    flush_input();

    if ((opcao == 1 && valor <= usuario->bitcoin) ||
        (opcao == 2 && valor <= usuario->ethereum) ||
        (opcao == 3 && valor <= usuario->ripple))
    {

        if (opcao == 1)
            usuario->bitcoin -= valor;
        if (opcao == 2)
            usuario->ethereum -= valor;
        if (opcao == 3)
            usuario->ripple -= valor;
    }
}


