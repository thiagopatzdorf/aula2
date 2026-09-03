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

---

## 2. Encontrar a senha — força bruta sequencial

Arquivo: `procurar_senha.c`

Agora ninguém fornece a resposta.

Uma estratégia possível é procurar assim:

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

Mas isso é apenas uma forma de explorar o espaço.

---

## 3. Encontrar a senha — força bruta paralela

Arquivo: `procurar_senha_threads.c`

Não existe obrigação de testar uma possibilidade por vez.

Podemos dividir o espaço entre várias threads.

Com 8 threads:

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

As oito buscas podem avançar ao mesmo tempo, dependendo do hardware disponível.

A senha `4821`, por exemplo, está na faixa da Thread 3. Enquanto ela procura ali, as demais examinam outras regiões.

Idealmente:

```text
trabalho por trabalhador ≈ possibilidades / trabalhadores
```

Então 8 workers podem dividir uma busca de 10.000 possibilidades em cerca de 1.250 candidatos por worker.

Isso é uma melhoria real de tempo.

Mas existe uma diferença fundamental:

```text
10.000 possibilidades / 8 workers
```

continua sendo um problema com:

```text
10.000 possibilidades
```

O paralelismo distribuiu o trabalho.

Ele não descobriu nada novo sobre a senha.

---

## 4. E se, em vez de calcular mais, descobrirmos mais?

Aqui aparece uma terceira abordagem.

Imagine novamente que a senha tenha quatro dígitos.

Sem nenhuma informação:

```text
0000 até 9999
```

São 10.000 candidatos.

Agora alguém informa:

```text
O primeiro dígito é 4.
```

O espaço cai para:

```text
4000 até 4999
```

Agora existem apenas 1.000 candidatos.

Depois descobrimos:

```text
O último dígito é 1.
```

Não precisamos mais considerar:

```text
4000
4002
4003
...
```

Só candidatos da forma:

```text
40?1
41?1
42?1
...
49?1
```

O espaço caiu novamente.

Isso é diferente de colocar mais threads.

### Mais hardware

```text
10.000 candidatos
↓
dividir entre 8 workers
↓
continuam existindo 10.000 candidatos
```

### Mais informação

```text
10.000 candidatos
↓
conhecer uma propriedade da resposta
↓
1.000 candidatos
↓
nova propriedade
↓
100 candidatos
```

No primeiro caso, fazemos aproximadamente o mesmo trabalho mais rápido.

No segundo, descobrimos que grande parte do trabalho nunca precisou ser feita.

> Mais computação aumenta a quantidade de possibilidades que conseguimos testar. Informação reduz a quantidade de possibilidades que precisamos testar.

Essa distinção é central para a discussão.

---

## 5. Senhas reais não são necessariamente buscas uniformes

Nosso exemplo pressupõe que não sabemos absolutamente nada sobre a resposta.

Na prática, problemas de busca frequentemente possuem estrutura.

Uma senha escolhida aleatoriamente se comporta de maneira diferente de uma senha escolhida por uma pessoa.

Pessoas tendem a repetir padrões, palavras, datas e estruturas familiares. Se sabemos algo sobre como os candidatos são distribuídos, podemos priorizar regiões mais prováveis do espaço em vez de tratá-las todas como igualmente prováveis.

Da mesma forma, informação adicional sobre um problema pode eliminar possibilidades antes mesmo de avaliá-las.

A ideia importante aqui não é como atacar uma senha real.

É perceber três estratégias conceitualmente diferentes:

```text
1. Busca sequencial
   testar uma possibilidade após a outra

2. Busca paralela
   testar várias possibilidades simultaneamente

3. Redução do espaço de busca
   usar informação ou estrutura para não testar possibilidades desnecessárias
```

A terceira é a mais interessante para a pergunta desta aula.

---

## 6. A diferença cresce

| Tamanho | Possibilidades numéricas |
|---|---:|
| 4 dígitos | 10.000 |
| 8 dígitos | 100.000.000 |
| 16 dígitos | 10.000.000.000.000.000 |

Se aumentamos apenas o hardware:

```text
10^16 / 8
```

continua sendo gigantesco.

Mas se descobrimos uma propriedade capaz de eliminar quase todo o espaço, o problema prático pode mudar radicalmente.

É por isso que existe uma diferença importante entre:

```text
computar mais rápido
```

e:

```text
descobrir que não precisamos computar aquilo
```

---

## 7. Ligação com P e NP

Esse exemplo serve para construir a **intuição** da diferença entre encontrar e verificar soluções.

De forma simplificada:

- **P**: problemas para os quais conhecemos algoritmos que encontram uma solução em tempo polinomial.
- **NP**: problemas para os quais uma solução candidata pode ser verificada em tempo polinomial.

A grande pergunta é:

```text
P = NP?
```

Se conseguimos verificar uma solução rapidamente, será que sempre existe uma maneira de encontrá-la rapidamente também?

Ainda não sabemos.

E aqui é importante separar as ideias.

Paralelizar força bruta não prova `P = NP`.

Se o número de possibilidades cresce exponencialmente, dividir a busca entre 8, 80 ou 8.000 workers pode melhorar brutalmente o tempo na prática, mas uma quantidade fixa de workers não transforma automaticamente um crescimento exponencial em polinomial.

Da mesma forma, conhecer alguns dígitos de uma senha não transforma o exemplo em uma prova sobre P e NP.

O que ele mostra é outra coisa:

> Informação e estrutura podem reduzir o espaço efetivo que precisamos explorar.

Isso nos leva a uma pergunta mais interessante sobre inteligência.

Talvez inteligência não seja apenas a capacidade de executar mais operações por segundo.

Talvez parte dela seja a capacidade de descobrir regularidades que tornam operações desnecessárias.

```text
possibilidades
↓
informação
↓
estrutura
↓
menos busca
↓
decisão
```

> Importante: quebrar essa senha de 4 dígitos não está sendo apresentado como um problema NP-completo. É um exemplo visual para separar **verificação**, **busca sequencial**, **paralelismo** e **redução do espaço de busca** antes de entrar na teoria formal.

---

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

---

## Pergunta da aula

Uma máquina mais poderosa consegue explorar mais possibilidades.

Mas uma inteligência melhor talvez consiga perceber que quase todas elas podem ser ignoradas.

**O que é mais poderoso: calcular mais possibilidades ou descobrir quais possibilidades nunca precisaram ser calculadas?**
