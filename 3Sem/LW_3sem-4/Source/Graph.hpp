#include "../../LW_3sem-1/Source/DynamicArray.hpp"
#include "../../LW_3sem-1/Source/ShrdPtr.hpp"
#include "../../LW_3sem-3/Source/Dictionary.hpp"

template <class V, class W>
class Graph
{
private:
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
  Graph();
  void addVertex(V const &);
  void addEdge(V const &, V const &, W const &);
  void removeVertex(V const &);
  void removeEdge(V const &, V const &);
  bool containVertex(V const &);
  W const & getWeight(V const &, V const &) const;

  DynamicArray<Graph<V,W>> splitIntoIndependentSubgraphs();

private:

  void recursiveTraversal(AdjacencyTable const & adj, Graph<V, W> & subgraph)
  {
    typename AdjacencyTable::InOrderIterator it = adj.createIterator();
    if (!it.isEmpty()){
      do {
        V vertex = it.vertex();
        if (!subgraph.containVertex(vertex))
        {
          subgraph.addVertex(vertex);
          recursiveTraversal(*((*vertexTables)[vertex].get()), subgraph);
        }
      } while (it.next());
    }
  };

  Dictionary<V, ShrdPtr<AdjacencyTable>>* vertexTables;
};

template <class V, class W>
Graph<V, W>::Graph():
  vertexTables(new Dictionary<V, ShrdPtr<AdjacencyTable>>)
{ }

template <class V, class W>
void Graph<V, W>::addVertex(V const & vertex)
{
  if ((*vertexTables)[vertex].get() == nullptr)
    (*vertexTables)[vertex] = ShrdPtr(new AdjacencyTable); 
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
  typename AdjacencyTable::InOrderIterator it = vertexTables->at(vertex)->createIterator();
  
  if (!it.isEmpty())
  {
    do {
      V vertexToClear = it.vertex();
      vertexTables->at(vertexToClear)->remove(vertex);
    } while (it.next());
  }
  vertexTables->remove(vertex);
}

template <class V, class W>
void Graph<V, W>::removeEdge(V const & vertex1, V const & vertex2)
{
  vertexTables->at(vertex1)->remove(vertex2);
  vertexTables->at(vertex2)->remove(vertex1);
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
  typename Dictionary<V, ShrdPtr<AdjacencyTable>>::InOrderIterator it = (*vertexTables).createInOrderIterator();
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
        recursiveTraversal(*((*vertexTables)[vertex].get()), subgraph);
        typename Dictionary<V, ShrdPtr<AdjacencyTable>>::InOrderIterator it2 = (*(subgraph.vertexTables)).createInOrderIterator();
        if (!it2.isEmpty())
        {
          do {
            subgraph.vertexTables->at(it2.key()) = vertexTables->at(it2.key());
          } while (it2.next());
        }

        subgraphs.append(std::move(subgraph));
      }
    } while (it.next());
  }
  return subgraphs;
}