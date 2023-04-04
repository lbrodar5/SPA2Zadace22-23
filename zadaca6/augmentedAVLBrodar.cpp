#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int key;
    int height;
    int size;
	Node *left, *right, *parent;
};

class AVL
{
private:
    
    Node *root; 

	int height(Node *node)
	{
		if (node == nullptr)
			return 0;
		
        return node->height;
	}

    int size(Node *node)
    {
        if (node == nullptr)
            return 0;

        return node->size;
    }

    void updateSize(Node *node)
    {
        node->size = 1 + size(node->left) + size(node->right);
    }

    Node* rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *temp = x->right;
 
        x->right = y;
        y->left = temp;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        updateSize(y);
        updateSize(x);

        if(temp != nullptr)
            temp->parent = y;

        x->parent = y->parent;
        y->parent = x;

        return x;
    }

    Node* leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        updateSize(y);
        updateSize(x);

        if(temp != nullptr)
            temp->parent = x;

        y->parent = x->parent;
        x->parent = y;

        return y;
    }

    int balanceOfNode(Node *node)
    {
        if(node == nullptr)
            return 0;
        
        return height(node->left) - height(node->right);
    }

    Node* insert(Node *node, int key)
    {
        if(node == nullptr)
            node = new Node {key, 0, 1 , nullptr, nullptr, nullptr};
        else if(key < node->key)
        {
            node->left = insert(node->left, key);
            node->left->parent = node;
        }
        else if(key > node->key)
        {
            node->right = insert(node->right, key);
            node->right->parent = node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        updateSize(node);

        int balance = balanceOfNode(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    
        return node;
    }

    void inorder(Node *node)
    {
        if(node == nullptr)
            return;
        
        inorder(node->left);
        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) <<", S: " << node->size << "] ";
        cout << endl;
        inorder(node->right);
    }

    void preorder(Node *node)
    {
        if(node == nullptr)
            return;
        
        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) <<", S: " << node->size << "] ";
        cout << endl;
        preorder(node->left);
        preorder(node->right);
    }

    Node* OS_SELECT(Node* node, int i)
    {
        int r = size(node->left) + 1;

        if (i == r)
            return node;
        else if (i < r)
            return OS_SELECT(node->left, i);
        else
            return OS_SELECT(node->right, i - r);
    }




public:
    AVL() : root(nullptr) {}

	void insert(int key)
	{
        root = insert(root, key);
	}

    void printInorder()
    {
        inorder(root);
    }

    void printPreorder()
    {
        preorder(root);
    }

    void OS_SELECT(int i)
    {
        Node* node = OS_SELECT(root,i);

        if(node == nullptr)
            return;

        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) <<", S: " << node->size << "] ";
    }

    int OS_KEY_RANK(AVL T, int k)
    {
        Node *node = T.root;
        int rank = 1;

        while (node != nullptr)
        {
            if (node->key == k)
            {
                rank += size(node->left);
                break;
            }
            else if (node->key > k)
                node = node->left;
            else
            {
                rank += size(node->left) + 1;
                node = node->right;
            }
        }

        if (node == nullptr)
            return -1; 
            
        return rank;
    }

    void ithSuccessor(int key, int i) 
    {
        int r = OS_KEY_RANK(*this, key) + i;
        Node* node = OS_SELECT(root, r);
        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) << ", S: " << node->size << "] ";
    }
};

int main()
{
    AVL tree;
    tree.insert(29);
    tree.insert(6);
    tree.insert(56);
    tree.insert(3);
    tree.insert(7);
    tree.insert(37);
    tree.insert(61);
    tree.insert(4);
    tree.insert(22);
    tree.insert(48);
    tree.insert(59);
    tree.insert(69);

    //tree.printInorder();

    tree.OS_SELECT(8);

    cout << endl;

    cout << tree.OS_KEY_RANK(tree,6) << endl;

    tree.ithSuccessor(7,3);

    return 0;
}