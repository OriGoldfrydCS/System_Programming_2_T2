// ID: 200661775
// Email: origoldbsc@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <sstream>

using namespace ariel;
using namespace std;

// Initiate an empty instances of graph to be used in the following tests
Graph g1;        
Graph g2;        
Graph g3;        

// Test case for unary + operator with undirected graph
TEST_CASE("Operation +: Unary + on undirected graph") {
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    g2 = +g1;
    CHECK(g2.printGraph() == "[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");

    // Additional checks for Algorithms functions
    CHECK(Algorithms::isConnected(g2) == true);
    CHECK(Algorithms::isStronglyConnected(g2) == true);
    CHECK(Algorithms::shortestPath(g2, 0, 2) == "0->2");
    CHECK(Algorithms::isContainsCycle(g2) != "0");
    CHECK(Algorithms::isBipartite(g2) == "The graph is not bipartite");
    CHECK(Algorithms::negativeCycle(g2) == "No negative cycle exists");
}


// Test Case for +
TEST_CASE("Operation +: Add two graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, -2, 1},
        {2, 0, -11},
        {1, -13, 0}};
    g2.loadGraph(graph2);

    g3 = g1 + g2;
    CHECK(g3.printGraph() == "[0, -1, 1]\n[3, 0, -9]\n[1, -11, 0]");

    // Additional checks for Algorithms functions
    CHECK(Algorithms::isConnected(g3) == true);
    CHECK(Algorithms::isStronglyConnected(g3) == true);
    CHECK(Algorithms::shortestPath(g3, 0, 2) == "Graph contains a negative cycle");
    CHECK(((Algorithms::isContainsCycle(g3) == "0->1->0") || (Algorithms::isContainsCycle(g3) == "1->2->1") 
    || (Algorithms::isContainsCycle(g3) == "0->1->2->1"))); 
    CHECK(Algorithms::isBipartite(g3) == "The graph is not bipartite");
    CHECK(((Algorithms::negativeCycle(g3) == "0->1->0") || (Algorithms::negativeCycle(g3) == "1->2->1")));
}


TEST_CASE("Operation +: Add two larger graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 0, 2, 0},
        {1, 0, 3, 0, 1},
        {0, 3, 0, 1, 2},
        {2, 0, 1, 0, 0},
        {0, 1, 2, 0, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 2, 1, 0, 3},
        {2, 0, 0, 1, 0},
        {1, 0, 0, 2, 1},
        {0, 1, 2, 0, 0},
        {3, 0, 1, 0, 0}};
    g2.loadGraph(graph2);

    g3 = g1 + g2;
    CHECK(g3.printGraph() == "[0, 3, 1, 2, 3]\n[3, 0, 3, 1, 1]\n[1, 3, 0, 3, 3]\n[2, 1, 3, 0, 0]\n[3, 1, 3, 0, 0]");

    // Additional checks for Algorithms functions
    CHECK(Algorithms::isConnected(g3) == true);
    CHECK(Algorithms::isStronglyConnected(g3) == true);
    CHECK(Algorithms::shortestPath(g3, 0, 4) == "0->4");
    CHECK(Algorithms::isContainsCycle(g3) == "0->1->2->0");
    CHECK(Algorithms::isBipartite(g3) == "The graph is not bipartite");
    CHECK(Algorithms::negativeCycle(g3) == "No negative cycle exists");
}

TEST_CASE("Operation +: Add graphs of different sizes") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 2, 1, 0},
        {2, 0, 1, 3},
        {1, 1, 0, 2},
        {0, 3, 2, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 + g2);
}

TEST_CASE("Operation +: Add graphs with different sizes") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 0, 2},
        {1, 0, 2, 0},
        {0, 2, 0, 1},
        {2, 0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 + g2);
}

