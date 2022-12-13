#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_queue.h"
#include "array_stack.h"

typedef struct Graph {
    bool *mark;
    int **matrix;
    int edge;
    int tam;
} Graph;

Graph createGraph(int tam) {
    Graph gtemp;

    gtemp.mark = (bool*) malloc(tam*sizeof(bool));
    if(gtemp.mark==NULL) { printf("Problema na alocaçao\n"); exit(-1); }

    gtemp.matrix = (int**) malloc(tam*sizeof(int*));
    if(gtemp.matrix==NULL) { free(gtemp.mark); printf("Problema na alocaçao\n"); exit(-1); }
    for(int i=0; i<tam; i++) {
        gtemp.matrix[i] = (int*) malloc(tam*sizeof(int));
        if(gtemp.matrix[i]==NULL) { free(gtemp.mark); free(gtemp.matrix); printf("Problema na alocaçao\n"); exit(-1); }
    }

    gtemp.edge = 0;
    gtemp.tam = tam;

    return gtemp;
}

void clearGraph(Graph *g) {
    free(g->mark);
    for(int i=0; i<g->tam; i++) free(g->matrix[i]);
    free(g->matrix);
    g->edge = 0;
    g->tam = 0;
}

int first(Graph g, int vertex) {
    for(int i=0; i<g.tam; i++) {
        if(g.matrix[vertex][i]!=0) return i;
    }
    return g.tam;
}

int nextVertx(Graph g, int start, int vertx) {
    for(int i=vertx+1; i<g.tam; i++) {
        if(g.matrix[start][i]!=0) return i;
    }
    return g.tam;
}

void setEdge(Graph* g, int i, int j, int weight) {
    if(weight==0) printf("error404\n");
    if(g->matrix[i][j]==0) g->edge++;
    g->matrix[i][j] = weight;
    g->matrix[j][i] = weight;
}

void delEdge(Graph* g, int i, int j) {
    if(g->matrix[i][j]!=0) g->edge--;
    g->matrix[i][j] = 0;
}

bool isEdge(Graph g, int i, int j) {
    if(g.matrix[i][j]==0) return false;
    else return true;
}

int weight(Graph g, int i, int j) {
    if(g.matrix[i][j]==0) return -1;
    else return g.matrix[i][j];
}

void setMark(Graph* g, int vertx, bool value) {
    g->mark[vertx] = value;
}

int getMark(Graph g, int vertx) {
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
        printf("%d ", vertx);
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
    printf("%d ", start);
    setMark(&g, start, 1);
    int vertx = first(g, start);
    while(vertx<g.tam) {
        if(getMark(g, vertx)==0) DFS(g, vertx);
        vertx = nextVertx(g, start, vertx);
    }
    //posVisit();
}

void toposort(Graph g, int vertx, Stack s) {
    setMark(&g, vertx, 1);
    int start = first(g, vertx);
    while(start<g.tam) {
        if(getMark(g, start)==0) toposort(g, start, s);
        start = nextVertx(g, vertx, start);
    }
    pushElem(vertx, &s);
}
