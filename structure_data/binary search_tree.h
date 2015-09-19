#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_

//У каждого узла не более двух детей.
//Любое значение меньше значения узла становится левым ребенком или ребенком левого ребенка.
//Любое значение больше или равное значению узла становится правым ребенком или ребенком правого ребенка.

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
	T Value() { return value; }
	BinaryTreeNode *Left() { return left; }
	BinaryTreeNode *Right() { return right; }
};


/// Сравнивает текущий узел с данным.
/// Сравнение производится по полю Value.
/// Метод возвращает 1, если значение текущего узла больше,
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
	int Count() { return count; };
	void PreOrderTraversal(BinaryTreeNode<T> *node);
	void PostOrderTraversal(BinaryTreeNode<T> *node);
	void InOrderTraversal(BinaryTreeNode<T> *node);
private:
	void AddTo(BinaryTreeNode<T> *node, T value);
	BinaryTreeNode<T> *FindWithParent(T value, BinaryTreeNode<T> *parent);
};

// Рекурсивная вставка.
template <typename T>
void BinaryTree<T>::AddTo(BinaryTreeNode<T> *node, T value)
{
	// Случай 1: Вставляемое значение меньше значения узла
	if (node->CompareTo(value) > 0)
	{
		// Если нет левого поддерева, добавляем значение в левого ребенка,
		if (node->left == nullptr)
		{
			node->left = new BinaryTreeNode(value);
		}
		else
		{
			// в противном случае повторяем для левого поддерева
			AddTo(node->left, value);
		}
	}
	// Случай 2: Вставляемое значение больше или равно значению узла
	else
	{
		// Если нет правого поддерева, добавляем значение в правого ребенка,
		if (node->right == nullptr)
		{
			node->right = new BinaryTreeNode(value);
		}
		else
		{
			// в противном случае повторяем для правого поддерева.
			AddTo(node->right, value);
		}
	}
}

template <typename T>
void BinaryTree<T>::Add(T value)
{
	// Случай 1: Если дерево пустое, просто создаем корневой узел.
	if (head == nullptr)
	{
		head = new BinaryTreeNode(value);
	}
	// Случай 2: Дерево не пустое => 
	// ищем правильное место для вставки.
	else
	{
		AddTo(head, value);
	}

	count++;
}

template <typename T>
bool BinaryTree<T>::Remove(T value)
{
	BinaryTreeNode *current, parent;

	// Находим удаляемый узел.
	current = FindWithParent(value, parent);

	if (current == nullptr)
	{
		return false;
	}

	count--;

	// Случай 1: Если нет детей справа, левый ребенок встает на место удаляемого.
	if (current->Right() == nullptr)
	{
		if (parent == nullptr)
		{
			head = current->Left();

		}
		else
		{
			int result = parent->CompareTo(value);
			if (result > 0)
			{
				// Если значение родителя больше текущего,
				// левый ребенок текущего узла становится левым ребенком родителя.
				parent->Left() = current->Left();
			}
			else if (result < 0)
			{
				// Если значение родителя меньше текущего,
				// левый ребенок текущего узла становится правым ребенком родителя.
				parent->Right() = current->Left();
			}
		}
	}
	// Случай 2: Если у правого ребенка нет детей слева
	// то он занимает место удаляемого узла.
	else if (current->Right()->Left() == nullptr)
	{
		current->Right()->Left() = current->Left();

		if (parent == nullptr)
		{
			head = current->Right();
		}
		else
		{
			int result = parent->CompareTo(value);

			if (result > 0)
			{
				// Если значение родителя больше текущего,
				// правый ребенок текущего узла становится левым ребенком родителя.
				parent->Left() = current->Right();
			}
			else if (result < 0)
			{
				// Если значение родителя меньше текущего,
				// правый ребенок текущего узла становится правым ребенком родителя.
				parent->Right() = current->Right();
			}
		}
	}
	// Случай 3: Если у правого ребенка есть дети слева, крайний левый ребенок
	//           из правого поддерева заменяет удаляемый узел.
	else
	{
		// Найдем крайний левый узел.
		BinaryTreeNode *leftMost = current->Right()->Left();
		BinaryTreeNode *leftMostParent = current->Right();

		while (leftMost->Left() != nullptr)
		{
			leftMostParent = leftMost;
			leftMost = leftMost->Left();
		}

		// Левое поддерево родителя становится правым поддеревом крайнего левого узла.
		leftMostParent->Left() = leftMost->Right();

		// Левый и правый ребенок текущего узла становится левым и правым ребенком крайнего левого.
		leftMost->Left() = current->Left();
		leftMost->Right() = current->Right();

		if (parent == nullptr)
		{
			head = leftMost;
		}
		else
		{
			int result = parent->CompareTo(value);
			if (result > 0)
			{
				// Если значение родителя больше текущего,
				// крайний левый узел становится левым ребенком родителя.
				parent->Left() = leftMost;

			}
			else if (result < 0)
			{
				// Если значение родителя меньше текущего,
				// крайний левый узел становится правым ребенком родиеля.
				parent->Right = leftMost();
			}
		}
	}
	delete current;
	return true;
}

