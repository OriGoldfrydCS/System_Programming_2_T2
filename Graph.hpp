#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace ariel {

    class Graph {
    private:
        vector<vector<int>> _adjacencyMatrix;
        size_t _numVertices;
        size_t _numEdges;
        bool _isDirected;

        bool checkDirected();
        size_t countEdges();

    public:
        Graph();

        void loadGraph(vector<vector<int>>& matrix);
        string printGraph() const;
        size_t getNumVertices() const;
        size_t getNumEdges() const;
        bool isGraphDirected() const;
        vector<vector<int>>& getAdjacencyMatrix();

        Graph operator+() const;
        Graph operator+(Graph& other) const;
        Graph& operator+=(int scalar);
        Graph operator-();
        Graph operator-(Graph& other) const;
        Graph& operator-=(int scalar);
        Graph operator*(Graph& other) const;
        Graph& operator*=(int scalar);
        Graph& operator/=(int scalar);
        bool operator==(Graph& other) const;
        bool operator!=(Graph& other) const;
        bool operator<(Graph& other) const;
        bool operator<=(Graph& other) const;
        bool operator>(Graph& other) const;
        bool operator>=(Graph& other) const;
        Graph& operator++();
        Graph& operator--();

        friend ostream& operator<<(ostream& output, const Graph& graph);
        
        };

}

#endif 