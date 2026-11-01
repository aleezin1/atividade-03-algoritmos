/*
 * Atividade Avaliativa 03 - Ordenacao e Arquivos em C
 *
 * Programa unico que:
 *  1) Cria e grava um arquivo com dados numericos desordenados (dados.txt);
 *  2) Le esses dados do arquivo;
 *  3) Permite escolher o tipo de ordenacao (Bubble, Insertion, Selection,
 *     Merge ou Quick Sort);
 *  4) Ordena os dados e salva o resultado em um novo arquivo (ordenado.txt);
 *  5) Permite alterar um valor dentro do arquivo e reordenar novamente.
 *
 * Conceitos utilizados (planos de aula):
 *  - Aula 08: fopen, fprintf, fscanf, fclose, remove, rename (arquivos);
 *  - Aula 09: ponteiros, passagem por referencia, malloc e free;
 *  - Aula 11: algoritmos de ordenacao;
 *  - Aula 12: menu com estrutura switch/case.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARQ_DADOS    "dados.txt"     // arquivo com os valores originais
#define ARQ_ORDENADO "ordenado.txt"  // arquivo com os valores ordenados
#define ARQ_TEMP     "temp.txt"      // arquivo temporario usado na alteracao

/* ============================================================
 *  FUNCOES AUXILIARES (ponteiros - aula 09)
 * ============================================================ */

// Troca dois valores usando ponteiros (passagem por referencia)
void trocar(int *a, int *b) {
    int temp = *a;   // temp recebe o valor de a
    *a = *b;         // a recebe o valor de b
    *b = temp;       // b recebe o valor guardado em temp
}

// Exibe o vetor percorrendo-o com aritmetica de ponteiros
void mostrarVetor(int *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(v + i)); // *(v+i) acessa o elemento i do vetor
    }
    printf("\n");
}

/* ============================================================
 *  ALGORITMOS DE ORDENACAO (aula 11)
 * ============================================================ */

// 1. Bubble Sort: compara pares vizinhos e troca se estiverem fora de ordem
void bubbleSort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {          // atual maior que o proximo?
                trocar(&v[j], &v[j + 1]);   // troca os dois
            }
        }
    }
}

// 2. Insertion Sort: insere cada elemento na posicao correta
void insertionSort(int v[], int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {        // comeca no segundo elemento
        chave = v[i];                // guarda o valor atual
        j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];         // desloca os maiores para a direita
            j--;
        }
        v[j + 1] = chave;            // insere a chave na posicao correta
    }
}

// 3. Selection Sort: encontra o menor e coloca na posicao correta
void selectionSort(int v[], int n) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;                     // assume que o menor e o atual
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[min]) min = j;   // achou um menor
        }
        if (min != i) {
            trocar(&v[i], &v[min]);  // troca se encontrou menor
        }
    }
}

// Intercala dois subvetores ordenados: v[inicio..meio] e v[meio+1..fim]
void merge(int v[], int inicio, int meio, int fim) {
    int i = inicio, j = meio + 1, k = 0;
    int *aux = (int *) malloc((fim - inicio + 1) * sizeof(int)); // vetor temporario

    if (aux == NULL) {
        printf("Erro de alocacao no merge!\n");
        return;
    }

    // Intercala os dois subvetores
    while (i <= meio && j <= fim) {
        if (v[i] <= v[j]) aux[k++] = v[i++];
        else              aux[k++] = v[j++];
    }
    // Copia o que sobrou de cada lado
    while (i <= meio) aux[k++] = v[i++];
    while (j <= fim)  aux[k++] = v[j++];

    // Devolve os valores ao vetor original
    for (i = inicio, k = 0; i <= fim; i++, k++)
        v[i] = aux[k];

    free(aux); // libera a memoria temporaria
}

// 4. Merge Sort: divide ao meio recursivamente e intercala as partes
void mergeSort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(v, inicio, meio);      // parte esquerda
        mergeSort(v, meio + 1, fim);     // parte direita
        merge(v, inicio, meio, fim);     // intercala
    }
}

// 5. Quick Sort: escolhe um pivo e separa menores a esquerda e maiores a direita
void quickSort(int v[], int inicio, int fim) {
    int i = inicio, j = fim;
    int pivo = v[(inicio + fim) / 2];    // pivo = elemento do meio

    // Particionamento
    while (i <= j) {
        while (v[i] < pivo) i++;
        while (v[j] > pivo) j--;
        if (i <= j) {
            trocar(&v[i], &v[j]);
            i++;
            j--;
        }
    }
    // Recursao nas partes esquerda e direita
    if (inicio < j) quickSort(v, inicio, j);
    if (i < fim)    quickSort(v, i, fim);
}

