class AVL
{
private:
    int nodes;
    int leafs;
    int height;
	struct node
    {
        int num;
        int balance;
		node *left;
		node *right;
		node *previous;
	};
    node *root, *current;

public:
	AVL();
	void build(int info);
	int soManyLeafs(node* node);
	int treeHeight(node* node);
	int printHeight();
	void inOrder(node* node, std::ostream &out);
	void preOrder(node* node, std::ostream &out);
	void postOrder(node* node, std::ostream &out);
    bool isFull(int count, int max);
    int smallestNode();
    int largestNode();
    int howManyNodes();
    int howManyLeafs();
    void print_inOrder(std::ostream &out);
    void print_preOrder(std::ostream &out);
    void print_postOrder(std::ostream &out);
    void checkBalance(node* node);
    void balance(node* node);
    node* leftLeft(node* node);
    node* leftRight(node* node);
    node* rightRight(node* node);
    node* rightLeft(node* node);
};

/*class node
{
public:
    int num;
        int balance;
		node *left;
		node *right;
		node *previous;
};*/
