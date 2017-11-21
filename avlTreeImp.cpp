#include <iostream>
#include <iomanip>
#include <fstream>
#include "avlTree.h"

using namespace std;

AVL::AVL()
{
	root = nullptr;
	current = nullptr;
}


void AVL::build(int info)
{

    if (root == nullptr)
    {
        Node *temp = new Node;
        temp -> num = info;
        temp -> left = nullptr;
        temp -> right = nullptr;
        temp -> previous = nullptr;

        root = temp;
        current = temp;
        nodes = 1;
        std::cout << info << " has been inserted at root." << std::endl;
    }
    else if ((info < current -> num) && (current -> left == nullptr))
    {
        Node *temp = new Node;
        temp -> num = info;
        temp -> left = nullptr;
        temp -> right = nullptr;
        temp -> previous = nullptr;

        current -> left = temp;

        std::cout << info << " inserted" << std::endl;

        balance(current);

        current = root;
        if (nodes == 0)
        {
            nodes = 1;
        }
        else if (nodes > 0)
        {
            nodes++;
        }

    }
    else if ((info < current -> num) && (current -> left != nullptr))
    {
        current = current -> left;
        build(info);
    }
    else if ((info > current -> num) && (current -> right == nullptr))
    {
        Node *temp = new Node;
        temp -> num = info;
        temp -> left = nullptr;
        temp -> right = nullptr;
        temp -> previous = nullptr;

        current -> right = temp;

        std::cout << info << " inserted" << std::endl;

        balance(current);

        current = root;

        if (nodes == 0)
        {
            nodes = 1;
        }
        else if (nodes > 0)
        {
            nodes++;
        }


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


    /*if (root == nullptr)
    {
        root -> num = info;
        root -> left = nullptr;
        root -> right = nullptr;
        root -> previous = nullptr;

        nodes = 1;
    }
    else
    {
        Node *node = root;
        Node *previous;

        while (true)
        {
            if (node -> num == info)
            {
                return;
            }
            previous = node;

            bool lessThan = node -> num > info;
            if (lessThan == true)
            {
                node = node -> left;
            }
            else
            {
                node = node -> right;
            }

            if (node == nullptr)
            {
                if (lessThan)
                {
                    previous -> left = new Node;
                    previous -> left -> num = info;
                    previous -> left -> left = nullptr;
                    previous -> left -> right = nullptr;
                    previous -> left -> previous = previous;

                }
                else
                {
                    previous -> right = new Node;
                    previous -> right -> num = info;
                    previous -> right -> left = nullptr;
                    previous -> right -> right = nullptr;
                    previous -> right -> previous = previous;


                }

                balance(previous);
                return;
            }
        }
    }*/
}
int AVL::soManyLeafs(Node* node)
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

int AVL::treeHeight(Node* node)
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


void AVL::inOrder(Node *node, std::ostream &out)
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

void AVL::preOrder(Node *node, std::ostream &out)
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

void AVL::postOrder(Node *node, std::ostream &out)
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

void AVL::checkBalance(Node *node)
{
    node -> balance = treeHeight(node -> right) - treeHeight(node -> left);
}

void AVL::balance(Node *node)
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
        if (treeHeight(node -> right -> left) <= treeHeight(node -> right -> right))
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
    //cout << "Tree Balanced" << endl;
}

AVL::Node* AVL::leftLeft(Node *node)
{
    Node *temp = new Node;
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
    rotations++;
    return temp;
}

AVL::Node* AVL::leftRight(Node *node)
{
    node -> right = leftLeft(node -> right);
    return rightRight(node);
}

AVL::Node* AVL::rightRight(Node *node)
{
    Node *temp = new Node;
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
    rotations++;
    return temp;
}

AVL::Node* AVL::rightLeft(Node *node)
{
    node -> right = rightRight(node -> right);
    return leftLeft(node);
}

void AVL::printBalance(Node *node)
{
    if (node != nullptr) {
        printBalance(node->left);
        std::cout << node->balance << " ";
        printBalance(node->right);
    }
}

void AVL::printBalance()
{
    printBalance(root);
}
