#include <stdio.h>

int main(void) {
    const int senha_correta = 4821;
    int tentativas = 0;

    for (int tentativa = 0; tentativa <= 9999; tentativa++) {
        tentativas++;

        if (tentativa == senha_correta) {
            printf("Senha encontrada: %04d\n", tentativa);
            printf("Tentativas realizadas: %d\n", tentativas);
            return 0;
        }
    }

    printf("Senha nao encontrada.\n");
    return 1;
}
