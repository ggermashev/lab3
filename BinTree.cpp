#include <iostream>
#include "BinTree.h"

template <class T>
BinTree<T>::BinTree()
{
	root = nullptr;
	size = 0;
}

template <class T>
BinTree<T>::BinTree(T* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		this->AddNode(arr[i]);
	}
}

template <class T>
Node<T>::Node(Node<T>* node)
{
	if (!node)
	{
		return;
	}
	left = NULL;
	right = NULL;
	par = NULL;
	data = node->data;
	if (node->left) left = (node->left);
	if (node->right) right = (node->right);
	if (node->par) par = (node->par);
	isLeaf = node->isLeaf;
	height = node->height;
}

template <class T>
Node<T>::Node()
{
	left = NULL;
	right = NULL;
	par = NULL;
	height = 0;
	isLeaf = true;
}

template <class T>
void BinTree<T>::DestroyNode(Node<T>* node) {
	if (!this)
	{
		std::cout << "Tree is empty\nin: DestroyNode\n";
		return ;
	}
	if (!root)
	{
		std::cout << "Tree is empty\nin: DestroyNode\n";
		return;
	}
	if (node)
	{
		DestroyNode(node->left);
		DestroyNode(node->right);
		delete node;
	}
}
template <class T>
BinTree<T>::~BinTree()
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: ~BinTree\n";
		return;
	}
	if (!root)
	{
		std::cout << "Tree is empty\nin: ~BinTree\n";
		return;
	}
	DestroyNode(root);
}

template <class T>
int BinTree<T>::GetSize()
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: GetSize\n";
		return 0;
	}
	if (!root)
	{
		std::cout << "Tree is empty\nin: GetSize\n";
		return 0;
	}
	return size;
}

template <class T>
void BinTree<T>::AddNode(T value) 
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: AddNode\n";
		return;
	}
	if (FindNode(value))
	{
		std::cout << "Tree already has this node!\nin: AddNode\n";
		return; //если уже есть
	}
	if (!root)
	{ //если пустое
		root = new Node<T>;
		root->data = value;
		root->isLeaf = true;
		root->left = NULL;
		root->right = NULL;
		root->par = NULL;
		size = 1;
		root->height = 1;
		return;
	}
	Node<T>* cur = root; 
	while (!cur->isLeaf) 
	{ //поиск листа
		if (value > cur->data) 
		{
			if (!cur->right) break;
			cur = cur->right;
		}
		else 
		{
			if (!cur->left) break;
			cur = cur->left;
		}
	} //меньше - влево, больше - вправо
	if (value < cur->data) 
	{
		cur->left = new Node<T>;
		cur->left->par = cur;
		cur->left->data = value;
		cur->left->isLeaf = true;
		cur->isLeaf = false;
		cur->left->left = nullptr;
		cur->left->right = nullptr;
		cur->left->height = cur->height + 1;
		size++;
	}
	else 
	{
		cur->right = new Node<T>;
		cur->right->par = cur;
		cur->right->data = value;
		cur -> right->isLeaf = true;
		cur->isLeaf = false;
		cur->right->left = nullptr;
		cur->right->right = nullptr;
		cur->right->height = cur->height + 1;
		size++;
	}
	
	
	Node<T>* ptr = cur;
	while (ptr)
	{
		if (abs(Delta(ptr)) == 2)
		{
			Node<T>* pr = ptr->par;
			ptr = Balance(ptr);
			if (pr) {
				if (ptr->data > pr->data)
				{
					//pr->right = ptr;
					//ptr->par = pr;
				}
				else
				{
					//pr->left = ptr;
					//ptr->par = pr;
				}
			}
			else root = ptr;
			int* h = new int;
			*h = 1;
			Change_height(h, root);
			Change_leaf(root);
			break;
		}
		ptr = ptr->par;
	}
	
	return;
}

