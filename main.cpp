#include <iostream>
#include <vector>

using namespace std;

struct BinomialVertex
{
	int key;//  ключ(вес) элемента,
	int degree;// степень узла(количество дочерних узлов данного узла).
	BinomialVertex* child;// указатель на левого ребенка узла,
	BinomialVertex* sibling;// указатель на правого брата узла,
	BinomialVertex(int _key, int _degree, BinomialVertex* _child = nullptr, BinomialVertex* _sibling = nullptr)
	{
		key = _key;
		degree = _degree;
		child = _child;
		sibling = _sibling;
	}
};

class BinomailHeap
{
	BinomialVertex* head;
private :

	BinomialVertex* MergeTrees(BinomialVertex* first, BinomialVertex* second) {
		first->child = second;
		second->sibling = first->child;
		first->degree++;
		return first;
	}

	BinomialVertex* MergeAllTrees(BinomialVertex* current)
	{
		if (!current || !current->sibling) return current;
		BinomialVertex *first(current->sibling), *second(first->sibling);
		if ((second && current->degree == first->degree == second->degree) || (current->degree < first->degree))
			current->sibling = MergeAllTrees(first);
		else {
			if (current->key <= first->key)
			{
				current = MergeTrees(current, first);
				current->sibling = second;
			}
			else
				current = MergeTrees(first, current);
		}
		return current;
	}

	BinomialVertex* Reverse(BinomialVertex* root)
	{
		BinomialVertex* first(root->sibling), *second((first) ? (first->sibling) : first);
		root->sibling = nullptr;
		while (second)
		{
			first->sibling = root;
			root = first;
			first = second;
			second = second->sibling;
		}
		first->sibling = root;
		return first;
}

public :

	BinomialVertex* Merge(BinomialVertex* first, BinomialVertex* second)
	{
		if (!first) return second;
		if (!second) return first;
		BinomialVertex* newHeap, *help;
		if (first->degree <= second->degree)
		{
			newHeap = first; first = first->sibling; }
		else{
	        newHeap = second; second = second->sibling; }
		help = newHeap;
		while (first&&second)
		{
			if (first->degree <= second->degree)
			{
				help->sibling = first; help = first; first = first->sibling; }
			else
			{
				help->sibling = second; help = second; second = second->sibling; }
		}
		if (first) help->sibling = first;
		else help->sibling = second;
		return MergeAllTrees(newHeap);
	}
	
	int FindMin()
	{
		if (!head) return 0;
		BinomialVertex* help(head);
		int min(help->key);
		while (help->sibling)
		{
			if (help->sibling->key < min) min = help->sibling->key;
			help = help->sibling;
		}
		return min;
	}

	void ExtractMin()
	{
		if (!head) return;
		int min(FindMin());
		BinomialVertex* help(head), *last(nullptr), *deleted(nullptr);
		while (help)
		{
			if (help->key == min)
			{
				if (last) last->sibling = help->sibling;
				else head = help->sibling;
				deleted = help;
				help = nullptr;
			}
			else help = help->sibling;
		}
		BinomialVertex* newHeap = Reverse(deleted->child);
		head = Merge(head, newHeap);
	}

	void Insert(int value)
	{
		BinomialVertex* newHead(new BinomialVertex(value, 0));
		newHead->sibling = head;
		head = MergeAllTrees(newHead);
	}
};


int main()
{
	setlocale(0, "Russian");

	system("pause");
	return 0;
}