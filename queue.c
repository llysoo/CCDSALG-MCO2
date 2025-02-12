#include <stdlib.h>
#include <string.h>
#include "queue.h"

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->qHead = NULL;
    queue->qTail = NULL;
    return queue;
}

void enqueue(Queue* queue, char* nData) {
    qNode* temp = (qNode*)malloc(sizeof(qNode));
    temp->nData = strdup(nData);
    temp->pNext = NULL;

    if (queue->qTail == NULL) {
        queue->qHead = temp;
        queue->qTail = temp;
    } else {
        queue->qTail->pNext = temp;
        queue->qTail = temp;
    }
}

char* dequeue(Queue* queue, int* error) {
    if (queueIsEmpty(queue)) {
        if (error) *error = 1; // Indicate an error if the queue is empty
        return NULL;
    }
    if (error) *error = 0; // No error

    qNode* temp = queue->qHead;
    char* nData = temp->nData;
    queue->qHead = temp->pNext;

    if (queue->qHead == NULL) {
        queue->qTail = NULL;
    }

    free(temp);
    return nData;
}

int queueIsEmpty(Queue* queue) {
    return queue->qHead == NULL;
}

void freeQueue(Queue* queue) {
    while (!queueIsEmpty(queue)) {
        int error;
        free(dequeue(queue, &error)); // Dequeue all elements to free memory
    }
    free(queue);
}
