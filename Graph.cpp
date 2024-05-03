#include "Graph.hpp"
#include <stdexcept>
#include <cmath>

namespace ariel {

    Graph::Graph() : _numVertices(0), _numEdges(0), _isDirected(false) {}

    void Graph::loadGraph(vector<vector<int>>& matrix) 
    {
        if (matrix.empty()) 
        {
            throw invalid_argument("Invalid graph: The graph matrix is empty");
        }

        (*this)._numVertices = matrix.size();
        (*this)._numEdges = 0;

        for (size_t i = 0; i < matrix.size(); i++) 
        {
            if (matrix[i].size() != (*this)._numVertices) 
            {
                throw invalid_argument("Invalid graph: The graph is not a square matrix");
            }
        }

        _adjacencyMatrix = matrix;
        _isDirected = checkDirected();
        _numEdges = countEdges();
    }

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
    

    size_t Graph::getNumVertices() const 
    {
        return (*this)._numVertices;
    }

    size_t Graph::getNumEdges() const 
    {
        return (*this)._numEdges;
    }

    bool Graph::isGraphDirected() const 
    {
        return (*this)._isDirected;
    }

    vector<vector<int>>& Graph::getAdjacencyMatrix() 
    {
        return (*this)._adjacencyMatrix;
    }

    Graph Graph::operator+() const 
    {
        return *this;
    }

    Graph Graph::operator+(Graph& other) const 
    {
        if ((*this)._numVertices != other._numVertices) 
        {
            throw invalid_argument("Invalid opetaion: Graphs with different sizes cannot be added");
        }
        if ((*this)._adjacencyMatrix.size() != (*this)._adjacencyMatrix[0].size() || 
            other._adjacencyMatrix.size() != other._adjacencyMatrix[0].size()) 
        {
            throw invalid_argument("Invalid operation: one or both graphs are non-square graphs");
        }
    
        Graph result;
        vector<vector<int>> nexMatrix((*this)._numVertices, vector<int>((*this)._numVertices, 0));
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                nexMatrix[i][j] = (*this)._adjacencyMatrix[i][j] + other._adjacencyMatrix[i][j];
            }
        }
        result.loadGraph(nexMatrix);
        return result;
    }


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
        
        return *this;
    }

    Graph Graph::operator-()  
    {
        Graph result;
        vector<vector<int>> newMatrix((*this)._numVertices, vector<int>((*this)._numVertices, 0));
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                newMatrix[i][j] = -1 * (*this)._adjacencyMatrix[i][j];
            }
        }
        result.loadGraph(newMatrix);
        return result;
    }

    Graph Graph::operator-(Graph& other) const 
    {
        if ((*this)._numVertices != other._numVertices) 
        {
            throw invalid_argument("Invalid opetaion: Graphs with different sizes cannot be subtracted");
        }
        if ((*this)._adjacencyMatrix.size() != (*this)._adjacencyMatrix[0].size() || 
            other._adjacencyMatrix.size() != other._adjacencyMatrix[0].size()) 
        {
            throw invalid_argument("Invalid operation: one or both graphs are non-square graphs");
        }

        Graph result;
        vector<vector<int>> nexMatrix((*this)._numVertices, vector<int>((*this)._numVertices, 0));
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < _numVertices; j++) {
                nexMatrix[i][j] = (*this)._adjacencyMatrix[i][j] - other._adjacencyMatrix[i][j];
            }
        }
        result.loadGraph(nexMatrix);
        return result;
    }

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

        _numEdges = countEdges();
        return *this;
    }

    Graph Graph::operator*(Graph& other) const 
    {
        if ((*this)._numVertices != other._numVertices) 
        {
            throw invalid_argument("Invalid operation: Graphs with different sizes cannot be multiplied");
        }
        
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

        result.loadGraph(newMatrix);
        return result;
    }

    Graph& Graph::operator*=(int scalar) 
    {
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                (*this)._adjacencyMatrix[i][j] *= scalar;
            }
        }

        _numEdges = countEdges(); 
        return *this;
    }

    Graph& Graph::operator/=(int scalar) 
    {
        if (scalar == 0) 
        {
            throw invalid_argument("Invalid operation: Division by zero");
        }
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

        _numEdges = countEdges();
        return *this;
    }

    bool Graph::operator==(Graph& other) const 
    {
        if ((*this)._numVertices != other._numVertices) 
        {
            return false;
        }

        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] != other._adjacencyMatrix[i][j]) 
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool Graph::operator!=(Graph& other) const 
    {
        return !(*this == other);
    }

    bool Graph::operator<(Graph& other) const 
    {
        if ((*this)._numVertices < other._numVertices) 
        {
            return true;
        } 
        if ((*this)._numVertices > other._numVertices) 
        {
            return false;
        }

        bool isContained = true;
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] > other._adjacencyMatrix[i][j]) 
                {
                    isContained = false;
                    break;
                }
            }
            if (!isContained) {
                break;
            }
        }

        if (isContained) {
            return true;
        }

        return (*this)._numEdges < other._numEdges;
    }

    bool Graph::operator<=(Graph& other) const 
    {
        return *this < other || *this == other;
    }

    bool Graph::operator>(Graph& other) const 
    {
        if ((*this)._numVertices > other._numVertices) 
        {
            return true;
        } 
        
        if ((*this)._numVertices < other._numVertices) 
        {
            return false;
        }

        bool isContained = true;
        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] < other._adjacencyMatrix[i][j]) 
                {
                    isContained = false;
                    break;
                }
            }
            if (!isContained) 
            {
                break;
            }
        }

        if (isContained) 
        {
            return true;
        }

        if ((*this)._numEdges > other._numEdges) 
        {
            return true;
        } 
        
        if ((*this)._numEdges < other._numEdges) 
        {
            return false;
        }

        for (size_t i = 0; i < (*this)._numVertices; i++) 
        {
            for (size_t j = 0; j < (*this)._numVertices; j++) 
            {
                if ((*this)._adjacencyMatrix[i][j] > other._adjacencyMatrix[i][j]) 
                {
                    return true;
                } 

                if ((*this)._adjacencyMatrix[i][j] < other._adjacencyMatrix[i][j]) 
                {
                    return false;
                }
            }
        }

        return false;
    }

    bool Graph::operator>=(Graph& other) const 
    {
        return *this > other || *this == other;
    }

    Graph& Graph::operator++() 
    {
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

        return *this;
    }

    Graph& Graph::operator--() 
    {
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

        _numEdges = countEdges();
        return *this;
    }

    ostream& operator<<(ostream& output, const Graph& graph) 
    {
        output << graph.printGraph();
        cout << endl;
        return output;
    }

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

    size_t Graph::countEdges() 
    {
        size_t count = 0;
        if ((*this)._isDirected) 
        {
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
}