#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_CITIES 10

/***********************************/
/*     USER DEFINED DATATYPES      */
/***********************************/

// Define a structure for an adjacency list node
typedef struct Node {
    int destination;
    int weight;
    struct Node* next;
} Node;

// Define a structure for the graph
typedef struct Graph {
    int cityCount;
    Node* adjList[MAX_CITIES]; // Array of adjacency lists
} Graph;

// Define a structure for the priority queue (min-heap)
typedef struct PriorityQueue {
    int vertices[MAX_CITIES];
    int dist[MAX_CITIES];
    int size;
} PriorityQueue;

// Function to create a new adjacency list node
Node* createNode(int dest, int weight);

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight);

// Function to initialize the priority queue
void initPriorityQueue(PriorityQueue* pq, int cityCount);

// Function to swap two elements in the priority queue
void swap(PriorityQueue* pq, int i, int j);

// Function to heapify the priority queue
void heapify(PriorityQueue* pq, int i);

// Function to extract the minimum distance vertex from the priority queue
int extractMin(PriorityQueue* pq);

// Function to decrease the key (update the distance) of a vertex in the priority queue
void decreaseKey(PriorityQueue* pq, int vertex, int newDist);

// Function to reconstruct the shortest path
void reconstructPath(int prev[], int start, int end);




/***********************************/
/*            YOUR TASK            */
/***********************************/

// find the shortest path
void shortestPath(Graph* graph, int start, int end, int dist[], int prev[]) {
    PriorityQueue pq;
    // To do code logic here
    initPriorityQueue(&pq, graph->cityCount);
    dist[start] = 0; // set the distance of the source city to 0
    decreaseKey(&pq, start, 0); // update start city in priority queue
    
    // process all vertices
    while (pq.size > 0) {
        // extract city with minimum distance
        int current = extractMin(&pq);
        
        // if we reached a city with infinite distance, no more reachable cities
        if (dist[current] == INT_MAX) {
            break;
        }
        
        // explore all neighbors of current city
        Node* neighbor = graph->adjList[current];
        while (neighbor != NULL) {
            int nextCity = neighbor->destination;
            int weight = neighbor->weight;
            
            // calculate new distance to neighbor through current city
            int newDist = dist[current] + weight;
            
            // if we found a shorter path, update it
            if (newDist < dist[nextCity]) {
                dist[nextCity] = newDist;
                prev[nextCity] = current;
                decreaseKey(&pq, nextCity, newDist);
            }
            
            neighbor = neighbor->next;
        }
    }
}

int main() {
    Graph graph;
    printf("Enter the number of cities: ");
    scanf("%d", &graph.cityCount);

    // Initialize adjacency list
    for (int i = 0; i < graph.cityCount; i++) {
        graph.adjList[i] = NULL;
    }

    int edgeCount;
    printf("Enter the number of edges: ");
    scanf("%d", &edgeCount);

    printf("Enter the edges (source destination weight) for %d edges:\n", edgeCount);
    for (int i = 0; i < edgeCount; i++) {
        int src, dest, weight;
        printf("Enter edge %d (source destination weight): ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
    }

    int start, end;
    printf("Enter the source city (0 to %d): ", graph.cityCount - 1);
    scanf("%d", &start);

    printf("Enter the destination city (0 to %d): ", graph.cityCount - 1);
    scanf("%d", &end);

    int dist[MAX_CITIES], prev[MAX_CITIES];
    for (int i = 0; i < graph.cityCount; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    shortestPath(&graph, start, end, dist, prev);

    if (dist[end] == INT_MAX) {
        printf("There is no path from city %d to city %d\n", start, end);
    } else {
        printf("The shortest distance from city %d to city %d is %d\n", start, end, dist[end]);
        reconstructPath(prev, start, end);
    }

    return 0;
}




/*********************************************************************************************/
/*     IF YOU WANT TO EXPERIENCE WHAT THE PREVIOUS BATCH EXPERIENCED, DON'T SCROLL DOWN      */
/*********************************************************************************************/



















































































/******************************************************************************************************/
/*     IF YOU WANT TO EXPERIENCE WHAT THE PREVIOUS BATCH EXPERIENCED, DON'T READ THESE FUNCTIONS      */
/******************************************************************************************************/

// Function to create a new adjacency list node
Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->destination = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the graph (undirected)
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // If undirected, also add reverse edge
    newNode = createNode(src, weight);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Function to initialize the priority queue
void initPriorityQueue(PriorityQueue* pq, int cityCount) {
    pq->size = cityCount;
    for (int i = 0; i < cityCount; i++) {
        pq->vertices[i] = i;
        pq->dist[i] = INT_MAX;
    }
}

// Function to swap two elements in the priority queue
void swap(PriorityQueue* pq, int i, int j) {
    int tempV = pq->vertices[i];
    int tempD = pq->dist[i];
    pq->vertices[i] = pq->vertices[j];
    pq->dist[i] = pq->dist[j];
    pq->vertices[j] = tempV;
    pq->dist[j] = tempD;
}

// Function to heapify the priority queue (min-heap)
void heapify(PriorityQueue* pq, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->dist[left] < pq->dist[smallest])
        smallest = left;

    if (right < pq->size && pq->dist[right] < pq->dist[smallest])
        smallest = right;

    if (smallest != i) {
        swap(pq, i, smallest);
        heapify(pq, smallest);
    }
}

// Function to extract the minimum distance vertex
int extractMin(PriorityQueue* pq) {
    if (pq->size == 0)
        return -1;

    int minVertex = pq->vertices[0];
    swap(pq, 0, pq->size - 1);
    pq->size--;
    heapify(pq, 0);

    return minVertex;
}

// Function to decrease the key (update distance) of a vertex
void decreaseKey(PriorityQueue* pq, int vertex, int newDist) {
    int i;
    for (i = 0; i < pq->size; i++) {
        if (pq->vertices[i] == vertex) {
            pq->dist[i] = newDist;
            break;
        }
    }

    // Bubble up
    while (i > 0 && pq->dist[(i - 1) / 2] > pq->dist[i]) {
        swap(pq, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// Function to reconstruct and print the shortest path
void reconstructPath(int prev[], int start, int end) {
    if (end == start) {
        printf("The path is: %d ", start);
        return;
    }

    if (prev[end] == -1) {
        printf("No path");
        return;
    }

    reconstructPath(prev, start, prev[end]);
    printf("%d ", end);
}