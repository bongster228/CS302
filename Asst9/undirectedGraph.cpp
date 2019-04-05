#include <iostream>
#include <fstream>
#include <iomanip>
#include "undirectedGraph.h"
#include "priorityQueue.h"
using namespace std;

//----------------------------------------------------------------
// Public Members


undirectedGraph::undirectedGraph(){
    
    vertexCount = 0;
    title = {};
    graphMatrix = nullptr;
    dist = nullptr;
    pred = nullptr;
    cityNames = nullptr;
}

//----------------------------------------------------------------

undirectedGraph::undirectedGraph(int numOfVertex){

    if(numOfVertex <= 5){
        cout << "Invalid vertex count." << endl;
        exit(-1);
    }

    vertexCount = numOfVertex;
    title = {};
    graphMatrix = nullptr;
    dist = nullptr;
    pred = nullptr;
    cityNames = nullptr;

    setGraphSize(vertexCount);
}

//----------------------------------------------------------------

undirectedGraph::~undirectedGraph(){

    for(int i = 0; i < vertexCount; ++i){
        delete[] graphMatrix[i];
    }

    delete[] graphMatrix;
    delete[] dist;
    delete[] pred;
    delete[] cityNames;
}

//----------------------------------------------------------------

string undirectedGraph::getTitle() const{
    return title;
}

//----------------------------------------------------------------

void undirectedGraph::setTitle(const string graphTitle){
    title = graphTitle;
}

//----------------------------------------------------------------

void undirectedGraph::setGraphSize(int numOfVertex){

    // Destroy old graph to prevent memory leak.
    if(graphMatrix != nullptr) destroyGraph();

    vertexCount = numOfVertex;

    // Create and initialize graphMatrix.
    graphMatrix = new double*[vertexCount];

    // Allocate rows and columns and set them all to INF.
    for(int row = 0; row < vertexCount; ++row){
        
        graphMatrix[row] = new double[vertexCount];
            
            for(int column = 0; column < vertexCount; ++column){
                graphMatrix[row][column] = 0;
            } // end for()

    } // end for()

}

//----------------------------------------------------------------

void undirectedGraph::addEdge(int fromVertex, int toVertex, double weight){

// Verify the parameters for validity
if(fromVertex == toVertex){
    cout << "From and to vertices are equal." << endl;
    return;
}

if(fromVertex >= vertexCount || toVertex >= vertexCount){
    cout << "Vertex parameters exceeds vertex count." << endl;
    return;
}

if(fromVertex < 0 || toVertex < 0){
    cout << "Vertex parameters too low." << endl;
    return;
}

// Passed in vertices are valid.
graphMatrix[fromVertex][toVertex] = weight;
graphMatrix[toVertex][fromVertex] = weight;

}

//----------------------------------------------------------------

bool undirectedGraph::readGraph(const string fileName){

    fstream graphFile;
    graphFile.open(fileName);
    
    if(!graphFile.is_open()){
        cout << "File cannot be opened." << endl;
        return false;
    }

    // The first line contains title.
    graphFile >> title;
    setTitle(title);

    // The second line contains vertexCount.
    graphFile >> vertexCount;
    if(vertexCount < 5){
        cout << "Vertex count too low." << endl;
        return false;
    }

    // Create the graph matrix with valid vertex count.
    setGraphSize(vertexCount);

    // Next item contains the # of edges.
    int numOfEdges = 0;
    graphFile >> numOfEdges;

    int from = 0, to = 0;
    double weight = 0.0;

    // Add all the edges to the graphMatrix.
    for(int i = 0; i < numOfEdges; ++i){
        
        graphFile >> from >> to >> weight;
        addEdge(from, to, weight);

    }

    graphFile.close();
    return true;
}

//----------------------------------------------------------------

int undirectedGraph::getGraphSize() const{
    return vertexCount;
}

//----------------------------------------------------------------

void undirectedGraph::printMatrix() const{
    cout << "Graph Adjacency Maxtrix:" << endl;
    cout << "   Title: " << getTitle() << endl << endl;

    string dashes;
    dashes.append(8, '-');
    
    // Output top row with indexs representing vertices.
    cout << setw(5) << "";
    for(int col = 0; col <= 5; col++){
        cout << setw(8) << col;
    }
    cout << endl;
    
    // Outputs dashes
    cout << setw(5) << "";
    for(int col = 0; col <= 5; col++){
        cout << setw(8) << dashes;
    }
    cout << endl;
    
    // Outputs the graphMatrix
    for(int row = 0; row <= 5; ++row){
        
        cout << setw(5) << row << "|";

        for(int column = 0; column <= 5; ++column){
            
            if(row == column) cout << setw(8) << "*";
            else if(graphMatrix[row][column] == 0) cout << setw(8) << "--";
            else cout << setw(8) << graphMatrix[row][column];

        } // end for()

        cout << endl;

    } // end for()
}

