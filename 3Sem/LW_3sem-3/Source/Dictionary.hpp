#pragma once

#include <stdexcept>

template <class K, class V>
class Dictionary
{
private:
  struct Node
  {
    K key;
    V value;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0;

    Node(K const & key):
      key(key)
    { }

    Node(K const & key, V const & value):
      key(key),
      value(value)
    { }
    
    static Node* copyTree(Node* nodeToCopy)
    {
      if (nodeToCopy == nullptr)
      {
        return nullptr;
      }
      Node* node = new Node(nodeToCopy->key, nodeToCopy->value);
      node->left = copyTree(nodeToCopy->left);
      node->right = copyTree(nodeToCopy->right);
      return node;
    }

    static void deleteTree(Node* node) {
      if (node == nullptr)
        return;
      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
      return;
    }

    static int getHeight(Node* node) {
      if (node == nullptr)
        return -1;
      return node->height;
    }

    static void updateHeight(Node* node) {
      int leftHeight = getHeight(node->left);
      int rightHeight = getHeight(node->right);
      node->height = ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
    }

    static void swap(Node* node1, Node* node2) {
      K key = std::move(node1->key);
      V value = std::move(node1->value);
      node1->key = std::move(node2->key);
      node1->value = std::move(node2->value);
      node2->key = std::move(key);
      node2->value = std::move(value);
    }

    static void rightRotate (Node* node) {
      swap(node, node->left);
      Node* buffer = node->right;
      node->right = node->left;
      node->left = node->right->left;
      node->right->left = node->right->right;
      node->right->right = buffer;
      updateHeight(node->right);
      updateHeight(node);
    }

    static void leftRotate (Node* node) {
      swap(node, node->right);
      Node* buffer = node->left;
      node->left = node->right;
      node->right = node->left->right;
      node->left->right = node->left->left;
      node->left->left = buffer;
      updateHeight(node->left);
      updateHeight(node);
    }

    static int getBalance(Node* node) {
      return (node == nullptr) ? 0 : getHeight(node->right) - getHeight(node->left);
    }

    static void balance(Node* node) {
      int balance = getBalance(node);
      if (balance == -2) {
        if (getBalance(node->left) == 1)
          leftRotate(node->left);
        rightRotate(node);
      }
      else if (balance == 2) {
        if (getBalance(node->right) == -1)
          rightRotate(node->right);
        leftRotate(node);
      }
    }

    static Node* findOrCreate(Node* node, K const & key, Node** ptrToTargetNode) {
      if (node == nullptr) {
        Node* targetNode = new Node(key); 
        (*ptrToTargetNode) = targetNode;  
        return targetNode;
      }
      if (key < node->key) {
        node->left = findOrCreate(node->left, key, ptrToTargetNode);
      } 
      else if (key > node->key) {
        node->right = findOrCreate(node->right, key, ptrToTargetNode);
      }
      else {
        (*ptrToTargetNode) = node;
      }
      updateHeight(node);
      balance(node);
      return node;
    }

    static Node* remove(Node* node, K const & key) {
        if (node == nullptr) {
          return nullptr; // Узел не найден
        }

        // Рекурсивно ищем узел для удаления
        if (key < node->key) {
          node->left = remove(node->left, key);
        } 
        else if (key > node->key) {
          node->right = remove(node->right, key);
        } 
        else {
          // Узел найден
          // Узел с одним или без детей
          if (node->left == nullptr) {
            Node* buffer = node->right;
            delete node;
            return buffer;
          } else if (node->right == nullptr) {
            Node* buffer = node->left;
            delete node;
            return buffer;
          }

          // Узел с двумя детьми: получаем минимальный узел из правого поддерева
          Node* buffer = minKeyNode(node->right);
          node->key = buffer->key; // Копируем значение
          node->value = buffer->value; // Копируем значение
          node->right = remove(node->right, buffer->key); // Удаляем минимальный узел
        }
        updateHeight(node);
        balance(node);
        return node;
    }

