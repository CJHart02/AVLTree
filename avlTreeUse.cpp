#include <iostream>
#include <fstream>
#include <iomanip>
#include "avlTree.h"

using namespace std;

int main()
{
	AVL avl;

	int count, nodesInTree, leafsInTree, smallest, largest;
	int info = 0;
	short height;
    count = 0;
    nodesInTree = 0;

	ifstream inFile;
	ofstream outFile;

    inFile.open("random_ints.txt");
    outFile.open("sorted_ints.txt");

    while (info != -999)
    {
        inFile >> info;
        if (info != -999)
        {
            avl.build(info);
        }
    }

    nodesInTree = avl.howManyNodes();
    leafsInTree = avl.howManyLeafs();
    smallest = avl.smallestNode();
    largest = avl.largestNode();
    avl.print_inOrder(outFile);
    avl.print_preOrder(outFile);
    avl.print_postOrder(outFile);

    height = avl.printHeight();

    cout << "\n \n" << "Tree Height: " << height << endl;
    outFile << "\n \n" << "Tree Height: " << height << endl;
    cout << "Number of Nodes: " << nodesInTree << endl;
    outFile << "Number of Nodes: " << nodesInTree << endl;
    cout << "Number of Leafs: " << leafsInTree << endl;
    outFile << "Number of Leafs: " << leafsInTree << endl;
    cout << "Smallest Number: " << smallest << endl;
    outFile << "Smallest Number: " << smallest << endl;
    cout << "Largest Number: " << largest << endl;
    outFile << "Largest Number: " << largest << endl;

    cout << "Balance" << endl;
    avl.printBalance();
    cout << endl;

    inFile.close();
    outFile.close();

    return 0;
}

