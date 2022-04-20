#pragma once
#include "Crime.h"
using namespace::std

struct Node
{
    int age;
    int height;
    Node* left;
    Node* right;

    Node()
    {
        age = 0;
        height = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(int newAge)
    {
        //overload constructor
        age = newAge;
        height = 0;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree
{
    Node* head = nullptr;
    //Right/left Rotate
    Node* rightRotate(Node* node)
    {
        Node* newParent = node->left;
        Node* grandChild = node->left->right;

        newParent->right = node;
        node->left = grandChild;

        //set height
        node->height = getHeight(node);
        newParent->height = getHeight(newParent);

        return newParent;
    }
    Node* leftRotate(Node* node)
    {
        Node* grandChild = node->right->left;
        Node* newParent = node->right;

        newParent->left = node;
        node->right = grandChild;

        //set height
        node->height = getHeight(node);
        newParent->height = getHeight(newParent);

        return newParent;
    }
    int getHeight(Node* node)
    {
        if (node == nullptr)
            return NULL;
        else
            return max(getHeight(node->left), getHeight(node->right)) + 1;
    }

public:
    //insert function
    Node* Insert(Node* node, int newAge)
    {
        if (head == NULL)
        {
            head = InsertHelper(newAge);
            return  head;
        }
        if (node == NULL)
        {
            //if node is empty return new head
            return  InsertHelper(newAge);
        }
        else if (newAge < node->age)
        {
            //rerecurive insert to left node
            node->left = Insert(node->left, newAge);
        }
        else if (newAge > node->age)
        {
            //recursive insert to right node
            node->right = Insert(node->right, newAge);
        }
        else {
            //duplicate age
            return node;
        }
        node->height = getHeight(node);

        head = Balance(newAge, node);
        return head;
    }
    Node* InsertHelper(int newAge)
    {
        Node* newNode = new Node(newAge);
        //set height
        int newHeight = getHeight(newNode);
        newNode->height = newHeight;
        return newNode;
    }
    Node* Balance(int newAge, Node* node)
    {
        int balance = getBalance(node);
        Node* balancedNode = nullptr;
        if (balance == 2)
        {
            if (getBalance(node->left) == 1)
            {
                balancedNode = rightRotate(node);
            }
            else if (getBalance(node->right) == -1)
            {
                balancedNode = rightRotate(leftRotate(node));
            }
        }
        else if (balance == -2)
        {
            if (getBalance(node->right) == -1)
            {
                balancedNode = leftRotate(node);
            }
            else if (getBalance(node->left) == 1)
            {
                balancedNode = leftRotate(rightRotate(node));
            }
        }
        else
            //already balanced
            return node;
        return balancedNode;
    }
    int getBalance(Node* node)
    {
        if (node == nullptr)
            return 0;
        return node->left->height - node->right->height;
    }
    vector<int> PrintInorder(Node* node)
    {
        vector<int> sortedAges;
        if (node != NULL)
        {
            //search left node first then right
            PrintInorder(node->left);
            sortedAges.push_back(node->age);
            PrintInorder(node->right);
        }
        return sortedAges;
    }
};
