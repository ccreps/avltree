// Nonlinear_HW6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include "AVLTree.h"
using namespace std;

//Constructor for Node
Node::Node(double nodeKey) {
    key = nodeKey;
}

//UpdateHeight, SetChild, ReplaceChild, GetBalance are all from Zybook Figure 9.2.1
void AVLTree::UpdateHeight(Node* node) {
    int leftHeight = -1;
    if (node->left != nullptr) {
        leftHeight = node->left->height;
    }
    int rightHeight = -1;
    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }
    node->height = max(leftHeight, rightHeight) + 1;
}

bool AVLTree::SetChild(Node* parent, const string &whichChild, Node* child) {
    if (whichChild != "left" && whichChild != "right")
        return false;

    if (whichChild == "left")
        parent->left = child;
    else
        parent->right = child;
    if (child != nullptr)
        child->parent = parent;

    UpdateHeight(parent);
    return true;
}

bool AVLTree::ReplaceChild(Node* parent, Node* currentChild, Node* newChild) {
    if (parent->left == currentChild)
        return SetChild(parent, "left", newChild);
    else if (parent->right == currentChild)
        return SetChild(parent, "right", newChild);
    return false;
}

int AVLTree::GetBalance(Node* node) {
    int leftHeight = -1;
    if (node->left != nullptr)
        leftHeight = node->left->height;
    int rightHeight = -1;
    if (node->right != nullptr)
        rightHeight = node->right->height;
    return leftHeight - rightHeight;
}

void AVLTree::RotateRight(Node* node) {
    Node* leftRightChild = node->left->right;
    if (node->parent != nullptr)
        ReplaceChild(node->parent, node, node->left);
    else { //node is not root
        root = node->left;
        root->parent = nullptr;
    }
    SetChild(node->left, "right", node);
    SetChild(node, "left", leftRightChild);
}

void AVLTree::RotateLeft(Node* node) {
    Node* rightLeftChild = node->right->left;
    if (node->parent != nullptr)
        ReplaceChild(node->parent, node, node->right);
    else { //node is not root
        root = node->right;
        root->parent = nullptr;
    }
    SetChild(node->right, "left", node);
    SetChild(node, "right", rightLeftChild);
}

//Implemented using Zybook Figure 9.2.2
Node* AVLTree::Rebalance(Node* node) {
    UpdateHeight(node);
    if (GetBalance(node) == -2) {
        if (GetBalance(node->right) == 1) {
            //Double rotation case
            RotateRight(node->right);
        }
        RotateLeft(node);
        return node;
    }
    else if (GetBalance(node) == 2) {
        if (GetBalance(node->left) == -1) {
            //Double rotation case
            RotateLeft(node->left);
        }
        RotateRight(node);
        return node;
    }
    return node;
}

//Taken from Zybook Figure 9.3.2 AVLTreeInsert Algorithm
void AVLTree::insert(Node* node) {
    if (root == nullptr) {
        root = node;
        node->parent = nullptr;
        return;
    }

    Node* cur = root;
    while (cur != nullptr) {
        if (node->key < cur->key) {
            if (cur->left == nullptr) {
                cur->left = node;
                node->parent = cur;
                cur = nullptr;
            }

            else {
                cur = cur->left;
            }
        }

        else {
            if (cur->right == nullptr) {
                cur->right = node;
                node->parent = cur;
                cur = nullptr;
            }

            else {
                cur = cur->right;
            }
        }
    }

    node = node->parent;
    while (node != nullptr) {
        Rebalance(node);
        node = node->parent;
    }
}

void AVLTree::insertWithoutRebalance(Node* node) {
    if (root == nullptr) {
        root = node;
        node->parent = nullptr;
        return;
    }

    Node* cur = root;
    while (cur != nullptr) {
        if (node->key < cur->key) {
            if (cur->left == nullptr) {
                cur->left = node;
                node->parent = cur;
                cur = nullptr;
            }

            else {
                cur = cur->left;
            }
        }

        else {
            if (cur->right == nullptr) {
                cur->right = node;
                node->parent = cur;
                cur = nullptr;
            }

            else {
                cur = cur->right;
            }
        }
    }
    node = node->parent;
    while (node != nullptr) {
        UpdateHeight(node);
        node = node->parent;
    }
}

int AVLTree::GetHeight() {
    return root->height;
}

//Makes two trees (balanced, and unbalanced) then prints the height of each
void generateRandomTree(int treeSize) {
    AVLTree* balancedTree = new AVLTree;
    AVLTree* unbalancedTree = new AVLTree;

    for (int i = 0; i < treeSize; i++) {
        Node* nodeOne = new Node((double)rand() / RAND_MAX);
        Node* nodeTwo = new Node((double)rand() / RAND_MAX);
        balancedTree->insert(nodeOne);
        unbalancedTree->insertWithoutRebalance(nodeTwo);
    }

    cout << "balancedTree height is: " << balancedTree->GetHeight() << endl;
    cout << "unbalancedTree height is: " << unbalancedTree->GetHeight() << endl;
    cout << endl;
}

int main()
{
    // Set the seed for the random number generator based on the current time (taken from midterm exam solution)
    auto seedTime = std::chrono::system_clock::now();
    unsigned int seed = std::chrono::duration_cast<std::chrono::seconds>(seedTime.time_since_epoch()).count() % UINT_MAX;
    std::srand(seed);

    //Create the RandomTrees for testing and print heights
    for (int i = 0; i < 10; i++) {
        generateRandomTree(100000);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