/* ============================================================
 *  MANIPULACAO DE ARQUIVOS (aula 08)
 * ============================================================ */

// Grava um vetor de inteiros em um arquivo (um valor por linha)
int gravarArquivo(const char *arquivo, int *v, int n) {
    FILE *fp = fopen(arquivo, "w");  // abre em modo escrita ("w")
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", arquivo);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", v[i]);   // grava cada valor em uma linha
    }
    fclose(fp);                      // fecha o arquivo
    return 1;
}

// Conta quantos valores numericos existem no arquivo
int contarValores(const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");  // abre em modo leitura ("r")
    int valor, qtd = 0;
    if (fp == NULL) return -1;       // arquivo nao existe
    while (fscanf(fp, "%d", &valor) == 1) {
        qtd++;
    }
    fclose(fp);
    return qtd;
}

// Le os valores do arquivo para um vetor alocado dinamicamente.
// Retorna o ponteiro para o vetor e grava a quantidade em *n.
int *lerArquivo(const char *arquivo, int *n) {
    int qtd = contarValores(arquivo);
    if (qtd <= 0) {
        if (qtd < 0) printf("Arquivo %s nao encontrado. Crie-o primeiro (opcao 1).\n", arquivo);
        else         printf("Arquivo %s esta vazio.\n", arquivo);
        *n = 0;
        return NULL;
    }

    int *v = (int *) malloc(qtd * sizeof(int)); // alocacao dinamica (aula 09)
    if (v == NULL) {
        printf("Erro de alocacao!\n");
        *n = 0;
        return NULL;
    }

    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura.\n", arquivo);
        free(v);
        *n = 0;
        return NULL;
    }
    for (int i = 0; i < qtd; i++) {
        fscanf(fp, "%d", &v[i]);     // le cada valor do arquivo
    }
    fclose(fp);

    *n = qtd;                        // devolve a quantidade por referencia
    return v;
}

// Exibe o conteudo de um arquivo de valores
void exibirArquivo(const char *arquivo) {
    int n;
    int *v = lerArquivo(arquivo, &n);
    if (v == NULL) return;
    printf("\nConteudo de %s (%d valores):\n", arquivo, n);
    mostrarVetor(v, n);
    free(v);
}

/* ============================================================
 *  FUNCIONALIDADES DO PROGRAMA
 * ============================================================ */

// 1) Cria e grava o arquivo dados.txt com valores desordenados
void criarArquivo(void) {
    int n, modo;

    printf("\nQuantos valores deseja gravar? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Quantidade invalida!\n");
        while (getchar() != '\n');   // limpa a entrada
        return;
    }

    int *v = (int *) malloc(n * sizeof(int));
    if (v == NULL) {
        printf("Erro de alocacao!\n");
        return;
    }

    printf("\n1 - Digitar os valores\n");
    printf("2 - Gerar valores aleatorios (0 a 999)\n");
    printf("Escolha: ");
    scanf("%d", &modo);

    switch (modo) {
        case 1:
            for (int i = 0; i < n; i++) {
                printf("Valor %d: ", i + 1);
                scanf("%d", &v[i]);
            }
            break;
        case 2:
            for (int i = 0; i < n; i++) {
                v[i] = rand() % 1000;    // numero aleatorio entre 0 e 999
            }
            break;
        default:
            printf("Opcao invalida!\n");
            free(v);
            return;
    }

    if (gravarArquivo(ARQ_DADOS, v, n)) {
        printf("\nArquivo %s criado com %d valores:\n", ARQ_DADOS, n);
        mostrarVetor(v, n);
    }
    free(v); // libera a memoria alocada
}

