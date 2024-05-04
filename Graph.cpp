// ID: 200661775
// Email: origoldbsc@gmail.com

#include "Graph.hpp"
#include <stdexcept>
#include <cmath>

namespace ariel {

    /**
     * @brief A default constructor for the Graph class.
     */
    Graph::Graph() : _numVertices(0), _numEdges(0), _isDirected(false) {}


    /**
     * @brief This method loads a graph from an adjacency matrix.
     * 
     * @param matrix The adjacency matrix representing the graph.
     * @throws If the matrix is empty or not square throw invalid_argument exception
     */
    void Graph::loadGraph(vector<vector<int>>& matrix) 
    {
        // Matrix with no vertices is invalid graph
        if (matrix.empty()) 
        {
            throw invalid_argument("Invalid graph: The graph matrix is empty");
        }

        (*this)._numVertices = matrix.size();       // A variable to store how many vertices have in the  graph
        (*this)._numEdges = 0;                      // A variable to store how many edges have in the  graph

        // Check if the matrix is square
        for (size_t i = 0; i < matrix.size(); i++) 
        {
            if (matrix[i].size() != (*this)._numVertices) 
            {
                throw invalid_argument("Invalid graph: The graph is not a square matrix");
            }
        }

        (*this)._adjacencyMatrix = matrix;

        // Check if the graph is directed or not
        (*this)._isDirected = checkDirected();

        // Count the number of edges based on graph type
        (*this)._numEdges = countEdges();
    }


    /**
     * @brief This method prints the number of vertices and edges in the graph.
     */
    string Graph::printGraph() const 
    {
        string result;
        for (size_t i = 0; i < (*this)._adjacencyMatrix.size(); i++) 
        {
            if (i != 0) 
            {
                result += "\n";
            }
            result += "[";
            for (size_t j = 0; j < (*this)._adjacencyMatrix[i].size(); j++) 
            {
                result += to_string((*this)._adjacencyMatrix[i][j]);
                if (j < (*this)._adjacencyMatrix[i].size() - 1) 
                {
                    result += ", ";
                }
            }
            result += "]";
        }
        return result;
    }
    

    /**
     * @brief This method returns the number of vertices in the graph.
     * 
     * @return The number of vertices.
     */
    size_t Graph::getNumVertices() const 
    {
        return (*this)._numVertices;
    }

    /**
     * @brief This method returns the number of edges in the graph.
     * 
     * @return The number of edges.
     */
    size_t Graph::getNumEdges() const 
    {
        return (*this)._numEdges;
    }

    /**
     * @brief This method returns if the graph is directed or not.
     * 
     * @return True if the graph is directed, false otherwise.
     */
    bool Graph::isGraphDirected() const 
    {
        return (*this)._isDirected;
    }

    /**
     * @brief This method returns the adjacency matrix of the graph. 
     * 
     * A 2D array represented by vetcor of vectors.
     * @return A reference to the adjacency matrix.
     */
    vector<vector<int>>& Graph::getAdjacencyMatrix() 
    {
        return (*this)._adjacencyMatrix;
    }


    /*********************************************/
    ///            MATH. ORERATIONS             ///
    /*********************************************/

    /**
     * @brief This method preforms an unary plus operator.
     * 
     * @return The current graph.
     */
    Graph& Graph::operator+()  
    {
        return *this;
    }


