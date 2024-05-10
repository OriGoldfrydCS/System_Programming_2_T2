// Email: origoldbsc@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace ariel {

/**
* @This class represents a graph by using an adjacency matrix.
*/
class Graph 
{

    // Private attributes and functions
    private:
        vector<vector<int>> _adjacencyMatrix;   // A variable that stores the adjacency matrix that representing a graph
        size_t _numVertices;                    // A variable that stores the number of vertices in the graph
        size_t _numEdges;                       // A variable that stores the  number of edges in the graph
        bool _isDirected;                       // A flag that indicates if the graph is directed or undirected


        /**
        * @brief This auxiliary function determines if a graph is directed or not.
        * @return true if the graph is directed, otherwise false.
        */
        bool checkDirected();


        /**
        * @brief This auxiliary function counts the number of edges in a graph.
        * @return number of edges.
        */
        size_t countEdges();


        /**
         * @brief This auxiliary function checks if the current graph is a subgraph of another graph.
         * 
         * @param other The graph to compare with.
         * @return True if the current graph is a subgraph of the other graph, otherwise false.
         */
        bool isSubgraph(const Graph& other) const;


        /**
         * @brief This auxiliary function compares the edges of the current graph with another graph.
         * 
         * @param other The graph to compare with.
         * @return True if the current graph has fewer edges or smaller edge values, otherwise false.
         */
        bool compareEdges(const Graph& other) const;

    // Public methods 
    public:

        /**
         * @brief A default constructor for the Graph class.
         */
        Graph();


        /**
         * @brief This method loads a graph from an adjacency matrix.
         * @param matrix The adjacency matrix representing the graph.
         * @throws If the matrix is empty or not square throw invalid_argument exception
         */
        void loadGraph(vector<vector<int>>& matrix);


        /**
         * @brief This method prints the number of vertices and edges in the graph.
         */
        string printGraph() const;


        /**
         * @brief This method returns the number of vertices in the graph.
         * @return The number of vertices.
         */
        size_t getNumVertices() const;


        /**
         * @brief This method returns the number of edges in the graph.
         * @return The number of edges.
         */
        size_t getNumEdges() const;


        /**
         * @brief This method returns if the graph is directed or not.
         * @return True if the graph is directed, false otherwise.
         */
        bool isGraphDirected() const;


        /**
         * @brief This method returns the adjacency matrix of the graph. 
         * A 2D array represented by vetcor of vectors.
         * @return A reference to the adjacency matrix.
         */
        vector<vector<int>>& getAdjacencyMatrix();


        /**
         * @brief This method preforms an unary plus operator.
         * @return The current graph.
         */
        Graph& operator+();


        /**
         * @brief This method adds two graphs together.
         * @param other The graph to add to the current graph.
         * @return The resulting graph.
         * @throws if the graphs have different sizes or are not square.
         */
        Graph operator+(const Graph& other) const;


        /**
         * @brief This method adds a scalar value to all edges of the graph (which are not zero-weighted).
         * @param scalar The scalar value to add.
         * @return The current graph.
         */
        Graph& operator+=(int scalar);


        /**
         * @brief This method preforms an unary minus operator.     
         * @return The current graph.
         */
        Graph& operator-();


        /**
         * @brief This method subtracts one graph from another.
         * @param other The graph to subtract from the current graph.
         * @return The resulting graph.
         * @throws if the graphs have different sizes or are not square.
         */
        Graph operator-(const Graph& other) const;


        /**
         * @brief This method subtracts a scalar value from all edges of the graph.
         * @param scalar The scalar value to subtract.
         * @return The current graph.
         */
        Graph& operator-=(int scalar);


        /**
         * @brief This method multiplies two graphs together.
         * @param other The graph to multiply with the current graph.
         * @return The resulting graph after multiplication.
         * @throws if the graphs have different sizes.
         */
        Graph operator*(const Graph& other) const;


        /**
         * @brief This method multiplies all edges of the graph by a scalar value.
         * @param scalar The scalar value to multiply with.
         * @return The current graph.
         */
        Graph& operator*=(int scalar);


        /**
         * @brief This method divides all edges of the graph by a scalar value.
         * @param scalar The scalar value to divide by.
         * @return The current graph.
         * @throws if the scalar value is zero.
         */
        Graph& operator/=(int scalar);


        /**
         * @brief This method checks if two graphs are equal.
         * @param other The graph to compare with.
         * @return True if the graphs are equal, otherwise false.
         */
        bool operator==(const Graph& other) const;


        /**
         * @brief This method checks if two graphs are not equal.
         * @param other The graph to compare with.
         * @return True if the graphs are not equal, otherwise false.
         */
        bool operator!=(const Graph& other) const;


        /**
         * @brief This method checks if the current graph (this) is less than another graph (other).
         * @param other The graph to compare with.
         * @return True if the current graph is less than the other graph, otherwise false.
         */
        bool operator<(const Graph& other) const;


        /**
         * @brief This method checks if the current graph (this) is less than or equal to another graph (other).
         * @param other The graph to compare with.
         * @return True if the current graph is less than or equal to the other graph, otherwise false.
         */
        bool operator<=(const Graph& other) const;


        /**
         * @brief This method checks if the current graph (this) is greater than another graph (other).
         * @param other The graph to compare with.
         * @return True if the current graph is greater than the other graph, otherwise false.
         */
        bool operator>(const Graph& other) const;


        /**
         * @brief This method checks if the current graph (this) is greater than or equal to another graph (other).
         * @param other The graph to compare with.
         * @return True if the current graph is greater than or equal to the other graph, otherwise false.
         */
        bool operator>=(const Graph& other) const;


        /**
         * @brief This method increments the weight of each edge by 1 for all non-zero edges.
         * @return The current graph.
         */
        Graph& operator++();

        /**
         * @brief This method increments (postpix operator) the weight of each edge by 1 for all non-zero edges..
         * 
         * @return The graph before the operation.
         */
        Graph operator++(int); 

        /**
         * @brief This method decrements the weight of each edge by 1 for all non-zero edges.
         * @return The current graph.
         */
        Graph& operator--();


        /**
         * @brief This method decrements (postfix operator) the weight of each edge by 1 for all non-zero edges.
         * 
         * @return The graph before the operation.
         */
        Graph operator--(int); 

        /**
         * @brief This method is for output stream operator for the graph.
         * @param output The output stream.
         * @param graph The graph to print.
         * @return The output stream.
         */
        friend ostream& operator<<(ostream& output, const Graph& graph);
    };

}

#endif