template <class T>
bool BinTree<T>::FindNode(T value) 
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: FindNode\n";
		return false;
	}
	if (!root) return false;
	Node<T>* cur = root;
	while (!cur->isLeaf) //проходим до листа
	{
		if (cur->data == value) return true; //нашли
		if (value < cur->data) //меньше - влево\ больше - вправо
		{
			if (!cur->left) break;
			cur = cur->left;
		}
		else
		{
			if (!cur->right) break;
			cur = cur->right;
		}
	}
	if (cur->data == value) return true; //лист. нашли

	return false; //иначе нет
}


template <class T>
void BinTree<T>::DltNode(T value) {
	int* h = new int;
	*h = 1;
	if (!this)
	{
		std::cout << "Tree is empty\nin: DltNode\n";
		return ;
	}
	if (!root)
	{
		std::cout << "Tree is empty\nin: DltNode\n";
		return;
	}
	if (!FindNode(value))
	{
		std::cout << "There is no such node!\nin: DltNode\n";
		std::cout << "***\n";
		return; //нечего удалять
	}
	Node<T>* cur = root;
	while (!cur->isLeaf) //идем до листа
	{
		if (cur->data == value) break;
		if (value < cur->data)
		{
			if (!cur->left) break;
			cur = cur->left;
		}
		else
		{
			if (!cur->right) break;
			cur = cur->right;
		}
	} 
	//элемент есть, поэтому если не нашли в цикле, то в листе - именно он
	if (cur->isLeaf) { //если лист - просто удаляем
		if (!cur->par)
		{

			delete cur;
			cur = NULL;
			root = NULL;
			size--;
			
			//Change_height(h, root);
			return;
		}
		
		if (cur->data < cur->par->data) {
			
			cur->par->left = NULL;
			if (!cur->par->right) cur->par->isLeaf = true;
			
			Node<T>* ptr = cur->par;
			while (ptr)
			{
				if (abs(Delta(ptr)) == 2)
				{
					Node<T>* pr = ptr->par;
					ptr = Balance(ptr);
					if (pr) {
						if (ptr->data > pr->data)
						{
							//pr->right = ptr;
							//ptr->par = pr;
						}
						else
						{
							//pr->left = ptr;
							//ptr->par = pr;
						}
					}
					else root = ptr;
					int* h = new int;
					*h = 1;
					Change_height(h, root);
					Change_leaf(root);
					break;
				}
				ptr = ptr->par;
			}
			
		}
		if (cur->data > cur->par->data) {
			cur->par->right = NULL;
			if (!cur->par->left) cur->par->isLeaf = true;
			
			Node<T>* ptr = cur->par;
			while (ptr)
			{
				if (abs(Delta(ptr)) == 2)
				{
					Node<T>* pr = ptr->par;
					ptr = Balance(ptr);
					if (pr) {
						if (ptr->data > pr->data)
						{
							//pr->right = ptr;
							//ptr->par = pr;
						}
						else
						{
							//pr->left = ptr;
							//ptr->par = pr;
						}
					}
					else root = ptr;
					int* h = new int;
					*h = 1;
					Change_height(h, root);
					Change_leaf(root);
					break;
				}
				ptr = ptr->par;
			}
			
		}
		//delete cur;
		cur = NULL;
		size--;
		
		//Change_height(h, root);


		return;
	} 
	else {
		if (cur->left == NULL) //если нет левого элемента - после родителя ставим правое поддерево
		{
			if (cur == root)
			{
				root = cur->right;
				//delete cur;
				cur = NULL;
				size--;
				Change_height(h, root);
				
				Node<T>* ptr = root;
				while (ptr)
				{
					if (abs(Delta(ptr)) == 2)
					{
						Node<T>* pr = ptr->par;
						ptr = Balance(ptr);
						if (pr) {
							if (ptr->data > pr->data)
							{
								//pr->right = ptr;
								//ptr->par = pr;
							}
							else
							{
								//pr->left = ptr;
								//ptr->par = pr;
							}
						}
						else root = ptr;
						int* h = new int;
						*h = 1;
						Change_height(h, root);
						Change_leaf(root);
						break;
					}
					ptr = ptr->par;
				}
				
				return;
			}
			if (cur->par)
			{
				if (cur->data < cur->par->data)
				{
					cur->par->left = cur->right; // если левый элемент
					cur->right->par = cur->par;
				}
				else
				{
					cur->par->right = cur->right; //если правый элемент
					cur->right->par = cur->par;
				}
			}
			//delete cur;
			
			size--;
			Change_height(h, root);
			
			Node<T>* ptr = cur->par;
			while (ptr)
			{
				if (abs(Delta(ptr)) == 2)
				{
					Node<T>* pr = ptr->par;
					ptr = Balance(ptr);
					if (pr) {
						if (ptr->data > pr->data)
						{
							//pr->right = ptr;
							//ptr->par = pr;
						}
						else
						{
							//pr->left = ptr;
							//ptr->par = pr;
						}
					}
					else root = ptr;
					int* h = new int;
					*h = 1;
					Change_height(h, root);
					Change_leaf(root);
					break;
				}
				ptr = ptr->par;
			}
			
			cur = NULL;
			return;
		}
		else if (cur->right == NULL) // если нет правого элемента - после родителя ставим левое поддерево
		{
			if (cur == root)
			{
				root = cur->left;
				//delete cur;
				cur = NULL;
				size--;
				Change_height(h, root);
				
				Node<T>* ptr = root;
				while (ptr)
				{
					if (abs(Delta(ptr)) == 2)
					{
						Node<T>* pr = ptr->par;
						ptr = Balance(ptr);
						if (pr) {
							if (ptr->data > pr->data)
							{
								//pr->right = ptr;
								//ptr->par = pr;
							}
							else
							{
								//pr->left = ptr;
								//ptr->par = pr;
							}
						}
						else root = ptr;
						int* h = new int;
						*h = 1;
						Change_height(h, root);
						Change_leaf(root);
						break;
					}
					ptr = ptr->par;
				}
				
				return;
			}
			if (cur->par) {
				if (cur->data < cur->par->data)
				{
					cur->par->left = cur->left; //если левый элемент
					cur->left->par = cur->par;
				}
				else
				{
					cur->par->right = cur->left; // если правый элемент
					cur->left->par = cur->par;
				}
			}
			//delete cur;
			
			size--;
			Change_height(h, root);
			
			Node<T>* ptr = cur->par;
			while (ptr)
			{
				if (abs(Delta(ptr)) == 2)
				{
					Node<T>* pr = ptr->par;
					ptr = Balance(ptr);
					if (pr) {
						if (ptr->data > pr->data)
						{
							//pr->right = ptr;
							//ptr->par = pr;
						}
						else
						{
							//pr->left = ptr;
							//ptr->par = pr;
						}
					}
					else root = ptr;
					int* h = new int;
					*h = 1;
					Change_height(h, root);
					Change_leaf(root);
					break;
				}
				ptr = ptr->par;
			}
			
			cur = NULL;
			return;
		}
		else //есть левое и правое поддерево - заменяем элемент на минимальный больший(т.е вправо и до конца влево) ////////
		{
			Node<T>* cur2 = cur;
			cur2 = cur->right;
			while (cur2->left)
			{
				cur2 = cur2->left;
			}
			if (cur == root)
			{
				if (cur2 == cur->right)
				{
					cur2->left = cur->left;
					cur2->isLeaf = false;
					if (!cur2->par->right) cur2->par->isLeaf = true;
					cur2->par = NULL;
					root = cur2;
					//delete cur;
					size--;
					
					Change_height(h, root);
					
					Node<T>* ptr = root;
					while (ptr)
					{
						if (abs(Delta(ptr)) == 2)
						{
							Node<T>* pr = ptr->par;
							ptr = Balance(ptr);
							if (pr) {
								if (ptr->data > pr->data)
								{
									//pr->right = ptr;
									//ptr->par = pr;
								}
								else
								{
									//pr->left = ptr;
									//ptr->par = pr;
								}
							}
							else root = ptr;
							int* h = new int;
							*h = 1;
							Change_height(h, root);
							Change_leaf(root);
							break;
						}
						ptr = ptr->par;
					}
					
					return;
				}
				else
				{
					cur2->right = cur->right;
					cur2->left = cur->left;
					cur2->isLeaf = false;
					
					if (!cur2->par->right) cur2->par->isLeaf = true;
					cur2->par->left = NULL;
					cur2->par = NULL;
					root = cur2;
					//delete cur;
					size--;
					Change_height(h, root);
					
					Node<T>* ptr = root;
					while (ptr)
					{
						if (abs(Delta(ptr)) == 2)
						{
							Node<T>* pr = ptr->par;
							ptr = Balance(ptr);
							if (pr) {
								if (ptr->data > pr->data)
								{
									//pr->right = ptr;
									//ptr->par = pr;
								}
								else
								{
									//pr->left = ptr;
									//ptr->par = pr;
								}
							}
							else root = ptr;
							int* h = new int;
							*h = 1;
							Change_height(h, root);
							Change_leaf(root);
							break;
						}
						ptr = ptr->par;
					}
					
					return;
				}
				
			}
			if (cur->par) {
				if (cur->data < cur->par->data) cur->par->left = cur2; //если левый элемент
				else cur->par->right = cur2; // если правый элемент
			}
			//cur2->par = cur->par;
			cur2->isLeaf = false; //больше не лист
			if (cur2->par)
			{
				if (cur2->data < cur2->par->data)
					if (cur2->par->right = nullptr) cur2->par->isLeaf = true;
			}
			//cur2->par->left = nullptr; //убираем связь с предыдущим
			if (cur->par) cur2->par = cur->par; //новый родитель


			cur2->left = cur->left;// добавляем левые и правые поддеревья старого элемента
			if (cur2 != cur->right) cur2->right = cur->right;
			//delete cur;
			
			size--;
			Change_height(h, root);
			
			
			Node<T>* ptr = cur->par;
			while (ptr)
			{
				if (abs(Delta(ptr)) == 2)
				{
					Node<T>* pr = ptr->par;
					ptr = Balance(ptr);
					if (pr) {
						if (ptr->data > pr->data)
						{
							//pr->right = ptr;
							//ptr->par = pr;
						}
						else
						{
							//pr->left = ptr;
							//ptr->par = pr;
						}
					}
					else root = ptr;
					int* h = new int;
					*h = 1;
					Change_height(h, root);
					Change_leaf(root);
					break;
				}
				ptr = ptr->par;
			}
			
			cur = NULL;
			return;
		}
	}
}


