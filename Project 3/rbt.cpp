// Implementing Red-Black Tree in C++

#include <iostream>

namespace RBT
{
  struct Node
  {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
    int color;
  };

  Node *createNewNode(int data, std::string name)
  {
    Node *newNode = new Node;
    newNode->data = data;
    newNode->name = name;
    newNode->parent = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->color = 1; // new node is always red
    return newNode;
  }
}

class RedBlackTree
{
private:
  RBT::Node *root;

  // This section contains helper functions
  // The reason why I implemented many helper functions is because I want to implement them as recursive.
  // In order to do that, I need to update root as an argument. But the function used in the main does not contain root as a parameter.

  // Helper function to perform inorder traverse populate the array
  void helper_inorder(RBT::Node *node, std::pair<std::string, int> orderedDataRB[], int &index)
  {
    if (node != nullptr)
    {
      // std::string c;
      // if ((node->color) == 0)
      //   c = " (B)";
      // else
      //   c = " (R)";
      // Traverse the left subtree
      helper_inorder(node->left, orderedDataRB, index);

      // Process the current node (store data in the array)
      orderedDataRB[index] = std::make_pair(node->name, node->data);
      // std::cout << orderedDataRB[index].first << orderedDataRB[index].second << c << std::endl;
      index++;

      // Traverse the right subtree
      helper_inorder(node->right, orderedDataRB, index);
    }
  }
  // Helper function to perform preorder traverse populate the array
  void helper_preorder(RBT::Node *node, std::pair<std::string, int> orderedDataRB[], int &index)
  {
    if (node != nullptr)
    {
      // Process the current node (store data in the array)
      orderedDataRB[index] = std::make_pair(node->name, node->data);
      // std::cout << orderedDataBST[index].first << orderedDataBST[index].second << std::endl;
      index++;
      // Traverse the left subtree
      helper_preorder(node->left, orderedDataRB, index);
      // Traverse the right subtree
      helper_preorder(node->right, orderedDataRB, index);
    }
  }
  // Helper function to perform postorder traverse populate the array
  void helper_postorder(RBT::Node *node, std::pair<std::string, int> orderedDataRB[], int &index)
  {
    if (node != nullptr)
    {
      // Traverse the left subtree
      helper_postorder(node->left, orderedDataRB, index);
      // Traverse the right subtree
      helper_postorder(node->right, orderedDataRB, index);
      // Process the current node (store data in the array)
      orderedDataRB[index] = std::make_pair(node->name, node->data);
      // std::cout << orderedDataBST[index].first << orderedDataBST[index].second << std::endl;
      index++;
    }
  }

  // Helper function to get the height of the BST
  int helper_getHeight(RBT::Node *node)
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
  int helper_getTotalNodes(RBT::Node *node)
  {
    if (node == nullptr)
    {
      return 0; // Number of nodes in an empty tree is 0
    }

    return 1 + helper_getTotalNodes(node->left) + helper_getTotalNodes(node->right);
  }

  // Left rotate function to use in insert and rbInsertFixup
  void leftRotate(RBT::Node *x) // I implemented pseudo code form text book "Intro. to the Algortihms"
  {
    RBT::Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
      y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  // Right rotate function to use in insert and rbInsertFixup
  void rightRotate(RBT::Node *y) // I implemented pseudo code form text book "Intro. to the Algortihms"
  {
    RBT::Node *x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
      x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nullptr)
      root = x;
    else if (y == y->parent->left)
      y->parent->left = x;
    else
      y->parent->right = x;
    x->right = y;
    y->parent = x;
  }

