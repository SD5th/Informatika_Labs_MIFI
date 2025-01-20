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

    Node()
    { }

    Node(K const & key):
      key(key)
    { }

    Node(K const & key, V const & value):
      key(key),
      value(value)
    { }
    
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
/* Constructors */
  // Constructor of zero-array
  Dictionary();

/* Getters */
  // Get number of values
  size_t getCount() const;

  // Does dictionary contain key
  bool containsKey(K const &) const;

/* Modifying Operations */
  // Remove by key
  void remove(K const &);

/* Operators */
  // Dereferencing by key
  V &operator[](K const &);

  // Const version of dereferencing by key
  V const & operator[](K const &) const;
};

/* Constructors */
  // Constructor of zero-array
  template <class K, class V>
  Dictionary<K, V>::Dictionary()
  { }

/* Getters */
  // Get size
  template <class K, class V>
  size_t Dictionary<K, V>::getCount() const 
  {
    return Node::countNodes(head);
  }

  template <class K, class V>
  bool Dictionary<K, V>::containsKey(K const & key) const 
  {
    if (head == nullptr)
      return false;
    Node* result = Node::find(head, key);
    return (result != nullptr);
  }

/* Modifying Operations */
  // Remove
  template <class K, class V>
  void Dictionary<K, V>::remove(K const & key)  
  {
    head = Node::remove(head, key);
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
    Node* targetNode = Node::find(head, key);
    if (targetNode == nullptr)
      throw std::out_of_range("Dictionary::operator[](const K &key) const: Key isn't in Dictionary.");
    V const & result = targetNode->value;
    delete targetNode;
    return result;
  }