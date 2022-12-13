#include <stdlib.h>
#include <stdio.h>

void bottomUp(int* Harray, int tam) {
    for(int i=tam/2; i>0; i--) {
        int k = i;
        int v = Harray[k];
        int heap = 0;
        while(!heap && 2*k<tam+1) {
            int j = 2*k;
            if(j<tam)
                if(Harray[j] > Harray[j+1])
                j = j+1;
            if(v <= Harray[j])
                heap = 1;
            else {
                Harray[k] = Harray[j];
                k = j;
            }
        }
        Harray[k] = v;
    }
}

int removeElem(int* heap, int *n) {
    int tam = *n;
    if(tam == 0) {
        printf("Heap vazia\n");
        return -1;
    }
    else {
        int temp = heap[1];
        heap[1] = heap[tam];
        heap[tam] = temp;
        tam--; 
        (*n)--;
        if(tam != 0) bottomUp(heap, tam);
        return heap[tam+1];
    }
}