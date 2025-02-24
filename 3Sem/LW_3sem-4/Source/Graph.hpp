#include "../../LW_3sem-1/Source/DynamicArray.hpp"
#include "../../LW_3sem-1/Source/ShrdPtr.hpp"
#include "../../LW_3sem-3/Source/Dictionary.hpp"

template <class V, class W>
class Graph
{
private:
/* Class for inner use */
  class AdjacencyTable
  {
  public:
    class InOrderIterator
    {
    public:
      typename Dictionary<V, W>::InOrderIterator* iterator;

      InOrderIterator(Dictionary<V,W>* table):
        iterator(new typename Dictionary<V, W>::InOrderIterator(table->createInOrderIterator()))
      { }

      ~InOrderIterator()
      {
        delete iterator;
      }

      W & weight()
      {
        return iterator->value();
      }
      
      V const & vertex() const{
        return iterator->key();
      }

      bool isEmpty() const
      {
        return iterator->isEmpty();
      }

      bool next() const
      {
        return iterator->next();
      }
    };
  
    AdjacencyTable():
      table(new Dictionary<V, W>)
    {  }

    AdjacencyTable(AdjacencyTable const & other):
      table(*(other.table))
    {  }

    ~AdjacencyTable()
    {
      delete table;
    }

    W &operator[](V const & vertex)
    {
      return table->operator[](vertex);
    }

    W const & operator[](V const & vertex) const
    {
      return table->operator[](vertex);
    }

    W const & at(V const & vertex) const
    {
      return table->at(vertex);
    }

    W & at(V const & vertex)
    {
      return table->at(vertex);
    }
    
    void remove(V const & vertex)
    {
      table->remove(vertex);
    }

    AdjacencyTable::InOrderIterator createIterator()
    {
      return InOrderIterator(table);  
    }

    AdjacencyTable::InOrderIterator createIterator() const
    {
      return InOrderIterator(table);  
    }
      

  private:
    Dictionary<V, W>* table;
  };
public:
/* Constructor-destructor */
  Graph();
  ~Graph();

/* Add functions */
  void addVertex(V const &);
  void addEdge(V const &, V const &, W const &);
  
/* Remove functions */  
  void removeVertex(V const &);
  void removeEdge(V const &, V const &);

/* Get functions */
  size_t countVerticies();
  bool containVertex(V const &);
  W const & getWeight(V const &, V const &) const;

/* Algorithms */
  DynamicArray<Graph<V,W>> splitIntoIndependentSubgraphs();
  DynamicArray<V> longestPathInGraphAsArray();
private:
  Dictionary<V, AdjacencyTable*>* vertexTables;

/* Util-functions (for inner use) */
  void splitIntoIndependentSubgraphsUtil(AdjacencyTable*, Graph<V, W> &);
  Dictionary<V, size_t> longestPathInGraphAsArrayUtil(Dictionary<V, size_t>, V const &, Graph<V, W> const &);
};

template <class V, class W>
Graph<V, W>::Graph():
  vertexTables(new Dictionary<V, AdjacencyTable*>)
{ }

template <class V, class W>
Graph<V, W>::~Graph()
{
  /*
  typename Dictionary<V, AdjacencyTable*>::InOrderIterator it = vertexTables->createInOrderIterator();
  if (!it.isEmpty())
  {
    do
    {
      delete it.value();
    } while (it.next());
  }
  delete vertexTables;
  */
}

template <class V, class W>
void Graph<V, W>::addVertex(V const & vertex)
{
  if (!vertexTables->containsKey(vertex))
    (*vertexTables)[vertex] = new AdjacencyTable; 
}

template <class V, class W>
void Graph<V, W>::addEdge(V const & vertex1, V const & vertex2, W const & weight)
{
  vertexTables->at(vertex1)->operator[](vertex2) = weight;
  vertexTables->at(vertex2)->operator[](vertex1) = weight;
}

template <class V, class W>
void Graph<V, W>::removeVertex(V const & vertex)
{
  if (!vertexTables->containsKey(vertex))
    return;
  typename AdjacencyTable::InOrderIterator it = vertexTables->at(vertex)->createIterator();
  
  if (!it.isEmpty())
  {
    do {
      V vertexToClear = it.vertex();
      vertexTables->at(vertexToClear)->remove(vertex);
    } while (it.next());
  }
  //delete vertexTables->at();
  vertexTables->remove(vertex);
}

template <class V, class W>
void Graph<V, W>::removeEdge(V const & vertex1, V const & vertex2)
{
  vertexTables->at(vertex1)->remove(vertex2);
  vertexTables->at(vertex2)->remove(vertex1);
}

