#include <bits/stdc++.h>
using namespace std;

class AVLTree {
private:
    struct Node {
        int key, height, size;
        Node *left, *right;

        Node(int k) : key(k), height(1), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int size(Node* node) {
        return node ? node->size : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->size = size(y->left) + size(y->right) + 1;
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->size = size(x->left) + size(x->right) + 1;
        y->size = size(y->left) + size(y->right) + 1;
        return y;
    }

    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;

        node->height = max(height(node->left), height(node->right)) + 1;
        node->size = size(node->left) + size(node->right) + 1;
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) return rightRotate(node);
        if (balance < -1 && key > node->right->key) return leftRotate(node);
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

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;
        if (key < root->key) root->left = deleteNode(root->left, key);
        else if (key > root->key) root->right = deleteNode(root->right, key);
        else {
            if (!root->left) return root->right;
            else if (!root->right) return root->left;
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
        root->height = max(height(root->left), height(root->right)) + 1;
        root->size = size(root->left) + size(root->right) + 1;
        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    bool find(Node* node, int key) {
        if (!node) return false;
        if (key == node->key) return true;
        return key < node->key ? find(node->left, key) : find(node->right, key);
    }

    int orderOfKey(Node* node, int key) {
        if (!node) return 0;
        if (key <= node->key) return orderOfKey(node->left, key);
        return size(node->left) + 1 + orderOfKey(node->right, key);
    }

    int getByOrder(Node* node, int k) {
        if (!node) return -1;
        int leftSize = size(node->left);
        if (k < leftSize) return getByOrder(node->left, k);
        if (k == leftSize) return node->key;
        return getByOrder(node->right, k - leftSize - 1);
    }

public:
    AVLTree() : root(nullptr) {}

    bool find(int key) {
        return find(root, key);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    int orderOfKey(int key) {
        return orderOfKey(root, key);
    }

    int getByOrder(int k) {
        return getByOrder(root, k);
    }
};