// Test case for unary - operator with directed graph
TEST_CASE("Operation -: Unary - on directed graph") {
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {0, 0, 3},
        {0, 0, 0}};
    g1.loadGraph(graph1);

    g2 = -g1;
    CHECK(g2.printGraph() == "[0, -1, -2]\n[0, 0, -3]\n[0, 0, 0]");

    // Additional checks for Algorithms functions
    CHECK(Algorithms::isConnected(g2) == true);
    CHECK(Algorithms::isStronglyConnected(g2) == false);
    CHECK(Algorithms::shortestPath(g2, 0, 2) == "0->1->2");
    CHECK(Algorithms::isContainsCycle(g2) == "0");
    CHECK(Algorithms::isBipartite(g2) == "The graph is not bipartite");
    CHECK(Algorithms::negativeCycle(g2) == "No negative cycle exists");
}


// Test Case for -
TEST_CASE("Operation -: Subtract two graphs") 
{
    vector<vector<int>> graph1 = {
        {1, 2, 0},
        {2, 1, 3},
        {0, 3, 1}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 2, 1},
        {2, 0, 1},
        {1, 1, 0}};
    g2.loadGraph(graph2);

    g3 = g1 - g2;
    CHECK(g3.printGraph() == "[1, 0, -1]\n[0, 1, 2]\n[-1, 2, 1]");

    // Additional checks for Algorithms functions
    CHECK(Algorithms::isConnected(g3) == true);
    CHECK(Algorithms::isStronglyConnected(g3) == true);
    CHECK(Algorithms::shortestPath(g3, 0, 2) == "0->2");
    CHECK(((Algorithms::isContainsCycle(g3) == "0->0") || (Algorithms::isContainsCycle(g3) == "1->1") || (Algorithms::isContainsCycle(g3) == "2->2")));
    CHECK(Algorithms::isBipartite(g3) == "The graph is not bipartite");
    CHECK(Algorithms::negativeCycle(g3) == "No negative cycle exists");
}

TEST_CASE("Operation -: Subtract graphs with different sizes") 
{
    vector<vector<int>> graph1 = {
        {1, 2, 0},
        {2, 1, 3},
        {0, 3, 1}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 2, 1, 0},
        {2, 0, 1, 3},
        {1, 1, 0, 2},
        {0, 3, 2, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 - g2);
}

TEST_CASE("Operation -: Subtract graphs with different sizes") 
{
    vector<vector<int>> graph1 = {
        {1, 2, 0, -4},
        {2, 1, 3, -1},
        {0, 3, 1, 4},
        {1, 1, 1, 1}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 2, 1},
        {2, 0, 1},
        {1, 1, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 - g2);
}

// Test Case for *
TEST_CASE("Operation *: Multiply two graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g2.loadGraph(graph2);

    g3 = g1 * g2;

    CHECK(g3.printGraph() == "[0, 0, 2, 0]\n[0, 0, 0, 2]\n[2, 0, 0, 0]\n[0, 2, 0, 0]");
    
    CHECK(Algorithms::isConnected(g3) == false);
    CHECK(Algorithms::isStronglyConnected(g3) == false);
    CHECK(Algorithms::shortestPath(g3, 0, 2) == "0->2");
    CHECK(Algorithms::isContainsCycle(g3) == "0");
    CHECK(Algorithms::isBipartite(g3) == "The graph is bipartite: A={0,1}, B={2,3}");
    CHECK(Algorithms::negativeCycle(g3) == "No negative cycle exists");


}

TEST_CASE("Operation *: Multiply two larger graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 0, 2},
        {1, 0, 3, 0},
        {0, 3, 0, 1},
        {2, 0, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 2, 1, 0},
        {2, 0, 0, 1},
        {1, 0, 0, 2},
        {0, 1, 2, 0}};
    g2.loadGraph(graph2);

    g3 = g1 * g2;
    CHECK(g3.printGraph() == "[0, 2, 4, 1]\n[3, 0, 1, 6]\n[6, 1, 0, 3]\n[1, 4, 2, 0]");
}

