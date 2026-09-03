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

## 2. Procurar a senha

Arquivo: `procurar_senha.c`

Agora ninguém fornece a resposta.

O programa precisa procurar:

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

Se a senha for `4821`, começando em `0000`, o programa realiza 4.822 tentativas até encontrá-la.

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

Você não conhece a resposta e, sem nenhuma informação adicional, percorre possibilidades até chegar nela.

```text
0000 → 0001 → 0002 → ... → 4821
```

Esse segundo processo pode crescer muito rapidamente.

| Tamanho | Possibilidades numéricas |
|---|---:|
| 4 dígitos | 10.000 |
| 8 dígitos | 100.000.000 |
| 16 dígitos | 10.000.000.000.000.000 |

Aumentar a senha não torna difícil verificar uma tentativa específica na mesma proporção em que torna inviável testar todas as possibilidades.

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

> Importante: quebrar essa senha de 4 dígitos não está sendo apresentado aqui como um problema NP-completo. É apenas um exemplo visual para separar as ideias de **verificação** e **busca** antes de entrar na teoria formal.

## Compilar

Com GCC:

```bash
gcc validar_senha.c -o validar_senha
gcc procurar_senha.c -o procurar_senha
```

Executar:

```bash
./validar_senha
./procurar_senha
```

## Pergunta da aula

Se informação adicional consegue eliminar enormes partes de um espaço de busca, até que ponto inteligência pode ser entendida como a capacidade de descobrir **o que não precisa ser computado**?
