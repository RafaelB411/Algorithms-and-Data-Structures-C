#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct Dictionary {
    int hlen;
    int hcnt;
    Llist* table;
    int (*hfunc)(int);
} Dictionary;

Dictionary createDictionary(int size, int (*function)(int)){
    Dictionary dtemp;
    dtemp.hlen = size;
    dtemp.hcnt = 0;
    dtemp.table = (Llist*) malloc(size*sizeof(Llist));
    for(int i=0; i<size; i++)
        dtemp.table[i] = createList();
    dtemp.hfunc = function;
    return dtemp;
}

void clearDictionary(Dictionary *dictionary) {
    for(int i=0; i<dictionary->hlen; i++) {
        clearList(&dictionary->table[i]);
    }
    free(dictionary->table);
}

void insertKey(Dictionary dictionary, int key) {
    if(findElem(dictionary, key)==-1) {
        int pos = dictionary.hfunc(key);
        Llist ltemp = dictionary.table[pos];
        appendElem(&ltemp, key);
    }
}

void removeKey(Dictionary dictionary, int key) {
    int ward = 0;
    if(find(dictionary, key)==-1) printf("Chave nao encontrada\n");
    else {
        int pos = dictionary.hfunc(key);
        Llist ltemp = dictionary.table[pos];
        while(ltemp.curr->next!=NULL && !ward) {
            if(ltemp.curr->next->elem == key) ward = 1;
            ltemp.curr = ltemp.curr->next;
        }
        removeElem(&ltemp);
    }
}

int findElem(Dictionary dictionary, int key) {
    int pos = dictionary.hfunc(key);
    Llist ltemp = dictionary.table[pos];
    while(ltemp.curr->next != NULL) {
        if(ltemp.curr->next->elem == key) return 1;
        ltemp.curr = ltemp.curr->next;
    }
    return -1;
}