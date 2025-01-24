#include <catch2/catch_all.hpp>

#include <iostream>

#include "../Source/Graph.hpp"
#include "../Source/PixelMatrix.hpp"

TEST_CASE("Graph: Constructors")
{
  SECTION("Empty constructor")
  {
    Graph<Pos, bool> graph;
  }
}

TEST_CASE("Graph: Operations")
{
  SECTION("Contain Vertex")
  {
    Graph<Pos, bool> graph;
    Pos pos1 = Pos(1,2);
    Pos pos2 = Pos(3,4);
    graph.addVertex(pos1);
    graph.addVertex(pos2);
    REQUIRE(graph.containVertex(pos1));
    REQUIRE(graph.containVertex(pos2));
    graph.addEdge(pos1, pos2, true);
    REQUIRE(graph.getWeight(pos1, pos2));
    graph.removeEdge(pos1, pos2);
    REQUIRE_THROWS(graph.getWeight(pos1, pos2));
    graph.addEdge(pos1, pos2, true);
    graph.removeVertex(pos2);
    REQUIRE(!graph.containVertex(pos2));
    graph.addVertex(pos2);
    graph.removeVertex(pos2);
    REQUIRE(!graph.containVertex(pos2));
  }

  SECTION("Split into independent subgraphs")
  {
    Graph<Pos, bool> graph;
    Pos pos1 = Pos(1,0);
    Pos pos2 = Pos(2,0);
    Pos pos3 = Pos(3,0);
    Pos pos4 = Pos(4,0);
    Pos pos5 = Pos(5,0);
    Pos pos6 = Pos(6,0);
    Pos pos7 = Pos(7,0);

    graph.addVertex(pos1);
    graph.addVertex(pos2);
    graph.addVertex(pos3);
    graph.addEdge(pos1, pos2, true);
    graph.addEdge(pos2, pos3, true);
    graph.addEdge(pos3, pos1, true);

    graph.addVertex(pos4);
    graph.addVertex(pos5);
    graph.addVertex(pos6);
    graph.addEdge(pos4, pos5, true);
    graph.addEdge(pos5, pos6, true);

    graph.addVertex(pos7);

    DynamicArray<Graph<Pos, bool>> subgraphs = graph.splitIntoIndependentSubgraphs();
    Graph graph1 = subgraphs[0];
    Graph graph2 = subgraphs[1];
    Graph graph3 = subgraphs[2];

    REQUIRE(graph1.containVertex(pos1));
    REQUIRE(graph1.containVertex(pos2));
    REQUIRE(graph1.containVertex(pos3));
    REQUIRE(!graph1.containVertex(pos4));
    REQUIRE(!graph1.containVertex(pos5));
    REQUIRE(!graph1.containVertex(pos6));
    REQUIRE(!graph1.containVertex(pos7));
    REQUIRE(graph1.getWeight(pos1, pos2));
    REQUIRE(graph1.getWeight(pos1, pos3));
    REQUIRE(graph1.getWeight(pos2, pos3));

    REQUIRE(!graph2.containVertex(pos1));
    REQUIRE(!graph2.containVertex(pos2));
    REQUIRE(!graph2.containVertex(pos3));
    REQUIRE(graph2.containVertex(pos4));
    REQUIRE(graph2.containVertex(pos5));
    REQUIRE(graph2.containVertex(pos6));
    REQUIRE(!graph2.containVertex(pos7));
    REQUIRE(graph2.getWeight(pos4, pos5));
    REQUIRE(graph2.getWeight(pos5, pos6));

    REQUIRE(!graph3.containVertex(pos1));
    REQUIRE(!graph3.containVertex(pos2));
    REQUIRE(!graph3.containVertex(pos3));
    REQUIRE(!graph3.containVertex(pos4));
    REQUIRE(!graph3.containVertex(pos5));
    REQUIRE(!graph3.containVertex(pos6));
    REQUIRE(graph3.containVertex(pos7));
  }

  SECTION("Longest path")
  {
    Graph<Pos, bool> graph;
    Pos pos1 = Pos(1,0);
    Pos pos2 = Pos(2,0);
    Pos pos3 = Pos(3,0);
    Pos pos4 = Pos(4,0);
    Pos pos5 = Pos(5,0);

    graph.addVertex(pos1);
    graph.addVertex(pos2);
    graph.addVertex(pos3);
    graph.addVertex(pos4);
    graph.addVertex(pos5);

    graph.addEdge(pos1, pos2, true);
    graph.addEdge(pos1, pos3, true);
    graph.addEdge(pos2, pos3, true);
    graph.addEdge(pos3, pos4, true);
    graph.addEdge(pos3, pos5, true);
    graph.addEdge(pos4, pos5, true);

    DynamicArray<Pos> longestPath = graph.longestPathInGraphAsArray();
  }
}