    static Node* minKeyNode(Node* node)
    {
      if (node->left == nullptr)
        return node;
      return minKeyNode(node->left);
    }

    static Node* find(Node* node, K const & key)
    {
      if (key < node->key)
      {
        if (node->left == nullptr)
          return nullptr;
        else
          return find(node->left, key);
      }
      else if (key > node->key)
      {
        if (node->right == nullptr)
          return nullptr;
        else
          return find(node->right, key);
      }
      else 
      {
        return node;
      }
    }
  
    static size_t countNodes(Node* node)
    {
      if (node == nullptr)
        return 0;
      if (node->left == nullptr && node->right == nullptr)
        return 1;
      return countNodes(node->left) + countNodes(node->right) + 1;
    }
  };
  
  Node* head = nullptr;

public:
  class InOrderIterator
  {
    friend class Dictionary;
    private:
      struct ChainNode
      {
        ChainNode* previous;
        Node* treeNode;
        bool isLeft;
        ChainNode(ChainNode* previous, Node* treeNode, bool isLeft):
          previous(previous),
          treeNode(treeNode),
          isLeft(isLeft)
        { }
      };

      ChainNode** curr;
      
      InOrderIterator(Node* treeNode)
      {
        curr = new ChainNode*;
        (*curr) = new ChainNode(nullptr, treeNode, false);
        while ((*curr)->treeNode->left != nullptr)
        {
          ChainNode* buffer = new ChainNode((*curr), (*curr)->treeNode->left, true);
          (*curr) = buffer;
        }
      }

    public:
      ~InOrderIterator()
      {
        while ((*curr)->previous != nullptr)
        {
          ChainNode* prev = (*curr)->previous;
          delete (*curr);
          (*curr) = prev;
        }
        delete *curr;
        delete curr;
      }

      V & value() 
      {
        return (*curr)->treeNode->value;
      }

      V const & value() const 
      {
        return (*curr)->treeNode->value;
      }

      //V const & key() const
      K const & key() const
      {
        return (*curr)->treeNode->key;
      }

      bool hasNext() const
      {
        if ((*curr)->isLeft)
          return true;
        if ((*curr)->treeNode->right == nullptr)
          return false;
        return true;
      }

      bool next() const
      {
        if (!hasNext())
          return false;
        if ((*curr)->treeNode->right != nullptr)
        {
          ChainNode* buffer = new ChainNode((*curr), (*curr)->treeNode->right, (*curr)->isLeft);
          (*curr) = buffer;
          while ((*curr)->treeNode->left != nullptr)
          {
            ChainNode* buffer = new ChainNode((*curr), (*curr)->treeNode->left, true);
            (*curr) = buffer;
          }
        }
        else 
        {
          K currKey = (*curr)->treeNode->key;
          while ((*curr)->treeNode->key <= currKey)
          {
            ChainNode* prev = (*curr)->previous;
            delete (*curr);
            (*curr) = prev;
          }
        }
        return true;
      }
  };

/* Constructors */
  // Constructor of zero-array
  Dictionary();

  // Copy-constructors
  Dictionary(Dictionary const &);

/* Destructor */
  ~Dictionary();

/* Getters */
  // Get number of values
  size_t getCount() const;

  // Does dictionary contain key
  bool containsKey(K const &) const;

  // Secure way to read value of that key (similar to const [])
  V const & at(K const &) const;

/* Modifying Operations */
  // Remove by key
  void remove(K const &);

  // Delete all tree
  void removeAllKeys();
  
  // Secure way to change value of that key
  V & at(K const &);

/* Operators */
  // Dereferencing by key
  V &operator[](K const &);

  // Const version of dereferencing by key
  V const & operator[](K const &) const;

/* Iterators */
  /* Standart ascending InOrder iterator */
  InOrderIterator createInOrderIterator();

