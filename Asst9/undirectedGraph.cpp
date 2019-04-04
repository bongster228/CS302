#include <iostream>
#include <fstream>
#include <iomanip>
#include "undirectedGraph.h"
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

}

//----------------------------------------------------------------

void undirectedGraph::setGraphSize(int numOfVertex){

    // Destroy old graph to prevent memory leak.
    if(graphMatrix != nullptr) destroyGraph();

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
    cout << "From and to vertexes are equal." << endl;
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
    for(int col = 0; col < 5; col++){
        cout << setw(8) << col;
    }
    cout << endl;
    
    // Outputs dashes
    cout << setw(5) << "";
    for(int col = 0; col < 5; col++){
        cout << setw(8) << dashes;
    }
    cout << endl;
    
    // Outputs the graphMatrix
    for(int row = 0; row < 5; ++row){
        
        cout << setw(5) << row << "|";

        for(int column = 0; column < 5; ++column){
            
            if(row == column) cout << setw(8) << "*";
            else if(graphMatrix[row][column] == 0) cout << setw(8) << "--";
            else cout << setw(8) << graphMatrix[row][column];

        } // end for()

        cout << endl;

    } // end for()
}