TEST_CASE("Operation *: Multiply graphs of different sizes") 
{
    vector<vector<int>> graph1 = {
        {0, -1, 0},
        {-1, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, -1, 2},
        {1, 0, 1, 0},
        {-1, 1, 0, 3},
        {2, 0, 3, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 * g2);
}

// Test Case for *=
TEST_CASE("Operation *=: Multiply a graph by a scalar") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 0, -5},
        {1, 0, 3, 0},
        {0, 3, 0, 1},
        {-5, 0, 1, 0}};
    g1.loadGraph(graph1);

    g1 *= 2;
    CHECK(g1.printGraph() == "[0, 2, 0, -10]\n[2, 0, 6, 0]\n[0, 6, 0, 2]\n[-10, 0, 2, 0]");

    CHECK(Algorithms::isConnected(g1) == true);
    CHECK(Algorithms::isStronglyConnected(g1) == true);
    CHECK(Algorithms::shortestPath(g1, 0, 2) == "0->3->2");
    CHECK(Algorithms::isContainsCycle(g1) == "0->1->2->3->0");
    CHECK(Algorithms::isBipartite(g1) == "The graph is bipartite: A={0,2}, B={1,3}");
    CHECK(Algorithms::negativeCycle(g1) == "No negative cycle exists");
}

TEST_CASE("Operation *=: Multiply a graph by a negative scalar") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 0, 2},
        {1, 0, 3, 0},
        {0, 3, 0, 1},
        {2, 0, 1, 0}};
    g1.loadGraph(graph1);

    g1 *= -3;
    CHECK(g1.printGraph() == "[0, -3, 0, -6]\n[-3, 0, -9, 0]\n[0, -9, 0, -3]\n[-6, 0, -3, 0]");

    CHECK(Algorithms::isConnected(g1) == true);
    CHECK(Algorithms::isStronglyConnected(g1) == true);
    CHECK(Algorithms::shortestPath(g1, 0, 2) == "Graph contains a negative cycle");
    CHECK(Algorithms::isContainsCycle(g1) == "0->1->2->3->0");
    CHECK(Algorithms::isBipartite(g1) == "The graph is bipartite: A={0,2}, B={1,3}");
    CHECK(Algorithms::negativeCycle(g1) == "0->1->2->3->0");
}

// Test Case for /=
TEST_CASE("Operation /=: Divide graph by a scalar") 
{
    vector<vector<int>> graph1 = {
        {0, 2, 0},
        {2, 0, 4},
        {0, 4, 0}};
    g1.loadGraph(graph1);

    g1 /= 2;
    CHECK(g1.printGraph() == "[0, 1, 0]\n[1, 0, 2]\n[0, 2, 0]");
}

TEST_CASE("Operation /=: Divide graph by zero") 
{
    vector<vector<int>> graph1 = {
        {0, 2, 0},
        {2, 0, 4},
        {0, 4, 0}};
    g1.loadGraph(graph1);

    CHECK_THROWS(g1 /= 0);
}

// Test Case for ==
TEST_CASE("Operation ==: Compare two identical graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 == g2);
}

TEST_CASE("Operation ==: Compare two non-identical graphs with the same number of edges") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0},
        {1, 0, 0, 3},
        {2, 0, 0, 1},
        {0, 3, 1, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 1},
        {0, 0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 != g2);
}

TEST_CASE("Operation ==: Compare graphs of different sizes") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0},
        {1, 0, 3, 1},
        {2, 3, 0, 2},
        {0, 1, 2, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 != g2);
}

// Test Case for !=
TEST_CASE("Operation !=: Compare two different graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 4},
        {2, 4, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 != g2);
}

TEST_CASE("Operation !=: Compare two identical graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g2.loadGraph(graph2);

    CHECK(!(g1 != g2));
}

// Test Case for <
TEST_CASE("Operation <: Compare a smaller graph with a larger graph") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 4},
        {2, 4, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);
}

