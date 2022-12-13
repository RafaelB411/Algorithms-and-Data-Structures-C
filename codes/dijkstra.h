#include <stdio.h>
#include <stdlib.h>
#include "graph_matrix.h"

typedef struct Tupla {
    int head;
    int end;
    int weight;
} Tupla;

typedef struct Heap {
    Tupla* array;
    int maxsize;
    int n;
} Heap;

Heap createHeap(int tam) {
    Heap htemp;
    htemp.maxsize = tam;
    htemp.n = 0;
    htemp.array = (Tupla*) malloc((tam+1)*sizeof(Tupla));
    if(htemp.array == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    return htemp;
}

void clearHeap(Heap* heap) {
    free(heap->array);
    heap->maxsize = 0;
    heap->n = heap->maxsize;
}

int parent(int pos) {
    return pos/2;
}

int prior(Tupla elem1, Tupla elem2) {
    if(elem1.weight>elem2.weight) return 1;
    else return 0;
}

void heapify(Heap* heap) {
    for(int i=heap->n/2; i>0; i--) {
        int k = i;
        Tupla v = heap->array[k];
        int ward = 0;
        while(!ward && 2*k<(heap->n)+1) {
            int j = 2*k;
            if(j<heap->n)
                if(heap->array[j].weight > heap->array[j+1].weight)
                j = j+1;
            if(v.weight <= heap->array[j].weight)
                ward = 1;
            else {
                heap->array[k] = heap->array[j];
                k = j;
            }
        }
        heap->array[k] = v;
    }
}

void insertElem(Heap* heap, Tupla elem) {
    if(heap->n>=heap->maxsize) printf("Tamanho maximo atingido!\n");
    else {
        int curr = (heap->n)+1;
        heap->n++;
        heap->array[curr] = elem;
        heapify(heap);
    }
}

Tupla removeElem(Heap* heap) {
    int tam = heap->n;
    Tupla temp = heap->array[1];
    heap->array[1] = heap->array[tam];
    heap->array[tam] = temp;
    tam--; 
    heap->n--;
    if(tam != 0) heapify(heap);
    return heap->array[tam+1];
}

void dijkstra(Graph* g, int start, int* distance, int* parents) {
    int p, vertx, succ;
    Tupla t;
    Heap h;
    h = createHeap(g->tam);
    
    for(int i=0; i<g->tam; i++) {
        distance[i] = 1000;
        parents[i] = -1;
        setMark(g, i, false);
    }

    t.head = t.end = start;
    t.weight = 0;

    insertElem(&h, t);
    distance[start] = 0;

    for(int i=0; i<g->tam; i++) {
        do {
            if(h.n!=0) {
                Tupla temp = removeElem(&h);
                p = temp.head;
                vertx = temp.end;
            }
        } while(getMark(*g, vertx));

        setMark(g, vertx, true);
        parents[vertx] = p;
        succ = first(*g, vertx);

        while(succ<g->tam) {
            if(!getMark(*g, succ) && distance[succ] > distance[vertx]+weight(*g, vertx, succ)) {
                distance[succ] = distance[vertx]+weight(*g, vertx, succ);
                t.head = vertx; t.end = succ;
                t.weight = distance[succ];
                insertElem(&h, t);
            }
            succ = nextVertx(*g, vertx, succ);
        }
    }

    clearHeap(&h);
}