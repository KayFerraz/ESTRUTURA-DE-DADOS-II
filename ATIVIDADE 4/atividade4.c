
#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3 // Defina a ordem da árvore B aqui

// Estrutura de um nó da árvore B
typedef struct Node {
    int chaves[2 * ORDEM - 1];
    struct Node* filhos[2 * ORDEM];
    int chavesCount;
    int isLeaf;
} Node;

// Função para criar um novo nó
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->chavesCount = 0;
    newNode->isLeaf = 1;
    for (int i = 0; i < 2 * ORDEM; i++) {
        newNode->chaves[i] = 0;
        newNode->filhos[i] = NULL;
    }
    return newNode;
}

// Função para buscar uma chave na árvore B
int search(Node* root, int chave) {
    if (root == NULL) {
        return 0;
    }

    int i = 0;
    while (i < root->chavesCount && chave > root->chaves[i]) {
        i++;
    }

    if (i < root->chavesCount && chave == root->chaves[i]) {
        return 1; // Chave encontrada
    }

    if (root->isLeaf) {
        return 0; // Chave não encontrada
    }

    return search(root->filhos[i], chave); // Recursivamente, busca no filho apropriado
}

// Função para inserir uma chave na árvore B
void insert(Node** root, int chave) {
    if (*root == NULL) {
        *root = createNode();
    }

    Node* r = *root;

    if (r->chavesCount == 2 * ORDEM - 1) {
        Node* newNode = createNode();
        newNode->isLeaf = 0;
        newNode->filhos[0] = r;
        *root = newNode;
        splitChild(newNode, 0);
        insertNonFull(newNode, chave);
    } else {
        insertNonFull(r, chave);
    }
}

// Função auxiliar para dividir um nó filho cheio durante a inserção
void splitChild(Node* parent, int i) {
    Node* child = parent->filhos[i];
    Node* newChild = createNode();
    parent->chavesCount++;

    for (int j = ORDEM - 1; j < 2 * ORDEM - 1; j++) {
        newChild->chaves[j - ORDEM + 1] = child->chaves[j];
        child->chaves[j] = 0;
    }

    for (int j = ORDEM; j < 2 * ORDEM; j++) {
        newChild->filhos[j - ORDEM] = child->filhos[j];
        child->filhos[j] = NULL;
    }

    child->chavesCount = ORDEM - 1;
    newChild->chavesCount = ORDEM - 1;

    for (int j = parent->chavesCount; j > i; j--) {
        parent->filhos[j + 1] = parent->filhos[j];
    }

    parent->filhos[i + 1] = newChild;

    for (int j = parent->chavesCount - 1; j >= i; j--) {
        parent->chaves[j + 1] = parent->chaves[j];
    }

    parent->chaves[i] = child->chaves[ORDEM - 1];
}

// Função auxiliar para inserir em um nó não cheio
void insertNonFull(Node* node, int chave) {
    int i = node->chavesCount - 1;

    if (node->isLeaf) {
        while (i >= 0 && chave < node->chaves[i]) {
            node->chaves[i + 1] = node->chaves[i];
            i--;
        }

        node->chaves[i + 1] = chave;
        node->chavesCount++;
    } else {
        while (i >= 0 && chave < node->chaves[i]) {
            i--;
        }

        i++;

        if (node->filhos[i]->chavesCount == 2 * ORDEM - 1) {
            splitChild(node, i);

            if (chave > node->chaves[i]) {
                i++;
            }
        }

        insertNonFull(node->filhos[i], chave);
    }
}

// Função para imprimir a árvore B em ordem
void printInOrder(Node* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->chavesCount; i++) {
            printInOrder(root->filhos[i]);
            printf("%d ", root->chaves[i]);
        }
        printInOrder(root->filhos[i]);
    }
}

// Função para imprimir a árvore B em pré-ordem
void printPreOrder(Node* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->chavesCount; i++) {
            printf("%d ", root->chaves[i]);
            printPreOrder(root->filhos[i]);
        }
        printPreOrder(root->filhos[i]);
    }
}

// Função para encontrar o nó mínimo de uma subárvore
Node* findMin(Node* node) {
    while (!node->isLeaf) {
        node = node->filhos[0];
    }
    return node;
}

// Função para remover uma chave da árvore B
void removeKey(Node** root, int chave) {
    if (*root == NULL) {
        return;
    }

    removeKeyFromNode(*root, chave);

    if ((*root)->chavesCount == 0) {
        Node* tmp = *root;
        if ((*root)->isLeaf) {
            *root = NULL;
        } else {
            *root = (*root)->filhos[0];
        }
        free(tmp);
    }
}

