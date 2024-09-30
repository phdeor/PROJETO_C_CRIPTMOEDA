#ifndef FUNCAO_H
#define FUNCAO_H

#define MAX_TRANSACOES 100

typedef struct {
    char data_hora[20];
    char tipo[20];
    float valor;
    char cripto[20];
    float cotacao;
    float tx;
    float reais;
    float bitcoin;
    float ethereum;
    float ripple;
} Transacao;

typedef struct {
    char nome[50];
    char cpf[13];
    float reais;
    float bitcoin;
    float ethereum;
    float ripple;
    Transacao transacoes[MAX_TRANSACOES];
    int num_transacoes;
} USUARIO;

typedef struct {
    char nome[20];
    float cotacao;
} Criptomoeda;

extern Criptomoeda CT[];

void inicializaUsuario(USUARIO *usuario, const char *nome, const char *cpf, float reais, float bitcoin, float ethereum, float ripple);
void menu(USUARIO *usuario);
void consultar_saldo(USUARIO *usuario);
void consultar_extrato(USUARIO *usuario);
void depositar(USUARIO *usuario);
void sacar(USUARIO *usuario);
void comprar_criptomoedas(USUARIO *usuario);
void vender_criptomoedas(USUARIO *usuario);
void atualizar_cotacao();

#endif
