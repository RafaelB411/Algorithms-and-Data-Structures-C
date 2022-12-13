#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    int cell;
    char key[51];
} Item;

Item createElem(int cvalue, char* kvalue) {
    Item itemp;
    itemp.cell = cvalue;
    strcpy(itemp.key, kvalue);
    return itemp;
}

int getCell(Item elem) { return elem.cell; }
char* getKey(Item elem) { return elem.key; }

typedef struct Dictionary {
    int hlen;
    int hcnt;
    Item* table;
    int (*hfun)(char*);
} Dictionary;

Dictionary createDict(int size, int (*fuction)(char*)) {
    Dictionary dtemp;
    dtemp.hlen = size;
    dtemp.hcnt = 0;
    dtemp.table = (Item*) malloc(size*sizeof(Item));
    if(dtemp.table == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    for(int i=0; i<size; i++) dtemp.table[i].cell = -1;
    dtemp.hfun = fuction;
    return dtemp;
}

void clearDict(Dictionary* dictionary) {
    free(dictionary->table);
    dictionary->hcnt = 0;
}

void insertElem(Dictionary* dictionary, char* key) {
    int cvalue = dictionary->hfun(key);
    int pos = cvalue;
    while(dictionary->table[pos].cell != -1) pos = (pos+1)%dictionary->hlen;
    dictionary->table[pos] = createElem(cvalue, key);
    dictionary->hcnt++;
}

void removeElem(Dictionary* dictionary, char* key) {
    int ward=0;
    for(int i=0; i<dictionary->hlen && !ward; i++) {
        if(strcmp(key, dictionary->table[i].key)==0) {
            dictionary->table[i].cell = -1;
            dictionary->hcnt--;
            ward = 1;
        }
    }
}

int searchElem(Dictionary dictionary, char* key) {
    for(int i=0; i<dictionary.hlen; i++) {
        if(strcmp(key, dictionary.table[i].key)==0)
            return i;
    }
    return -1;
}

int sizeDict(Dictionary dictionary) { return dictionary.hcnt; }