template <class T>
int BinTree<T>::FindSize(Node<T>* node, int* sz) //кол-во элементов  в дереве
{ 
	if (!this)
	{
		std::cout << "Tree is empty\nin: FindSize\n";
		return 0;
	}
	if (!root)
	{
		std::cout << "Tree is empty\nin:FindSize\n";
		return 0;
	}
	if (!node)
	{
		return 0;
	}
	int help = *sz;
	help++;
	*sz = help;
	if (!node->isLeaf) {
		if (node->left)
		{
			FindSize(node->left, sz);
		}
		if (node->right)
		{
			FindSize(node->right, sz);
		}
	}
	return *sz;
}

template <class T>
BinTree<T>* BinTree<T>::GetSubTree(T value)
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: GetSubTree\n";
		return NULL;
	}
	if (!root)
	{
		std::cout << "Tree is empty\nin: GetSubTree\n";
		return NULL;
	}
	if (!FindNode(value))
	{
		std::cout << "There is no such node!\nin: GetSubTree\n";
		return nullptr; //такого нет
	}
	BinTree<T>* subTree = new BinTree<T>; 
	Node<T>* cur = root;
	while (cur->data != value) //поиск
	{
		if (value < cur->data)
		{
			if (!cur->left) break;
			cur = cur->left;
		}
		else
		{
			if (!cur->right) break;
			cur = cur->right;
		}
	}
	int* sz = new int;
	*sz = 0;
	int j = FindSize(cur, sz);
	T* ar = NULL;
	int* ind = NULL;
	ar = subTree->GoThrough(cur, ar, ind);
	
	for (int i = 0; i < j; i++)
	{
		subTree->AddNode(ar[i]);
	}
	subTree->size = j;
	return subTree;
}

