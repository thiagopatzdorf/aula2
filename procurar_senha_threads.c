#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

#define NUM_THREADS 8
#define MAX_SENHA 9999

static const int senha_correta = 4821;
static atomic_int encontrada = 0;

typedef struct {
    int inicio;
    int fim;
    int id;
} Faixa;

void *procurar(void *arg) {
    Faixa *faixa = (Faixa *)arg;

    for (int tentativa = faixa->inicio;
         tentativa <= faixa->fim && !atomic_load(&encontrada);
         tentativa++) {

        if (tentativa == senha_correta) {
            if (!atomic_exchange(&encontrada, 1)) {
                printf("Thread %d encontrou a senha: %04d\n", faixa->id, tentativa);
            }
            break;
        }
    }

    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    Faixa faixas[NUM_THREADS];

    int total = MAX_SENHA + 1;
    int bloco = total / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        faixas[i].inicio = i * bloco;
        faixas[i].fim = (i == NUM_THREADS - 1)
            ? MAX_SENHA
            : ((i + 1) * bloco) - 1;
        faixas[i].id = i;

        pthread_create(&threads[i], NULL, procurar, &faixas[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    if (!atomic_load(&encontrada)) {
        printf("Senha nao encontrada.\n");
    }

    return 0;
}
