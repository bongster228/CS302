#include <string>
#include <limits>

class undirectedGraph{

public:

    undirectedGraph();                          
    undirectedGraph(int);                       // If vertex count is passed, it must be >= 5. If not then show error. If the
                                                // vertex count is >= 5, setGraphSize() should be called to allocate memory
                                                // and initialize adjacency matrix.
    ~undirectedGraph();

    void setGraphSize(int);                     // Allocate and initialize the adjacency matrix to all 0's. If the current graph
                                                // exists, the destroyGraph() should be called before allocating memory.

    void addEdge(int, int, double);             // Add an edge to the adjacency matrix. Function must ensure the two passed in
                                                // vertexes are valid (>= 0 and < vertexCount) and not equal. If not valid, an error
                                                // should be displayed and nothing changed. 

    bool readGraph(const std::string);          // Read a formatted graph file. The file will include a title, vertex count, and a series
                                                // of lines for the edges. The edge lines will include the from vertex, to vertex, and weight.
                                                // The function must verify that the vertex count is >= 5. If not, display error. If valid
                                                // create a new grpah by calling the setGraphSize() and adding each edge to the adjacency maxtrix
                                                // by calling addEdge(). Return false if file cannot be opened, return true if read is sucessful.

    int getGraphSize() const;                   // Return the current vertex count.

    void printMatrix() const;                   // Print the current adjacency matrix in a formatted manner.

    void prims(int);                            // Implement the Primms algorithm using a priority queue to find a MST for the current graph. If
                                                // a current graph does not exist, display error.

    bool readCityNames(const std::string);      // The first entry in the file will correspond to vertex 0 and so forth. The city names array should
                                                // be cretaed and the city name stored in the array. Only vertexCount number of city names should 
                                                // be read from the file. If there is an error, return false. If the read is successful, return true.

    std::string getTitle() const;
    void setTitle(const std::string);


private:

    int vertexCount;
    std::string title;
    double **graphMatrix;
    double *dist;
    double *pred;
    std::string *cityNames;

    // Used to express infinity values in graphs.
    constexpr static double INF = std::numeric_limits<double>::max();

    void printMST() const;                      // Access the predecessor array (pred), the distances array (dist), and the city names array to display the
                                                // final result. Include the MST by vertex number and then again using the city names. IF the city names are
                                                // not available, only the vertex's should be printed.
    void destroyGraph();

};