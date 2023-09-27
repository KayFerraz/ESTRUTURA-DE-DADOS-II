#include <stdio.h>
#include <stdlib.h>

#define ORDER 4
typedef struct Node {
    int keys[ORDER - 1];
    struct Node* children[ORDER];
    struct Node* next;  
    int num_keys;
    int is_leaf;
} Node;


Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->num_keys = 0;
    newNode->is_leaf = 1;
    newNode->next = NULL;
    return newNode;
}

void printAllKeys(Node* root) {
    if (root == NULL) {
        return;
    }

    Node* current = root;
    while (current != NULL) {
        for (int i = 0; i < current->num_keys; i++) {
            printf("%d ", current->keys[i]);
        }
        current = current->next;
    }
}

int main() {
    Node* root = createNode();
    root->keys[0] = 5;
    root->keys[1] = 10;
    root->num_keys = 2;

    Node* leaf1 = createNode();
    leaf1->keys[0] = 2;
    leaf1->keys[1] = 3;
    leaf1->num_keys = 2;
    leaf1->next = NULL;

    Node* leaf2 = createNode();
    leaf2->keys[0] = 7;
    leaf2->keys[1] = 8;
    leaf2->num_keys = 2;
    leaf2->next = NULL;

    root->children[0] = leaf1;
    root->children[1] = leaf2;

    printf("Chaves da arvore B+: ");
    printAllKeys(root);
    printf("\n");

    free(root);
    free(leaf1);
    free(leaf2);

    return 0;
}