    /**
     * @brief This method adds two graphs together.
     * 
     * @param other The graph to add to the current graph.
     * @return The resulting graph.
     * @throws if the graphs have different sizes or are not square.
     */
    Graph Graph::operator+(const Graph& other) const 
    {   
        // Check if the two graphs have the same number of vertices
        if ((*this)._numVertices != other._numVertices) 
        {
            throw invalid_argument("Invalid opetaion: Graphs with different sizes cannot be added");
        }

        // Check if the graphs are square matrices
        if ((*this)._adjacencyMatrix.size() != (*this)._adjacencyMatrix[0].size() || 
        other._adjacencyMatrix.size() != other._adjacencyMatrix[0].size()) 
        {
            throw invalid_argument("Invalid operation: one or both graphs are non-square graphs");
        }

        // Create a new matrix to store the result
        Graph result;
        vector<vector<int>> nexMatrix((*this)._numVertices, vector<int>((*this)._numVertices, 0));
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                nexMatrix[i][j] = (*this)._adjacencyMatrix[i][j] + other._adjacencyMatrix[i][j];
            }
        }

        // Load the new matrix and return it
        result.loadGraph(nexMatrix);
        return result;
    }


    /**
     * @brief This method adds a scalar value to all edges of the graph (which are not zero-weighted).
     * 
     * @param scalar The scalar value to add.
     * @return The current graph.
     */
    Graph& Graph::operator+=(int scalar) 
    {
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] != 0) 
                {
                    (*this)._adjacencyMatrix[i][j] += scalar;
                }
            }
        }
        // Update the number of edges
        (*this)._numEdges = countEdges();
        return *this;
    }


    /**
     * @brief This method preforms an unary minus operator.
     *        
     * @return The current graph.
     */
    Graph& Graph::operator-()  
    {
        for (size_t i = 0; i < (*this)._numVertices; i++)
        {
            for (size_t j = 0; j < (*this)._numVertices; j++)
            {
                (*this)._adjacencyMatrix[i][j] = -1 * (*this)._adjacencyMatrix[i][j];
            }
        }
        
        return *this;
    }


    /**
     * @brief This method subtracts one graph from another.
     * 
     * @param other The graph to subtract from the current graph.
     * @return The resulting graph.
     * @throws if the graphs have different sizes or are not square.
     */
    Graph Graph::operator-(const Graph& other) const 
    {   
        // Check if the two graphs have the same number of vertices
        if ((*this)._numVertices != other._numVertices) 
        {
            throw invalid_argument("Invalid opetaion: Graphs with different sizes cannot be subtracted");
        }

        // Check if the graphs are square matrices
        if ((*this)._adjacencyMatrix.size() != (*this)._adjacencyMatrix[0].size() || 
        other._adjacencyMatrix.size() != other._adjacencyMatrix[0].size()) 
        {
            throw invalid_argument("Invalid operation: one or both graphs are non-square graphs");
        }

        // Create a new matrix to store the result
        Graph result;
        vector<vector<int>> nexMatrix((*this)._numVertices, vector<int>((*this)._numVertices, 0));
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < _numVertices; j++) {
                nexMatrix[i][j] = (*this)._adjacencyMatrix[i][j] - other._adjacencyMatrix[i][j];
            }
        }

         // Load the new matrix and return it
        result.loadGraph(nexMatrix);
        return result;
    }


    /**
     * @brief This method subtracts a scalar value from all edges of the graph.
     * 
     * @param scalar The scalar value to subtract.
     * @return The current graph.
     */
    Graph& Graph::operator-=(int scalar) 
    {
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] != 0) 
                {
                    (*this)._adjacencyMatrix[i][j] -= scalar;
                }
            }
        }

        // Update the number of edges
        (*this)._numEdges = countEdges();
        return *this;
    }


    /**
     * @brief This method multiplies two graphs together.
     * 
     * @param other The graph to multiply with the current graph.
     * @return The resulting graph after multiplication.
     * @throws if the graphs have different sizes.
     */
    Graph Graph::operator*(const Graph& other) const 
    {
        // Check if the two graphs have the same number of vertices
        if ((*this)._numVertices != other._numVertices) 
        {
            throw invalid_argument("Invalid operation: Graphs with different sizes cannot be multiplied");
        }
        
        // Create a new matrix to store the result 
        Graph result;
        vector<vector<int>> newMatrix((*this)._numVertices, vector<int>((*this)._numVertices, 0));
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                for (size_t k = 0; k < (*this)._numVertices; k++) 
                {
                    newMatrix[i][j] += (*this)._adjacencyMatrix[i][k] * other._adjacencyMatrix[k][j];
                }
            }
        }

        // Remove self-loops (set diagonal elements to 0)
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            newMatrix[i][i] = 0;
        }

        // Load the new matrix and return it
        result.loadGraph(newMatrix);
        return result;
    }


    /**
     * @brief This method multiplies all edges of the graph by a scalar value.
     * 
     * @param scalar The scalar value to multiply with.
     * @return The current graph.
     */
    Graph& Graph::operator*=(int scalar) 
    {

        // Multiply each edge in the adj. matrix by the scalar
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                (*this)._adjacencyMatrix[i][j] *= scalar;
            }
        }

        // Update the number of edges
        (*this)._numEdges = countEdges(); 
        return *this;
    }


    /**
     * @brief This method divides all edges of the graph by a scalar value.
     * 
     * @param scalar The scalar value to divide by.
     * @return The current graph.
     * @throws if the scalar value is zero.
     */
    Graph& Graph::operator/=(int scalar) 
    {
        // Check if the scalar value is zero
        if (scalar == 0) 
        {
            throw invalid_argument("Invalid operation: Division by zero");
        }

        // Divide each non-zero edge in the adj. matrix by the scalar
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if (_adjacencyMatrix[i][j] != 0) 
                {
                    double result = static_cast<double>((*this)._adjacencyMatrix[i][j]) / scalar;
                    (*this)._adjacencyMatrix[i][j] = static_cast<int>(ceil(result));
                }
            }
        }

        // Update the number of edges
        (*this)._numEdges = countEdges();
        return *this;
    }


    /*********************************************/
    ///            COMP. ORERATIONS             ///
    /*********************************************/


    /**
     * @brief This method checks if two graphs are equal.
     * 
     * @param other The graph to compare with.
     * @return True if the graphs are equal, otherwise false.
     */
    bool Graph::operator==(const Graph& other) const 
    {
        // Check if the two graphs have the same number of vertices
        if ((*this)._numVertices != other._numVertices) 
        {
            return false;
        }

        // Compare the edges
        bool equalEdges = true;
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] != other._adjacencyMatrix[i][j]) {
                    equalEdges = false;
                    break;
                }
            }
            if (!equalEdges) 
            {
                break;
            }
        }

        if (equalEdges) 
        {
            return true;
        }

        // If not equal, check if they are less than or greater than each other
        return !(*this > other) && !(*this < other);
    }


    /**
     * @brief This method checks if two graphs are not equal.
     * 
     * @param other The graph to compare with.
     * @return True if the graphs are not equal, otherwise false.
     */
    bool Graph::operator!=(const Graph& other) const 
    {
        return !(*this == other);
    }


    /**
     * @brief This method checks if the current graph (this) is less than another graph (other).
     * 
     * @param other The graph to compare with.
     * @return True if the current graph is less than the other graph, otherwise false.
     */
    bool Graph::operator<(const Graph& other) const
    {
        // Compare the number of vertices
        if ((*this)._numVertices < other._numVertices)
        {
            // Check if the this graph is a subgraph of the other graph
            return isSubgraph(other) || (*this)._numEdges < other._numEdges;
        }

        // Compare the number of edges
        if ((*this)._numVertices > other._numVertices)
        {
            return false;
        }
        
        // If the number of vertices is equal, compare the number of edges
        return compareEdges(other);
    }


    /**
     * @brief This method checks if the current graph (this) is less than or equal to another graph (other).
     * 
     * @param other The graph to compare with.
     * @return True if the current graph is less than or equal to the other graph, otherwise false.
     */
    bool Graph::operator<=(const Graph& other) const 
    {
        return *this < other || *this == other;
    }


    /**
     * @brief This method checks if the current graph (this) is greater than another graph (other).
     * 
     * @param other The graph to compare with.
     * @return True if the current graph is greater than the other graph, otherwise false.
     */
    bool Graph::operator>(const Graph& other) const 
    {
        return other < *this;
    }


    /**
     * @brief This method checks if the current graph (this) is greater than or equal to another graph (other).
     * 
     * @param other The graph to compare with.
     * @return True if the current graph is greater than or equal to the other graph, otherwise false.
     */
    bool Graph::operator>=(const Graph& other) const 
    {
        return *this > other || *this == other;
    }


    /*********************************************/
    ///            OTHER ORERATIONS             ///
    /*********************************************/


    /**
     * @brief This method increments the weight of each edge by 1 for all non-zero edges.
     * 
     * @return The current graph.
     */
    Graph& Graph::operator++() 
    {   
        // Increment the weight of each non-zero edge
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] != 0) 
                {
                    (*this)._adjacencyMatrix[i][j]++;
                }
            }
        }

        // Update number of edges
        (*this)._numEdges = countEdges();
        return *this;   
    }

    /**
     * @brief This method decrements the weight of each edge by 1 for all non-zero edges.
     * 
     * @return The current graph.
     */
    Graph& Graph::operator--() 
    {
        // Decrement the weight of each non-zero edge
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] != 0) 
                {
                    (*this)._adjacencyMatrix[i][j]--;
                }
            }
        }
        
        // Update number of edges
        (*this)._numEdges = countEdges();
        return *this;
    }


    /**
     * @brief This method is for output stream operator for the graph.
     * 
     * @param output The output stream.
     * @param graph The graph to print.
     * @return The output stream.
     */
    ostream& operator<<(ostream& output, const Graph& graph) 
    {
        output << graph.printGraph();
        cout << endl;
        return output;
    }



    /*********************************************/
    ///             PRIVATE SECTION             ///
    /*********************************************/

    /**
    * @brief This auxiliary function determines if a graph is directed or not.
    * 
    * @return true if the graph is directed, otherwise false.
    */
    bool Graph::checkDirected() 
    {
        for (size_t vertex_v = 0; vertex_v < _numVertices; vertex_v++) 
        {
            for (size_t vertex_u = 0; vertex_u < _numVertices; vertex_u++) 
            {
                if ((*this)._adjacencyMatrix[vertex_v][vertex_u] != (*this)._adjacencyMatrix[vertex_u][vertex_v]) 
                {
                    return true;
                }
            }
        }
        return false;
    }


    /**
    * @brief This auxiliary function counts the number of edges in a graph.
    * 
    * @return number of edges.
    */
    size_t Graph::countEdges() 
    {
        size_t count = 0;
        if ((*this)._isDirected) 
        {
            // Count edges for directed graph
            for (size_t i = 0; i < (*this)._numVertices; i++) 
            {
                for (size_t j = 0; j < (*this)._numVertices; j++) 
                {
                    if ((*this)._adjacencyMatrix[i][j] != 0) 
                    {
                        count++;
                    }
                }
            }
        } 
        else 
        {
            // Count edges for undirected graph
            for (size_t i = 0; i < (*this)._numVertices; i++) 
            {
                for (size_t j = i; j < (*this)._numVertices; j++) 
                {
                    if ((*this)._adjacencyMatrix[i][j] != 0) 
                    {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    /**
     * @brief This auxiliary function checks if the current graph is a subgraph of another graph.
     * 
     * @param other The graph to compare with.
     * @return True if the current graph is a subgraph of the other graph, otherwise false.
     */
    bool Graph::isSubgraph(const Graph& other) const
    {
        for (size_t i = 0; i < (*this)._numVertices; i++)
        {
            for (size_t j = 0; j < (*this)._numVertices; j++)
            {
                if ((*this)._adjacencyMatrix[i][j] != 0 && other._adjacencyMatrix[i][j] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }


    /**
     * @brief This auxiliary function compares the edges of the current graph with another graph.
     * 
     * @param other The graph to compare with.
     * @return True if the current graph has fewer edges or smaller edge values, otherwise false.
     */
    bool Graph::compareEdges(const Graph& other) const
    {
        if ((*this)._numEdges < other._numEdges)
        {
            return true;
        }
        if ((*this)._numEdges > other._numEdges)
        {
            return false;
        }
        for (size_t i = 0; i < (*this)._numVertices; i++)
        {
            for (size_t j = 0; j < (*this)._numVertices; j++)
            {
                // If the number of edges is equal, compare each value in the edge 
                if ((*this)._adjacencyMatrix[i][j] < other._adjacencyMatrix[i][j])
                {
                    return true;
                }
                if ((*this)._adjacencyMatrix[i][j] > other._adjacencyMatrix[i][j])
                {
                    return false;
                }
            }
        }
        return false;
    }
}