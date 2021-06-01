#include "BinTree.h"
#include "BinTree.cpp"
#include <iostream>
#include "Tests.h"
#include "Timer.h"

void menu() 
{
	
	int choice = 1;
	int elem;
	int* arr = NULL;
	int* cnt = NULL;
	int size;
	BinTree<int>* tr = NULL;
	BinTree<int>* tr2 = NULL;
	while (choice != 0) {
		std::cout << "1: Create empty\n2: Create from array\n3: AddNode\n4: DltNode\n5: CheckNode\n6: GetSubTree\n7: Output\n8: Check heights\n9: Check deltas\n0: Exit\ninput your choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case 0:
			if (tr) tr->~BinTree();
			return;
		case 1:
			if (tr)
			{
				tr->~BinTree();
				tr = NULL;
			}
			tr = new BinTree<int>;
			break;
		case 2:
			if (tr)
			{
				tr->~BinTree();
				tr = NULL;
			}
			std::cout << "input size: ";
			std::cin >> size;
			if (arr) delete[]arr;
			arr = new int[size];
			std::cout << "input elements: ";
			for (int i = 0; i < size; i++)
			{
				std::cin >> arr[i];
			}
			tr = new BinTree<int>(arr, size);
			break;
		case 3:
			std::cout << "input node to add: ";
			std::cin >> elem;
			tr->AddNode(elem);
			break;
		case 4:
			std::cout << "input node to dlt: ";
			std::cin >> elem;
			tr->DltNode(elem);
			break;
		case 5:
			std::cout << "input node to check: ";
			std::cin >> elem;
			if (tr->FindNode(elem)) std::cout << "true\n";
			else std::cout << "false\n";
			break;
		case 6:
			std::cout << "input root of subTree: ";
			std::cin >> elem;
			//if (arr) delete[]arr;
			//if (cnt) delete cnt;
			arr = NULL;
			cnt = NULL;
			tr2 = tr->GetSubTree(elem);
			arr = tr2->GoThrough(NULL, arr, cnt);
			for (int i = 0; i < tr2->GetSize(); i++)
			{
				std::cout << arr[i] << " ";
			}
			std::cout << "\n";
			tr2->~BinTree();
			tr2 = NULL;
			break;
		case 7:
			//if (arr) delete[]arr;
			//if (cnt) delete cnt;
			arr = NULL;
			cnt = NULL;
			std::cout << "7\n";
			arr = tr->GoThrough(NULL, arr, cnt);
			for (int i = 0; i < tr->GetSize(); i++)
			{
				std::cout << arr[i] << " ";
			}
			std::cout << "\n";
			break;
		case 8:
			//if (arr) delete[]arr;
			//if (cnt) delete cnt;
			arr = NULL;
			cnt = NULL;
			arr = tr->GoThroughHeights(NULL, arr, cnt);
			for (int i = 0; i < tr->GetSize(); i++)
			{
				std::cout << arr[i] << " ";
			}
			std::cout << "\n";
			break;
		case 9:
			//if (arr) delete[]arr;
			//if (cnt) delete cnt;
			arr = NULL;
			cnt = NULL;
			arr = tr->GoThroughDeltas(NULL, arr, cnt);
			for (int i = 0; i < tr->GetSize(); i++)
			{
				std::cout << arr[i] << " ";
			}
			std::cout << "\n";
			break;
		default:
			std::cout << "Wrong choice! Try again.\n";
			break;
		}
	}
}

int main()
{
	menu();
	Test_AddNode();
	Test_DltNode();
	Test_GetSubTree();

	//get_time_add();

	return 0;
}