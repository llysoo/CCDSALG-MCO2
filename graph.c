#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"

static Vertex vertices[MAX_VERTICES];
static int vertex_count = 0;

void initGraph() {
    vertex_count = 0;
}

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int readGraph(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("%s not found.\n", filename);
        return -1;
    }

    if (fscanf(file, "%d", &vertex_count) != 1) {
        fclose(file);
        printf("Error reading vertex count from %s.\n", filename);
        return -1;
    }

    for (int i = 0; i < vertex_count; i++) {
        char name[MAX_NAME];
        if (fscanf(file, "%s", name) != 1) {
            fclose(file);
            printf("Error reading vertex name from %s.\n", filename);
            return -1;
        }
        strcpy(vertices[i].name, name);
        vertices[i].adj_count = 0;

        char adjacent[MAX_NAME];
        while (fscanf(file, "%s", adjacent) == 1 && strcmp(adjacent, "-1") != 0) {
            if (vertices[i].adj_count >= MAX_VERTICES) {
                fclose(file);
                printf("Error: too many adjacents for vertex %s.\n", name);
                return -1;
            }
            strcpy(vertices[i].adjacents[vertices[i].adj_count], adjacent);
            vertices[i].adj_count++;
        }
    }

    fclose(file);
    return 0;
}

int findVertexIndex(const char* vertexName) {
    char tempName[MAX_NAME];
    strcpy(tempName, vertexName);
    toLowerCase(tempName);

    for (int i = 0; i < vertex_count; i++) {
        char tempVertex[MAX_NAME];
        strcpy(tempVertex, vertices[i].name);
        toLowerCase(tempVertex);
        if (strcmp(tempVertex, tempName) == 0) {
            return i;
        }
    }
    return -1;
}

void displayGraph() {
    for (int i = 0; i < vertex_count; i++) {
        printf("%s: ", vertices[i].name);
        for (int j = 0; j < vertices[i].adj_count; j++) {
            printf("%s ", vertices[i].adjacents[j]);
        }
        printf("\n");
    }
}

void displayVertexDegree(FILE* file) {
    for (int i = 0; i < vertex_count; i++) {
        fprintf(file, "%s\t%d\n", vertices[i].name, vertices[i].adj_count);
    }
}

int getVertexCount() {
    return vertex_count;
}

const Vertex* getVertices() {
    return vertices;
}
