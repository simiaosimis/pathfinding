#ifndef INCLUDE_DIJKSTRA_H
#define INCLUDE_DIJKSTRA_H

#define INFINITY_VALUE 999
#define NUMBER_OF_TILES 1450
 
class Dijkstra{

    public:

        // A structure to represent a node in adjacency list
        struct AdjListNode
        {
            int dest;
            int weight;
            struct AdjListNode* next;
        };
         
        // A structure to represent an adjacency liat
        struct AdjList
        {
            struct AdjListNode *head;  // pointer to head node of list
        };
         
        // A structure to represent a graph. A graph is an array of adjacency lists.
        // Size of array will be V (number of vertices in graph)
        struct Graph
        {
            int V;
            struct AdjList* array;
        };

        // Structure to represent a min heap node
        struct MinHeapNode
        {
            int  v;
            int dist;
        };
         
        // Structure to represent a min heap
        struct MinHeap
        {
            int size;      // Number of heap nodes present currently
            int capacity;  // Capacity of min heap
            int *pos;     // This is needed for decreaseKey()
            struct MinHeapNode **array;
        };

        bool isGraphCreated;

        Dijkstra();
        struct AdjListNode* newAdjListNode(int dest, int weight);
        struct Graph* createGraph(int V);
        void addEdge(struct Graph* graph, int src, int dest, int weight);
        struct MinHeapNode* newMinHeapNode(int v, int dist);
        struct MinHeap* createMinHeap(int capacity);
        void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
        void minHeapify(struct MinHeap* minHeap, int idx);
        int isEmpty(struct MinHeap* minHeap);
        struct MinHeapNode* extractMin(struct MinHeap* minHeap);
        void decreaseKey(struct MinHeap* minHeap, int v, int dist);
        bool isInMinHeap(struct MinHeap *minHeap, int v);
        void printArr(int dist[], int n);
        void makeDijkstra(struct Graph* graph, int src);
        void printPath(int node, int source);
};

#endif //INCLUDE_DIJKSTRA_H