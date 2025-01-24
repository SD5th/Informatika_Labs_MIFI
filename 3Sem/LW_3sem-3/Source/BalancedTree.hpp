#pragma once

#include <stdexcept>

template <class K, class V>
class BalancedTree
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
      K key = node1->key;
      V value = node1->value;
      node1->key = node2->key;
      node1->value = node2->value;
      node2->key = key;
      node2->value = value;
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
          return nullptr; 
        } 
        if (key < node->key) {
          node->left = remove(node->left, key);
        } 
        else if (key > node->key) {
          node->right = remove(node->right, key);
        } 
        else {
          if (node->left == nullptr) {
            Node* buffer = node->right;
            delete node;
            return buffer;
          } else if (node->right == nullptr) {
            Node* buffer = node->left;
            delete node;
            return buffer;
          }

          Node* buffer = minKeyNode(node->right);
          node->key = buffer->key; 
          node->value = buffer->value; 
          node->right = remove(node->right, buffer->key); 
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

    static Node* maxKeyNode(Node* node)
    {
      if (node->right == nullptr)
        return node;
      return maxKeyNode(node->right);
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
    friend class BalancedTree;
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
      if (treeNode == nullptr)
      {
        (*curr) = nullptr;
        return;
      }
      
      (*curr) = new ChainNode(nullptr, treeNode, false);
      while ((*curr)->treeNode->left != nullptr)
      {
        ChainNode* buffer = new ChainNode((*curr), (*curr)->treeNode->left, true);
        (*curr) = buffer;
      }
    }

  public:
    // Destructor
    ~InOrderIterator();

    // Get link to current value
    V & value();

    // Get const link to current value
    V const & value() const;
      
    // Get const link to current key
    K const & key() const;

    // Check if empty
    bool isEmpty() const;

    // Check if current node is last
    bool hasNext() const;

    // Go to the next key
    bool next() const;   
  };

/* Constructors */
  // Constructor of empty tree
  BalancedTree();

  // Copy-constructor
  BalancedTree(BalancedTree const &);

/* Destructor */
  ~BalancedTree();

/* Getters */
  // Get number of nodes
  size_t getCount() const;

  // Does tree contain key
  bool containsKey(K const &) const;

  // Secure way to read value of that key (similar to const [])
  V const & at(K const &) const;

  // Get minimal key
  K getMinKey() const;

  // Get maximal key
  K getMaxKey() const;

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
  BalancedTree<K, V>::BalancedTree()
  { }

  // Copy-constructor
  template <class K, class V>
  BalancedTree<K, V>::BalancedTree(BalancedTree const & other)
  {
    head = Node::copyTree(other.head);
  }

/* Destructor */
  template <class K, class V>
  BalancedTree<K, V>::~BalancedTree()
  {
    removeAllKeys();
  }

/* Getters */
  // Get size
  template <class K, class V>
  size_t BalancedTree<K, V>::getCount() const 
  {
    return Node::countNodes(head);
  }

  // Check if BalancedTree contains a key
  template <class K, class V>
  bool BalancedTree<K, V>::containsKey(K const & key) const 
  {
    if (head == nullptr)
      return false;
    Node* result = Node::find(head, key);
    return (result != nullptr);
  }

  // Secure way to read value of that key (similar to const [])
  template<class K, class V> 
  const V & BalancedTree<K, V>::at(const K & key) const
  {
    if (head == nullptr)
      throw std::out_of_range("V & BalancedTree<K, V>::at(const K & key): Key isn't in BalancedTree.");
    Node* targetNode = Node::find(head, key);
    if (targetNode == nullptr)
      throw std::out_of_range("const V & BalancedTree<K, V>::at(const K & key) const: Key isn't in BalancedTree.");
    V const & result = targetNode->value;
    return result;
  }

  // Get minimal key
  template<class K, class V> 
  K BalancedTree<K, V>::getMinKey() const
  {
    Node* minNode = Node::minKeyNode(head);
    return minNode->key;
  }

  // Get maximal key
  template<class K, class V> 
  K BalancedTree<K, V>::getMaxKey() const
  {
    Node* maxNode = Node::maxKeyNode(head);
    return maxNode->key;
  }

/* Modifying Operations */
  // Remove
  template <class K, class V>
  void BalancedTree<K, V>::remove(K const & key)  
  {
    head = Node::remove(head, key);
  }
  
  // Delete all tree
  template <class K, class V>
  void BalancedTree<K, V>::removeAllKeys()  
  {
    Node::deleteTree(head);
    head = nullptr;
  }

  // Secure way to change value of that key
  template<class K, class V> 
  V & BalancedTree<K, V>::at(const K & key)
  {
    if (head == nullptr)
      throw std::out_of_range("V & BalancedTree<K, V>::at(const K & key): Key isn't in BalancedTree.");
    Node* targetNode = Node::find(head, key);
    if (targetNode == nullptr)
      throw std::out_of_range("V & BalancedTree<K, V>::at(const K & key): Key isn't in BalancedTree.");
    V & result = targetNode->value;
    return result;
  }


