#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_queue.h"
#include "array_stack.h"

typedef struct Edge {
    int vert;
    int wt;
    struct Edge *next;
} Edge;

Edge *createVoidEdge() {
    Edge* linkTmp = NULL;
    linkTmp = (Edge*) malloc(1*sizeof(Edge));
    if(linkTmp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    linkTmp->next = NULL;
    return linkTmp;
}

Edge *createEdge(int vertx, int weight, Edge* nextval) {
    Edge *linkTmp = NULL;
    linkTmp = (Edge*) malloc(1*sizeof(Edge));
    if(linkTmp == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    linkTmp->vert = vertx;
    linkTmp->wt = weight;
    linkTmp->next = nextval;
    return linkTmp;
}

typedef struct List {
    Edge *head;
    Edge *tail;
    Edge *curr;
    int cnt;
} List;

List createList() {
    List listaTmp;
    listaTmp.head = createVoidEdge();
    listaTmp.curr = listaTmp.head;
    listaTmp.tail = listaTmp.head;
    listaTmp.cnt = 0;
    return listaTmp;
}

void clearList(List *lista) {
    while(lista->head!=NULL) {
        lista->curr = lista->head;
        lista->head = lista->head->next;
        free(lista->curr);
    }
}

void addEdge(List* lista, int vertx, int wt) {
    lista->curr->next = createEdge(vertx, wt, lista->curr->next);
    if(lista->tail == lista->curr) lista->tail = lista->curr->next;
    lista->cnt++; 
}

int getVertx(List* lista) {
    if(lista->curr->next == NULL) { printf("No vertex\n"); return -1; }
    else return lista->curr->next->vert;
}

int currPos(List lista) {
    int count=0;
    Edge *ltemp;
    ltemp = lista.head;
    while(ltemp!=lista.curr) {
        ltemp = ltemp->next;
        count++;
    }
    return count;
}

void next(List* lista) {
    if(lista->curr!=lista->tail) lista->curr = lista->curr->next;
}

void removeEdge(List* lista) {
    if(!(lista->curr->next!=NULL)) printf("Nao ha elemento\n");
    else {
        Edge* ltemp = lista->curr->next;
        if(lista->tail == lista->curr->next) lista->tail = lista->curr;
        lista->curr->next = lista->curr->next->next;
        free(ltemp);
        lista->cnt--;
    }
}

typedef struct Graph { 
    bool *mark;
    List *vertex;
    int edge;
    int tam;
} Graph;

Graph createGraph(int tam) {
    Graph gtemp;

    gtemp.edge = 0;
    gtemp.tam = tam;

    gtemp.mark = (bool*) malloc(tam*sizeof(bool));
    if(gtemp.mark==NULL) { printf("Problema na alocaçao\n"); exit(-1); }
    for(int i=0; i<tam; i++) { gtemp.mark[i] = 0; }

    gtemp.vertex = (List*) malloc(tam*sizeof(List));
    if(gtemp.vertex==NULL) { printf("Problema na alocaçao\n"); exit(-1); }
    for(int i=0; i<tam; i++) {
        gtemp.vertex[i] = createList();
    }

    return gtemp;
}

void clearGraph(Graph *g) {
    free(g->mark);
    for(int i=0; i<g->tam; i++) clearList(&g->vertex[i]);
    free(g->vertex);
    g->edge = 0;
    g->tam = 0;
}

int first(Graph g, int v) {
    if(g.vertex[v].cnt==0) { return g.tam; }
    g.vertex[v].curr = g.vertex[v].head;
    int vertx = getVertx(&g.vertex[v]);
    return vertx;
}

bool isEdge(Graph g, int i, int j) {
    int temp;
    for(g.vertex[i].curr=g.vertex[i].head; currPos(g.vertex[i])<g.vertex[i].cnt; next(&g.vertex[i])) {
        temp = getVertx(&g.vertex[i]);
        if(temp==j) return true;
    }
    return false;
}

int nextVertx(Graph g, int v, int prev) {
    int vertx;
    if(isEdge(g, v, prev)) {
        if(currPos(g.vertex[v])+1 < g.vertex[v].cnt) {
            next(&g.vertex[v]);
            vertx = getVertx(&g.vertex[v]);
            return vertx;
        }
    }
    return g.tam;
}

void setEdge(Graph* g, int i, int j, int weight) {
    if(weight==0) printf("error404\n");
    else {
        if(isEdge(*g, i, j)) {
            removeEdge(&(g->vertex[i]));
            addEdge(&g->vertex[i], j, weight);
        }
        else {
            g->edge++;
            addEdge(&g->vertex[i], j, weight);
        }
    }
}

void delEdge(Graph* g, int i, int j) {
    if(isEdge(*g, i, j)) {
        removeEdge(&g->vertex[i]);
        g->edge--;
    }
}

int weight(Graph g, int i, int j) {
    int curr;
    if(isEdge(g, i, j)) {
        curr = g.vertex[i].curr->wt;
        return curr;
    }
    else return 0;
}

void setMark(Graph* g, int vertx, bool value) {
    g->mark[vertx] = value;
}

bool getMark(Graph g, int vertx) {
    return g.mark[vertx];
}

void graphTraverse(Graph g) {
    for(int vertx=0; vertx<g.tam; vertx++) {
        setMark(&g, vertx, 0);
    }
/*    for(int vertx=0; vertx<g.tam; vertx++) {
        if(getMark(g, vertx)==0) traverse(g, vertx);
    } */
}

void BFS(Graph g, int start) {
    Queue q = createQueue();
    enqueue(&q, start);
    setMark(&g, start, 1);
    while(length(q)>0) {
        int vertx = dequeue(&q);
        //preVisit()
        int next = first(g, vertx);
        while(next<g.tam) {
            if(getMark(g, next)==0) {
                setMark(&g, next, 1);
                enqueue(&q, next);
            }
            next = nextVertx(g, vertx, next);
        }
        //posVisit()
    }
    clearQueue(&q);
}

void DFS(Graph g, int start) {
    //preVisit();
    setMark(&g, start, 1);
    int vertx = first(g, start);
    while(vertx<g.tam) {
        if(getMark(g, vertx)==0) DFS(g, vertx);
        vertx = nextVertx(g, start, vertx);
    }
    //posVisit();
}

void toposort(Graph g, int vertx, Stack* s) {
    setMark(&g, vertx, 1);
    int start = first(g, vertx);
    while(start<g.tam) {
        if(getMark(g, start)==0) toposort(g, start, s);
        start = nextVertx(g, vertx, start);
    }
    pushElem(vertx, s);
}
