#pragma once
#include "Crime.h"
#include <chrono>
using namespace std;

struct avlNode
{
    int gatorID;
    int height;
    int balanceFac;
    avlNode *left;
    avlNode *right;
    avlNode() : gatorID(0), left(nullptr), right(nullptr), height(0), balanceFac(0) {}
    avlNode(int x) : gatorID(x), left(nullptr), right(nullptr), height(0), balanceFac(0) {}
    avlNode(int x, avlNode *left, avlNode *right) : gatorID(x), left(left), right(right), height(0), balanceFac(0) {}


};

class avlTree
{
    avlNode* root = nullptr;
    vector<avlNode*> treeVec;
    int count = 0;
        avlNode* leftRotation(avlNode* node){
        avlNode* grandchild = node->right->left;
        avlNode* newParent = node->right; 
        newParent->left = node;
        node->right = grandchild;
        if(newParent->left != nullptr)
            updateHeight(newParent->left);
        if(newParent->right != nullptr)
            updateHeight(newParent->right);
        updateHeight(newParent);


        return newParent;
    }
    avlNode* rightRotation(avlNode* node){
        avlNode* grandchild = node->left->right;
        avlNode* newParent = node->left; 
        newParent->right = node;
        node->left = grandchild;
        if(newParent->left != nullptr)
            updateHeight(newParent->left);
        if(newParent->right != nullptr)
            updateHeight(newParent->right);
        updateHeight(newParent);


        return newParent;
    }
    public:
    vector<int> sortAge;
        void insert(int id);
        avlNode* insertHelper(avlNode* root, int id);
        void updateHeight(avlNode* root);//done
        void printInorder(); //done
        void printInorderHelper(avlNode* root);//done
};

void avlTree::insert(int id){
    this->root = insertHelper(this->root, id);
}
avlNode* avlTree::insertHelper(avlNode* root, int id){ //done
//Insert BST requirements::
            if(root == nullptr){
               return new avlNode(id);
            }
            else if(id < root->gatorID){ //left -- key less than root
               //cout << root->gatorID << endl;
               root->left = insertHelper(root->left, id);
            }
            else{ //right 
               root->right = insertHelper(root->right, id); 
            }
            
            //Updating Height and Balance Factor::
            updateHeight(root);

            
            //auto balancing avl requirments::
            if(root->balanceFac == -2){//right heavy
                if(root->right->balanceFac == -1){
                    //right right case || left rotation
                    root = leftRotation(root);
                }
                else{
                    //right left case
                   root->right = rightRotation(root->right);
                   root = leftRotation(root);
                }
            }
            else if(root->balanceFac == 2){ //left heavy
                if(root->left->balanceFac == 1){
                    //left left case || right rotation
                    root = rightRotation(root);
                }
                else{ //left right case || left rotate then right rotate || ex. insert order 3,1,2
                   root->left = leftRotation(root->left);
                   root = rightRotation(root);
                }
            }      
            return root;
}
void avlTree::updateHeight(avlNode* node){
    int leftH = -1;
    int rightH = -1;

    if(node->left != nullptr)
        leftH = node->left->height;
    if(node->right != nullptr)
        rightH = node->right->height;

    node->height = max(leftH, rightH) + 1;

    node->balanceFac = leftH - rightH;

}
void avlTree::printInorder(){ printInorderHelper(this->root);}
void avlTree::printInorderHelper(avlNode* root){
    if (root != nullptr) {
        printInorderHelper(root->left);
        sortAge.push_back(root->gatorID);
        printInorderHelper(root->right);

    }
}