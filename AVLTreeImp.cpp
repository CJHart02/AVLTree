#include "AVLTree.h"
#include <fstream>
#include <iomanip>
#include <iostream>

AVL::AVL() {
  root = nullptr;
  current = nullptr;
}

void AVL::build(int info) {
  if (root == nullptr) {
    node *temp = new node();
    temp->num = info;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->previous = nullptr;

    root = temp;
    current = temp;
    if (nodes == 0) {
      nodes = 1;
    } else if (nodes > 1) {
      nodes++;
    }
    std::cout << info << " has been inserted at root." << std::endl;
  } else if ((info < current->num) && (current->left == nullptr)) {
    node *temp = new node;
    temp->num = info;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->previous = nullptr;

    current->left = temp;
    current = root;
    if (nodes == 0) {
      nodes = 1;
    } else if (nodes > 0) {
      nodes++;
    }
    std::cout << info << " inserted" << std::endl;
  } else if ((info < current->num) && (current->left != nullptr)) {
    current = current->left;
    build(info);
  } else if ((info > current->num) && (current->right == nullptr)) {
    node *temp = new node;
    temp->num = info;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->previous = nullptr;

    current->right = temp;
    current = root;
    if (nodes == 0) {
      nodes = 1;
    } else if (nodes > 0) {
      nodes++;
    }
    std::cout << info << " inserted" << std::endl;
  } else if ((info > current->num) && (current->right != nullptr)) {
    current = current->right;
    build(info);
  } else if (info == current->num) {
    current = root;
  }
}
int AVL::soManyLeafs(node *Node) {
  if (Node == nullptr) {
    return 0;
  }
  if (Node->left == nullptr && Node->right == nullptr) {
    return 1;
  } else {
    return soManyLeafs(Node->left) + soManyLeafs(Node->right);
  }
}

int AVL::treeHeight(node *Node) {
  if (Node == nullptr) {
    return 0;
  } else {

    int l = treeHeight(Node->left);
    int r = treeHeight(Node->right);

    if (l > r) {
      return (l + 1);
    } else {
      return (r + 1);
    }
  }
}

int AVL::printHeight() {
  int height = treeHeight(root);
  return height;
}

void AVL::inOrder(node *Node, std::ostream &out) {
  std::ofstream outFile;
  if (Node != nullptr) {
    if (Node->left) {
      inOrder(Node->left, out);
    }
    std::cout << Node->num << ", ";
    out << Node->num << ", ";
    if (Node->right) {
      inOrder(Node->right, out);
    }
  } else
    return;
}

void AVL::preOrder(node *Node, std::ostream &out) {
  std::ofstream outFile;
  if (Node != nullptr) {
    std::cout << Node->num << ", ";
    out << Node->num << ", ";
    if (Node->left) {
      preOrder(Node->left, out);
    }
    if (Node->right) {
      preOrder(Node->right, out);
    }
  } else
    return;
}

void AVL::postOrder(node *Node, std::ostream &out) {
  std::ofstream outFile;
  if (Node != nullptr) {
    if (Node->left) {
      postOrder(Node->left, out);
    }
    if (Node->right) {
      postOrder(Node->right, out);
    }
    std::cout << Node->num << ", ";
    out << Node->num << ", ";
  } else
    return;
}

bool AVL::isFull(int count, int max) {
  if (count == max)
    return true;
  else
    return false;
}

int AVL::smallestNode() {
  current = root;
  while (current->left != nullptr) {
    current = current->left;
  }
  if (current->left == nullptr) {
    return current->num;
  }
}

int AVL::largestNode() {
  current = root;
  while (current->right != nullptr) {
    current = current->right;
  }
  if (current->right == nullptr) {
    return current->num;
  }
}

int AVL::howManyNodes() { return nodes; }

int AVL::howManyLeafs() {
  leafs = soManyLeafs(root);
  return leafs;
}

void AVL::print_inOrder(std::ostream &out) {
  std::ofstream outFile;
  std::cout << "\n"
            << "Inorder" << std::endl;
  out << "Inorder" << std::endl;
  inOrder(root, out);
  std::cout << std::endl;
}

void AVL::print_preOrder(std::ostream &out) {
  std::ofstream outFile;
  std::cout << "\n"
            << "Preorder" << std::endl;
  out << "\n \n"
      << "Preorder" << std::endl;
  preOrder(root, out);
  std::cout << std::endl;
}

void AVL::print_postOrder(std::ostream &out) {
  std::ofstream outFile;
  std::cout << "\n"
            << "Postorder" << std::endl;
  out << "\n \n"
      << "Postorder" << std::endl;
  postOrder(root, out);
  std::cout << std::endl;
}

void AVL::checkBalance(node *Node) {
  Node->balance = treeHeight(Node->right) - treeHeight(Node->left);
}

void AVL::balance(node *Node) {
  checkBalance(Node);

  if (Node->balance == -2) {
    if (treeHeight(Node->left->left) <= treeHeight(Node->left->right)) {
      Node = leftRight(Node);
    } else {
      Node = rightRight(Node);
    }
  } else if (Node->balance == 2) {
    if (treeHeight(Node->right->left) <= treeHeight(Node->right->right)) {
      Node = leftLeft(Node);
    } else {
      Node = rightLeft(Node);
    }
  }

  if (Node->previous != nullptr) {
    balance(Node->previous);
  } else if (Node->previous == nullptr) {
    root = Node;
  }
}

node *AVL::leftLeft(node *Node) {
  node *temp;
  temp = Node->right;
  temp->previous = Node->previous;
  Node->right = temp->left;

  if (Node->right != nullptr) {
    Node->right->previous = Node;
  }

  temp->left = Node;
  Node->previous = temp;

  if (temp->previous != nullptr) {
    if (temp->previous == Node) {
      temp->previous->right = temp;
    } else {
      temp->previous->left = temp;
    }
  }

  checkBalance(Node);
  checkBalance(temp);

  return temp;
}

node *AVL::leftRight(node *Node) {
  Node->right = leftLeft(Node->right);
  return rightRight(Node);
}

node *AVL::rightRight(node *Node) {
  node *temp;
  temp = Node->left;

  temp->previous = Node->previous;
  Node->left = temp->right;

  if (Node->left != nullptr) {
    Node->left->previous = Node;
  }

  temp->right = Node;
  Node->previous = temp;

  if (temp->previous != nullptr) {
    if (temp->previous->right == Node) {
      temp->previous->right = temp;
    } else {
      temp->previous->left = temp;
    }
  }

  checkBalance(Node);
  checkBalance(temp);

  return temp;
}

node *AVL::rightLeft(node *Node) {
  Node->right = rightRight(Node->right);
  return leftLeft(Node);
}
