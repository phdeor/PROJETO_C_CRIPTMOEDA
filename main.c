#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pasta1/funcao.h"  // Inclui a header com a função menu() 
#include "pasta3/login.h"   // Inclui a header com a função login()

Criptomoeda CT[3] = {
    {"Bitcoin", 30000.0},
    {"Ethereum", 2000.0},
    {"Ripple", 0.5}
};

int main() {
    srand(time(NULL));
    
    login();  // Chama o sistema de login antes de acessar o menu

    USUARIO usuario;
    inicializaUsuario(&usuario, "Nome Usuario", "12345678910", 10000.0, 0.0, 0.0, 0.0);
    
    menu(&usuario);
    
    return 0;
}