/* Operators */
  // Dereferencing by index
  template <class K, class V>
  V & BalancedTree<K, V>::operator[](K const & key)
  {
    Node** ptrToTargetNode = new (Node*);
    head = Node::findOrCreate(head, key, ptrToTargetNode);
    V & result = (*ptrToTargetNode)->value;
    delete ptrToTargetNode;
    return result;
  }

  // Const version of dereferencing by index
  template <class K, class V>
  V const & BalancedTree<K, V>::operator[](K const & key) const
  {
    if (head == nullptr)
      throw std::out_of_range("V & BalancedTree<K, V>::at(const K & key): Key isn't in BalancedTree.");
    Node* targetNode = Node::find(head, key);
    if (targetNode == nullptr)
      throw std::out_of_range("V const & BalancedTree<K, V>::operator[](K const & key) const: Key isn't in BalancedTree.");
    V const & result = targetNode->value;
    return result;
  }

/* Iterators */
  /* Standart ascending InOrder iterator */
  template <class K, class V> 
  typename BalancedTree<K, V>::InOrderIterator BalancedTree<K, V>::createInOrderIterator()
  {
    return typename BalancedTree<K, V>::InOrderIterator::InOrderIterator(head);
  }

  /* Standart ascending InOrder iterator without permission to change values */
  template <class K, class V> 
  const typename BalancedTree<K, V>::InOrderIterator BalancedTree<K, V>::createInOrderIterator() const
  {
    return typename BalancedTree<K, V>::InOrderIterator::InOrderIterator(head);
  }

/* InOrder Iterator */
  // Destructor
  template<class K, class V> 
  BalancedTree<K, V>::InOrderIterator::~InOrderIterator()
  {
    if ((*curr) == nullptr)
    {
      delete curr;
      return;
    }
    while ((*curr)->previous != nullptr)
    {
      ChainNode* prev = (*curr)->previous;
      delete (*curr);
      (*curr) = prev;
    }
    delete *curr;
    delete curr;
  }

  // Get link to current value
  template <class K, class V>  
  V& BalancedTree<K, V>::InOrderIterator::value()
  {
    return (*curr)->treeNode->value;
  }

  // Get const link to current value
  template <class K, class V>  
  const V &BalancedTree<K, V>::InOrderIterator::value() const
  {
    return (*curr)->treeNode->value;
  }

  // Get const link to current key
  template<class K, class V>  
  const K &BalancedTree<K, V>::InOrderIterator::key() const
  { 
    return (*curr)->treeNode->key;
  }

  // Check if empty
  template<class K, class V>  
  bool BalancedTree<K, V>::InOrderIterator::isEmpty() const
  {
    if (*curr == nullptr)
      return true;
    return false;
  }


  // Check if current node is last
  template<class K, class V>  
  bool BalancedTree<K, V>::InOrderIterator::hasNext() const
  {
    if ((*curr)->isLeft)
      return true;
    if ((*curr)->treeNode->right == nullptr)
      return false;
    return true;
  }

  // Go to the next key
  template<class K, class V>  
  bool BalancedTree<K, V>::InOrderIterator::next() const
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

template <class K>
class BalancedTree<K, std::nullptr_t>
{
private:
  struct Node
  {
    K key;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0;

    Node(K const & key):
      key(key)
    { }

