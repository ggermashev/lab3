#include "Timer.h"
#include "Bintree.h"
#include <iostream>
#include <fstream>
#include <math.h>

void get_time_add()
{
	std::ofstream time_add;
	time_add.open("Time_add.txt");
	std::ofstream time_find;
	time_find.open("Time_find.txt");
	srand(time(NULL));
	int dk = 100000;
	int k = 100000;
	for (int i = 0; i < 20; i++)
	{
		std::cout << i << std::endl;
		int* arr = new int[k];
		for (int j = 0; j < k; j++)
		{
			arr[j] = rand() % 1000000;
		}
		float tm1 = clock();
		BinTree<int>* tr = new BinTree<int>(arr, k);
		float tm2 = clock();
		float time_ad = tm2 - tm1;
		time_add << time_ad/1000 << "\n";
		delete[]arr;
		tr->~BinTree();
		tr = NULL;
		k += dk;
	}
	time_add.close();
	time_find.close();
}

