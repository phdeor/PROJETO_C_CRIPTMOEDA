#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcao.h"

#define ARQUIVO_BINARIO "usuarios.dat"

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
    {"Gustavo Mendes", "10101010101", "senha10", 0.0, 0.0, 0.0, 0.0, {{0}}, 0}
};

int verifica_senha(USUARIO *usuario) {
    char senha[20];
    printf("Digite sua senha para confirmar a transacao: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0'; // Remove a nova linha

    return strcmp(usuario->senha, senha) == 0;
}

int flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 1;
}

void menu(USUARIO *usuario) {
    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Consultar Saldo\n");
        printf("2. Consultar Extrato\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Comprar Criptomoedas\n");
        printf("6. Vender Criptomoedas\n");
        printf("7. Atualizar Cotacoes\n");
        printf("8. Sair\n");
        printf("Digite sua opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Tente novamente.\n");
            flush_input();  
            continue;
        }
        flush_input();  

        switch (opcao) {
            case 1:
                consultar_saldo(usuario);
                // salvar_dados(usuarios_fixos, NUM_USUARIOS);
                break;
            case 2:
                consultar_extrato(usuario);
                gerar_extrato(usuario);
                // salvar_dados(usuarios_fixos, NUM_USUARIOS);
                break;
            case 3:
                depositar(usuario);
                gerar_extrato(usuario);
                // salvar_dados(usuarios_fixos, NUM_USUARIOS);
                break;
            case 4:
                sacar(usuario);
                gerar_extrato(usuario);
                // salvar_dados(usuarios_fixos, NUM_USUARIOS);
                break;
            case 5:
                comprar_criptomoedas(usuario);
                gerar_extrato(usuario);
                // salvar_dados(usuarios_fixos, NUM_USUARIOS);
                break;
            case 6:
                vender_criptomoedas(usuario);
                gerar_extrato(usuario);
                // salvar_dados(usuarios_fixos, NUM_USUARIOS);
                break;
            case 7:
                atualizar_cotacao();
                // salvar_dados(usuarios_fixos, NUM_USUARIOS);
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

void inicializaUsuario(USUARIO *usuario, const char *nome, const char *cpf, float reais, float bitcoin, float ethereum, float ripple) {
    strcpy(usuario->nome, nome);
    strcpy(usuario->cpf, cpf);
    usuario->reais = reais;
    usuario->bitcoin = bitcoin;
    usuario->ethereum = ethereum;
    usuario->ripple = ripple;
    usuario->num_transacoes = 0;
}

void obter_data_hora_atual(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%04d %02d:%02d:%02d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void registrar_transacao(USUARIO *usuario, const char *tipo, float valor, const char *cripto, float cotacao, float tx) {
    Transacao nova_transacao;
    obter_data_hora_atual(nova_transacao.data_hora);
    strcpy(nova_transacao.tipo, tipo);
    strcpy(nova_transacao.cripto, cripto);
    nova_transacao.valor = valor;
    nova_transacao.cotacao = cotacao;
    nova_transacao.tx = tx;
    nova_transacao.reais = usuario->reais;
    nova_transacao.bitcoin = usuario->bitcoin;
    nova_transacao.ethereum = usuario->ethereum;
    nova_transacao.ripple = usuario->ripple;

    if (usuario->num_transacoes >= MAX_TRANSACOES) {
        for (int i = 1; i < MAX_TRANSACOES; i++) {
            usuario->transacoes[i - 1] = usuario->transacoes[i];
        }
        usuario->transacoes[MAX_TRANSACOES - 1] = nova_transacao;
    } else {
        usuario->transacoes[usuario->num_transacoes] = nova_transacao;
        usuario->num_transacoes++;
    }
}

void consultar_saldo(USUARIO *usuario) {
    printf("\nConsultar Saldo:");
    printf("\nNome: %s\n", usuario->nome);
    printf("CPF: %s\n", usuario->cpf);
    printf("Reais: %.2f\n", usuario->reais);
    printf("Bitcoin: %.4f\n", usuario->bitcoin);
    printf("Ethereum: %.2f\n", usuario->ethereum);
    printf("Ripple: %.2f\n", usuario->ripple);
}

void consultar_extrato(USUARIO *usuario) {
    printf("\nConsultar Extrato:\n");
    gerar_extrato(usuario); 
}

void depositar(USUARIO *usuario) {
    float deposito;
    printf("\nDigite o valor que voce deseja depositar: ");
    scanf("%f", &deposito);
    flush_input();  

    if (deposito > 0) {
        usuario->reais += deposito;
        registrar_transacao(usuario, "deposito", deposito, "Reais", 0.0, 0.0);
        printf("Deposito realizado com sucesso!\n");
    } else {
        printf("Valor invalido para deposito.\n");
    }
}

void sacar(USUARIO *usuario) {
    if (!verifica_senha(usuario)) {
        printf("Senha incorreta. Transacao cancelada.\n");
        return;
    }
    float valor;
    printf("\nDigite o valor que voce deseja sacar: ");
    scanf("%f", &valor);
    flush_input();  

    if (valor > 0 && valor <= usuario->reais) {
        usuario->reais -= valor;
        registrar_transacao(usuario, "saque", valor, "Reais", 0.0, 0.0);
        printf("Saque realizado com sucesso!\n");
    } else {
        printf("Valor invalido ou saldo insuficiente.\n");
    }
}

float gerar_variacao() {
    return ((float)rand() / RAND_MAX * 2 - 1) * 0.05;
}

void atualizar_cotacao() {
    for (int i = 0; i < 3; i++) {
        float variacao = gerar_variacao();
        CT[i].cotacao *= (1 + variacao);
        printf("Nova cotacao de %s: %.2f (variacao: %.2f%%)\n", CT[i].nome, CT[i].cotacao, variacao * 100);
    }
}

void comprar_criptomoedas(USUARIO *usuario) {
    if (!verifica_senha(usuario)) {
        printf("Senha incorreta. Transacao cancelada.\n");
        return;
    }
    int opcao;
    printf("\nDigite o codigo da criptomoeda (1-Bitcoin, 2-Ethereum, 3-Ripple): ");
    scanf("%d", &opcao);
    flush_input();  

    if (opcao < 1 || opcao > 3) {
        printf("Opcao invalida.\n");
        return;
    }

    float valor;
    printf("Digite a quantidade que voce deseja comprar: ");
    scanf("%f", &valor);
    flush_input();  

    if (valor <= 0) {
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

    if (confirmacao == 's' || confirmacao == 'S') {
        if (usuario->reais >= total) {
            usuario->reais -= total;
            if (opcao == 1) usuario->bitcoin += valor;
            if (opcao == 2) usuario->ethereum += valor;
            if (opcao == 3) usuario->ripple += valor;

            registrar_transacao(usuario, "compra", total, cripto->nome, cripto->cotacao, taxa);
            printf("Compra realizada com sucesso!\n");
    } else {
        printf("Saldo insuficiente.\n");
    }
    } else {
        printf("Compra cancelada.\n");
    }
}    

void vender_criptomoedas(USUARIO *usuario) {
    if (!verifica_senha(usuario)) {
        printf("Senha incorreta. Transacao cancelada.\n");
        return;
    }
    int opcao;
    printf("\nDigite o codigo da criptomoeda (1-Bitcoin, 2-Ethereum, 3-Ripple): ");
    scanf("%d", &opcao);
    flush_input();  

    if (opcao < 1 || opcao > 3) {
        printf("Opcao invalida.\n");
        return;
    }

    float valor;
    printf("Digite a quantidade que voce deseja vender: ");
    scanf("%f", &valor);
    flush_input();  


    if (valor <= 0) {
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
        (opcao == 3 && valor <= usuario->ripple)) {
        
        if (opcao == 1) usuario->bitcoin -= valor;
        if (opcao == 2) usuario->ethereum -= valor;
        if (opcao == 3) usuario->ripple -= valor;

        usuario->reais += total;
        registrar_transacao(usuario, "venda", total, cripto->nome, cripto->cotacao, taxa);
        printf("Venda realizada com sucesso!\n");
    } else {
        printf("Quantidade insuficiente para venda.\n");
    }
}

void gerar_extrato(USUARIO *usuario) {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "%s_%s.txt", usuario->nome, usuario->cpf);
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de extrato");
        return;
    }
    fprintf(arquivo, "Extrato de %s (CPF: %s)\n", usuario->nome, usuario->cpf);
    fprintf(arquivo, "Reais: %.2f\n", usuario->reais);
    fprintf(arquivo, "Transacoes:\n");

    for (int i = 0; i < usuario->num_transacoes; i++) {
        Transacao *t = &usuario->transacoes[i];
        fprintf(arquivo, "%s - %s: R$ %.2f - %s (Cotacao: %.4f, Taxa: %.2f)\n", 
                t->data_hora, t->tipo, t->valor, t->cripto, t->cotacao, t->tx);
    }

    fclose(arquivo);
}

void salvar_dados(USUARIO usuarios[], int num_usuarios) {
    FILE *arquivo = fopen("usuarios.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvamento.\n");
        return;
    }

    fwrite(usuarios, sizeof(USUARIO), num_usuarios, arquivo);
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

void carregar_dados(USUARIO usuarios[], int *num_usuarios) {
    FILE *arquivo = fopen("usuarios.dat", "rb");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado. Iniciando com dados padrão.\n");
        *num_usuarios = NUM_USUARIOS;
        // Inicialize com usuários fixos padrão se o arquivo não existir
        inicializaUsuario(&usuarios[0], "Usuario 1", "11111111111", 1000.0, 0.5, 1.0, 2.0);
        inicializaUsuario(&usuarios[1], "Usuario 2", "22222222222", 2000.0, 0.2, 0.5, 1.0);
        inicializaUsuario(&usuarios[2], "Usuario 3", "33333333333", 1500.0, 0.1, 0.3, 0.7);
        inicializaUsuario(&usuarios[3], "Usuario 4", "44444444444", 3000.0, 0.7, 1.2, 1.5);
        inicializaUsuario(&usuarios[4], "Usuario 5", "55555555555", 5000.0, 1.0, 2.0, 3.0);
        inicializaUsuario(&usuarios[5], "Usuario 6", "66666666666", 1000.0, 0.1, 0.5, 1.0);
        inicializaUsuario(&usuarios[6], "Usuario 7", "77777777777", 2500.0, 0.4, 0.9, 1.2);
        inicializaUsuario(&usuarios[7], "Usuario 8", "88888888888", 1200.0, 0.3, 0.8, 0.5);
        inicializaUsuario(&usuarios[8], "Usuario 9", "99999999999", 1800.0, 0.2, 0.6, 1.1);
        inicializaUsuario(&usuarios[9], "Usuario 10", "10101010101", 7000.0, 1.5, 2.5, 3.5);
    } else {
        fread(usuarios, sizeof(USUARIO), NUM_USUARIOS, arquivo);
        fclose(arquivo);
        printf("Dados carregados com sucesso!\n");
    }
}


