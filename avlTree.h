class AVL
{
private:
    int nodes;
    int rotations = 0;
    int leafs;
    int height;
	struct Node
	{
        int num;
        int balance;
		Node *left;
		Node *right;
		Node *previous;
	};
    	Node *root, *current;

public:
	AVL();
	void build(int info);
	int soManyLeafs(Node *node);
	int treeHeight(Node *node);
	int printHeight();
	void inOrder(Node *node, std::ostream &out);
	void preOrder(Node *node, std::ostream &out);
	void postOrder(Node *node, std::ostream &out);
    bool isFull(int count, int max);
    int smallestNode();
    int largestNode();
    int howManyNodes();
    int howManyLeafs();
    void print_inOrder(std::ostream &out);
    void print_preOrder(std::ostream &out);
    void print_postOrder(std::ostream &out);
    void checkBalance(Node *node);
    void balance(Node *node);
    Node* leftLeft(Node *node);
    Node* leftRight(Node *node);
    Node* rightRight(Node *node);
    Node* rightLeft(Node *node);
    void printBalance(Node *node);
    void printBalance();
};
