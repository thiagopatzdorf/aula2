# Aula 2 — Verificar é o mesmo que encontrar?

A ideia desta aula é visualizar uma diferença simples:

> Receber uma resposta e verificar se ela está correta pode ser muito diferente de ter que encontrar essa resposta do zero.

Usamos uma senha de 4 dígitos apenas como exemplo didático.

## 1. Validar uma senha

Arquivo: `validar_senha.c`

Nesse programa, o usuário já fornece uma tentativa.

O computador só precisa responder:

```text
A tentativa é igual à senha correta?
```

Exemplo:

```text
Senha correta: 4821
Tentativa:      4821
```

O trabalho principal é uma comparação.

```c
if (strcmp(tentativa, senha_correta) == 0) {
    printf("Senha correta.\n");
}
```

A solução candidata já foi entregue. O programa apenas verifica.

## 2. Procurar a senha — busca sequencial

Arquivo: `procurar_senha.c`

Agora ninguém fornece a resposta.

O programa pode procurar assim:

```text
0000
0001
0002
0003
...
4819
4820
4821
```

até encontrar a senha correta.

```c
for (int tentativa = 0; tentativa <= 9999; tentativa++) {
    if (tentativa == senha_correta) {
        printf("Senha encontrada: %04d\n", tentativa);
        return 0;
    }
}
```

Se a senha for `4821`, começando em `0000`, esse algoritmo realiza 4.822 tentativas até encontrá-la.

Mas isso é só uma estratégia possível.

## 3. Procurar a senha — busca paralela

Arquivo: `procurar_senha_threads.c`

Não existe obrigação de testar uma possibilidade por vez.

Podemos dividir o espaço entre várias threads.

Com 8 threads e uma senha de 4 dígitos, por exemplo:

```text
Thread 0: 0000 até 1249
Thread 1: 1250 até 2499
Thread 2: 2500 até 3749
Thread 3: 3750 até 4999
Thread 4: 5000 até 6249
Thread 5: 6250 até 7499
Thread 6: 7500 até 8749
Thread 7: 8750 até 9999
```

As oito buscas podem avançar ao mesmo tempo.

A senha `4821`, por exemplo, está na faixa da Thread 3. Enquanto ela procura ali, as demais threads examinam outras regiões do espaço.

Isso demonstra uma distinção importante:

> Um problema pode ter um espaço de busca enorme sem que sejamos obrigados a explorá-lo sequencialmente.

Paralelismo reduz o **tempo de relógio** da busca ao distribuir trabalho entre recursos computacionais.

Porém, ele não reduz automaticamente o tamanho matemático do espaço de possibilidades.

Se existem 10.000 candidatos, continuam existindo 10.000 candidatos. Nós apenas podemos dividir o trabalho.

Idealmente, com `k` trabalhadores realmente executando em paralelo, uma busca uniforme pode se aproximar de:

```text
trabalho por trabalhador ≈ possibilidades / k
```

Então 8 workers podem, em condições ideais, dividir uma busca em aproximadamente oito partes.

### Threads não significam necessariamente execução física simultânea

Criar 8 threads não garante que 8 instruções estejam literalmente sendo executadas ao mesmo tempo.

Isso depende do hardware e do sistema operacional.

- Em uma CPU com 8 processadores lógicos disponíveis, até 8 threads podem progredir efetivamente em paralelo.
- Em uma CPU com menos núcleos/processadores lógicos, o sistema operacional alterna as threads.
- Também podemos distribuir a busca entre vários computadores.
- GPUs conseguem executar quantidades muito maiores de operações semelhantes em paralelo.

Portanto, existe uma segunda maneira de atacar um problema além de descobrir um algoritmo melhor:

```text
1. Melhorar o algoritmo.
2. Aumentar o paralelismo.
```

Essas duas coisas não são iguais.

## A diferença

### Verificar

Você recebe um candidato:

```text
4821
```

E pergunta:

```text
Está correto?
```

### Encontrar

Você não conhece a resposta e precisa explorar possibilidades.

Isso pode ser feito:

```text
sequencialmente
```

ou:

```text
em paralelo
```

O espaço continua crescendo rapidamente:

| Tamanho | Possibilidades numéricas |
|---|---:|
| 4 dígitos | 10.000 |
| 8 dígitos | 100.000.000 |
| 16 dígitos | 10.000.000.000.000.000 |

Aumentar recursos computacionais ajuda bastante, mas não é a mesma coisa que descobrir uma forma de evitar a busca.

Esse contraste é importante para a discussão da aula:

```text
força bruta + mais hardware
```

é diferente de:

```text
nova informação ou estrutura → menos possibilidades precisam ser examinadas
```

## Ligação com P e NP

Esse exemplo serve para construir a **intuição** da diferença entre encontrar e verificar soluções.

De forma simplificada:

- **P**: problemas para os quais conhecemos algoritmos que encontram a solução em tempo polinomial.
- **NP**: problemas para os quais uma solução candidata pode ser verificada em tempo polinomial.

A grande pergunta é:

```text
P = NP?
```

Se conseguimos verificar uma solução rapidamente, será que sempre existe uma maneira de encontrá-la rapidamente também?

Ainda não sabemos.

Paralelizar uma força bruta não prova `P = NP`.

Se o número de possibilidades cresce exponencialmente com o tamanho da entrada, usar uma quantidade fixa de threads — 8, 80 ou 8.000 — pode reduzir bastante o tempo na prática, mas não necessariamente muda a classe de complexidade do algoritmo.

> Importante: quebrar essa senha de 4 dígitos não está sendo apresentado aqui como um problema NP-completo. É apenas um exemplo visual para separar **verificação**, **busca sequencial**, **busca paralela** e **descoberta de estrutura** antes de entrar na teoria formal.

## Compilar

Com GCC:

```bash
gcc validar_senha.c -o validar_senha
gcc procurar_senha.c -o procurar_senha
gcc procurar_senha_threads.c -o procurar_senha_threads -pthread
```

Executar:

```bash
./validar_senha
./procurar_senha
./procurar_senha_threads
```

## Pergunta da aula

Mais computação permite testar mais possibilidades ao mesmo tempo.

Mas informação pode fazer algo ainda mais poderoso: eliminar possibilidades antes mesmo de testá-las.

Até que ponto inteligência pode ser entendida como a capacidade de descobrir **o que não precisa ser computado**?