// Exibe o menu de algoritmos e retorna a opcao escolhida
int escolherAlgoritmo(void) {
    int opcao;
    printf("\n===== ALGORITMO DE ORDENACAO =====\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Selection Sort\n");
    printf("4 - Merge Sort\n");
    printf("5 - Quick Sort\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    return opcao;
}

// 2, 3 e 4) Le dados.txt, ordena com o algoritmo escolhido e salva em ordenado.txt
void ordenarESalvar(void) {
    int n;
    int *v = lerArquivo(ARQ_DADOS, &n);   // le os dados do arquivo
    if (v == NULL) return;

    printf("\nValores lidos de %s:\n", ARQ_DADOS);
    mostrarVetor(v, n);

    int opcao = escolherAlgoritmo();
    const char *nome;

    clock_t inicio = clock();             // marca o tempo inicial
    switch (opcao) {
        case 1: bubbleSort(v, n);        nome = "Bubble Sort";    break;
        case 2: insertionSort(v, n);     nome = "Insertion Sort"; break;
        case 3: selectionSort(v, n);     nome = "Selection Sort"; break;
        case 4: mergeSort(v, 0, n - 1);  nome = "Merge Sort";     break;
        case 5: quickSort(v, 0, n - 1);  nome = "Quick Sort";     break;
        default:
            printf("Opcao invalida!\n");
            free(v);
            return;
    }
    clock_t fim = clock();                // marca o tempo final

    printf("\nValores ordenados (%s):\n", nome);
    mostrarVetor(v, n);
    printf("Tempo de ordenacao: %.6f segundos\n",
           (double)(fim - inicio) / CLOCKS_PER_SEC);

    if (gravarArquivo(ARQ_ORDENADO, v, n)) {
        printf("Resultado salvo em %s\n", ARQ_ORDENADO);
    }
    free(v);
}

// 5) Altera um valor dentro de dados.txt e permite reordenar
void alterarValor(void) {
    int n, posicao, novoValor;
    int *v = lerArquivo(ARQ_DADOS, &n);
    if (v == NULL) return;

    // Mostra os valores com suas posicoes
    printf("\nValores atuais de %s:\n", ARQ_DADOS);
    for (int i = 0; i < n; i++) {
        printf("[%d] %d\n", i + 1, v[i]);
    }
    free(v);

    printf("\nPosicao do valor a alterar (1 a %d): ", n);
    scanf("%d", &posicao);
    if (posicao < 1 || posicao > n) {
        printf("Posicao invalida!\n");
        return;
    }
    printf("Novo valor: ");
    scanf("%d", &novoValor);

    // Tecnica da aula 08: copia para um arquivo temporario,
    // alterando a linha desejada, e depois substitui o original.
    FILE *origem = fopen(ARQ_DADOS, "r");
    FILE *temp   = fopen(ARQ_TEMP, "w");
    if (origem == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        if (origem) fclose(origem);
        if (temp)   fclose(temp);
        return;
    }

    int valor, linha = 0;
    while (fscanf(origem, "%d", &valor) == 1) {
        linha++;
        if (linha == posicao)
            fprintf(temp, "%d\n", novoValor);  // grava o valor alterado
        else
            fprintf(temp, "%d\n", valor);      // copia o valor original
    }
    fclose(origem);
    fclose(temp);

    remove(ARQ_DADOS);               // apaga o arquivo antigo
    rename(ARQ_TEMP, ARQ_DADOS);     // o temporario passa a ser o dados.txt
    printf("Valor da posicao %d alterado para %d com sucesso!\n", posicao, novoValor);

    // Oferece reordenar novamente
    char resp;
    printf("\nDeseja reordenar os dados agora? (s/n): ");
    scanf(" %c", &resp);
    if (resp == 's' || resp == 'S') {
        ordenarESalvar();
    }
}

/* ============================================================
 *  PROGRAMA PRINCIPAL - menu com switch/case (aula 12)
 * ============================================================ */
int main() {
    int opcao;
    srand((unsigned) time(NULL));   // semente para os numeros aleatorios

    do {
        printf("\n========== ORDENACAO E ARQUIVOS ==========\n");
        printf("1 - Criar arquivo de dados (%s)\n", ARQ_DADOS);
        printf("2 - Exibir dados originais (%s)\n", ARQ_DADOS);
        printf("3 - Ordenar dados e salvar (%s)\n", ARQ_ORDENADO);
        printf("4 - Alterar um valor e reordenar\n");
        printf("5 - Exibir dados ordenados (%s)\n", ARQ_ORDENADO);
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');   // descarta entrada nao numerica
            opcao = -1;
        }

        switch (opcao) {
            case 1: criarArquivo();               break;
            case 2: exibirArquivo(ARQ_DADOS);     break;
            case 3: ordenarESalvar();             break;
            case 4: alterarValor();               break;
            case 5: exibirArquivo(ARQ_ORDENADO);  break;
            case 0: printf("\nEncerrando o programa. Ate logo!\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
