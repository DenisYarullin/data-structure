#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_

//” каждого узла не более двух детей.
//Ћюбое значение меньше значени€ узла становитс€ левым ребенком или ребенком левого ребенка.
//Ћюбое значение больше или равное значению узла становитс€ правым ребенком или ребенком правого ребенка.

template <typename T>
class BinaryTreeNode
{
private:
	T value;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
public:
	BinaryTreeNode(T value_) : value(value_), left(nullptr), right(nullptr) {}
	int CompareTo(T otherValue) const;
};


/// —равнивает текущий узел с данным.
/// —равнение производитс€ по полю Value.
/// ћетод возвращает 1, если значение текущего узла больше,
/// чем переданного методу, -1, если меньше и 0, если они равны
template <typename T>
int BinaryTreeNode<T>::CompareTo(T otherValue) const
{
	if (value > otherValue)
		return 1;
	else if (value < otherValue)
		return -1;
	else
		return 0;
}


template <typename T>
class BinaryTree
{
private:
	int count;
	BinaryTreeNode *head;
public:
	BinaryTree() : count(0), head(nullptr) {}
	void Add(T value);
	bool Contains(T value);
	bool Remove(T value);
	void Clear();
	int Count();
	void PreOrderTraversal();
	void PostOrderTraversal();
	void InOrderTraversal();
private:
	void AddTo(BinaryTreeNode<T> *node, T value);
};

// –екурсивна€ вставка.
template <typename T>
void BinaryTree<T>::AddTo(BinaryTreeNode<T> *node, T value)
{
	// —лучай 1: ¬ставл€емое значение меньше значени€ узла
	if (node->CompareTo(value) > 0)
	{
		// ≈сли нет левого поддерева, добавл€ем значение в левого ребенка,
		if (node->left == nullptr)
		{
			node->left = new BinaryTreeNode(value);
		}
		else
		{
			// в противном случае повтор€ем дл€ левого поддерева
			AddTo(node->left, value);
		}
	}
	// —лучай 2: ¬ставл€емое значение больше или равно значению узла
	else
	{
		// ≈сли нет правого поддерева, добавл€ем значение в правого ребенка,
		if (node->right == nullptr)
		{
			node->right = new BinaryTreeNode(value);
		}
		else
		{
			// в противном случае повтор€ем дл€ правого поддерева.
			AddTo(node->right, value);
		}
	}
}

template <typename T>
void BinaryTree<T>::Add(T value)
{
	// —лучай 1: ≈сли дерево пустое, просто создаем корневой узел.
	if (head == nullptr)
	{
		head = new BinaryTreeNode(value);
	}
	// —лучай 2: ƒерево не пустое => 
	// ищем правильное место дл€ вставки.
	else
	{
		AddTo(head, value);
	}

	count++;
}

template <typename T>
bool BinaryTree<T>::Remove(T value)
{

}

template <typename T>
bool BinaryTree<T>::Contains(T value)
{
	return true;
}

#endif // BINARY_SEARCH_H_

