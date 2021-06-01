#include "Tests.h"
#include "Bintree.h"
#include <iostream>
#include <fstream>

void Test_AddNode() 
{
	std::ifstream ftest;
	ftest.open("AddNode.txt");
	int* arr = new int[4];
	for (int i = 0; i < 4; i++)
	{
		ftest >> arr[i];
	}
	BinTree<int>* tr = new BinTree<int>(arr, 4);
	int elem;
	ftest >> elem;
	tr->AddNode(elem);
	delete[]arr;
	arr = NULL;
	int* cnt = NULL;
	arr = tr->GoThrough(NULL, arr, cnt);
	for (int i = 0; i < 5; i++)
	{
		ftest >> elem;
		if (arr[i] != elem)
		{
			std::cout << "Error in test_AddNode!\n";
			ftest.close();
			return;
		}
	}
	ftest.close();
}

void Test_DltNode()
{
	std::ifstream ftest;
	ftest.open("DltNode.txt");
	int* arr = new int[5];
	for (int i = 0; i < 5; i++)
	{
		ftest >> arr[i];
	}
	BinTree<int>* tr = new BinTree<int>(arr, 5);
	int elem;
	ftest >> elem;
	tr->DltNode(elem);
	delete[]arr;
	arr = NULL;
	int* cnt = NULL;
	arr = tr->GoThrough(NULL, arr, cnt);
	for (int i = 0; i < 4; i++)
	{
		ftest >> elem;
		if (arr[i] != elem)
		{
			std::cout << "Error in test_DltNode!\n";
			ftest.close();
			return;
		}
	}
	ftest.close();
	return;
}

void Test_GetSubTree()
{
	std::ifstream ftest;
	ftest.open("GetSubTree.txt");
	int* arr = new int[5];
	for (int i = 0; i < 5; i++)
	{
		ftest >> arr[i];
	}
	BinTree<int>* tr = new BinTree<int>(arr, 5);
	int elem;
	ftest >> elem;
	BinTree<int>* tr2 = tr->GetSubTree(elem);
	delete[]arr;
	arr = NULL;
	int* cnt = NULL;
	arr = tr2->GoThrough(NULL, arr, cnt);
	for (int i = 0; i < tr2->GetSize(); i++)
	{
		ftest >> elem;
		if (arr[i] != elem)
		{
			std::cout << "Error in Test_GetSubTree!\n";
			ftest.close();
			return;
		}
	}
	ftest.close();
	return;
}