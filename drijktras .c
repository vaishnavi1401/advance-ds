/*
NAME:VAISHNAVI AGGARWAL
ROLL NUMBER: 54
PHONE NUMBER:7078322286
EMAIL:Vaishnaviaggarwal1401@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct node {
    int vertex, weight;
    struct node * next;
}node;

// Each element of the priority queue (min heap)
// is a pair of vertex and a value (its distance)
typedef struct vertex
{
	int vertex, dist;
}vertex;

node * addEdge(node * head, int vertex, int weight)
{
    node * newNode = (node *) calloc(1, sizeof(node));

    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = head;

    return newNode;
}

void heapify(vertex minHeap[], int size, int i, int pos[])//  heapify procedure
{
	vertex temp;

    while ((2 * i) <= size) {
        if ((2 * i) + 1 > size) {
			if (minHeap[i].dist > minHeap[2 * i].dist) {
				pos[minHeap[i].vertex] = 2 * i;
				pos[minHeap[2 * i].vertex] = i;

                temp = minHeap[i];
                minHeap[i] = minHeap[2 * i];
                minHeap[2 * i] = temp;
            }

            break;
        }

        if (minHeap[i].dist > minHeap[2 * i].dist || minHeap[i].dist > minHeap[2 * i + 1].dist) {
            if (minHeap[2 * i].dist <= minHeap[(2 * i) + 1].dist) {
                pos[minHeap[i].vertex] = 2 * i;
				pos[minHeap[2 * i].vertex] = i;

                temp = minHeap[2 * i];
                minHeap[2 * i] = minHeap[i];
                minHeap[i] = temp;

                i = 2 * i;
            } else if (minHeap[2 * i].dist > minHeap[(2 * i) + 1].dist) {
                pos[minHeap[i].vertex] = 2 * i + 1;
				pos[minHeap[2 * i + 1].vertex] = i;

                temp = minHeap[(2 * i) + 1];
                minHeap[(2 * i) + 1] = minHeap[i];
                minHeap[i] = temp;

                i = (2 * i) + 1;
            }
        } else {
            break;
        }
    }
}

// Build Heap Procedure
void buildHeap(vertex minHeap[], int size, int pos[])
{
    int i;

    for (i = size / 2; i >= 1; --i) {
        heapify(minHeap, size, i, pos);
    }
}

// Searches for a node in the Heap and decreases its value
void decreaseKey(vertex minHeap[], vertex newNode, int pos[])
{
	minHeap[pos[newNode.vertex]].dist = newNode.dist;

	int i = pos[newNode.vertex];
	vertex temp;

    while (i > 1) {
        if (minHeap[i / 2].dist > minHeap[i].dist) {
            pos[minHeap[i].vertex] = i / 2;
			pos[minHeap[i / 2].vertex] = i;

            temp = minHeap[i / 2];
            minHeap[i / 2] = minHeap[i];
            minHeap[i] = temp;

            i = i / 2;
        } else {
            break;
        }
    }
}

// Removes and Returns the topmost element
vertex extractMin(vertex minHeap[], int size, int pos[])
{
	pos[minHeap[1].vertex] = size;
	pos[minHeap[size].vertex] = 1;

	vertex min = minHeap[1];

	minHeap[1] = minHeap[size];
	--size;
	heapify(minHeap, size, 1, pos);

	return min;
}

// Dijkstra's Algorithm function
void dijkstra(node * adjacencyList[], int vertices, int startVertex, int distances[], int parent[])
{
    int i;
    vertex minVertex;
    vertex priorityQueue[vertices + 1]; 	// To use the array as 1-indexed
    int pos[vertices + 1];	// Stores the position (index) of vertex

    // Initially no routes to vertices are know, so all are infinity
    for (i = 1; i <= vertices; ++i) {
        distances[i] = INT_MAX;
        parent[i] = 0;
        priorityQueue[i].dist = INT_MAX;
        priorityQueue[i].vertex = i;
		pos[i] = priorityQueue[i].vertex;
    }

    // Setting distance to source to zero
    distances[startVertex] = 0;
    priorityQueue[startVertex].dist = 0;
    buildHeap(priorityQueue, vertices, pos);

    for (i = 1; i <= vertices; ++i) {     // Untill there are vertices to be processed
		minVertex = extractMin(priorityQueue, vertices, pos);

		node * trav = adjacencyList[minVertex.vertex];    // Checking all the vertices adjacent to 'min'

        while (trav != NULL) {
        	int u = minVertex.vertex;
        	int v = trav->vertex;
        	int w = trav->weight;

            if (distances[u] != INT_MAX && distances[v] > distances[u] + w) {

                distances[v] = distances[u] + w;
                parent[v] = u;

                // Making changes to the priority queue
                vertex changedVertex;

                changedVertex.vertex = v;
                changedVertex.dist = distances[v];	// new distance
                decreaseKey(priorityQueue, changedVertex, pos);
            }

            trav = trav->next;
        }
    }
}

// Recursively looks at a vertex's parent to print the path
void printPath(int parent[], int vertex, int startVertex)
{
    if (vertex == startVertex) {	// reached the source vertex
        printf("%d ", startVertex);
        return;
    } else if (parent[vertex] == 0) {	// current vertex has no parent
    	printf("%d ", vertex);
    	return;
	} else {	// go for the current vertex's parent
        printPath(parent, parent[vertex], startVertex);
        printf("%d ", vertex);
    }
}

int main()
{
    int vertices, edges, i, j, v1, v2, w, startVertex;

    printf("Enter the Number of Vertices -\n");
    scanf("%d", &vertices);
    printf("Enter the Number of Edges -\n");
    scanf("%d", &edges);

    node * adjacencyList[vertices + 1];	// to use the array as 1-indexed for simplicity
    int distances[vertices + 1];
    int parent[vertices + 1];

    for (i = 0; i <= vertices; ++i) {	// Must initialize your array
        adjacencyList[i] = NULL;
    }
printf("enter source destination and weight \n");
    for (i = 1; i <= edges; ++i) {
        scanf("%d%d%d", &v1, &v2, &w);
        adjacencyList[v1] = addEdge(adjacencyList[v1], v2, w);
        adjacencyList[v2] = addEdge(adjacencyList[v2], v1, w);
    }

    printf("Enter start vertex -\n");
    scanf("%d", &startVertex);
    dijkstra(adjacencyList, vertices, startVertex, distances, parent);
	printf("Shortest distances -\n");

    for (i = 1; i <= vertices; ++i) {
    	printf("Vertex %d, Distance = %d, Parent = %d, ", i, distances[i], parent[i]);
    	printf("Path = ");
    	printPath(parent, i, startVertex);
    	printf("\n");
	}

    return 0;
}
