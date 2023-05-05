#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
using namespace std;

// A node in the AVL tree that stores a double
class Node {
public:
	double key;
	int height = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent = nullptr;

	Node(double nodeKey);
};

// An AVL tree that can insert with and without rebalancing
class AVLTree
{
public:
	// Insert a new element and rebalance the tree
	void insert(Node* node);
	// Insert a new element without rebalancing the tree
	void insertWithoutRebalance(Node* node);
	// Updates a node's height value by taking the maximum of the child subtree heights and adding 1
	static void UpdateHeight(Node* node);
	//Sets a node as the parent's left or right child, updates the child's parent pointer, and updates the parent node's height
	static bool SetChild(Node* parent, const string &whichChild, Node* child);
	//Replaces one of a node's existing child pointers wioth a new value, utilizing SetChild to perform the replacement
	static bool ReplaceChild(Node* parent, Node* currentChild, Node* newChild);
	//Computes a node's balance factor by subtracting the right subtree from the left subtree height
	int GetBalance(Node* node);
	//Reassigns pointers for rotation of node to the right
	void RotateRight(Node* node);
	//Reassigns pointers for rotation of node to the left
	void RotateLeft(Node* node);
	//Rebalances the AVL Tree using rotations (if balance factor ==2 || -2), updates height values, and computes balance factor
	Node* Rebalance(Node* node);
	//Return the height of the tree
	int GetHeight();

private:
	Node* root = nullptr;
};

#endif // !AVLTREE_H