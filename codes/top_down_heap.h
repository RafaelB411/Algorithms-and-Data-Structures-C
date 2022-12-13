#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    char* array;
    int maxsize;
    int n;
} Heap;

Heap createHeap(int tam) {
    Heap htemp;
    htemp.maxsize = tam;
    htemp.n = 0;
    htemp.array = (char*) malloc((tam+1)*sizeof(char));
    if(htemp.array == NULL) { printf("Problema na alocacao\n"); exit(-1); }
    return htemp;
}

void clearHeap(Heap* heap) {
    free(heap->array);
    heap->maxsize = 0;
    heap->n = heap->maxsize;
}

int size(Heap heap) {
    return heap.n;
}

int isLeaf(Heap heap, int pos) {
    if(pos>=heap.n/2 && pos<heap.n) return 1;
    else return 0;
}

int leftChild(int pos) {
    return 2*pos;
}

int rightChild(int pos) {
    return 2*pos+1;
}

int parent(int pos) {
    return pos/2;
}

int prior(int elem1, int elem2) {
    if(elem1>elem2) return 1;
    else return 0;
}

void insertElem(Heap* heap, char elem) {
    if(heap->n>=heap->maxsize) printf("Tamanho maximo atingido!\n");
    else {
        int curr = (heap->n)+1;
        heap->n++;
        heap->array[curr] = elem;
        while(curr!=1 && prior(heap->array[curr], heap->array[parent(curr)])) {
            int temp = heap->array[curr];
            heap->array[curr] = heap->array[parent(curr)];
            heap->array[parent(curr)] = temp;
            curr = parent(curr);
        }
    }
}

void heapify(Heap* heap) {
    for(int i=heap->n/2; i>0; i--) {
        int k = i;
        char v = heap->array[k];
        int ward = 0;
        while(!ward && 2*k<(heap->n)+1) {
            int j = 2*k;
            if(j<heap->n)
                if(heap->array[j] < heap->array[j+1])
                j = j+1;
            if(v >= heap->array[j])
                ward = 1;
            else {
                heap->array[k] = heap->array[j];
                k = j;
            }
        }
        heap->array[k] = v;
    }
}

int removeElem(Heap* heap) {
    int tam = heap->n;
    if(tam == 0) {
        printf("Heap vazia.\n");
        return -1;
    }
    else {
        int temp = heap->array[1];
        heap->array[1] = heap->array[tam];
        heap->array[tam] = temp;
        tam--; 
        heap->n--;
        if(tam != 0) heapify(heap);
        return heap->array[tam+1];
    }
}

void getMax(Heap heap) {
    if(heap.n==0) printf("Nao ha elemento no topo.\n");
    else printf("%c\n", heap.array[1]);
}