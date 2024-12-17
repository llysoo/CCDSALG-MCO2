#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include "traversal.h"

// Function to pause the program and wait for the user to press Enter
void pauseProgram() {
    printf("Press Enter to exit...");
    getchar(); // Consume the newline character left in the input buffer by scanf
    getchar(); // Wait for the user to press Enter
}

int main() {
    char filename[MAX_NAME];
    char startVertex[MAX_NAME];
    int validFile = 0;
    int validVertex = 0;

    printf("Input filename: ");
    scanf("%s", filename);

    // Check if the file exists and is readable
    FILE* checkFile = fopen(filename, "r");
    if (checkFile) {
        fclose(checkFile);
        validFile = 1;
    } else {
        printf("%s not found.\n", filename);
        pauseProgram(); // Wait for user input before exiting
        return 1;
    }

    if (validFile) {
        initGraph();
        if (readGraph(filename) != 0) {
            printf("Error reading graph from %s.\n", filename);
            pauseProgram(); // Wait for user input before exiting
            return 1;
        }

        printf("Input start vertex for the traversal: ");
        scanf("%s", startVertex);

        int startIndex = findVertexIndex(startVertex);
        if (startIndex != -1) {
            validVertex = 1;
        } else {
            printf("Vertex %s not found.\n", startVertex);
            pauseProgram(); // Wait for user input before exiting
            return 1;
        }

        if (validVertex) {
            FILE* file = fopen("TRAVERSAL.TXT", "w");
            if (file) {
                displayVertexDegree(file);
                fprintf(file, "\n");

                fprintf(file, "BFS: ");
                bfsTraversal(startVertex, file);
                fprintf(file, "\n");
                
                fprintf(file, "DFS: ");
                dfsTraversal(startVertex, file);
                fprintf(file, "\n");

                fclose(file);
                printf("Vertex %s found and traversals have been written to TRAVERSAL.TXT.\n", startVertex);
            } else {
                printf("Error opening file TRAVERSAL.TXT for writing.\n");
                pauseProgram(); // Wait for user input before exiting
                return 1;
            }
        }
    }

    pauseProgram(); // Wait for user input before exiting
    return 0;
}