    static Node* copyTree(Node* nodeToCopy)
    {
      if (nodeToCopy == nullptr)
      {
        return nullptr;
      }
      Node* node = new Node(nodeToCopy->key);
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
      K key = node1->key;
      node1->key = node2->key;
      node2->key = key;
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

    static Node* create(Node* node, K const & key) {
      if (node == nullptr) {
        return new Node(key);
      }
      if (key < node->key) {
        node->left = findOrCreate(node->left, key);
      } 
      else if (key > node->key) {
        node->right = findOrCreate(node->right, key);
      }
      else { 
        return node;
      }
      
      updateHeight(node);
      balance(node);
      return node;
    }

    static Node* remove(Node* node, K const & key) {
        if (node == nullptr) {
          return nullptr; 
        } 
        if (key < node->key) {
          node->left = remove(node->left, key);
        } 
        else if (key > node->key) {
          node->right = remove(node->right, key);
        } 
        else {
          if (node->left == nullptr) {
            Node* buffer = node->right;
            delete node;
            return buffer;
          } else if (node->right == nullptr) {
            Node* buffer = node->left;
            delete node;
            return buffer;
          }

          Node* buffer = minKeyNode(node->right);
          node->key = buffer->key; 
          node->right = remove(node->right, buffer->key); 
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

    static Node* maxKeyNode(Node* node)
    {
      if (node->right == nullptr)
        return node;
      return maxKeyNode(node->right);
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
    friend class BalancedTree;
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
      if (treeNode == nullptr)
      {
        (*curr) = nullptr;
        return;
      }
      
      (*curr) = new ChainNode(nullptr, treeNode, false);
      while ((*curr)->treeNode->left != nullptr)
      {
        ChainNode* buffer = new ChainNode((*curr), (*curr)->treeNode->left, true);
        (*curr) = buffer;
      }
    }

  public:
    // Destructor
    ~InOrderIterator();

    // Get const link to current key
    K const & key() const;

    // Check if empty
    bool isEmpty() const;

    // Check if current node is last
    bool hasNext() const;

    // Go to the next key
    bool next() const;   
  };

/* Constructors */
  // Constructor of empty tree
  BalancedTree();

  // Copy-constructor
  BalancedTree(BalancedTree const &);

/* Destructor */
  ~BalancedTree();

/* Getters */
  // Get number of nodes
  size_t getCount() const;

  // Does tree contain key
  bool containsKey(K const &) const;

  // Get minimal key
  K getMinKey() const;

  // Get maximal key
  K getMaxKey() const;

/* Modifying Operations */
  // Add by key
  void add(K const &);

  // Remove by key
  void remove(K const &);

  // Delete all tree
  void removeAllKeys();

/* Operators */
  // Const version of dereferencing by key
  bool operator[](K const &) const;

/* Iterators */
  /* Standart ascending InOrder iterator */
  InOrderIterator createInOrderIterator();

  /* Standart ascending InOrder iterator without permission to change values */
  const InOrderIterator createInOrderIterator() const;
};

/* Constructors */
  // Constructor of zero-array
  template <class K>
  BalancedTree<K, std::nullptr_t>::BalancedTree()
  { }

  // Copy-constructor
  template <class K>
  BalancedTree<K, std::nullptr_t>::BalancedTree(BalancedTree const & other)
  {
    head = Node::copyTree(other.head);
  }

/* Destructor */
  template <class K>
  BalancedTree<K, std::nullptr_t>::~BalancedTree()
  {
    removeAllKeys();
  }

/* Getters */
  // Get size
  template <class K>
  size_t BalancedTree<K, std::nullptr_t>::getCount() const 
  {
    return Node::countNodes(head);
  }

  // Check if BalancedTree contains a key
  template <class K>
  bool BalancedTree<K, std::nullptr_t>::containsKey(K const & key) const 
  {
    if (head == nullptr)
      return false;
    Node* result = Node::find(head, key);
    return (result != nullptr);
  }

  // Get minimal key
  template<class K> 
  K BalancedTree<K, std::nullptr_t>::getMinKey() const
  {
    Node* minNode = Node::minKeyNode(head);
    return minNode->key;
  }

  // Get maximal key
  template<class K> 
  K BalancedTree<K, std::nullptr_t>::getMaxKey() const
  {
    Node* maxNode = Node::maxKeyNode(head);
    return maxNode->key;
  }

/* Modifying Operations */
  // Add by key
  template <class K>
  void BalancedTree<K, std::nullptr_t>::add(K const & key)
  {
    head = Node::create(head, key);
  }


  // Remove
  template <class K>
  void BalancedTree<K, std::nullptr_t>::remove(K const & key)  
  {
    head = Node::remove(head, key);
  }
  
  // Delete all tree
  template <class K>
  void BalancedTree<K, std::nullptr_t>::removeAllKeys()  
  {
    Node::deleteTree(head);
    head = nullptr;
  }


/* Iterators */
  /* Standart ascending InOrder iterator */
  template <class K> 
  typename BalancedTree<K, std::nullptr_t>::InOrderIterator BalancedTree<K, std::nullptr_t>::createInOrderIterator()
  {
    return typename BalancedTree<K, std::nullptr_t>::InOrderIterator::InOrderIterator(head);
  }

  /* Standart ascending InOrder iterator without permission to change values */
  template <class K> 
  const typename BalancedTree<K, std::nullptr_t>::InOrderIterator BalancedTree<K, std::nullptr_t>::createInOrderIterator() const
  {
    return typename BalancedTree<K, std::nullptr_t>::InOrderIterator::InOrderIterator(head);
  }

/* InOrder Iterator */
  // Destructor
  template<class K> 
  BalancedTree<K, std::nullptr_t>::InOrderIterator::~InOrderIterator()
  {
    if ((*curr) == nullptr)
    {
      delete curr;
      return;
    }
    while ((*curr)->previous != nullptr)
    {
      ChainNode* prev = (*curr)->previous;
      delete (*curr);
      (*curr) = prev;
    }
    delete *curr;
    delete curr;
  }

  // Get const link to current key
  template<class K>  
  const K &BalancedTree<K, std::nullptr_t>::InOrderIterator::key() const
  { 
    return (*curr)->treeNode->key;
  }

  // Check if empty
  template<class K>  
  bool BalancedTree<K, std::nullptr_t>::InOrderIterator::isEmpty() const
  {
    if (*curr == nullptr)
      return true;
    return false;
  }


  // Check if current node is last
  template<class K>  
  bool BalancedTree<K, std::nullptr_t>::InOrderIterator::hasNext() const
  {
    if ((*curr)->isLeft)
      return true;
    if ((*curr)->treeNode->right == nullptr)
      return false;
    return true;
  }

  // Go to the next key
  template<class K>  
  bool BalancedTree<K, std::nullptr_t>::InOrderIterator::next() const
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