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

typedef struct Queue {
    Link* front;
    Link* rear;
    int size;
} Queue;

Queue createQueue() {
    Queue qtemp;
    qtemp.front = createVoidLink();
    qtemp.rear = qtemp.front;
    qtemp.size = 0;
    return qtemp;
}

void clearQueue(Queue* queue) {
    Link* ltemp;
    if(queue->front->next!=NULL) {
        ltemp = queue->front->next;
        queue->front->next = ltemp->next;
        if(queue->rear==ltemp) queue->rear = queue->front;
        free(ltemp);
    }
    queue->size = 0;
}

void destroy(Queue* queue) {
    clearQueue(queue);
    free(queue->front);
}

void enqueue(Queue* queue, int elem) {
    queue->rear->next = createLink(elem, NULL);
    queue->rear = queue->rear->next;
    queue->size++;
}

int dequeue(Queue* queue) {
    if(queue->size == 0) { printf("Fila vazia\n"); return -1; }
    int value = queue->front->next->elem;
    Link* ltemp = queue->front->next;
    queue->front->next = ltemp->next;
    if(queue->rear==ltemp) queue->rear = queue->front;
    free(ltemp);
    queue->size--;
    return value;
}

int frontValue(Queue queue) {
    if(queue.size==0) { printf("Fila vazia\n"); return -1; }
    else return queue.front->next->elem;
}

int length(Queue queue) { return queue.size; }