template<class V, class W> 
size_t Graph<V, W>::countVerticies()
{
  return vertexTables->getCount();
}

template<class V, class W> 
bool Graph<V, W>::containVertex(const V & vertex)
{
  return vertexTables->containsKey(vertex);
}

template <class V, class W>
W const & Graph<V, W>::getWeight(V const & vertex1, V const & vertex2) const
{
  return vertexTables->at(vertex1)->at(vertex2);
}

template<class V, class W> 
DynamicArray<Graph<V, W>> Graph<V, W>::splitIntoIndependentSubgraphs()
{
  DynamicArray<Graph<V, W>> subgraphs;
  typename Dictionary<V, AdjacencyTable*>::InOrderIterator it = vertexTables->createInOrderIterator();
  if (!it.isEmpty())
  {
    do {
      V vertex = it.key();
      bool unusedVertex = true;
      for (size_t i = 0; i < subgraphs.getSize(); i++)
        if (subgraphs[i].containVertex(vertex))
        {
          unusedVertex = false;
          break;
        }
      if (unusedVertex)
      {
        Graph<V, W> subgraph;
        subgraph.addVertex(vertex);
        splitIntoIndependentSubgraphsUtil((vertexTables->at(vertex)), subgraph);
        typename Dictionary<V, AdjacencyTable*>::InOrderIterator it2 = subgraph.vertexTables->createInOrderIterator();
        if (!it2.isEmpty())
        {
          do {
            subgraph.vertexTables->at(it2.key()) = vertexTables->at(it2.key());
          } while (it2.next());
        }

        subgraphs.append(subgraph);
      }
    } while (it.next());
  }
  return subgraphs;
}

template<class V, class W>  
void Graph<V, W>::splitIntoIndependentSubgraphsUtil(Graph<V, W>::AdjacencyTable* adj, Graph<V, W> &subgraph)
{
  typename AdjacencyTable::InOrderIterator it = adj->createIterator();
  if (!it.isEmpty()){
    do {
      V vertex = it.vertex();
      if (!subgraph.containVertex(vertex))
      {
        subgraph.addVertex(vertex);
        splitIntoIndependentSubgraphsUtil(vertexTables->at(vertex), subgraph);
      }
    } while (it.next());
  }
}

template<class V, class W> 
DynamicArray<V> Graph<V, W>::longestPathInGraphAsArray()
{
  DynamicArray<Graph<V, W>> subgraphs(splitIntoIndependentSubgraphs());
  Dictionary<V, size_t> best; 
  size_t bestCount = 0;
  for (size_t i = 0; i < subgraphs.getSize(); i++)
  {
    typename Dictionary<V, AdjacencyTable*>::InOrderIterator it = subgraphs[i].vertexTables->createInOrderIterator();
    if (!it.isEmpty())
    {
      do {
        V startVertex = it.key();
        Dictionary<V, size_t> candidate = longestPathInGraphAsArrayUtil(Dictionary<V, size_t>(), startVertex, subgraphs[i]);
        size_t candidateCount = candidate.getCount();
        if (candidateCount > bestCount)
        {
          bestCount = candidateCount;
          best = candidate;
        }
      } while (it.next());
    }
  }

  if (bestCount == 0)
    return DynamicArray<V>();
  DynamicArray<V> result = DynamicArray<V>(bestCount);
  typename Dictionary<V, size_t>::InOrderIterator it = best.createInOrderIterator();
  do {
    result[it.value()] = it.key();
  } while (it.next());
  return result;
}

template<class V, class W> 
Dictionary<V, size_t> Graph<V, W>::longestPathInGraphAsArrayUtil(Dictionary<V, size_t> currentPath, V const & lastVertex, Graph<V, W> const & graph)
{
  size_t currentCount = currentPath.getCount();
  currentPath[lastVertex] = currentCount;
  typename AdjacencyTable::InOrderIterator it = graph.vertexTables->at(lastVertex)->createIterator();
  Dictionary<V, size_t> bestPath;
  Dictionary<V, size_t> candidatePath;
  if (it.isEmpty())
    return currentPath;
  else {
    bestPath = currentPath; 
    size_t bestCount = currentCount + 1;

    do {
      V nextVertex = it.vertex();
      if (!currentPath.containsKey(nextVertex))
      {
        candidatePath = longestPathInGraphAsArrayUtil(currentPath, nextVertex, graph);
        size_t candidateCount = candidatePath.getCount();
        if (candidateCount > bestCount)
        {
          bestCount = candidateCount;
          bestPath = candidatePath;
        }
      }
    } while (it.next());
    return bestPath;
  }
}
