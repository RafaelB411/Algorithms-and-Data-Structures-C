#include <stdio.h>
#include <stdlib.h>

typedef struct Alist {
    int maxSize;
    int listSize;
    int curr;
    int *listArray;
} Alist;

Alist createList() {
    Alist listaTemp; 
    listaTemp.maxSize = 10;
    listaTemp.listSize = 0; 
    listaTemp.curr = 0;
    listaTemp.listArray = (int*) calloc(10, sizeof(int));
    if(listaTemp.listArray == NULL){
        printf("Problema na alocacao\n");
        exit(-1);
    }
    return listaTemp;
}

void clearList(Alist* lista) {
    free(lista->listArray);
    lista->listSize = 0;
    lista->curr = 0;
}

void insertElem(Alist *lista, long long int elem) {
    if(!(lista->listSize < lista->maxSize))
        printf("Capacidade da lista excedida\n");
    else {
        for(int i=lista->listSize; i>lista->curr; i--) lista->listArray[i] = lista->listArray[i-1];
        lista->listArray[lista->curr] = elem;
        lista->listSize++; 
    }
}

void removeElem(Alist *lista) {
    if(!(lista->curr>=0) && !(lista->curr<lista->listSize))
        printf("Nao ha elemento\n");
    else {
        for(int i=lista->curr; i<lista->listSize-1; i++) lista->listArray[i] = lista->listArray[i+1];
        lista->listSize--;
    }
}

int countElem(Alist lista, long long int elem) {
    int count=0;
    for(int i=0; i<lista.listSize; i++) 
        if(lista.listArray[i]==elem) count++;
    return count;
}

void prev(Alist *lista) { if(lista->curr!=0) lista->curr--; }
void next(Alist *lista) { if(lista->curr < lista->listSize) lista->curr++; }