// Função auxiliar para remover uma chave de um nó
void removeKeyFromNode(Node* node, int chave) {
    int i = 0;
    while (i < node->chavesCount && chave > node->chaves[i]) {
        i++;
    }

    if (i < node->chavesCount && chave == node->chaves[i]) {
        if (node->isLeaf) {
            for (int j = i; j < node->chavesCount - 1; j++) {
                node->chaves[j] = node->chaves[j + 1];
            }
            node->chavesCount--;
        } else {
            Node* pred = findMin(node->filhos[i + 1]);
            node->chaves[i] = pred->chaves[0];
            removeKeyFromNode(node->filhos[i + 1], pred->chaves[0]);
        }
    } else {
        if (node->isLeaf) {
            return;
        }

        if (node->filhos[i]->chavesCount < ORDEM) {
            fill(node, i);
        }

        if (i == node->chavesCount) {
            i++;
        }

        removeKeyFromNode(node->filhos[i], chave);
    }
}

// Função auxiliar para preencher um filho que tem menos chaves
void fill(Node* node, int i) {
    if (i != 0 && node->filhos[i - 1]->chavesCount >= ORDEM) {
        borrowFromPrev(node, i);
    } else if (i != node->chavesCount && node->filhos[i + 1]->chavesCount >= ORDEM) {
        borrowFromNext(node, i);
    } else {
        if (i != node->chavesCount) {
            merge(node, i);
        } else {
            merge(node, i - 1);
        }
    }
}

// Função auxiliar para pegar uma chave do filho anterior
void borrowFromPrev(Node* node, int i) {
    Node* child = node->filhos[i];
    Node* sibling = node->filhos[i - 1];

    for (int j = child->chavesCount - 1; j >= 0; j--) {
        child->chaves[j + 1] = child->chaves[j];
    }

    if (!child->isLeaf) {
        for (int j = child->chavesCount; j >= 0; j--) {
            child->filhos[j + 1] = child->filhos[j];
        }
    }

    child->chaves[0] = node->chaves[i - 1];

    if (!child->isLeaf) {
        child->filhos[0] = sibling->filhos[sibling->chavesCount];
    }

    node->chaves[i - 1] = sibling->chaves[sibling->chavesCount - 1];

    child->chavesCount++;
    sibling->chavesCount--;
}

// Função auxiliar para pegar uma chave do filho seguinte
void borrowFromNext(Node* node, int i) {
    Node* child = node->filhos[i];
    Node* sibling = node->filhos[i + 1];

    child->chaves[child->chavesCount] = node->chaves[i];

    if (!child->isLeaf) {
        child->filhos[child->chavesCount + 1] = sibling->filhos[0];
    }

    node->chaves[i] = sibling->chaves[0];

    for (int j = 1; j < sibling->chavesCount; j++) {
        sibling->chaves[j - 1] = sibling->chaves[j];
    }

    if (!sibling->isLeaf) {
        for (int j = 1; j <= sibling->chavesCount; j++) {
            sibling->filhos[j - 1] = sibling->filhos[j];
        }
    }

    child->chavesCount++;
    sibling->chavesCount--;
}

// Função auxiliar para mesclar um nó com seu filho i
void merge(Node* node, int i) {
    Node* child = node->filhos[i];
    Node* sibling = node->filhos[i + 1];

    child->chaves[child->chavesCount] = node->chaves[i];

    for (int j = 0; j < sibling->chavesCount; j++) {
        child->chaves[child->chavesCount + 1 + j] = sibling->chaves[j];
    }

    if (!child->isLeaf) {
        for (int j = 0; j <= sibling->chavesCount; j++) {
            child->filhos[child->chavesCount + 1 + j] = sibling->filhos[j];
        }
    }

    for (int j = i + 1; j < node->chavesCount; j++) {
        node->chaves[j - 1] = node->chaves[j];
    }

    for (int j = i + 2; j <= node->chavesCount; j++) {
        node->filhos[j - 1] = node->filhos[j];
    }

    child->chavesCount += sibling->chavesCount + 1;
    node->chavesCount--;

    free(sibling);
}

int main() {
    Node* root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);

    printf("Árvore B em ordem:\n");
    printInOrder(root);
    printf("\n");

    printf("Árvore B em pré-ordem:\n");
    printPreOrder(root);
    printf("\n");

    int chave = 12;
    if (search(root, chave)) {
        printf("A chave %d foi encontrada na árvore.\n", chave);
    } else {
        printf("A chave %d não foi encontrada na árvore.\n", chave);
    }

    printf("Removendo a chave %d da árvore:\n", chave);
    removeKey(&root, chave);
    printInOrder(root);
    printf("\n");

    return 0;
}
