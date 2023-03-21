#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node* left, *right, *parent;
};

class BST
{
private:
    Node* root;

    Node* insert(int key, Node* node)
    {
        if (node == nullptr)
        {
            node = new Node;
            node->key = key;
            node->left = node->right = node->parent = nullptr;
        }
        else if (key < node->key)
        {
            node->left = insert(key, node->left);
            node->left->parent = node;
        }
        else if (key > node->key)
        {
            node->right = insert(key, node->right);
            node->right->parent = node;
        }
        return node;
    }

    void inorder(Node* node)
    {
        if (node != nullptr)
        {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    Node* search(int key, Node* node)
    {
        if (node == nullptr || node->key == key)
        {
            return node;
        }
        else if (key < node->key)
        {
            return search(key, node->left);
        }
        else
        {
            return search(key, node->right);
        }
    }

    Node* find_min(Node* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else if (node->left == nullptr)
        {
            return node;
        }
        else
        {
            return find_min(node->left);
        }
    }

    Node* find_max(Node* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else if (node->right == nullptr)
        {
            return node;
        }
        else
        {
            return find_max(node->right);
        }
    }

    Node* successor(Node* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->right != nullptr)
        {
            return find_min(node->right);
        }
        else
        {
            Node* p = node->parent;
            while (p != nullptr && node == p->right)
            {
                node = p;
                p = p->parent;
            }
            return p;
        }
    }

    Node* predecessor(Node* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->left != nullptr)
        {
            return find_max(node->left);
        }
        else
        {
            Node* p = node->parent;
            while (p != nullptr && node == p->left)
            {
                node = p;
                p = p->parent;
            }
            return p;
        }
    }

    Node* BSTdelete(int key, Node* node)
    {
        if (node == nullptr)
        {
            return node;
        }
        else if (key < node->key)
        {
            node->left = BSTdelete(key, node->left);
        }
        else if (key > node->key)
        {
            node->right = BSTdelete(key, node->right);
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr)
            {
                Node* t = node;
                node = node->right;
                node->parent = t->parent;
            delete t;

            }
            else if (node->right == nullptr)
            {
                Node* t = node;
                node = node->left;
                node->parent = t->parent;
                delete t;
            }
            else
            {
                Node* t = find_min(node->right);
                node->key = t->key;
                node->right = BSTdelete(t->key, node->right);
                }
        }

        return node;
    }

    public:
    BST() : root(nullptr) {}

    void print()
    {
        inorder(root);
        cout << endl;
    }

    void insert(int key)
    {
        root = insert(key, root);
    }

    bool search(int key)
    {
        Node* r = search(key, root);
        return r != nullptr;
    }

    int find_min()
        {
        Node* r = find_min(root);
        if (r != nullptr)
        {
            return r->key;
        }
       else
        {
            return -1;
        }
    }

    int find_max()
    {
        Node* r = find_max(root);
        if (r != nullptr)
        {
            return r->key;
        }
        else
        {
            return -1;
        }
    }

    int successor(int key)
    {
        Node* node = search(key, root);
        Node* r = successor(node);
        if (r != nullptr)
        {
            return r->key;
        }
        else
        {
            return -1;
        }
    }

    int predecessor(int key)
    {
        Node* node = search(key, root);
        Node* r = predecessor(node);
        if (r != nullptr)
        {
            return r->key;
        }
        else
        {
            return -1;
        }
    }

    void BSTdelete(int key)
    {
        root = BSTdelete(key, root);
    }
};

int main()
{
    BST bst;

    bst.insert(5);
    bst.insert(10);
    bst.insert(4);
    bst.insert(8);
    bst.insert(9);
    bst.insert(1);
    bst.insert(11);
    bst.insert(15);
    bst.insert(3);

    bst.print();

    cout << bst.find_min() << endl;
    cout << bst.find_max() << endl;

    cout << bst.successor(8) << endl;
    cout << bst.predecessor(10) << endl;

    bst.BSTdelete(10);
    bst.print();

    return 0;
}