template <class T>
T* BinTree<T>::GoThrough(Node<T>* node, T* arr, int* ind) // все элементы записываются в массив
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: GoThrough\n";
		return NULL;
	}
	/*
	if (!root)
	{
		std::cout << "Tree is empty\nin: GoThrough\n";
		return NULL;
	}
	*/
	if (!node) {
		node = root;
	}
	if (!arr) {
		arr = new T[this->size];
		if (!ind) ind = new int;
		*ind = -1;
	}
	int help = *ind;
	help++;
	*ind = help;
	//*ind = *ind + 1;
	if (!node) return NULL;
	arr[*ind] = node->data;
	if (!node->isLeaf)
	{
		if (node->left) GoThrough(node->left, arr, ind);
		if (node->right) GoThrough(node->right, arr, ind);
	}

	return arr;
}

template <class T>
bool BinTree<T>::CheckSubTree(BinTree<T>* subTree) //subTree - поддерево
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: CheckSubTree\n";
		return false;
	}
	if (!root)
	{
		std::cout << "Tree is empty!\nin: CheckSubTree\n";
		return false;
	}
	BinTree<T>* newTr = this->GetSubTree(subTree->root->data); //находим поддерево в исходном с тем же корнем
	if (newTr->size != subTree->size) return false;
	Node<T>* cur1 = newTr->root;
	Node<T>* cur2 = subTree->root;
	T* arr1 = nullptr;
	T* arr2 = nullptr;
	int* ind1 = nullptr;
	int* ind2 = nullptr;
	arr1 = newTr->GoThrough(cur1, arr1, ind1);
	arr2 = subTree->GoThrough(cur2, arr2, ind2);
	for (int i = 0; i < newTr->GetSize(); i++) {
		if (arr1[i] != arr2[i]) return false;
	}
	return true;
}

