#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *left, *right;
} node;

node *alloc(int data, node *left, node *right) {
    node *tmp = (node *)malloc(sizeof(node));
    tmp->data = data;
    tmp->left = left;
    tmp->right = right;
    return tmp;
}

void traverse(node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        traverse(root->left);
        traverse(root->right);
    }
}

void destroy(node *root) {
    if (root != NULL) {
        destroy(root->left);
        destroy(root->right);
        memset(root, 0, sizeof(node));
        free(root);
    }
}

int main() {
    node *root =
        alloc(0,
              alloc(3,
                    alloc(7, NULL, NULL),
                    alloc(4, NULL, NULL)),
              alloc(2,
                    alloc(1, NULL, NULL),
                    alloc(9, NULL, NULL)));

    traverse(root);
    destroy(root);

    return 0;
}
