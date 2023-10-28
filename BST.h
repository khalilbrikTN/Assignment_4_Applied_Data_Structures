//
// Created by Mohamed Khalil on 10/23/2023.
//

#ifndef ASSIGNMNET_3_BST_H
#define ASSIGNMNET_3_BST_H

#include "iostream"
#include "queue"
using namespace std;


template <class data_type, class key_type>
class Node{
public:
    Node* left;
    Node* right;
    data_type data;
    key_type key;
};

template <class data_type, class key_type>
class BST {
private:
    Node<data_type, key_type> *root; //The root of the entire tree
public:
    BST() {
        root = nullptr;  // Initialize the root as null
    };

    ~BST(){};

    // Function to get the root of the BST
    Node<data_type, key_type>* get_root() { return root; }

    // Function to create a new node with data and a key
    Node<data_type, key_type>* createNode(data_type data, key_type key) {
        Node<data_type, key_type>* node = new Node<data_type, key_type>();
        node->data = data;
        node->key = key;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    // Function to insert a new node with data and a key into the BST
    void Insert(key_type key, data_type data) {
        // Handle the root separately
        if(root == nullptr) {
            root = createNode(data, key);
            return;
        }

        Node<data_type, key_type>* parent = nullptr;
        Node<data_type, key_type>* current = root;

        while(current != nullptr) {
            parent = current;
            if(key >= current->key) {
                current = current->right;
            } else {
                current = current->left;
            }
        }

        if(key >= parent->key) {
            parent->right = createNode(data, key);
        } else {
            parent->left = createNode(data, key);
        }
    }

    // Function to check if the BST is empty
    bool empty() {
        return root == nullptr;
    }

    // Function to search for a node with a specific key
    Node<data_type, key_type>* search(Node<data_type, key_type> *head, key_type key) {
        if (head == nullptr) {
            return nullptr;
        }
        if (key == head->key) {
            return head;
        } else if (key > head->key) {
            return search(head->right, key);
        } else {
            return search(head->left, key);
        }
    };

    // Function to retrieve the data of a node with a specific key
    data_type retrieve(Node<data_type, key_type> *head, key_type key) {
        Node<data_type, key_type> *key_node = search(head, key);
        return key_node->data;
    };

    // Function to traverse the BST in-order and print keys
    void traverse(Node<data_type, key_type> *head) {
        if (head != nullptr) {
            traverse(head->left);
            cout << head->key <<" ";
            traverse(head->right);
        }
    }

    // Function to traverse the BST in preorder and print keys
    void preorder(Node<data_type, key_type> *head) {
        if (head != nullptr) {
            cout << head->key <<" ";
            preorder(head->left);
            preorder(head->right);
        }
    }

    // Function to traverse the BST in level order and print keys
    void levelorder(Node<data_type, key_type> *head) {
        queue<Node<data_type, key_type>*> q;
        Node<data_type, key_type>* temp = head;

        while (temp) {
            cout << temp->key << " ";

            if (temp->left)
                q.push(temp->left);

            if (temp->right)
                q.push(temp->right);

            if (!q.empty()) {
                temp = q.front();
                q.pop();
            } else {
                temp = nullptr;
            }
        }
    }

    // Function to find the node with the minimum key in a subtree
    Node<data_type, key_type>* min_sub_tree(Node<data_type, key_type>* head){
        if (head->left == nullptr) {
            return head;
        }
        return min_sub_tree(head->left);
    }


// Function to remove a node with a specific key from the BST
    Node<data_type,key_type>* remove(Node<data_type,key_type>* head, key_type key){
        if (head == nullptr) {return nullptr;}
        else if(key < head->key){head->left = remove(head->left, key);}
        else if(key > head->key){head->right = remove(head->right, key);}
        else {
            if(head->left == nullptr && head->right == nullptr){
                delete head;
                head = nullptr;
            } else if (head->left == nullptr) {
                Node<data_type,key_type>* temp = head;
                head = head->right;
                delete temp;
            } else if (head->right == nullptr) {
                Node<data_type,key_type>* temp = head;
                head = head->left;
                delete temp;
            } else {
                Node<data_type,key_type>* temp = min_sub_tree(head->right);
                head->data = temp->data;
                head->key = temp->key;
                head->right = remove(head->right, temp->key);
            }
            return head;
        }
    };


};


#endif //ASSIGNMNET_3_BST_H