template <class T>
void BinTree<T>::Change_height(int *h, Node<T>* node)
{
	Node<T>* ptr;
	if (*h == 1)
	{
		ptr = root;
		root->height = *h;
	}
	else ptr = node;
	ptr->height = *h;
	int help = *h;
	help++;
	*h = help;
	//int* save = new int;
	//*save = *h;
	int save = *h;
	if (ptr->left) Change_height(h, ptr->left);
	if (ptr->right) Change_height(&save, ptr->right);
}

template <class T>
void BinTree<T>::Change_leaf(Node<T>* node)
{
	int flag = 0;
	if (node->left)
	{
		node->isLeaf = false;
		flag = 1;
		Change_leaf(node->left);
	}
	if (node->right)
	{
		node->isLeaf = false;
		flag = 1;
		Change_leaf(node->right);
	}
	if (flag == 0) node->isLeaf = true;
}

template <class T>
int BinTree<T>::Delta(Node<T>* node)
{
	int hl = node->height;
	int hr = node->height;
	int* h = new int;
	*h = node->height;
	if (node->left) hl = GetMaxHeight(node->left,h);
	*h = node->height;
	if (node->right) hr = GetMaxHeight(node->right,h);
	return hr - hl;
}

template <class T>
int BinTree<T>::GetMaxHeight(Node<T>* node, int* h)
{
	//if (!node) return *h;
	if (node->height > *h) *h = node->height;
	if (node->left) GetMaxHeight(node->left, h);
	if (node->right) GetMaxHeight(node->right, h);

	return *h;
}

