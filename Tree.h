#pragma once
#include<"Crime.h">
using namespace std;

struct Node
{
    int age;
    Node* left;
    Node* right;

    Node()
    {
        age = NULL;
        left = nullptr;
        right = nullptr;
    }
    Node(int newAge)
    {
        //overload constructor
        age = newAge;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree
{
    Node* head = nullptr;
    //Right/left Rotate
    //psuedo code from Kapoor youtube videos: https://www.youtube.com/watch?v=DcnxKzwiL84&list=PLvBZ6Nw3S6DQlFrtQLjYpWnuD-mgXSkUz&index=3
    Node* rightRotate(Node* node)
    {
        Node* grandChild = node->left->right;
        Node* newParent = node->left;

        newParent->right = node;
        node->left = grandChild;

        return newParent;
    }
    Node* leftRotate(Node* node)
    {
        Node* grandChild = node->right->left;
        Node* newParent = node->right;

        newParent->left = node;
        node->right = grandChild;

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
        if (getHeight(head) == NULL)
        {
            head = InsertHelper(newAge);
            return  head;
        }
        if (getHeight(node) == NULL)
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
        head = Balance(newAge, node);
        return head;
    }
    Node* InsertHelper(int newAge)
    {
        Node* newNode = new Node(newAge);
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
    vector<int> PrintInorder(Node* node)
    {
        vector<int> sortedAges;
        if (node != NULL)
        {
            //search left node first then right
            PrintInorder(node->left);
            sortedAges.push_back(node);
            PrintInorder(node->right);
        }
        return sortedAges;
    }