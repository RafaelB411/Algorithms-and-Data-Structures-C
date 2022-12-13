#include <stdio.h>
#include <stdlib.h>

typedef struct Link {
    int elem;
    struct Link *next;
} Link;

Link *createVoidLink() {
    Link* linkTmp = NULL;
    linkTmp = (Link*) malloc(1*sizeof(Link));
    if(linkTmp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    linkTmp->next = NULL;
    return linkTmp;
}

Link *createLink(int elemval, Link* nextval) {
    Link *linkTmp = NULL;
    linkTmp = (Link*) malloc(1*sizeof(Link));
    if(linkTmp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    linkTmp->elem = elemval;
    linkTmp->next = nextval;
    return linkTmp;
}

typedef struct Llist {
    Link *head;
    Link *tail;
    Link *curr;
    int cnt;
} Llist;

Llist createList() {
    Llist listaTmp;
    listaTmp.head = createVoidLink();
    listaTmp.curr = listaTmp.head;
    listaTmp.tail = listaTmp.head;
    listaTmp.cnt = 0;
    return listaTmp;
}

void clearList(Llist *lista) {
    while(lista->head!=NULL) {
        lista->curr = lista->head;
        lista->head = lista->head->next;
        free(lista->curr);
    }
}

void insertElem(Llist* lista, int elem) {
    lista->curr->next = createLink(elem, lista->curr->next);
    if(lista->tail == lista->curr) lista->tail = lista->curr->next;
    lista->cnt++; 
}

void appendElem(Llist* lista, int elem) {
    while(lista->tail->next!=NULL) lista->tail = lista->tail->next;
    lista->tail->next = createLink(elem, lista->tail->next);
    lista->tail = lista->tail->next;
    lista->cnt++;
}

void removeElem(Llist* lista) {
    if(!(lista->curr->next!=NULL)) printf("Nao ha elemento\n");
    else {
        Link* ltemp = lista->curr->next;
        if(lista->tail == lista->curr->next) lista->tail = lista->curr;
        lista->curr->next = lista->curr->next->next;
        free(ltemp);
        lista->cnt--;
    }
}

int countElem(Llist lista, int elem) {
    int count=0;
    Link *ltemp;
    ltemp = lista.head;
    for(int i=0; ltemp!=lista.tail; i++) {
        if(ltemp->next->elem == elem) count++;
        ltemp = ltemp->next;
    }
    return count;
}

void prev(Llist* lista) {
    if(lista->curr == lista->head) printf("Não há elemento anterior\n");
    else {
        Link* temp = lista->head;
        while(temp->next!=lista->curr) temp = temp->next;
        lista->curr = temp;
    }
}

void next(Llist* lista) {
    if(lista->curr!=lista->tail) lista->curr = lista->curr->next;
}

int length(Llist* lista) { return lista->cnt; }

int getValue(Llist* lista) {
    if(lista->curr->next == NULL) { printf("No value\n"); return -1; }
    else return lista->curr->next->elem;
}