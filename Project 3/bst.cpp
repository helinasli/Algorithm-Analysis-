//  Implementing Binary Search Tree in C++

#include <iostream>

namespace BST
{
  struct Node
  {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
  };

  Node *createNewNode(int data, const std::string &name, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr)
  {
    Node *newNode = new Node;
    newNode->data = data;
    newNode->name = name;
    newNode->parent = parent;
    newNode->left = left;
    newNode->right = right;
    return newNode;
  }
}

class BinarySearchTree
{
private:
  BST::Node *root;

  // This section contains helper functions
  // The reason why I implemented many helper functions is because I want to implement them as recursive.
  // In order to do that, I need to update root as an argument. But the function used in the main does not contain root as a parameter.
  // Helper function to perform inorder traverse populate the array
  void helper_inorder(BST::Node *node, std::pair<std::string, int> orderedDataBST[], int &index)
  {
    if (node != nullptr)
    {
      // Traverse the left subtree
      helper_inorder(node->left, orderedDataBST, index);

      // Process the current node (store data in the array)
      orderedDataBST[index] = std::make_pair(node->name, node->data);
      // std::cout << orderedDataBST[index].first << orderedDataBST[index].second << std::endl;
      index++;

      // Traverse the right subtree
      helper_inorder(node->right, orderedDataBST, index);
    }
  }
  // Helper function to perform preorder traverse populate the array
  void helper_preorder(BST::Node *node, std::pair<std::string, int> orderedDataBST[], int &index)
  {
    if (node != nullptr)
    {
      // Process the current node (store data in the array)
      orderedDataBST[index] = std::make_pair(node->name, node->data);
      // std::cout << orderedDataBST[index].first << orderedDataBST[index].second << std::endl;
      index++;
      // Traverse the left subtree
      helper_preorder(node->left, orderedDataBST, index);
      // Traverse the right subtree
      helper_preorder(node->right, orderedDataBST, index);
    }
  }
  // Helper function to perform postorder traverse populate the array
  void helper_postorder(BST::Node *node, std::pair<std::string, int> orderedDataBST[], int &index)
  {
    if (node != nullptr)
    {
      // Traverse the left subtree
      helper_postorder(node->left, orderedDataBST, index);
      // Traverse the right subtree
      helper_postorder(node->right, orderedDataBST, index);
      // Process the current node (store data in the array)
      orderedDataBST[index] = std::make_pair(node->name, node->data);
      // std::cout << orderedDataBST[index].first << orderedDataBST[index].second << std::endl;
      index++;
    }
  }

  // Helper function to get the height of the BST
  int helper_getHeight(BST::Node *node)
  {
    if (node == nullptr)
    {
      return -1; // Height of an empty tree is -1
    }

    int leftHeight = helper_getHeight(node->left);
    int rightHeight = helper_getHeight(node->right);

    return 1 + std::max(leftHeight, rightHeight); // Recursively calculate the height of the BST
  }

  // Helper function to get the total number of nodes in the BST
  int helper_getTotalNodes(BST::Node *node)
  {
    if (node == nullptr)
    {
      return 0; // Number of nodes in an empty tree is 0
    }

    return 1 + helper_getTotalNodes(node->left) + helper_getTotalNodes(node->right);
  }

  // Helper Transplant function to implement delete operation
  // TRANSPLANT function
  void transplant(BST::Node *u, BST::Node *v)
  {
    if (u->parent == nullptr)
    {
      root = v;
    }
    else if (u == u->parent->left)
    {
      u->parent->left = v;
    }
    else
    {
      u->parent->right = v;
    }

    if (v != nullptr)
    {
      v->parent = u->parent;
    }
  }

  // TREE-MINIMUM function to use in delete node function
  BST::Node *treeMinimum(BST::Node *x)
  {
    while (x->left != nullptr)
    {
      x = x->left;
    }
    return x;
  }
  // Public Functions
public:
  BinarySearchTree()
  {
    root = nullptr;
  }

