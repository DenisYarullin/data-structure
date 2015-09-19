#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_

//� ������� ���� �� ����� ���� �����.
//����� �������� ������ �������� ���� ���������� ����� �������� ��� �������� ������ �������.
//����� �������� ������ ��� ������ �������� ���� ���������� ������ �������� ��� �������� ������� �������.

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


/// ���������� ������� ���� � ������.
/// ��������� ������������ �� ���� Value.
/// ����� ���������� 1, ���� �������� �������� ���� ������,
/// ��� ����������� ������, -1, ���� ������ � 0, ���� ��� �����
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

// ����������� �������.
template <typename T>
void BinaryTree<T>::AddTo(BinaryTreeNode<T> *node, T value)
{
	// ������ 1: ����������� �������� ������ �������� ����
	if (node->CompareTo(value) > 0)
	{
		// ���� ��� ������ ���������, ��������� �������� � ������ �������,
		if (node->left == nullptr)
		{
			node->left = new BinaryTreeNode(value);
		}
		else
		{
			// � ��������� ������ ��������� ��� ������ ���������
			AddTo(node->left, value);
		}
	}
	// ������ 2: ����������� �������� ������ ��� ����� �������� ����
	else
	{
		// ���� ��� ������� ���������, ��������� �������� � ������� �������,
		if (node->right == nullptr)
		{
			node->right = new BinaryTreeNode(value);
		}
		else
		{
			// � ��������� ������ ��������� ��� ������� ���������.
			AddTo(node->right, value);
		}
	}
}

template <typename T>
void BinaryTree<T>::Add(T value)
{
	// ������ 1: ���� ������ ������, ������ ������� �������� ����.
	if (head == nullptr)
	{
		head = new BinaryTreeNode(value);
	}
	// ������ 2: ������ �� ������ => 
	// ���� ���������� ����� ��� �������.
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

	// ������� ��������� ����.
	current = FindWithParent(value, parent);

	if (current == nullptr)
	{
		return false;
	}

	count--;

	// ������ 1: ���� ��� ����� ������, ����� ������� ������ �� ����� ����������.
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
				// ���� �������� �������� ������ ��������,
				// ����� ������� �������� ���� ���������� ����� �������� ��������.
				parent->Left() = current->Left();
			}
			else if (result < 0)
			{
				// ���� �������� �������� ������ ��������,
				// ����� ������� �������� ���� ���������� ������ �������� ��������.
				parent->Right() = current->Left();
			}
		}
	}
	// ������ 2: ���� � ������� ������� ��� ����� �����
	// �� �� �������� ����� ���������� ����.
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
				// ���� �������� �������� ������ ��������,
				// ������ ������� �������� ���� ���������� ����� �������� ��������.
				parent->Left() = current->Right();
			}
			else if (result < 0)
			{
				// ���� �������� �������� ������ ��������,
				// ������ ������� �������� ���� ���������� ������ �������� ��������.
				parent->Right() = current->Right();
			}
		}
	}
	// ������ 3: ���� � ������� ������� ���� ���� �����, ������� ����� �������
	//           �� ������� ��������� �������� ��������� ����.
	else
	{
		// ������ ������� ����� ����.
		BinaryTreeNode *leftMost = current->Right()->Left();
		BinaryTreeNode *leftMostParent = current->Right();

		while (leftMost->Left() != nullptr)
		{
			leftMostParent = leftMost;
			leftMost = leftMost->Left();
		}

		// ����� ��������� �������� ���������� ������ ���������� �������� ������ ����.
		leftMostParent->Left() = leftMost->Right();

		// ����� � ������ ������� �������� ���� ���������� ����� � ������ �������� �������� ������.
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
				// ���� �������� �������� ������ ��������,
				// ������� ����� ���� ���������� ����� �������� ��������.
				parent->Left() = leftMost;

			}
			else if (result < 0)
			{
				// ���� �������� �������� ������ ��������,
				// ������� ����� ���� ���������� ������ �������� �������.
				parent->Right = leftMost();
			}
		}
	}
	delete current;
	return true;
}

/// ������� � ���������� ������ ���� � �������� ���������. ���� ��������
/// �� �������, ���������� null. ����� ���������� �������� ���������� ���� (��� null)
/// ��� ������������� � ������ Remove.
template <typename T>
BinaryTreeNode<T> * BinaryTree<T>::FindWithParent(T value, BinaryTreeNode<T> *parent)
{
	// ��������� ����� �������� � ������.
	BinaryTreeNode *current = head;
	//parent = nullptr;
	
	// �� ��� ��� ���� �� ����� ...
	while (current != nullptr)
	{
		int result = current->CompareTo(value);

		if (result > 0)
		{
			// ���� ������� �������� ������, ���� ������.
			parent = current;
			current = current->Left();
		}
		else if (result < 0)
		{
			// ���� ������� �������� ������, ���� �������.
			parent = current;
			current = current->Right();
		}
		else
		{
			// ���� �����, �� ���������������
			break;
		}
	}
	return current;
}

template <typename T>
bool BinaryTree<T>::Contains(T value)
{
	// ����� ���� �������������� ������ �������.
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

// ��� ���������� ������ �������� �������� �������� �������� ���� ����� ���,
// ��� ������� ������� � ����� ���������, � ����� � ������.������� �� �����,
// ������� �� ������� ��� ��������. ����� ����� �� ������� ��������� ����� �������
// � ��� ����, ����� ������ ������� � ��� ��� ����.
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


// ��� ����������� ������ �� �������� ����� ���������, ������ ���������, 
// � �����, ����� ������ ���� �����, ��������� � ������ ����.
// ����������� ����� ����� ������������ ��� ������� �������� ������,
// ��� ��� � ��������� ������ ���������������� ���������� ������� �� ������ ��� ���� ����,
// ��� ��� �������� ���������. ��������� ������ � ������ ������ �������������� ���������,
// ��, ����� �������, ��������� ������, ����������� ��� �������� �����.
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

// ��������� ����� ������������ �����, ����� ��� ���� ������ ������ � �������,
// ��������������� ��������� �����. � ������� ���� � ������ ��������� �������� ��������,
// ������� �� ������� �� �� ������ ���������� �� ������ ��������. �� ���� �� ����� �����������
// � ������ ����� ������.
// �����������. �� ��������� ��������� �������� � ������ �����.
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