  // Helper function to maintain the Red-Black Tree properties after insertion,
  // ensuring that the tree remains a valid Red-Black Tree.
  void rbInsertFixup(RBT::Node *z) // I implemented pseudo code form text book "Intro. to the Algortihms"
  {
    while (z->parent != nullptr && z->parent->color == 1)
    {
      if (z->parent == z->parent->parent->left)
      {
        RBT::Node *y = z->parent->parent->right;
        if (y != nullptr && y->color == 1)
        {
          z->parent->color = 0;         // Set parent to black
          y->color = 0;                 // Set uncle to black
          z->parent->parent->color = 1; // Set grandparent to red
          z = z->parent->parent;
        }
        else
        {
          if (z == z->parent->right)
          {
            z = z->parent;
            leftRotate(z);
          }
          z->parent->color = 0;         // Set parent to black
          z->parent->parent->color = 1; // Set grandparent to red
          rightRotate(z->parent->parent);
        }
      }
      else
      {
        RBT::Node *y = z->parent->parent->left;
        if (y != nullptr && y->color == 1)
        {
          z->parent->color = 0;
          y->color = 0;
          z->parent->parent->color = 1;
          z = z->parent->parent;
        }
        else
        {
          if (z == z->parent->left)
          {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->color = 0;
          z->parent->parent->color = 1;
          leftRotate(z->parent->parent);
        }
      }
    }
    root->color = 0; // Ensure root is black
  }

  // Helper Transplant function to implement delete operation
  // TRANSPLANT function
  void transplant(RBT::Node *u, RBT::Node *v) // I implemented pseudo code form text book "Intro. to the Algortihms"
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
  RBT::Node *treeMinimum(RBT::Node *x) // for use delete function
  {
    while (x->left != nullptr)
    {
      x = x->left;
    }
    return x;
  }

  // Helper function to ensure the Red-Black Tree property after deletion
  void rbDeleteFixup(RBT::Node *x) // I implemented pseudo code form text book "Intro. to the Algortihms"
  {
    if (x != nullptr && x->parent != nullptr)
    {
      while (x != root && x->color == 0)
      {

        if (x == x->parent->left)
        {
          RBT::Node *w = x->parent->right;

          if (w->color == 1)
          {
            w->color = 0;
            x->parent->color = 1;
            leftRotate(x->parent);
            w = x->parent->right;
          }

          if (w->left->color == 0 && w->right->color == 0)
          {
            w->color = 1;
            x = x->parent;
          }
          else
          {
            if (w->right->color == 0)
            {
              w->left->color = 0;
              w->color = 1;
              rightRotate(w);
              w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = 0;
            w->right->color = 0;
            leftRotate(x->parent);
            x = root;
          }
        }
        else
        {
          RBT::Node *w = x->parent->left;

          if (w->color == 1)
          {
            w->color = 0;
            x->parent->color = 1;
            rightRotate(x->parent);
            w = x->parent->left;
          }

          if (w->right->color == 0 && w->left->color == 0)
          {
            w->color = 1;
            x = x->parent;
          }
          else
          {
            if (w->left->color == 0)
            {
              w->right->color = 0;
              w->color = 1;
              leftRotate(w);
              w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = 0;
            w->left->color = 0;
            rightRotate(x->parent);
            x = root;
          }
        }
      }
      x->color = 0;
    }
    else
    {
      x = root;
    }
  }

public:
  RedBlackTree()
  {
    root = nullptr;
  }

  void preorder(std::pair<std::string, int> orderedDataRB[], int length) // Using helper functions for recursive
  {
    helper_preorder(root, orderedDataRB, length);
  }

  void inorder(std::pair<std::string, int> orderedDataRB[], int length)
  {
    helper_inorder(root, orderedDataRB, length);
  }

  void postorder(std::pair<std::string, int> orderedDataRB[], int length)
  {
    helper_postorder(root, orderedDataRB, length);
  }

  // Function to search for a node in the BST based on testPopulation
  RBT::Node *searchTree(int testPopulation) // I implemented pseudo code from textbook
  {
    RBT::Node *node = root;
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

  RBT::Node *successor(RBT::Node *node)
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
      RBT::Node *temp = node->parent;
      while (temp != nullptr && node == temp->right)
      {
        node = temp;
        temp = temp->parent;
      }
      return temp;
    }
  }

  RBT::Node *predecessor(RBT::Node *node)
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
      RBT::Node *temp = node->parent;
      while (temp != nullptr && node == temp->left)
      {
        node = temp;
        temp = temp->parent;
      }
      return temp;
    }
  }

  void insert(const std::string &name, int data) // I implemented pseudo code from textbook
  {
    RBT::Node *z = RBT::createNewNode(data, name);
    RBT::Node *y = nullptr;
    RBT::Node *x = root;

    while (x != nullptr)
    {
      y = x;
      if (z->data < x->data)
        x = x->left;
      else
        x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
      root = z;
    else if (z->data < y->data)
      y->left = z;
    else
      y->right = z;

    rbInsertFixup(z);
  }

  // Tree Delete function
  void deleteNode(int testPopulation)
  {
    RBT::Node *z = searchTree(testPopulation);
    RBT::Node *y = z;
    RBT::Node *x;
    int yOriginalColor = y->color;

    if (z->left == nullptr && z->right == nullptr) // If both child are nill
    {
      if (z->parent->right == z) // if it is right child then delete delete the connection bewtween its parent
        z->parent->right = nullptr;
      if (z->parent->left == z) // if it is left child then delete delete the connection bewtween its parent
        z->parent->left = nullptr;
      delete z;
      return;
    }
    else if (z->left == nullptr) // Left child is nil
    {
      x = z->right;
      transplant(z, z->right);
    }
    else if (z->right == nullptr) // Right child is nil
    {
      x = z->left;
      transplant(z, z->left);
    }
    else // Neither childs are nil
    {
      y = treeMinimum(z->right);
      yOriginalColor = y->color;
      x = y->right; // x could be nill or greater than y
      if (y != z->right)
      {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      else
      {
        if (x != nullptr) // I added control block beacuse it gives segmentation fault for pop1
        {
          x->parent = y;
        }
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }

    if (yOriginalColor == 0)
    {
      rbDeleteFixup(x);
    }
  }

  int getHeight()
  {
    return helper_getHeight(root);
  }

  RBT::Node *getMaximum()
  {
    RBT::Node *node = root;
    while (node != nullptr && node->right != nullptr)
    {
      node = node->right; // find the right most element
    }
    return node;
  }

  RBT::Node *getMinimum()
  {
    RBT::Node *node = root;
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