  void preorder(std::pair<std::string, int> orderedDataBST[], int length)
  {
    helper_preorder(root, orderedDataBST, length);
  }

  void inorder(std::pair<std::string, int> orderedDataBST[], int length)
  {
    helper_inorder(root, orderedDataBST, length);
  }

  void postorder(std::pair<std::string, int> orderedDataBST[], int length)
  {
    helper_postorder(root, orderedDataBST, length);
  }

  // Function to search for a node in the BST based on testPopulation
  BST::Node *searchTree(int testPopulation)
  {
    BST::Node *node = root;
    while (node != nullptr && testPopulation != node->data)
    {
      if (testPopulation < node->data)
      {
        node = node->left;
      }
      else
      {
        node = node->right;
      }
    }
    return node;
  }

  BST::Node *successor(BST::Node *node)
  {
    if (node->right != nullptr)
    {
      // Find leftmost node in the right subtree
      node = node->right;
      while (node != nullptr && node->left != nullptr)
      {
        node = node->left; // find the left most element
      }
      return node;
    }
    else
    { // find the lowest ancestor of node whose left child is an ancestor of node
      BST::Node *temp = node->parent;
      while (temp != nullptr && node == temp->right)
      {
        node = temp;
        temp = temp->parent;
      }
      return temp;
    }
  }

  BST::Node *predecessor(BST::Node *node)
  {
    if (node->left != nullptr)
    {
      // Find rightmost node in the left subtree
      node = node->left;
      while (node != nullptr && node->right != nullptr)
      {
        node = node->right; // find the rightmost element
      }
      return node;
    }
    else
    { // find the lowest ancestor of node whose right child is an ancestor of node
      BST::Node *temp = node->parent;
      while (temp != nullptr && node == temp->left)
      {
        node = temp;
        temp = temp->parent;
      }
      return temp;
    }
  }

  void insert(std::string name, int data)
  {
    BST::Node *newNode = BST::createNewNode(data, name);
    BST::Node *x = root;
    BST::Node *y = nullptr;

    while (x != nullptr)
    {
      y = x;
      if (newNode->data < x->data)
        x = x->left;
      else
        x = x->right;
    }

    newNode->parent = y;

    if (y == nullptr)
      root = newNode;
    else if (newNode->data < y->data)
      y->left = newNode;
    else
      y->right = newNode;
  }

  // Tree Delete function
  void deleteNode(int testPopulation)
  {
    BST::Node *z = searchTree(testPopulation);
    if (z->left == nullptr)
    {
      transplant(z, z->right); // replace by its right child
    }
    else if (z->right == nullptr)
    {
      transplant(z, z->left); // replace by its left child
    }
    else
    {
      BST::Node *y = treeMinimum(z->right); // is ’ssuccessor

      if (y->parent != z) // is farther down the tree?
      {
        transplant(y, y->right); // replace by its right child
        y->right = z->right;     // ’s right child becomes
        y->right->parent = y;    // ’s right child
      }

      transplant(z, y);    // replace by its successor
      y->left = z->left;   // and give z’s left child to y,
      y->left->parent = y; // which had no left child
    }

    delete z; // Assuming the Node has dynamic memory allocation
  }

  int getHeight()
  {
    return helper_getHeight(root);
  }

  // Function to get the maximum element in the BST recursively
  BST::Node *getMaximum()
  {
    BST::Node *node = root;
    while (node != nullptr && node->right != nullptr)
    {
      node = node->right; // find the right most element
    }
    return node;
  }

  // Function to get the minimum element in the BST
  BST::Node *getMinimum()
  {
    BST::Node *node = root;
    while (node != nullptr && node->left != nullptr)
    {
      node = node->left; // find the left most element
    }
    return node;
  }

  int getTotalNodes()
  {
    return helper_getTotalNodes(root);
  }
};