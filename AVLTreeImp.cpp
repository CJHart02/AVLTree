#include <iostream>
#include <iomanip>
#include <fstream>
#include "AVLTree.h"

AVL::AVL()
{
	root = nullptr;
	current = nullptr;
}


void AVL::build(int info)
{
    if (root == nullptr)
    {
        node *temp = new node;
        temp -> num = info;
        temp -> left = nullptr;
        temp -> right = nullptr;
        temp -> previous = nullptr;

        root = temp;
        current = temp;
        if (nodes == 0)
        {
            nodes = 1;
        }
        else if (nodes > 1)
        {
            nodes++;
        }
        std::cout << info << " has been inserted at root." << std::endl;
    }
    else if ((info < current -> num) && (current -> left == nullptr))
    {
        node *temp = new node;
        temp -> num = info;
        temp -> left = nullptr;
        temp -> right = nullptr;
        temp -> previous = nullptr;

        current -> left = temp;
        current = root;
        if (nodes == 0)
        {
            nodes = 1;
        }
        else if (nodes > 0)
        {
            nodes++;
        }
        std::cout << info << " inserted" << std::endl;
    }
    else if ((info < current -> num) && (current -> left != nullptr))
    {
        current = current -> left;
        build(info);
    }
    else if ((info > current -> num) && (current -> right == nullptr))
    {
        node *temp = new node;
        temp -> num = info;
        temp -> left = nullptr;
        temp -> right = nullptr;
        temp -> previous = nullptr;

        current -> right = temp;
        current = root;
        if (nodes == 0)
        {
            nodes = 1;
        }
        else if (nodes > 0)
        {
            nodes++;
        }
        std::cout << info << " inserted" << std::endl;
    }
    else if ((info > current -> num) && (current -> right != nullptr))
    {
        current = current -> right;
        build(info);
    }
    else if (info == current -> num)
    {
        current = root;
    }
}
int AVL::soManyLeafs(node* node)
{
    if(node == nullptr)
    {
        return 0;
    }
    if(node -> left == nullptr && node -> right == nullptr)
    {
        return 1;
    }
    else
    {
        return soManyLeafs(node -> left) + soManyLeafs(node -> right);
    }
}

int AVL::treeHeight(node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {

        int l = treeHeight(node -> left);
        int r = treeHeight(node -> right);

        if (l > r)
        {
            return (l + 1);
        }
        else
        {
            return (r + 1);
        }
    }
}

int AVL::printHeight()
{
    int height = treeHeight(root);
    return height;
}


void AVL::inOrder(node* node, std::ostream &out)
{
    std::ofstream outFile;
    if (node != nullptr)
	{
		if (node -> left)
        {
            inOrder(node -> left, out);
        }
		std::cout << node -> num << ", ";
		out << node -> num << ", ";
		if (node -> right)
        {
            inOrder(node -> right, out);
        }
	}
	else
        return;
}

void AVL::preOrder(node* node, std::ostream &out)
{
    std::ofstream outFile;
    if (node != nullptr)
	{
		std::cout << node -> num << ", ";
        out << node -> num << ", ";
		if (node -> left)
        {
            preOrder(node -> left, out);
        }
		if (node -> right)
        {
            preOrder(node -> right, out);
        }
	}
	else
        return;
}

void AVL::postOrder(node* node, std::ostream &out)
{
    std::ofstream outFile;
    if(node != nullptr)
	{
		if (node -> left)
        {
            postOrder(node -> left, out);
        }
		if (node -> right)
        {
            postOrder(node -> right, out);
        }
		std::cout << node -> num << ", ";
		out << node -> num << ", ";
	}
	else
        return;
}

bool AVL::isFull(int count, int max)
{
    if (count == max)
        return true;
    else
        return false;
}

int AVL::smallestNode()
{
    current = root;
    while (current -> left != nullptr)
    {
        current = current -> left;
    }
    if (current -> left == nullptr)
    {
        return current -> num;
    }
}

int AVL::largestNode()
{
    current = root;
    while (current -> right != nullptr)
    {
        current = current -> right;
    }
    if (current -> right == nullptr)
    {
        return current -> num;
    }
}

int AVL::howManyNodes()
{
    return nodes;
}

int AVL::howManyLeafs()
{
    leafs = soManyLeafs(root);
    return leafs;
}

void AVL::print_inOrder(std::ostream &out)
{
    std::ofstream outFile;
    std::cout << "\n" << "Inorder" << std::endl;
    out << "Inorder" << std::endl;
    inOrder(root, out);
    std::cout << std::endl;
}

void AVL::print_preOrder(std::ostream &out)
{
    std::ofstream outFile;
    std::cout << "\n" << "Preorder" << std::endl;
    out << "\n \n" << "Preorder" << std::endl;
    preOrder(root, out);
    std::cout << std::endl;
}

void AVL::print_postOrder(std::ostream &out)
{
    std::ofstream outFile;
    std::cout << "\n" << "Postorder" << std::endl;
    out << "\n \n" << "Postorder" << std::endl;
    postOrder(root, out);
    std::cout << std::endl;
}

void AVL::checkBalance(node* node)
{
    node -> balance = treeHeight(node -> right) - treeHeight(node -> left);
}

void AVL::balance(node* node)
{
    checkBalance(node);

    if (node -> balance == -2)
    {
        if (treeHeight(node -> left -> left) <= treeHeight(node -> left -> right))
        {
            node = leftRight(node);
        }
        else
        {
            node = rightRight(node);
        }
    }
    else if (node -> balance == 2)
    {
        if (treeHeight(node -> right -> left <= treeHeight(node -> right -> right))
        {
            node = leftLeft(node);
        }
        else
        {
            node = rightLeft(node);
        }
    }

    if(node -> previous != nullptr)
    {
        balance(node -> previous);
    }
    else if (node -> previous == nullptr)
    {
        root = node;
    }
}

node* AVL::leftLeft(node* node)
{
    node *temp;
    temp = node -> right;
    temp -> previous = node -> previous;
    node -> right = temp -> left;

    if (node -> right != nullptr)
    {
        node -> right -> previous = node;
    }

    temp -> left = node;
    node -> previous = temp;

    if (temp -> previous != nullptr)
    {
        if (temp -> previous == node)
        {
            temp -> previous -> right = temp;
        }
        else
        {
            temp -> previous -> left = temp;
        }
    }

    checkBalance(node);
    checkBalance(temp);

    return temp;
}

node* AVL::leftRight(node* node)
{
    node -> right = leftLeft(node -> right);
    return rightRight(node);
}

node* AVL::rightRight(node* node)
{
    node *temp;
    temp = node -> left;

    temp -> previous = node -> previous;
    node -> left = temp -> right;

    if (node -> left != nullptr)
    {
        node -> left -> previous = node;
    }

    temp -> right = node;
    node -> previous = temp;

    if (temp -> previous != nullptr)
    {
        if (temp -> previous -> right == node)
        {
            temp -> previous -> right = temp;
        }
        else
        {
            temp -> previous -> left = temp;
        }
    }

    checkBalance(node);
    checkBalance(temp);

    return temp;
}

node* AVL::rightLeft(node* node)
{
    node -> right = rightRight(node -> right);
    return -> leftLeft(node);
}
