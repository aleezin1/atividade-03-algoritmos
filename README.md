# Atividade Avaliativa 03 — Ordenação e Arquivos em C

Programa em C que une **algoritmos de ordenação** com **manipulação de arquivos**. Tudo é feito em um único programa com menu interativo.

## Integrantes

| Nome | RGM |
|---|---|
| Pablo Soares Gomes | 49150308 |
| Alexander Serafim | 049269569 |
| Felipe Dias Gomes | 48814342 |
| João Vitor Rocha Silva | 47170867 |

## Funcionalidades

1. **Cria e grava** um arquivo com dados numéricos desordenados (`dados.txt`). Os valores podem ser digitados ou gerados aleatoriamente.
2. **Lê** os dados do arquivo.
3. Permite **escolher o algoritmo de ordenação**:
   - Bubble Sort
   - Insertion Sort
   - Selection Sort
   - Merge Sort
   - Quick Sort
4. **Ordena** os dados e **salva** o resultado em um novo arquivo (`ordenado.txt`), mostrando também o tempo de ordenação.
5. Permite **alterar um valor** dentro do `dados.txt` e **reordenar** em seguida.

## Arquivos

| Arquivo | Descrição |
|---|---|
| `atividade03.c` | Código-fonte do programa |
| `dados.txt` | Valores originais (entrada), gerado pelo programa |
| `ordenado.txt` | Valores já ordenados (saída), gerado pelo programa |

## Menu

```
========== ORDENACAO E ARQUIVOS ==========
1 - Criar arquivo de dados (dados.txt)
2 - Exibir dados originais (dados.txt)
3 - Ordenar dados e salvar (ordenado.txt)
4 - Alterar um valor e reordenar
5 - Exibir dados ordenados (ordenado.txt)
0 - Sair
```

## Como compilar e executar

Com o GCC instalado:

```bash
gcc atividade03.c -o atividade03
./atividade03        # Linux/macOS
atividade03.exe      # Windows
```

O programa também roda no [OnlineGDB](https://www.onlinegdb.com/): basta colar o código, selecionar a linguagem **C** e clicar em **Run**.

## Exemplo de uso

```
dados.txt     →  42 7 19 3 88 15 61 0
ordenado.txt  →  0 3 7 15 19 42 61 88
```

Alterando a posição 2 (de `7` para `100`) e reordenando:

```
dados.txt     →  42 100 19 3 88 15 61 0
ordenado.txt  →  0 3 15 19 42 61 88 100
```

## Conceitos aplicados

| Plano de aula | Conceito | Onde aparece no código |
|---|---|---|
| Aula 08 — Arquivos em C | `fopen`, `fprintf`, `fscanf`, `fclose`, `remove`, `rename` | Gravação e leitura dos arquivos; alteração de um valor via arquivo temporário |
| Aula 09 — Ponteiros | Passagem por referência, aritmética de ponteiros, `malloc`/`free` | Função `trocar`, vetor dinâmico lido do arquivo, `mostrarVetor` |
| Aula 11 — Algoritmos de ordenação | Bubble, Insertion, Selection, Merge e Quick Sort | Funções de ordenação |
| Aula 12 — Estrutura `switch` | Menus com `switch/case` | Menu principal, escolha do algoritmo e da forma de entrada |

## Complexidade dos algoritmos

| Algoritmo | Estratégia | Complexidade média |
|---|---|---|
| Bubble Sort | Comparação e troca | O(n²) |
| Insertion Sort | Inserção ordenada | O(n²) |
| Selection Sort | Seleção do mínimo | O(n²) |
| Merge Sort | Dividir e conquistar | O(n log n) |
| Quick Sort | Dividir e conquistar | O(n log n) |