template <class T>
Node<T>* BinTree<T>::RotRight(Node<T>* node)
{
	int* h = new int;
	*h = 1;
	Node<T>* node2 = /*new Node<T>*/(node);
	Node<T>* newNode = new Node<T>(node2->left);
	newNode->par = node->par;

	newNode->isLeaf = false;

	if (newNode->right)
	{
		node2->left = /*new Node<T>*/(newNode->right);
		node2->left->par = node2;
	}
	else node2->left = NULL;
	
	newNode->right = new Node<T>(node2);
	newNode->right->par = newNode;
	if (newNode->right->left) newNode->right->left->par = newNode->right; //newNode;
	
	if (node->right) node->right->par = newNode->right;//
	node->data = newNode->data;
	if (!node->par) this->root = node;
	node->left = newNode->left;
	if (node->left) node->left->par = node;
	node->right = newNode->right;
	if (node->right) node->right->par = node;
	node->isLeaf = false;
	Change_leaf(root);
	Change_height(h, root);
	
	return node;
}

template <class T>
Node<T>* BinTree<T>::RotLeft(Node<T>* node)
{
	int* h = new int;
	*h = 1;
	Node<T>* node2 = /*new Node<T>*/(node);
	Node<T>* newNode = new Node<T>(node2->right);
	//newNode->par = node->par;

	newNode->isLeaf = false;

	if (newNode->left)
	{
		node2->right = /*new Node<T>*/(newNode->left);
		node2->right->par = node2;
		//newNode->left->par = 
	}
	else node2->right = NULL;
	
	newNode->left =new  Node<T>(node2);//
	newNode->left->par = newNode;
	if (newNode->left->right) newNode->left->right->par = newNode->left;

	//if (newNode->left) newNode->left->par = node2;
	if (node->left) node->left->par = newNode->left;//
	node->data = newNode->data;
	if (!node->par) this->root = node;
	node->left = newNode->left;
	if (node->left) node->left->par = node;
	node->right = newNode->right;
	if (node->right) node->right->par = node;
	node->isLeaf = false;
	Change_leaf(root);
	Change_height(h, root);
	
	return node;
}

template <class T>
Node<T>* BinTree<T>::Balance(Node<T>* node)
{
	int* h = new int;
	*h = 1;
	
	Change_height(h,root);
	
	if (Delta(node) == 2)
	{
		if (node->right)
			if (Delta(node->right) < 0)
				node->right = RotRight(node->right);
		
		return RotLeft(node);
		
	}

	if (Delta(node) == -2)
	{
		if (node->left)
			if (Delta(node->left) > 0)
				node->left = RotLeft(node->left);
		
		return  RotRight(node); 
	
		
	}
}

template <class T>
T* BinTree<T>::GoThroughHeights(Node<T>* node, T* arr, int* ind) // все элементы записываются в массив
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: GoThrough\n";
		return NULL;
	}

	if (!node) {
		node = root;
	}
	if (!arr) {
		arr = new T[this->size];
		if (!ind) ind = new int;
		*ind = -1;
	}
	int help = *ind;
	help++;
	*ind = help;
	//*ind = *ind + 1;
	if (!node) return NULL;
	arr[*ind] = node->height;
	if (!node->isLeaf)
	{
		if (node->left) GoThroughHeights(node->left, arr, ind);
		if (node->right) GoThroughHeights(node->right, arr, ind);
	}

	return arr;
}

template <class T>
T* BinTree<T>::GoThroughDeltas(Node<T>* node, T* arr, int* ind) // все элементы записываются в массив
{
	if (!this)
	{
		std::cout << "Tree is empty\nin: GoThrough\n";
		return NULL;
	}

	if (!node) {
		node = root;
	}
	if (!arr) {
		arr = new T[this->size];
		if (!ind) ind = new int;
		*ind = -1;
	}
	int help = *ind;
	help++;
	*ind = help;
	//*ind = *ind + 1;
	if (!node) return NULL;
	arr[*ind] = Delta(node);
	if (!node->isLeaf)
	{
		if (node->left) GoThroughDeltas(node->left, arr, ind);
		if (node->right) GoThroughDeltas(node->right, arr, ind);
	}

	return arr;
}