#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

Node* createNode(int key) {
    Node* ntemp = (Node*) malloc(1*sizeof(Node));
    if(ntemp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    ntemp->key = key;
    ntemp->left = NULL;
    ntemp->right = NULL;
    ntemp->height = 0;
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

int max(int x, int y) { if(x>y) return x; else return y; }

int height(Node* root) {
    if(root==NULL) return -1;
    else return root->height;
}

int getBalance(Node* root) {
    if(root==NULL) return 0;
    else return height(root->left)-height(root->right);
}

Node* rightRotate(Node* root) {
    Node* left = root->left;
    Node* lright = left->right;
    left->right = root;
    root->left = lright;
    root->height = max(height(root->left), height(root->right)) + 1;
    left->height = max(height(left->left), height(left->right)) + 1;
    return left;
}

Node* leftRotate(Node* root) {
    Node* right = root->right;
    Node* rleft = right->left;
    right->left = root;
    root->right = rleft;
    root->height = max(height(root->left), height(root->right)) + 1;
    right->height = max(height(right->left), height(root->right)) + 1;
    return right;
}

Node* insertHelp(Node* root, int key) {
    if(root == NULL) return createNode(key);
    else if(root->key > key) root->left = insertHelp(root->left, key);
    else root->right = insertHelp(root->right, key);

    root->height = 1 + max(height(root->right), height(root->left));
    int balance = getBalance(root);
    if(balance<-1 && key>=root->right->key) { return leftRotate(root); }
    if(balance>1 && key<root->left->key) { return rightRotate(root); }
    if(balance>1 && key>=root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance<-1 && key<root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

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
