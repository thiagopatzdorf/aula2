#include <stdio.h>
#include <string.h>

int main(void) {
    const char senha_correta[] = "4821";
    char tentativa[5];

    printf("Digite uma senha de 4 digitos: ");

    if (scanf("%4s", tentativa) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    if (strcmp(tentativa, senha_correta) == 0) {
        printf("Senha correta.\n");
    } else {
        printf("Senha incorreta.\n");
    }

    return 0;
}
