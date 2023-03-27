#include <iostream>
using namespace std;

struct Node {
    int key;
    int h;
    Node* left, * right, * parent;
};

class AVL {
    Node* root;

    int height(Node* node) {
        if (node == NULL)
            return 0;
        return node->h;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;  
        y->left = x->right; 

        if (x->right != NULL) {
            x->right->parent = y;
        }
        if (y->parent == NULL) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;

        x->parent = y->parent;
        y->parent = x;

        return x; 
    }


    Node* leftRotate(Node* x) {
        Node* y = x->right;   
        x->right = y->left;    
    
        if(y->left != NULL)
        {
            y->left->parent = x;
        }
        if (x->parent == NULL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;

        y->parent = x->parent;
        x->parent = y;

        return y;   
    }


    int balanceOfNode(Node* node) {
        if (node == NULL)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* insert(Node* node, int key) {
        if (node == NULL) {
            Node* newNode = new Node();
            newNode->key = key;
            newNode->h = 1;
            newNode->left = newNode->right = newNode->parent = NULL;
            return newNode;
        }

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->h = 1 + max(height(node->left), height(node->right));
        int balance = balanceOfNode(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == NULL)
            return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

public:
    AVL() {
        root = NULL;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void print() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVL tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    tree.print(); 

    return 0;
}