TEST_CASE("Operation <: Check if a smaller graph is contained in a larger graph") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0},
        {1, 0, 3, 1},
        {2, 3, 0, 2},
        {0, 1, 2, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 1, 0},
        {2, 3, 0, 2, 0},
        {0, 1, 2, 0, 0},
        {0, 0, 0, 0, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);
}

TEST_CASE("Operation <: Compare graphs of different sizes") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0},
        {1, 0, 3, 1},
        {2, 3, 0, 2},
        {0, 1, 2, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);
}

TEST_CASE("Operation <: Compare graphs with the same size but different edges") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 2, 4},
        {2, 0, 6},
        {4, 6, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);
}

TEST_CASE("Operator <: Graph with positive and negative edges, different sizes") {
    vector<vector<int>> matrix1 = {
        {0, 2, 0, 0, 0},
        {2, 0, -1, 3, 0},
        {0, -1, 0, 4, 0},
        {0, 3, 4, 0, -2},
        {0, 0, 0, -2, 0}};
    g1.loadGraph(matrix1);
    
    vector<vector<int>> matrix2 = {
        {0, -1, 3},
        {-1, 0, 4},
        {3, 4, 0}};
    g2.loadGraph(matrix2);
    
    CHECK(g2 < g1);
}

// Test Case for <=
TEST_CASE("Operation <=: Compare a smaller graph with a larger graph or identical") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 4},
        {2, 4, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 <= g2);
    CHECK(g2 >= g1);

    g3.loadGraph(graph1);
    CHECK(g1 <= g3);
}

// Test Case for >
TEST_CASE("Operation >: Compare a larger graph with a smaller graph") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 4},
        {2, 4, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 > g2);
}

TEST_CASE("Operation >: Compare a larger graph with more edges to a smaller graph") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {1, 0, 0, 3, 0},
        {2, 0, 0, 1, 2},
        {0, 3, 1, 0, 0},
        {3, 0, 2, 0, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2, 0},
        {1, 0, 0, 3},
        {2, 0, 0, 1},
        {0, 3, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 > g2);
}

TEST_CASE("Operation >: Compare graphs with different sizes") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {1, 0, 0, 3, 0},
        {2, 0, 0, 1, 2},
        {0, 3, 1, 0, 0},
        {3, 0, 2, 0, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 > g2);
}

// Test Case for >=
TEST_CASE("Operation >=: Compare a larger graph with a smaller graph or identical") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 4},
        {2, 4, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 >= g2);
    CHECK(g2 <= g1);

    g3.loadGraph(graph1);
    CHECK(g1 >= g3);
}

// Test Case for ++
TEST_CASE("Operation ++: Increment all edges") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    ++g1;
    CHECK(g1.printGraph() == "[0, 2, 3]\n[2, 0, 4]\n[3, 4, 0]");
}

TEST_CASE("Operation ++: Increment a graph with negative weights") 
{
    vector<vector<int>> graph1 = {
        {0, -1, 2},
        {-1, 0, -3},
        {2, -3, 0}};
    g1.loadGraph(graph1);

    ++g1;
    CHECK(g1.printGraph() == "[0, 0, 3]\n[0, 0, -2]\n[3, -2, 0]");
}

// Test Case for --
TEST_CASE("Operation --: Decrement all edges") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    --g1;
    CHECK(g1.printGraph() == "[0, 0, 1]\n[0, 0, 2]\n[1, 2, 0]");
}

TEST_CASE("Operation --: Decrement a graph with negative weights") 
{
    vector<vector<int>> graph1 = {
        {0, -1, 2},
        {-1, 0, -3},
        {2, -3, 0}};
    g1.loadGraph(graph1);

    --g1;
    CHECK(g1.printGraph() == "[0, -2, 1]\n[-2, 0, -4]\n[1, -4, 0]");

    // Additional checks for Algorithms functions
    CHECK(Algorithms::isConnected(g1) == true);
    CHECK(Algorithms::isStronglyConnected(g1) == true);
    CHECK(Algorithms::shortestPath(g1, 0, 2) == "Graph contains a negative cycle");
    CHECK(Algorithms::isContainsCycle(g1) == "0->1->2->0");
    CHECK(Algorithms::isBipartite(g1) == "The graph is not bipartite");
    CHECK(Algorithms::negativeCycle(g1) == "0->1->2->0");
}