//----------------------------------------------------------------

void undirectedGraph::prims(int sourceVertex){

    priorityQueue<double> minWeightHeap;

    pred = new double[vertexCount];
    dist = new double[vertexCount];

    double minValVertex = 0;
    double adjVertex = 0;
    int vertexPriority = 0;

    // Set up heap, predecessor, and distance array.
    for(int i = 0; i < vertexCount; ++i){

        // Source vertex is initialized with 0 priority
        // and 0.
        if(i == sourceVertex){

            minWeightHeap.insert(sourceVertex, 0);
            pred[sourceVertex] = 0;
            dist[sourceVertex] = 0.0;

        } // end if()

        // All other vertices are initialized with INF or -1;
        else {

            minWeightHeap.insert(i, INF);
            pred[i] = -1;
            dist[i] = INF;

        } // end else{}

    } // end for()

    // Create MST using prims algorithm
    while(!minWeightHeap.isEmpty()){

        // Extract min value vertex from heap.
        minWeightHeap.deleteMin(minValVertex, vertexPriority);

        // For every adjacent vertex to minValVertex
        for(int i = 0; i < vertexCount; ++i){

            // Hold column at the min vertex and find all adjacent vertices
            // to the minValVertex.
            if(graphMatrix[i][int(minValVertex)] != 0){
                
                adjVertex = i;
                
                // Change dist, pred, and priority if adjVertex has lower weight edge to 
                // the minValVertex that was dequeued.
                if(minWeightHeap.itemInHeap(adjVertex) && graphMatrix[int(minValVertex)][int(adjVertex)] < dist[int(adjVertex)]){
                    
                    // Set predecessor of adjVertex to minValVertex.
                    pred[int(adjVertex)] = int(minValVertex);


                    // Set weight(distance) of edge between adjVertex and minValVertex to the adjacency value on the graphMatrix
                    // using the two vertices.
                    dist[int(adjVertex)] = graphMatrix[int(minValVertex)][int(adjVertex)];


                    // Change the priority value of the adjVertex in the heap and peform reheapUp to sustain heap structure.
                    minWeightHeap.changePriority(adjVertex, graphMatrix[int(minValVertex)][int(adjVertex)]);

                }

            } // end if()

        } // end for()

    } // end while()

    printMST();

}

//----------------------------------------------------------------

bool undirectedGraph::readCityNames(string fileName){

    // Open and check file.
    fstream cityFile;
    cityFile.open(fileName);
    if(!cityFile.is_open()){
        cout << "City file could not be opened." << endl;
        return false;
    }

    cityNames = new string[vertexCount];

    for(int i = 0; i < vertexCount; ++i){
        cityFile >> cityNames[i];
    }

    cityFile.close();
    return true;
}

//****************************************************************
// Private Members

void undirectedGraph::printMST() const{

    string dashes12;
    string dashes19;
    dashes12.append(12, '-');
    dashes19.append(19, '-');

    cout << endl << "By Vertex's:" << endl;
    cout << dashes12 << endl;

    for(int i = 0; i < vertexCount; ++i){
        cout << i << " - " << pred[i] << "   " << dist[i] << endl;
    }

    cout << endl << "By Elbonian Cities:" << endl;
    cout << dashes19 << endl;

    for(int i = 0; i < vertexCount; ++i){
        cout << cityNames[i] << " - " << cityNames[int(pred[i])] << "   " << dist[i] << endl;
    }

    double totalCost = 0;
    for(int i = 0; i < vertexCount; ++i){
        totalCost += dist[i];
    }

    cout << fixed << setprecision(2) << endl << "Total Cost: " << totalCost << "k" << endl;

}

//----------------------------------------------------------------

void undirectedGraph::destroyGraph(){

    for(int i = 0; i < vertexCount; ++i){
        delete[] graphMatrix[i];
    }

    delete[] graphMatrix;
    delete[] dist;
    delete[] pred;
    delete[] cityNames;

    graphMatrix = nullptr;
    dist = nullptr;
    pred = nullptr;
    cityNames = nullptr;

    vertexCount = 0;
    title = {};

}

//----------------------------------------------------------------