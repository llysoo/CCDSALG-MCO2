#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100
#define MAX_NAME 50

typedef struct Vertex {
    char name[MAX_NAME];
    char adjacents[MAX_VERTICES][MAX_NAME];
    int adj_count;
} Vertex;

void initGraph();
void toLowerCase(char* str);
int readGraph(const char* filename);
int findVertexIndex(const char* vertexName);
void displayGraph();
void displayVertexDegree(FILE* file);
int getVertexCount();
const Vertex* getVertices();

#endif // GRAPH_H