TEST_CASE("Operations ++ and --: Increment and decrement larger graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {1, 0, 0, 3, 0},
        {2, 0, 0, 1, 2},
        {0, 3, 1, 0, 0},
        {3, 0, 2, 0, 0}};
    g1.loadGraph(graph1);

    ++g1;
    CHECK(g1.printGraph() == "[0, 2, 3, 0, 4]\n[2, 0, 0, 4, 0]\n[3, 0, 0, 2, 3]\n[0, 4, 2, 0, 0]\n[4, 0, 3, 0, 0]");

    --g1;
    --g1;
    CHECK(g1.printGraph() == "[0, 0, 1, 0, 2]\n[0, 0, 0, 2, 0]\n[1, 0, 0, 0, 1]\n[0, 2, 0, 0, 0]\n[2, 0, 1, 0, 0]");

    // Additional checks for Algorithms functions
    CHECK(Algorithms::isConnected(g1) == false);
    CHECK(Algorithms::isStronglyConnected(g1) == false);
    CHECK(Algorithms::shortestPath(g1, 0, 4) == "0->4");
    CHECK(Algorithms::shortestPath(g1, 0, 1) == "No path exists between 0 and 1");
    CHECK(Algorithms::isContainsCycle(g1) == "0->2->4->0");
    CHECK(Algorithms::isBipartite(g1) == "The graph is not bipartite");
    CHECK(Algorithms::negativeCycle(g1) == "No negative cycle exists");
}

// Test Case for +=
TEST_CASE("Operation +=: Add a scalar to all edges") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    g1 += 1;
    CHECK(g1.printGraph() == "[0, 2, 3]\n[2, 0, 4]\n[3, 4, 0]");
}

TEST_CASE("Operation +=: Add a negative scalar to all edges") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    g1 += -2;
    CHECK(g1.printGraph() == "[0, -1, 0]\n[-1, 0, 1]\n[0, 1, 0]");
}

// Test Case for -=
TEST_CASE("Operation -=: Subtract a scalar from all edges") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    g1 -= 1;
    CHECK(g1.printGraph() == "[0, 0, 1]\n[0, 0, 2]\n[1, 2, 0]");
}

TEST_CASE("Operation -=: Subtract a negative scalar from all edges") 
{
    vector<vector<int>> graph1 = {
        {0, -1, 9},
        {1, 0, 3},
        {-5, 3, 0}};
    g1.loadGraph(graph1);

    g1 -= -2;
    CHECK(g1.printGraph() == "[0, 1, 11]\n[3, 0, 5]\n[-3, 5, 0]");

    // Additional checks for Algorithms functions
    CHECK(Algorithms::isConnected(g1) == true);
    CHECK(Algorithms::isStronglyConnected(g1) == true);
    CHECK(Algorithms::shortestPath(g1, 1, 0) == "1->2->0");
    CHECK(Algorithms::isContainsCycle(g1) == "0->1->0");
    CHECK(Algorithms::isBipartite(g1) == "The graph is not bipartite");
    CHECK(Algorithms::negativeCycle(g1) == "No negative cycle exists");
}

TEST_CASE("Operations += and -=: Add and subtract scalars from larger graphs") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {1, 0, 0, 3, 0},
        {2, 0, 0, 1, 2},
        {0, 3, 1, 0, 0},
        {3, 0, 2, 0, 0}};
    g1.loadGraph(graph1);

    g1 += 2;
    CHECK(g1.printGraph() == "[0, 3, 4, 0, 5]\n[3, 0, 0, 5, 0]\n[4, 0, 0, 3, 4]\n[0, 5, 3, 0, 0]\n[5, 0, 4, 0, 0]");

    g1 -= 3;
    CHECK(g1.printGraph() == "[0, 0, 1, 0, 2]\n[0, 0, 0, 2, 0]\n[1, 0, 0, 0, 1]\n[0, 2, 0, 0, 0]\n[2, 0, 1, 0, 0]");
}

