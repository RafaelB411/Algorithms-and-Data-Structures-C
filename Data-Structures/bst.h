#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) {
    Node* ntemp = (Node*) malloc(1*sizeof(Node));
    if(ntemp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    ntemp->key = key;
    ntemp->left = NULL;
    ntemp->right = NULL;
    return ntemp;
}

typedef struct BSTree {
    Node* root;
    int cnt;
} BSTree;

BSTree createTree() {
    BSTree ttemp;
    ttemp.root = NULL;
    ttemp.cnt = 0;
    return ttemp;
}

void clearHelp(Node* root) {
    if(root==NULL) return;
    clearHelp(root->left);
    clearHelp(root->right);
    free(root);
}

void clearTree(BSTree *tree) {
    clearHelp(tree->root);
}

Node* insertHelp(Node* root, int key) {
    if(root == NULL) return createNode(key);
    else if(root->key > key) root->left = insertHelp(root->left, key);
    else if(root->key <= key) root->right = insertHelp(root->right, key);
    return root;
}

void insertElem(BSTree* tree, int key) {
    tree->root = insertHelp(tree->root, key);
    tree->cnt++;
}

Node* getMin(Node* root) {
    if(root->left == NULL) return root;
    return getMin(root->left);
}

Node* deleteMin(Node* root) {
    if(root->left == NULL) return root->right;
    root->left = deleteMin(root->left);
    return root;
}

Node* removeHelp(Node* root, int key) {
    if(root == NULL) return NULL;
    if(root->key > key) root->left = removeHelp(root->left, key);
    else if(root->key < key) root->right = removeHelp(root->right, key);
    else {
        if(root->left == NULL) return root->right;
        else if(root->right == NULL) return root->left;
        else {
            Node* temp = (Node*) malloc(1*sizeof(Node));
            if(temp == NULL) printf("Problema na alocacao\n");
            else {
                temp = getMin(root->right);
                root->key = temp->key;
                root->right = deleteMin(root->right);
            }
        }
    }
    return root;
}

void removeElem(BSTree tree, int key) {
    int temp = findHelp(tree.root, key);
    if(temp != -1) {
        tree.root = removeHelp(tree.root, key);
        tree.cnt--;
    }
}

int findHelp(Node* root, int key) {
    if(root == NULL) return -1;
    else if(root->key > key) return findHelp(root->left, key);
    else if(root->key == key) return root->key;
    else return findHelp(root->right, key);
}

int findElem(BSTree tree, int key) {
    return findHelp(tree.root, key);
}

void preorder(Node* root) {
    if(root!=NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node* root) {
    if(root!=NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void postorder(Node* root) {
    if(root!=NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}
