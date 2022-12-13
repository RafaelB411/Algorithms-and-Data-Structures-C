#include <stdio.h>
#include <stdlib.h>

void Mergesort(int* A, int l, int r) {
    if(l<r) {
        int m = (l+r)/2;
        Mergesort(A, l, m);
        Mergesort(A, m+1, r);
        Merge(A, l, r);
    }
}

void Merge(int* A, int l, int r) {
    int *temp = (int*) malloc((r+1) * sizeof(int));
    if(temp==NULL) { printf("Problema na alocacao\n"); exit(-1); }

    for(int i=l; i<r+1; i++) temp[i] = A[i];
    int m = (l+r)/2;
    int i1 = l; 
    int i2 = m+1;

    for(int curr=l; curr<r+1; curr++) {
        if(i1==m+1) { A[curr] = temp[i2]; i2++; }
        else if(i2>r) { A[curr] = temp[i1]; i1++; }
        else if(temp[i1]<=temp[i2]) {
            A[curr] = temp[i1];
            i1++;
        }
        else { A[curr] = temp[i2]; i2++; }
    }

    free(temp);
}