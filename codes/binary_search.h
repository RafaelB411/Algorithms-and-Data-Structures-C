#include <stdio.h>
#include <stdlib.h>

int Search(int* array, int key, int tam) {
    int l = 0, r = tam-1;
    while(l <= r) {
        int m = (l + r)/2;
        if(key == array[m]) return m;
        else if(key < array[m]) r = m-1;
        else l = m+1;
    }
    return -1;
}