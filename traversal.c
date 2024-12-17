#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "traversal.h"

void bfsTraversal(const char* startVertex, FILE* file) {
    Queue* queue = createQueue();
    int visited[MAX_VERTICES] = {0}; 
    char visitedVertices[MAX_VERTICES][MAX_NAME] = {0};
    int visitedCount = 0;
    
    enqueue(queue, (char*)startVertex);
    int startIndex = findVertexIndex(startVertex);
    if (startIndex != -1) {
        visited[startIndex] = 1;
        strcpy(visitedVertices[visitedCount++], getVertices()[startIndex].name); 
    }
    
    while (!queueIsEmpty(queue)) {
        int error;
        char* currentVertex = dequeue(queue, &error);
        
        if (!error) {
            int index = findVertexIndex(currentVertex);
            
            if (index != -1) {
                for (int i = 0; i < getVertices()[index].adj_count; i++) {
                    const char* adjacent = getVertices()[index].adjacents[i];
                    int adjIndex = findVertexIndex(adjacent);
                    
                    if (!visited[adjIndex]) {
                        enqueue(queue, (char*)adjacent);
                        visited[adjIndex] = 1;
                        strcpy(visitedVertices[visitedCount++], getVertices()[adjIndex].name);
                    }
                }
            }
            
            free(currentVertex);
        }
    }
    
    for (int i = 0; i < visitedCount; i++) {
        fprintf(file, "%s ", visitedVertices[i]);
    }
    fprintf(file, "\n");
    
    freeQueue(queue);
}

void dfsTraversal(const char* startVertex, FILE* file) {
    Stack* stack = createStack();
    int visited[MAX_VERTICES] = {0};
    char visitedVertices[MAX_VERTICES][MAX_NAME] = {0}; 
    int visitedCount = 0;

    pushStack(stack, (char*)startVertex);
    int startIndex = findVertexIndex(startVertex);
    if (startIndex != -1) {
        visited[startIndex] = 1;
        strcpy(visitedVertices[visitedCount++], getVertices()[startIndex].name); 
    }

    while (!stackIsEmpty(stack)) {
        char* currentVertex = stackTop(stack);
        int currentIndex = findVertexIndex(currentVertex);
        int i = 0; 

        int foundUnvisited = 0;
        while (i < getVertices()[currentIndex].adj_count && !foundUnvisited) {
            const char* adjacent = getVertices()[currentIndex].adjacents[i];
            int adjIndex = findVertexIndex(adjacent);

            if (adjIndex != -1 && !visited[adjIndex]) {
                visited[adjIndex] = 1;
                pushStack(stack, (char*)adjacent);
                strcpy(visitedVertices[visitedCount++], getVertices()[adjIndex].name);
                foundUnvisited = 1;
            }
            i++;
        }

        if (!foundUnvisited) {
            free(popStack(stack)); 
        }
    }

    for (int i = 0; i < visitedCount; i++) {
        fprintf(file, "%s ", visitedVertices[i]);
    }
    fprintf(file, "\n");

    freeStack(stack);
}