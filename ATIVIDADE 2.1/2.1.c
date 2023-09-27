// ITEM 1
int main() {
    float resultado = 3 + 4 * (6 - 7) / 5.0 + 3;
    FILE *arquivo = fopen("resultado.bin", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fwrite(&resultado, sizeof(float), 1, arquivo);
    fclose(arquivo);

    printf("Expressao avaliada e resultado gravado no arquivo 'resultado.bin'.\n");

    return 0;
}


// ITEM 2
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
struct Node {
    char data;
    struct Node* dir;
    struct Node* esq;
};

// Função para criar um novo nó
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->dir = NULL;
    node->esq = NULL;
    return node;
}

// Função para apresentação in-ordem
void inOrder(struct Node* node) {
    if (node == NULL)
        return;

    inOrder(node->esq);
    printf("%c ", node->data);
    inOrder(node->dir);
}

// Função para apresentação pré-ordem
void preOrder(struct Node* node) {
    if (node == NULL)
        return;

    printf("%c ", node->data);
    preOrder(node->esq);
    preOrder(node->dir);
}

// Função para apresentação pós-ordem
void postOrder(struct Node* node) {
    if (node == NULL)
        return;

    postOrder(node->esq);
    postOrder(node->dir);
    printf("%c ", node->data);
}

int main() {
    // Construir a árvore da expressão
    struct Node* root = newNode('+');
    root->esq = newNode('+');
    root->dir = newNode('3');
    root->esq->esq = newNode('3');
    root->esq->dir = newNode('/');
    root->esq->dir->esq = newNode('*');
    root->esq->dir->dir = newNode('3');
    root->esq->esq->esq = newNode('4');
    root->esq->dir->esq->esq = newNode('6');
    root->esq->dir->esq->dir = newNode('7');
    root->esq->dir->dir->esq = newNode('5');

    printf("In-ordem: ");
    inOrder(root);
    printf("\n");

    printf("Pré-ordem: ");
    preOrder(root);
    printf("\n");

    printf("Pós-ordem: ");
    postOrder(root);
    printf("\n");

    return 0;
}

// LER ARQ E CNSTRUIR ARV
#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Função para criar um novo nó
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Função para construir a árvore de expressão a partir da string
struct Node* construirArvore(char expressao[], int *indice) {
    if (expressao[*indice] == '\0' || expressao[*indice] == ')') {
        (*indice)++;
        return NULL;
    }

    struct Node* node = newNode(expressao[*indice]);
    (*indice)++;

    if (expressao[*indice] == '(') {
        (*indice)++;
        node->left = construirArvore(expressao, indice);
        (*indice)++;
    }

    if (expressao[*indice] == '(') {
        (*indice)++;
        node->right = construirArvore(expressao, indice);
        (*indice)++;
    }

    return node;
}

// Função para apresentação in-ordem
void inOrder(struct Node* node) {
    if (node == NULL)
        return;

    inOrder(node->left);
    printf("%c ", node->data);
    inOrder(node->right);
}

int main() {
    // Abrir o arquivo binário para leitura
    FILE *arquivo = fopen("expressao.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Obter o tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    // Ler a expressão do arquivo
    char *expressao = (char *)malloc(tamanho);
    fread(expressao, sizeof(char), tamanho, arquivo);

    fclose(arquivo);

    // Construir a árvore de expressão
    int indice = 0;
    struct Node* root = construirArvore(expressao, &indice);

    printf("Arvore de expressao in-ordem: ");
    inOrder(root);
    printf("\n");

    return 0;
}

