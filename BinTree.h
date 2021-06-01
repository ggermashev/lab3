#pragma once
#ifndef BINTREE_H
#define BINTREE_H

template <class T>
class Node {
public:
	T data;
	Node* left;
	Node* right;
	Node* par;
	bool isLeaf;
	int height;
	Node(Node<T>* node); 
	Node();
};

template <class T>
class BinTree {
private:
	Node<T>* root;
	int size;
public:
	BinTree();
	BinTree(T* arr, int size);
	void DestroyNode(Node<T>* node);
	~BinTree();
	int GetSize();
	void AddNode(T value); 
	bool FindNode(T value); 
	void DltNode(T value); 
	BinTree<T>* GetSubTree(T value);
	bool CheckSubTree(BinTree<T>* subTree); 
	T* GoThrough(Node<T>* node, T* arr, int* ind); 
	int FindSize(Node<T>* node, int* size); 
	Node<T>* Balance(Node<T>* node);
	void Change_height(int* h, Node<T>* node);
	int Delta(Node<T>* node);
	Node<T>* RotRight(Node<T>* node);
	Node<T>* RotLeft(Node<T>* node);
	void Change_leaf(Node<T>* node);
	T* GoThroughHeights(Node<T>* node, T* arr, int* ind);
	int GetMaxHeight(Node<T>* node, int* h);
	T* GoThroughDeltas(Node<T>* node, T* arr, int* ind);
};

#endif // !BINTREE_H