  /* Standart ascending InOrder iterator without permission to change values */
  const InOrderIterator createInOrderIterator() const;

};

/* Constructors */
  // Constructor of zero-array
  template <class K, class V>
  Dictionary<K, V>::Dictionary()
  { }

  // Copy-constructor
  template <class K, class V>
  Dictionary<K, V>::Dictionary(Dictionary const & other)
  {
    head = Node::copyTree(other.head);
  }

/* Destructor */
  template <class K, class V>
  Dictionary<K, V>::~Dictionary()
  {
    removeAllKeys();
  }

/* Getters */
  // Get size
  template <class K, class V>
  size_t Dictionary<K, V>::getCount() const 
  {
    return Node::countNodes(head);
  }

  // Check if dictionary contains a key
  template <class K, class V>
  bool Dictionary<K, V>::containsKey(K const & key) const 
  {
    if (head == nullptr)
      return false;
    Node* result = Node::find(head, key);
    return (result != nullptr);
  }

  // Secure way to read value of that key (similar to const [])
  template<class K, class V> 
  const V & Dictionary<K, V>::at(const K & key) const
  {
    if (head == nullptr)
      throw std::out_of_range("V & Dictionary<K, V>::at(const K & key): Key isn't in Dictionary.");
    Node* targetNode = Node::find(head, key);
    if (targetNode == nullptr)
      throw std::out_of_range("const V & Dictionary<K, V>::at(const K & key) const: Key isn't in Dictionary.");
    V const & result = targetNode->value;
    return result;
  }


/* Modifying Operations */
  // Remove
  template <class K, class V>
  void Dictionary<K, V>::remove(K const & key)  
  {
    head = Node::remove(head, key);
  }
  
  // Delete all tree
  template <class K, class V>
  void Dictionary<K, V>::removeAllKeys()  
  {
    Node::deleteTree(head);
    head = nullptr;
  }

  // Secure way to change value of that key
  template<class K, class V> 
  V & Dictionary<K, V>::at(const K & key)
  {
    if (head == nullptr)
      throw std::out_of_range("V & Dictionary<K, V>::at(const K & key): Key isn't in Dictionary.");
    Node* targetNode = Node::find(head, key);
    if (targetNode == nullptr)
      throw std::out_of_range("V & Dictionary<K, V>::at(const K & key): Key isn't in Dictionary.");
    V & result = targetNode->value;
    return result;
  }


/* Operators */
  // Dereferencing by index
  template <class K, class V>
  V & Dictionary<K, V>::operator[](K const & key)
  {
    Node** ptrToTargetNode = new (Node*);
    head = Node::findOrCreate(head, key, ptrToTargetNode);
    V & result = (*ptrToTargetNode)->value;
    delete ptrToTargetNode;
    return result;
  }

  // Const version of dereferencing by index
  template <class K, class V>
  V const & Dictionary<K, V>::operator[](K const & key) const
  {
    if (head == nullptr)
      throw std::out_of_range("V & Dictionary<K, V>::at(const K & key): Key isn't in Dictionary.");
    Node* targetNode = Node::find(head, key);
    if (targetNode == nullptr)
      throw std::out_of_range("V const & Dictionary<K, V>::operator[](K const & key) const: Key isn't in Dictionary.");
    V const & result = targetNode->value;
    return result;
  }

/* Iterators */
  /* Standart ascending InOrder iterator */
  template <class K, class V> 
  typename Dictionary<K, V>::InOrderIterator Dictionary<K, V>::createInOrderIterator()
  {
    return typename Dictionary<K, V>::InOrderIterator::InOrderIterator(head);
  }

  /* Standart ascending InOrder iterator without permission to change values */
  template <class K, class V> 
  const typename Dictionary<K, V>::InOrderIterator Dictionary<K, V>::createInOrderIterator() const
  {
    return typename Dictionary<K, V>::InOrderIterator::InOrderIterator(head);
  }