/// Находит и возвращает первый узел с заданным значением. Если значение
/// не найдено, возвращает null. Также возвращает родителя найденного узла (или null)
/// для использования в методе Remove.
template <typename T>
BinaryTreeNode<T> * BinaryTree<T>::FindWithParent(T value, BinaryTreeNode<T> *parent)
{
	// Попробуем найти значение в дереве.
	BinaryTreeNode *current = head;
	//parent = nullptr;
	
	// До тех пор пока не нашли ...
	while (current != nullptr)
	{
		int result = current->CompareTo(value);

		if (result > 0)
		{
			// Если искомое значение меньше, идем налево.
			parent = current;
			current = current->Left();
		}
		else if (result < 0)
		{
			// Если искомое значение больше, идем направо.
			parent = current;
			current = current->Right();
		}
		else
		{
			// Если равны, то останавливаемся
			break;
		}
	}
	return current;
}

template <typename T>
bool BinaryTree<T>::Contains(T value)
{
	// Поиск узла осуществляется другим методом.
	BinaryTreeNode *parent = nullptr; 
	BinaryTreeNode *current = FindWithParent(value, parent);
	delete parent;
	return current != nullptr;
}

template <typename T>
void BinaryTree<T>::Clear()
{	
	count = 0;
}

// При префиксном обходе алгоритм получает значение текущего узла перед тем,
// как перейти сначала в левое поддерево, а затем в правое.Начиная от корня,
// сначала мы получим его значение. Затем таким же образом обходятся левый ребенок
// и его дети, затем правый ребенок и все его дети.
template <typename T>
void BinaryTree<T>::PreOrderTraversal(BinaryTreeNode<T> *node)
{
	if (node != nullptr)
	{
		cout << node->Value() << endl;
		PreOrderTraversal(node->Left());
		PreOrderTraversal(node->Right());
	}
}


// При постфиксном обходе мы посещаем левое поддерево, правое поддерево, 
// а потом, после обхода всех детей, переходим к самому узлу.
// Постфиксный обход часто используется для полного удаления дерева,
// так как в некоторых языках программирования необходимо убирать из памяти все узлы явно,
// или для удаления поддерева. Поскольку корень в данном случае обрабатывается последним,
// мы, таким образом, уменьшаем работу, необходимую для удаления узлов.
template <typename T>
void BinaryTree<T>::PostOrderTraversal(BinaryTreeNode<T> *node)
{
	if (node != nullptr)
	{
		PostOrderTraversal(node->Left());
		PostOrderTraversal(node->Right());
		cout << node->Value() << endl;
	}
}

// Инфиксный обход используется тогда, когда нам надо обойти дерево в порядке,
// соответствующем значениям узлов. В примере выше в дереве находятся числовые значения,
// поэтому мы обходим их от самого маленького до самого большого. То есть от левых поддеревьев
// к правым через корень.
// Рекурсивный. Он выполняет указанное действие с каждым узлом.
template <typename T>
void BinaryTree<T>::InOrderTraversal(BinaryTreeNode<T> *node)
{
	if (node != nullptr)
	{
		InOrderTraversal(node->Left());
		cout << node->Value() << endl;
		InOrderTraversal(node->Right());
		
	}
}


#endif // BINARY_SEARCH_H_

