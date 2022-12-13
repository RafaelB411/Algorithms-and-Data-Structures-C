#include <stdio.h>
#include <stdlib.h>

int Partition(int* A, int l, int r) {
    int p = A[l], i = l, j = r+1, swap;

    do{
        do{
            i++;
        } while(A[i]>p && i<r);

        do{
            j--;
        } while(A[j]<p);

        swap = A[i];
        A[i] = A[j];
        A[j] = swap;
    } while(i < j);

    swap = A[i];
    A[i] = A[j];
    A[j] = swap;

    swap = A[l];
    A[l] = A[j];
    A[j] = swap;

    return j;
}

void Quicksort(int* A, int l, int r) {
    if(l<r) {
        int s = Partition(A, l, r);
        Quicksort(A, l, s-1);
        Quicksort(A, s+1, r);
    }
}