// Test Case for getNumVertices
TEST_CASE("getNumVertices: Verify the number of vertices") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {1, 0, 0, 3, 0},
        {2, 0, 0, 1, 2},
        {0, 3, 1, 0, 0},
        {3, 0, 2, 0, 0}};
    g1.loadGraph(graph1);

    CHECK(g1.getNumVertices() == 5);
}

// Test Case for getNumEdges
TEST_CASE("getNumEdges: Verify the number of edges in an undirected graph") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {1, 0, 0, 3, 0},
        {2, 0, 0, 1, 2},
        {0, 3, 1, 0, 0},
        {3, 0, 2, 0, 0}};
    g1.loadGraph(graph1);

    CHECK(g1.getNumEdges() == 6);
}

TEST_CASE("getNumEdges: Verify the number of edges in a directed graph") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {0, 0, 0, 3, 0},
        {0, 0, 0, 1, 2},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g1.loadGraph(graph1);

    CHECK(g1.getNumEdges() == 6);
}

// Test Case for isGraphDirected
TEST_CASE("isGraphDirected: Verify if a graph is directed") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {0, 0, 0, 3, 0},
        {0, 0, 0, 1, 2},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g1.loadGraph(graph1);

    CHECK(g1.isGraphDirected() == true);
}

TEST_CASE("isGraphDirected: Verify if a graph is undirected") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2, 0, 3},
        {1, 0, 0, 3, 0},
        {2, 0, 0, 1, 2},
        {0, 3, 1, 0, 0},
        {3, 0, 2, 0, 0}};
    g1.loadGraph(graph1);

    CHECK(g1.isGraphDirected() == false);
}

// Test Case for getAdjacencyMatrix
TEST_CASE("getAdjacencyMatrix: Verify the adjacency matrix") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    vector<vector<int>> adjMatrix = g1.getAdjacencyMatrix();
    CHECK(adjMatrix == graph1);
}

// Test Case for loadGraph
TEST_CASE("loadGraph: Load an empty graph") 
{
    vector<vector<int>> graph1 = {};
    CHECK_THROWS(g1.loadGraph(graph1));
}

TEST_CASE("loadGraph: Load a non-square graph") 
{
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0, 2}};
    CHECK_THROWS(g1.loadGraph(graph1));
}

TEST_CASE("loadGraph: Load a valid graph") 
{
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    CHECK_NOTHROW(g1.loadGraph(graph1));
    CHECK(g1.printGraph() == "[0, 1]\n[1, 0]");
}

TEST_CASE("loadGraph: Load a graph with negative weights") 
{
    vector<vector<int>> graph1 = {
        {0, -1, 2},
        {-1, 0, -3},
        {2, -3, 0}};
    CHECK_NOTHROW(g1.loadGraph(graph1));
    CHECK(g1.printGraph() == "[0, -1, 2]\n[-1, 0, -3]\n[2, -3, 0]");
}

// Test Case for printGraph
TEST_CASE("printGraph: Verify output format") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    CHECK(g1.printGraph() == "[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");
}

TEST_CASE("printGraph: Verify output format for a graph with negative weights") 
{
    vector<vector<int>> graph1 = {
        {0, -1, 2},
        {-1, 0, -3},
        {2, -3, 0}};
    g1.loadGraph(graph1);

    CHECK(g1.printGraph() == "[0, -1, 2]\n[-1, 0, -3]\n[2, -3, 0]");
}

// Test Case for operator<<
TEST_CASE("operator<<: Verify output stream") 
{
    vector<vector<int>> graph1 = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g1.loadGraph(graph1);

    ostringstream oss;
    oss<<g1;
    CHECK(oss.str() == "[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");
}
